# Simulador de processador utilizando C
Projeto para a disciplina de Arquitetura de Computadores.

### Registradores
- R0-R7, PC, LR e SP.

# Memória de dados
### No mesmo formato do arquivo de entrada (<endereço>:<conteúdo>)

###### Assuma que toda a faixa de endereços está disponível e que a memória está inicialmente zerada. Devem ser exibidas apenas as posições que forem acessadas pelo código (desconsiderando a pilha).

# Pilha
###  No mesmo formato do arquivo de entrada (<endereço>:<conteúdo>)

 - Assuma que o ponteiro de pilha com o valor inicial de 0x82000000 e que pilha possui tamanho de 16 bytes

# Flags
- Exiba os valores finais das flags C, Ov, Z, S
- Assuma que as todas iniciam zeradas

# Requisitos:
- O projeto deve ter uma Instrução NOP. Sempre que ocorrer uma instrução NOP, o simulador deve exibir as mesmas informações descritas no item c.
- O projeto deve ter uma instrução HALT, que encerrará o fluxo.
- MOV Rd, Rm      -> Rd = Rm, que busca o registrador d, o registrador m, e insere o valor de Rm em Rd.
- MOV Rd, #Im     -> Rd = #Im, que busca o registrador d e atribui um valor Immediate a Rd.
- STR [Rm], #Im   -> [Rm] = Rn, que busca o endereço do registrador Rm na memória, busca o valor do registrador Rn e atribui o valor de Rn ao endereço de Rn.
- LDR Rd, [Rm]    -> [Rm] = #Im.
- ADD Rd, Rm, Rn  -> Rd = Rm + Rn.
- SUB Rd, Rm, Rn  -> Rd = Rm - Rn.
- MUL Rd, Rm, Rn  -> Rd = Rm AND Rn.
- ORR Rd, Rm, Rn  -> = Rm or Rn.
- NOT Rd, Rm      -> Rd = ¬Rm.
- XOR Rd, Rm, Rm  -> Rd = Rm xor Rn.
- PSH Rn          -> [SP] Rn; SPP--.
- POP Rd          -> SP++; Rd = [SP].
- CMP Rm, Rn      -> Z = (Rm = Rn)? 1 : 0; S = (Rm < Rn)? 1 : 0.
- JMP #Im         -> PC = PC + #Im.
- JEQ #Im         -> PC = PC + #Im, se Z = 1 e S = 0.
- JLT #Im         -> PC = PC + #Im, se Z = 0 e S = 1.
- JGT #Im         -> PC = PC + #Im, se Z = 0 e S = 0.
- SHR Rd, Rm, #Im -> Rd = Rm >> #Im.
- SHL Rd, Rm, #Im -> Rd = Rm << #Im.
- ROR Rd, Rm      -> Rd = Rm >> 1:Rd(MSB) = Rm(LSB).
- ROL Rd, Rm      -> Rd = Rm << 1:Rd(LSB) = Rm(MSB).
