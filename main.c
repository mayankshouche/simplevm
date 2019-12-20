/*
	Simple Virtual Machine. Based on https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C
	Written 2019, Mayank Shouche.
	This work is licensed under the Creative Commons Attribution 4.0 International License.
*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NUM_REGS 4
#define READ_SZ 255

unsigned int regs[NUM_REGS];
int pc = 0;
unsigned int program[] = {0x1064, 0x11C8, 0x2201, 0x0000};
unsigned int* memory;

int opcode = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int immediateFull = 0;
int immediateHalf = 0;

bool status = true; //VM runs until status flag turns to zero

int fetch(void);
void getProgram(char* filename, unsigned int* program);
void decodeInstruction(int instruction);
void showRegs(void);

int main(int argc, char* argv[])
{
	//getProgram(argv[1], program);

	while (status)
	{
		decodeInstruction(fetch());
		switch(opcode)
		{
			case 0:
				printf("halt\n");
				status = false;
				break;

			case 1:
				printf("loadi r%d #%d\n", reg1, immediateFull);
				regs[reg1] = immediateFull;
				break;

			case 2:
				printf("add r%d r%d r%d\n", reg1, reg2, reg3);
				regs[reg1] = regs[reg2] + regs[reg3];
				break;

			case 3:
				printf("addi r%d r%d #%d\n", reg1, reg2, immediateHalf);
				regs[reg2] = regs[reg1] + immediateHalf;
				break;
		}
		showRegs();
	}


}

int fetch(void)
{
	return program[pc++];
}

void getProgram(char* filename, unsigned int* program)
{
	FILE* fp;
	fp = fopen(filename, "r");
	char* buffer[READ_SZ];
	int index = 0;

	while (fgets(buffer, READ_SZ, fp))
	{
		program[index] = malloc(sizeof(unsigned int)); //allocate space for each instruction read in
		program[index++] = strtol(buffer, NULL, 16);   //convert the string values from the file to hex ints
	}
}

void decodeInstruction(int instruction)
{
	opcode = (instruction & 0xF000 ) >> 12; //get first byte of instruction
	reg1 = (instruction & 0x0F00) >> 8;     //second byte
	reg2 = (instruction & 0x00F0) >> 4;     //third byte
	reg3 = (instruction & 0x000F);			//fourth...
	immediateFull = (instruction & 0x00FF);	//lower half
	immediateHalf = (instruction & 0x000F); //LSB
}

void showRegs(void)
{
	printf("reg0 = %d\nreg1 = %d\nreg2 = %d\nreg3 = %d\n", regs[0], regs[1], regs[2], regs[3]);
}