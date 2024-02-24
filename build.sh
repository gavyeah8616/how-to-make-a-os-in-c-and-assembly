#nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -t link.ld -o safe computer/boot/kernel.bin kasm.o kc.o
qemu -kernel safe computer/boot/kernel.bin
#grub-mkrescue -o safe computer.iso safe computer/

read a
