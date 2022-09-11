filepath = '4/zadania/log_generator/input.txt'


file = open(filepath, 'r')
lines = file.readlines()

address = lines[0].split(' ')[0]

hour = lines[0].split(' ')[3]
hour = hour[hour.find(':') + 1:]

operation = lines[0].split(' ')[5][1:]
page = lines[0].split(' ')[6]
status = lines[0].split(' ')[8]

for index, line in enumerate(lines):
  split_line = line.split(' ')
  address = split_line[0]
  hour = split_line[3]
  hour = hour[hour.find(':') + 1:]
  operation = split_line[5][1:]
  page = split_line[6]
  status = split_line[8]

  lines[index] = f"{hour} {address} {operation} {page} {status}\n"
  # print("{}".format(line.strip()))

with open('4/zadania/log_generator/output.txt', 'w') as f:
    f.writelines(lines)