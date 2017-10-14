#include <stdio.h>
#include <stdlib.h>

#define MEMMASK 0x00fff
#define word varword
#define byte varbyte

#include "prog8080.c"
#include "i8080.h"
#include "i8080_hal.h"
#include "i8080_hal.c"
#include "i8080.c"


void readline(){
}

void f1(){
	printf("Func1\n");
}

void f2(){
	printf("Func2\n");
}


void f3(){
	printf("Func3\n");
}

void* fs[3]={f1,f2,f3};


void execute_test(unsigned char* test, int success_check) {
    unsigned char* mem = i8080_hal_memory();
    int success = 0;
        int i;
 //   memset(mem, 0, 0x10000);
    for (i=0;i<sizeof(program); i++) {
            mem[i+0x100] = program[i];
    }
    //memcpy(mem, mem+0x100, program, sizeof(program));
   // load_file(filename, mem + 0x100);

    mem[5] = 0xC9;  // Inject RET at 0x0005 to handle "CALL 5".
    i8080_init();
    SP = MEMMASK; 
    i8080_jump(0x100);
    while (1) {
        int pc = i8080_pc();
        if (mem[pc] == 0x76) {
            printf("HLT at %04X\n", pc);
            exit(1);
        }
        if (pc == 0x0005) {
            if (i8080_regs_c() == 9) {
                int i;
                for (i = i8080_regs_de(); mem[i] != '$'; i += 1)
                    putchar(mem[i]);
                success = 1;
            }
            if (i8080_regs_c() == 2) putchar((char)i8080_regs_e());
        }
        i8080_instruction();
        if (i8080_pc() == 0) {
            printf("\nJump to 0000 from %04X\n", pc);
            if (success_check && !success)
                exit(1);
            return;
        }
    }
}


int main(){
	unsigned char x;

        printf("Start!\n");
        execute_test(program, 0);
	printf("Done!\n");
	

	return 0;
}
