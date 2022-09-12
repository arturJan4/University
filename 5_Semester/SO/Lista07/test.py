from glob import glob

VmSize = 0
VmRSS = 0

files = glob("/proc/**/status")

for file in files:
    for line in open(file, 'r'):
        line = line.split()
        if 'VmSize:' in line: 
          VmSize += int(line[1])
        if 'VmRSS:' in line: 
          VmRSS += int(line[1])

print(f"VmSize: {VmSize} kB")
print(f"VmRSS: {VmRSS} kB")