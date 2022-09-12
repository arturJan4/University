# Lista 5

## Zad 1
Finnix:
https://en.wikipedia.org/wiki/Finnix
https://www.linuxlinks.com/finnix/
https://www.linux.com/news/finnix-compact-linux-distribution-system-administrators/

## Zad 2

rescue
```
set

ls - pozwala zobaczyć dostępne lokalizacje. Tam wybrałem partycję na której wiedziałem, że znajduje się ubuntu (hd1,gpt5)
set root=(hd1,gpt5)
linux /boot/vmlinux(wersja, której nie pamiętam klikałem tab i się wstawiała reszta) root=/dev/sda1
initrd /boot/initrd.img(tak jak wyżej)
boot
```

```
sudo fdisk -l

sudo mount /dev/sda1 /mnt
sudo mount --bind /dev /mnt/dev
sudo mount --bind /proc /mnt/proc
sudo mount --bind /sys /mnt/sys
sudo chroot /mnt

grub-install /dev/sda

dpkg-reconfigure grub-pc

//lub
//grub-install --recheck /dev/sda
//update-grub

exit -> ctrl + D

sudo umount /mnt/dev
sudo umount /mnt/proc
sudo umount /mnt/sys
sudo umount /mnt
```

The proc, dev, sys (and devpts) filesystems are needed by grub (and update-initramfs); they contain symbolic links to devices and whatnot. If the aforementioned programs can't find them, they'll print error messages; for example, if there is no /dev/sda in the chrooted environment, what good will running grub-install /dev/sda do?

Also, /dev and all the device files/symlinks it contains is sort of an interface between the kernel and the hardware devices. Actions made on devices in the chrooted environment are not going to affect the live disk, but they WILL affect the devices!

What mount -o bind does is just make an alternate path to the same thing (whether it be a filesystem location in memory or a filesystem location on a block device).
