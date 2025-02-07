# Simulador de processador utilizando C
### Projeto para a disciplina de Arquitetura de Computadores.

# Requisitos:
- O projeto deve ter uma Instrução NOP.
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