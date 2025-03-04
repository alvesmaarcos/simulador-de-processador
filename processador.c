#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Estrutura para os registradores e flags
typedef struct {
    uint16_t R[8];  // Registradores R0-R7
    uint16_t PC;    // Program Counter
    uint16_t IR;    // Instruction Register
    uint16_t LR;    // Link Register
    uint32_t SP;    // Stack Pointer (32 bits)
    struct {
        bool C;    // Flag de Carry
        bool Ov;   // Flag de Overflow
        bool Z;    // Flag de Zero
        bool S;    // Flag de Sinal
    } flags;
} Registers;

// Memórias
uint16_t prog_mem[0x10000];  // Memória de programa (16 bits de endereço)
uint16_t data_mem[0x10000];  // Memória de dados (16 bits de endereço)
uint16_t stack_mem[16];      // Pilha (16 bytes)

// Função para exibir o estado conforme especificado
void print_state(Registers *reg) {
    // Registradores
    printf("Registradores:\n");
    for (int i = 0; i < 8; i++) {
        printf("R%d: 0x%04X\n", i, reg->R[i]);
    }
    printf("PC: 0x%04X\n", reg->PC);
    printf("LR: 0x%04X\n", reg->LR);
    printf("SP: 0x%08X\n", reg->SP);

    // Memória de dados
    printf("\nMemoria de dados:\n");
    for (int i = 0; i < 0x10000; i++) {
        if (data_mem[i] != 0) {
            printf("0x%04X: 0x%04X\n", i, data_mem[i]);
        }
    }

    // Pilha
    printf("\nPilha:\n");
    for (int i = 0; i < 8; i++) {
        printf("0x%04X: 0x%04X\n", 0x8200 - i * 2, stack_mem[i]);
    }

    // Flags
    printf("\nFlags:\n");
    printf("C: %d, Ov: %d, Z: %d, S: %d\n", reg->flags.C, reg->flags.Ov, reg->flags.Z, reg->flags.S);
}

// Função para empilhar um valor na pilha
void push(Registers *reg, uint16_t value) {
    if (reg->SP < 0x81F0 || reg->SP > 0x8200) {
        fprintf(stderr, "Erro: Estouro de pilha!\n");
        exit(1);
    }
    stack_mem[abs(reg->SP - 0x8200) / 2] = value;
    reg->SP -= 2;
}

// Função para desempilhar um valor da pilha
uint16_t pop(Registers *reg) {
    if (reg->SP > 0x8200) {
        fprintf(stderr, "Erro: Estouro de pilha!\n");
        exit(1);
    }
    reg->SP += 2;
    return stack_mem[abs(reg->SP - 0x8200) / 2];
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    // Inicialização dos registradores e memória
    Registers reg = {0};
    reg.SP = 0x8200;  // Inicializa o SP (topo da pilha)
    memset(prog_mem, 0, sizeof(prog_mem));
    memset(data_mem, 0, sizeof(data_mem));
    memset(stack_mem, 0, sizeof(stack_mem));

    // Leitura do arquivo de entrada
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        unsigned int addr, value;
        if (sscanf(line, "%x:%x", &addr, &value) == 2) {
            prog_mem[addr] = value;
        }
    }
    fclose(file);

    // Simulação da execução
    bool halt = false;
while (!halt) {
        // Fetch
        if (reg.PC >= 0xFFFE) break;  // Fim do programa
        reg.IR = prog_mem[reg.PC];
        uint16_t next_pc = reg.PC + 2;

        // Decode & Execute
        uint8_t opcode = (reg.IR >> 11) & 0x1F;  // Primeiros 5 bits
        uint8_t rd = (reg.IR >> 8) & 0x07;       // Registrador destino
        uint8_t rs = (reg.IR >> 5) & 0x07;       // Registrador fonte
        uint8_t imm = reg.IR & 0xFF;             // Valor imediato

        switch (opcode) {
            case 0x02: // MOV Rd, Rm
                printf("MOV R%d, R%d\n", rd, rs);  // Depuração
                reg.R[rd] = reg.R[rs];
                break;
            case 0x03: // MOV Rd, #imm
                printf("MOV R%d, #%d\n", rd, imm);  // Depuração
                reg.R[rd] = imm;
                break;
            case 0x08:  // ADD Rd, Rs, Rt
                printf("ADD R%d, R%d, R%d\n", rd, rs, (reg.IR >> 2) & 0x07);  // Depuração
                reg.R[rd] = reg.R[rs] + reg.R[(reg.IR >> 2) & 0x07];
                break;
            case 0x05: // SUB Rd, Rs, Rt
                printf("SUB R%d, R%d, R%d\n", rd, rs, (reg.IR >> 2) & 0x07);  // Depuração
                reg.R[rd] = reg.R[rs] - reg.R[(reg.IR >> 2) & 0x07];
                break;
                case 0x00:  // Instruções que começam com 0x00 (PSH, POP ou NOP)
                {
                    // Extrai os dois últimos bits da instrução
                    uint8_t op_type = reg.IR & 0x03;
            
                    // Depuração: Exibe o valor de IR e os dois últimos bits
                    // printf("IR: 0x%04X, op_type: 0x%02X\n", reg.IR, op_type);

                    // Verifica o tipo de operação
                    if (op_type == 0x01) {  // PSH Rs (termina com 01)
                        uint8_t rsPsh = (reg.IR >> 8) & 0x07;  // Extrai o registrador fonte (Rs)
                        printf("PSH R%d\n", rsPsh);  // Depuração: Exibe o registrador fonte
                        push(&reg, reg.R[rsPsh]);  // Empilha o valor de Rs
                    }
                    else if (op_type == 0x02) {  // POP Rd (termina com 10)
                        uint8_t rd = (reg.IR >> 8) & 0x07;  // Extrai o registrador destino (Rd)
                        printf("POP R%d\n", rd);  // Depuração: Exibe o registrador destino
                        reg.R[rd] = pop(&reg);  // Desempilha e armazena em Rd
                    }
                    // Caso op_type seja 0x00, não faz nada e continua a execução
    
                }
                break;
            case 0x09:  // JEQ endereço
                if (reg.flags.Z) {
                    next_pc = imm;
                }
                break;
            case 0x0A:  // JMP endereço
                next_pc = imm;
                break;
            case 0x0B:  // HALT
                halt = true;
                break;
            default:
                fprintf(stderr, "Instrução desconhecida: 0x%04X\n", reg.IR);
                halt = true;
                break;
        }

        reg.PC = next_pc;
    }

    // Exibir estado final
    print_state(&reg);

    return 0;
}