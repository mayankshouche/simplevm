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

unsigned int regs[NUM_REGS];
int pc = 0;
unsigned int program[];

int opcode = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int immediate = 0;

int fetch(void);
void getProgram(char* filename, unsigned int* program);

int main(int argc, char* argv[])
{
	getProgram(argv[1], program);

}

int fetch(void)
{
	return program[pc++];
}

void getProgram(char* filename, unsigned int* program)
{
	FILE* fp;
	fp = fopen(filename, "r");
	char* buffer[255];
	int index = 0;

	while (fgets(buffer, 255, fp))
	{
		program[index] = malloc(sizeof(unsigned int)); //allocate space for each instruction read in
		program[index++] = strtol(buffer, NULL, 16); //convert the string values from the file to hex ints
	}
}