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

main_cmd = ['./transpose']
filter_cmd = [r'| grep -E "(Time)|(miss ratio)" | grep -e "[0-9]*\.[0-9]*" -o']
time_regex = re.compile(r'[0-9]*\.[0-9]*')
make_sim_tries = 20
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

    def get_average_sim_times(howMany):
        times = howMany
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

    def trans(M): # https://stackoverflow.com/questions/23392986/how-to-transpose-an-array-in-python-3
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
def run_transpose(p='l1', n='4096', v='0'):
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


def time_to_n():
    output = "n, v0, v1\n"
    n_possible = [str(16 * i) for i in range(1, 513, 1)]
    for n in n_possible:
        output += n
        for variant in range(0, num_variants):
            time, mr = run_transpose(n=n, v=str(variant))
            output += ', ' + str(time[0])
        output += '\n'

    out_file = open('data_time_n.dat', 'w')
    out_file.write(output)
    out_file.close()
    print("time to n saved to data_time_n.dat")


# time_to_n_csv()


def change_block_size(n):
    # change .h file
    subprocess.check_call([f"sed -i 's/#define BLOCK .*/#define BLOCK {n}/g' transpose.h"], shell=True)
    # recompile
    subprocess.check_call([f"gcc -g -std=gnu11 -march=sandybridge -O2 -Wall -Wextra -Wno-unused -Wno-unused-result -DPAPI=1 -c -o transpose.o transpose.c"], shell=True)
    subprocess.check_call([f"gcc -g -std=gnu11 -march=sandybridge -O2 -Wall -Wextra -Wno-unused -Wno-unused-result -DPAPI=1 -c -o main.o main.c"], shell=True)
    subprocess.check_call([f"gcc -g transpose.o main.o common.o -lpapi -o transpose"], shell=True)


# for tiled version
# block size vs time
def block_size_test(block):
    change_block_size(block)

    if os.path.isfile('data_blocks.dat') and os.path.getsize('data_blocks.dat') > 0:
        output = ""
    else:
        output = "block, time \n"

    howMany = 10
    sum = 0
    for i in range(1, howMany + 1):
        time, mr = run_transpose(v='1')
        sum += float(time[0])

    output += (block + ', ' + str(sum/howMany) + ' \n')

    change_block_size('8')  # return default
    out_file = open('data_blocks.dat', 'a+')
    out_file.write(output)
    out_file.close()


# block_size_test('16')

def block_size_test_all():
    n_possible = [str(2**i) for i in range(0, 10)]
    for n in n_possible:
        block_size_test(n)
    change_block_size('8')  # return default
    print("block size to time saved to data_blocks.dat")


# block_size_test_all()

def block_n_time():
    block_possible = [str(2**i) for i in range(0, 8)]  # BLOCK sizes
    output = "n"

    n_possible = [str(128 * i) for i in range(1, 65, 1)]  # n - matrix size

    results = [[0.0 for x in range(len(block_possible))] for y in range(len(n_possible))]
    for block in range(len(block_possible)):
        block_val = block_possible[block]
        change_block_size(block_val)

        output += f', B({block_val})'
        for n in range(len(n_possible)):
            results[n][block] = float(run_transpose(n=n_possible[n], v='1')[0][0])

    output += '\n'

    for n in range(len(n_possible)):
        output += n_possible[n]
        for block in range(len(block_possible)):
            output += ', ' + str(results[n][block])
        output += '\n'

    out_file = open('data_block_time_n.dat', 'w')
    out_file.write(output)
    out_file.close()
    change_block_size('8')  # return default
    print("time to block to n saved to data_block_time_n.dat")


# block_n_time()

def time_to_n_v0():
    output = "n, v0\n"
    # n_possible = [str(8 * i) for i in range(1, 65, 1)] + [str(8 * i) for i in range(64, 4096, 64)]
    n_possible = [str(i) for i in range(8, 256, 8)]

    howMany = 20
    results = [0.0 for n in range(len(n_possible))]
    for i in range(0, howMany):
        for n in range(len(n_possible)):
            time, mr = run_transpose(n=n_possible[n], v='0')
            results[n] += float(time[0])

    for n in range(len(n_possible)):
        output += n_possible[n]
        output += ', ' + str(results[n]/howMany)
        output += '\n'

    out_file = open('data_time_n_v0.dat', 'w')
    out_file.write(output)
    out_file.close()
    print("time to n (v0 only) saved to data_time_n_v0.dat")


time_to_n_v0()

