bits 32
section .text
     align 4
    dd 0x1BADB0
    dd 0x00
    dd - (0x1BADB0+0x00)

global start
extern kmain
start:
      cli
      call kmain
      hlt
      
