#include <stdio.h>;

typedef struct {
    int R[8];
    int PC;
    int IR;
    int Z;
    int S;
    int C;
    int Ov; 
} Processador;

int main(){
    Processador c;
    for (int i = 0; i < 8; i++) {
        c.R[i] = 0b0;
    }
    c.PC = 0b0;
    c.IR = 0b0;
    c.Z = 0b0;
    c.S = 0b0;
    c.C = 0b0;
    c.Ov = 0b0; 

}