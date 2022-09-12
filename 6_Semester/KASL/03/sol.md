# Linux - Lista 3
SUID (set owner User ID)

run with owner privilege

cel -> root access

chmod 4777 etc. -> prefix 4

sudo useradd hacker (passwd hacker)

niektóre programy potrzebują i to nie jest zagrożenie

## sudoers
./demo -> brak uprawnien
sudo ./demo -> hacker no in sudoers
`sudo cat /var/log/auth.log`

/bin/bash -> inny bash
cat /etc/passwd


## znajdowanie plików
https://gtfobins.github.io/

`find /usr/bin -perm -u=s -type f 2>/dev/null`

## grep
artur robi:
`ls -al | grep "grep"`
`sudo chmod u+s /bin/grep` (dodaje sticky)

hacker robi:
`grep '' /etc/shadow | tail -n 5`

mamy hasz -> hydra/john the ripper

`sudo chmod u-s /bin/grep` (na koniec)

## mv
https://steflan-security.com/linux-privilege-escalation-suid-binaries/

## inne
ale są gorsze np. bash as root
