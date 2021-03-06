#include <stdio.h>
#include <stdlib.h>

#define MEMMASK 0x1fff
//#define MEMSIZE 0x2000
//#define MEMSIZE 0x1500
//#define MEMSIZE 0x1500
#define MEMSIZE sizeof(memory)

#define word varword
#define byte varbyte


char inkey()
{
	return 0; 
}

#include "prog8080.c"
#include "i8080.h"
#include "i8080_hal.h"
#include "i8080_hal.c"
#include "i8080.c"


//#define START0100


void execute_test(unsigned char* test, int success_check) {
    unsigned char* mem = i8080_hal_memory();
    int success = 0;
        int i;
 
    
    printf(" memmask:%x  memsize: %x \n", MEMMASK, MEMSIZE);
        
    
        
   // for (i=0;i<sizeof(program); i++) {
   //         mem[i+0x100] = program[i];
   // }
    
    

    
    
    i8080_init();
    
    //set up pointer to last byte of ram (FOR LHLD 6, which programs use to find end of memory)
    
#ifdef START0100
    
    mem[5] = 0xC9;  // Inject RET at 0x0005 to handle "CALL 5".
    mem[6] = MEMSIZE & 0xFF ;  
    mem[7] = (MEMSIZE >> 8);
    i8080_jump(0x100);
#else
    i8080_jump(0x0000);
#endif
    
    
    SP = MEMSIZE; /*stack at last byte of ram*/
    
    
    
    while (1) {
        int pc = i8080_pc();
        if (mem[pc] == 0x76) {
            printf("HLT at %04X\n", pc);
            exit(1);
        }
        
#ifdef START0100
        
        if (pc == 0x0005) {
            if (i8080_regs_c() == 9) {
                int i;
                for (i = i8080_regs_de(); mem[i] != '$'; i += 1)
                    putchar(mem[i]);
                success = 1;
                printf("\n");
            }
            if (i8080_regs_c() == 2) putchar((char)i8080_regs_e());
        }
#endif
       
        
        i8080_instruction();
        
        #ifdef START0100
        if (i8080_pc() == 0) {
            printf("\nJump to 0000 from %04X\n", pc);
            if (success_check && !success)
                exit(1);
            return;
        }
        #endif
    }
}


int main(){
	unsigned char x;

        printf("Start!\n");
        execute_test(memory, 0);
	printf("Done!\n");
	
	return 0;
}
