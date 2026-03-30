#include <stdint.h>
#include <stdio.h>
uint8_t PC = 0;
uint8_t R[4] ;
uint8_t M[16] = {
  0b10001010, // li r0, 10
  0b10010000, // li r1, 0
  0b10100000, // li r2, 0
  0b10110001, // li r3, 1
  0b00010111, // add r1, r1, r3
  0b00101001, // add r2, r2, r1
  0b11010001, // bner0 r1, 4
  0b11011111, // bner0 r3, 7
};

void inst_cycle(){
    uint8_t inst = *(uint8_t *)&M[PC];
    if (((inst >>6 )&0x3)==0) {
        R[(inst>>4)&0x3] = R[(inst>>2)&0x3] + R[inst&0x3];
    }else if(((inst>>6)&0x3)==2){
        R[(inst>>4)&0x3] = inst & 0xf;
    }else if(((inst>>6)&0x3)==3){
        if (R[inst&0x3] != R[0] ){
            PC = (inst>>2)&0xf;
            return;
        }
    }else {printf("Unsupported instuction!\n");}
    PC +=1;
}

int main(){
    for (int i = 0; i < 100; i ++) { inst_cycle(); }
    printf("r2 = %d\n", R[2]);
    return 0;
}
