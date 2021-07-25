import subprocess
import re
import os.path
from subprocess import Popen, PIPE

# cmd = ['ls', '-l']
# result = subprocess.run(cmd, capture_output=True, text=True).stdout
# print(result)

memoryType = ['l1', 'l2', 'l3']
n_possible = [str(number) for number in [16, 32, 64, 128, 256, 512, 1024, 2048]]
version = [0, 1, 2, 3]

main_cmd = ['./matmult']
filter_cmd = [r'| grep -E "(Time)|(miss ratio)" | grep -e "[0-9]*\.[0-9]*" -o']
time_regex = re.compile(r'[0-9]*\.[0-9]*')
make_sim_tries = 10

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

    def get_average_sim_times(howMany):
        times = howMany
        sum_time = [0] * 4
        sum_branch = [0] * 4
        sum_L1MR = [0] * 4
        sum_LLMR = [0] * 4
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

    def trans(M): # https://stackoverflow.com/questions/23392986/how-to-transpose-an-array-in-python-3
        return [[M[j][i] for j in range(len(M))] for i in range(len(M[0]))]

    for array in trans(get_average_sim_times(make_sim_tries)):
        str_ver = ', '.join(map(str, array))
        str_ver += ' \n'
        output += str_ver

    out_file = open('data_sim_out.csv', 'w')
    out_file.write(output)
    out_file.close()


make_sim()


# run main_cmd with given memory type, size of matrix and function version
# returns time and miss_ratio
def run_matmult(p='l1', n='1024', v='0'):
    parameters = ['-p', p, '-n', n, '-v', v]
    result = subprocess.Popen(main_cmd + parameters, stdout=subprocess.PIPE)
    (output, err) = result.communicate()
    result.wait()
    result_string = output.decode('utf-8').split(sep='\n')

    if p == 'ipc':
        instructions = re.findall(r'[0-9]+', result_string[3])
        ipc = re.findall(r'[0-9]+\.[0-9]+', result_string[4])
        return_val = instructions, ipc
    else:
        time = re.findall(r'[0-9]+\.[0-9]+', result_string[2])
        miss_ratio = re.findall(r'[0-9]+\.[0-9]+', result_string[3])
        return_val = time, miss_ratio

    result.kill()
    return return_val


def time_to_n_csv():
    output = "n, v0, v1, v2, v3\n"
    # n_possible = [str(16 * i) for i in range(1, 45)]
    for n in n_possible:
        output += n
        for variant in [0, 1, 2, 3]:
            time, mr = run_matmult(n=n, v=str(variant))
            output += ', ' + str(time[0])
        output += '\n'

    out_file = open('data_time_n.dat', 'w')
    out_file.write(output)
    out_file.close()


time_to_n_csv()


# for tiled version
# block size vs time
def block_size_test(block):
    if os.path.isfile('data_blocks.dat') and os.path.getsize('data_blocks.dat') > 0:
        output = ""
    else:
        output = "block, time \n"

    howMany = 10
    sum = 0
    for i in range(1, howMany + 1):
        time, mr = run_matmult(v='3')
        sum += float(time[0])

    output += (block + ', ' + str(sum/howMany) + ' \n')

    out_file = open('data_blocks.dat', 'a+')
    out_file.write(output)
    out_file.close()


# block_size_test('8') - changed manually in matmult.h


# for tiled version
# change offset manually, pass name by argument
def offset_test(offset):
    if os.path.isfile('data_offsets.dat') and os.path.getsize('data_offsets.dat') > 0:
        output = ""
    else:
        output = "offset, n, v0, v1, v2, v3 \n"

    for n in n_possible:
        output += offset + ', ' + n
        for variant in [0, 1, 2, 3]:
            time, mr = run_matmult(p='l1', n=n, v=str(variant))
            output += ', ' + str(time[0])
        output += ' \n'

    out_file = open('data_offsets.dat', 'a+')
    out_file.write(output)
    out_file.close()


# offset_test('reverse') # - 2, 1, 0


# cpi calculation
def cpi_to_n_csv():
    output = "n, v0, v1, v2, v3\n"
    n_possible = [str(16 * i + 32) for i in range(1, 45)]
    howMany = 20

    for n in n_possible:
        output += n
        total_iterations = int(n) ** 3
        for variant in [0, 1, 2, 3]:
            CPI = 0.0
            for iter in range(1, howMany+1):
                instr, ipc = run_matmult(p='ipc', n=n, v=str(variant))
                cycles = float(instr[0])/float(ipc[0])
                CPI += cycles / total_iterations
            output += ', ' + str(CPI/howMany)

            # print(total_iterations, cycles, instr[0], ipc[0], CPI)
        output += '\n'

    out_file = open('data_cpi_to_n.dat', 'w')
    out_file.write(output)
    out_file.close()


# cpi_to_n_csv()