# simplevm

This is a simple toy VM built in C. Idea and starting point are from https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C.

How to use:
> gcc -o main main.cpp


> ./main filename.bin

Ensure the bin file is assembled properly to assure proper operation.

Assembly/Machine Language Reference:

Opcodes: 
0) halt: 0x000

   halts operation of the system.
   
1) loadi: 0x1 <4-bit register number> <8-bit immediate>

   loads the 8-bit immediate value into the register specified by the second-most-signficant-byte.
   registers are numbered 0-3.
   
2) add: 0x2 <4-bit dest. register> <4-bit source register 1> <4-bit source register 2>

   adds the values in the two source registers and places the result in the destination register.
   
3) addi: 0x3 <4-bit dest. register> <4-bit source register> <4-bit immediate>

   adds the immediate value to the source register and stores the result in the destination register.
   
