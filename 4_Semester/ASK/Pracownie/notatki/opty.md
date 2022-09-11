# Dane o systemie
kernel: https://www.cyberciti.biz/faq/find-print-linux-unix-kernel-version/
linux distro: https://www.cyberciti.biz/faq/find-linux-distribution-name-version-number/
gcc i werja systemu: cat /proc/version

x86info -a - jakieś informacje o cpu

https://www.cpu-world.com/CPUs/Core_i5/Intel-Core%20i5%20i5-8300H.html - informacje o n-way
getconf -a | grep CACHE - do porównania z tym (tu jest sumarycznie na rdzenie)

o TLB:
cpuid | grep -i tlb

cpu-x

# skrypty automatyzujace
make sim
make test

# walka z papi
cpuid -i | grep "counters"
      number of counters per logical processor = 0x4 (4)

wywalić z memory_evset liczniki (rozwiązanie)
cpuid -1 -> permormance monitoring

https://superuser.com/questions/980632/run-perf-without-root-rights
