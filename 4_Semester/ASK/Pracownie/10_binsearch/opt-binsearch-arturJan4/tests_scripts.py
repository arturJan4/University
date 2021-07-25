import subprocess
import re
import os.path
from subprocess import Popen, PIPE

# cmd = ['ls', '-l']
# result = subprocess.run(cmd, capture_output=True, text=True).stdout
# print(result)

memory_type = ['l1', 'l2', 'l3']
n_possible = [str(number) for number in [16, 32, 64, 128, 256, 512, 1024, 2048]]
version = [0, 1]

main_cmd = ['./binsearch']
filter_cmd = [r'| grep -E "(Time)|(miss ratio)" | grep -e "[0-9]*\.[0-9]*" -o']
time_regex = re.compile(r'[0-9]*\.[0-9]*')
make_sim_tries = 10
num_variants = 2


# runs make_sim #make_sum_tries number of times
# gets the average
# prints results to sim_out.txt
def make_sim():
    output = "time, BMR, L1, LL \n"

    def run_sim():
        main_cmd = ['make', 'sim']
        result = subprocess.run(main_cmd, stdout=subprocess.PIPE)
        result_strings = result.stdout.decode('utf-8').split(sep='\n')

        time = []
        branch = []
        L1MR = []
        LLMR = []
        for line in result_strings:
            if 'Branch misprediction ratio' in line:
                branch.append(float(time_regex.findall(line)[0]))
            elif 'L1 miss ratio' in line:
                L1MR.append(float(time_regex.findall(line)[0]))
            elif 'LL miss ratio' in line:
                LLMR.append(float(time_regex.findall(line)[0]))
            elif 'Time elapsed' in line:
                time.append(float(time_regex.findall(line)[0]))

        return time, branch, L1MR, LLMR

    def get_average_sim_times(how_many):
        times = how_many
        sum_time = [0] * num_variants
        sum_branch = [0] * num_variants
        sum_L1MR = [0] * num_variants
        sum_LLMR = [0] * num_variants
        for i in range(1, times + 1):
            sim_out = run_sim()

            sum_time = [x + y for x, y in zip(sim_out[0], sum_time)]
            sum_branch = [x + y for x, y in zip(sim_out[1], sum_branch)]
            sum_L1MR = [x + y for x, y in zip(sim_out[2], sum_L1MR)]
            sum_LLMR = [x + y for x, y in zip(sim_out[3], sum_LLMR)]

        avg_time = [x/times for x in sum_time]
        avg_branch = [x / times for x in sum_branch]
        avg_L1MR = [x / times for x in sum_L1MR]
        avg_LLMR = [x / times for x in sum_LLMR]
        return avg_time, avg_branch, avg_L1MR, avg_LLMR

    def trans(M):  # https://stackoverflow.com/questions/23392986/how-to-transpose-an-array-in-python-3
        return [[M[j][i] for j in range(len(M))] for i in range(len(M[0]))]

    for array in trans(get_average_sim_times(make_sim_tries)):
        str_ver = ', '.join(map(str, array))
        str_ver += ' \n'
        output += str_ver

    out_file = open('data_sim_out.csv', 'w')
    out_file.write(output)
    out_file.close()
    print("make sim saved to data_sim_out.csv")


# make_sim()


# run main_cmd with given memory type, size of matrix and function version
# returns time and miss_ratio / instructions and ipc
# times (t) and n is log_2
# S is seed
def run_binsearch(p='l1', n='19', s='0x5bab3de5da7882fb', t='20',  v='0'):
    parameters = ['-p', p, '-S', s, '-n', n, '-t', t, '-v', v]

    result = subprocess.Popen(main_cmd + parameters, stdout=subprocess.PIPE)
    (output, err) = result.communicate()
    result.wait()
    result_string = output.decode('utf-8').split(sep='\n')
    # print(result_string)
    if p == 'ipc':
        instructions = re.findall(r'[0-9]+', result_string[5])
        ipc = re.findall(r'[0-9]+\.[0-9]+', result_string[6])
        return_val = instructions, ipc
    else:
        time = re.findall(r'[0-9]+\.[0-9]+', result_string[4])
        miss_ratio = re.findall(r'[0-9]+\.[0-9]+', result_string[5])
        return_val = time, miss_ratio

    result.kill()
    return return_val


# print(run_binsearch(p='ipc'))

def time_to_n():
    output = "n, v0, v1\n"
    n_possible = [str(i) for i in range(1, 26, 1)]

    howMany = 3
    for n in n_possible:
        output += n
        for variant in range(0, num_variants):
            time_sum = 0.0
            for i in range(1, howMany+1):
                time, mr = run_binsearch(n=n, v=str(variant))
                time_sum += float(time[0])
            output += ', ' + str(time_sum/howMany)
        output += '\n'

    out_file = open('data_time_n_prefetch_3.dat', 'w')
    out_file.write(output)
    out_file.close()
    print("time to n saved to data_time_n.dat")


time_to_n()


def ipc_to_n():
    output = "n, v0, v1\n"
    n_possible = [str(i) for i in range(1, 25, 1)]
    howMany = 10

    for n in n_possible:
        output += n
        for variant in range(0, num_variants):
            IPC = 0.0
            for i in range(1, howMany+1):
                instr, ipc = run_binsearch(p='ipc', n=n, v=str(variant))
                IPC += float(ipc[0])
            output += ', ' + str(IPC/howMany)

        output += '\n'

    out_file = open('data_ipc_to_n.dat', 'w')
    out_file.write(output)
    out_file.close()
    print("saved to data_ipc_to_n.dat")


# ipc_to_n()


# return time, miss-ration or instr, ipc
def get_average(p='l1', n='19', s='0x5bab3de5da7882fb', t='20', how_many=10):
    result = [[0.0, 0.0] for variant in range(0, num_variants)]

    for variant in range(0, num_variants):
        sum_first = 0.0
        sum_second = 0.0
        for i in range(1, how_many + 1):
            first, second = run_binsearch(p=p, n=n, s=s, t=t, v=str(variant))
            sum_first += float(first[0])
            sum_second += float(second[0])
        result[variant][0] = sum_first / how_many
        result[variant][1] = sum_second / how_many

    return result


def averages_table():
    output = "n, time (v0), L1 (v0), L2 (v0), L3(v0), time (v1), L1 (v1), L2 (v1), L3(v1)\n"
    n_possible = [str(i) for i in range(1, 25, 1)]

    for n in n_possible:
        output += n
        time = [0.0, 0.0]
        L1 = [0.0, 0.0]
        L2 = [0.0, 0.0]
        L3 = [0.0, 0.0]
        for variant in range(0, num_variants):
            for p in memory_type:
                result = get_average(p=p, n=n)
                if p == 'l1':
                    time[variant] = result[variant][0]
                    L1[variant] = result[variant][1]
                elif p == 'l2':
                    L2[variant] = result[variant][1]
                elif p == 'l3':
                    L3[variant] = result[variant][1]
        output += (', ' + str(time[0]) + ', ' + str(L1[0]) + ', ' + str(L2[0]) + ', ' + str(L3[0]) + ', ' + str(time[1]) + ', ' + str(L1[1]) + ', ' + str(L2[1]) + ', ' + str(L3[1]))
        output += '\n'

    out_file = open('data_average_expect.dat', 'w')
    out_file.write(output)
    out_file.close()
    print("saved to data_average_expect.dat")


# averages_table()
