# 8-bit CPU Simulator in C++

## Contents
- Architecture
- Instruction Set
- Microcode/Macrocode
- Assembler
- GUI

***

## Architecture 
- The CPU has 6 Registers available to the programmer labeled A-F.  
- `Register A` and `Register B` are the two operands connected to the `ALU`.
- Instructions are 16-bits consisting of `8-bit op-codes` and `8-bit immediate values`
- An overview of the architecture:

![Architecture](https://github.com/ascheufele/8-bit-cpu-simulator/blob/master/architecture.png)

## Instruction Set
I am currently expanding the instruction set, so far we have...

| Instruction | Binary Value, Right-most LSB | Description |
| ----------- | ------------ | ----------- |
| ldi         | 0000 0001    | Load immediate value into `Register A` |
| addi | 0000 0011 | Add immediate value to contents of `Register A` and store the result in `Register A` |
| subi | 0000 1101 | Subtract an immediate value from the value in `Register A` and store the result in `Register A` |
| goto | 0000 1011 | jump to the instruction at the memory location indicated by the immediate value |
| halt | 0000 0110 | halt the CPU by freezing the `Clock`|
| ldb | 0000 1001 | load immediate value to `Register B` |
| ldc | 0001 0000 | load immediate value to `Register C` |
| ldd | 0001 0010 | load immediate value to `Register D` |
| lde | 0001 0100 | load immediate value to `Register E` |
| ldf | 0001 0110 | load immediate value to `Register F` |

## Microcode/Macrocode
- The `Control unit` executes microcode to perform CPU instructions. Macrocode (human-readable microcode) in ➡ [`macrocode.txt`](https://github.com/ascheufele/8-bit-cpu-simulator/blob/master/macrocode.txt)
- For every CPU clock cycle, the control unit performs multiple cycles, adjusting the control lines of CPU components
- I wrote a Python script that translates the human-readable macrocode to machine-readable microcode ➡ [`mTranslator.py`](https://github.com/ascheufele/8-bit-cpu-simulator/blob/master/mTranslator.py)
- Here are the current macro-instructions:

| Macro-instruction | Description |
| ----------------- | ----------- |
| pc incr | increment program counter |
| ram in | 8 LSB from bus into `Memory` location indicated by the value in `Program Counter` |
| ram out | 16-bit instruction at `Memory[Program Counter Value]` to bus |
| a in | 8 LSB from  `Bus` into `Register A` |
| a out | 8-bit value in `Register A` to `Bus` |
| ir in | 8 MSB from bus (opcode) into `Instruction Register` |
| reset | Set `Control Unit` Clock to zero |
| b in | 8 LSB from `Bus` into `Register B` |
| alu out | `ALU` result out to 8 LSB of `Bus` |
| halt | freeze the CPU `Clock` |
| pc inp | 8 LSB from bus into `Program Counter` (used for goto) |
| c in | 8 LSB from `Bus` into `Register C ` |
| c out | 8-bit value in `Register C` to `Bus` |
| d in | 8 LSB from `Bus` into `Register D ` |
| d out | 8-bit value in `Register D` to `Bus`|
| e in | 8 LSB from `Bus` into `Register E ` |
| e out | 8-bit value in `Register E` to `Bus`|
| f in | 8 LSB from `Bus` into `Register F ` |
| f out | 8-bit value in `Register F` to `Bus`|
| add | set `ALU` operation to `Addition` |
| sub | set `ALU` operation to `Subtraction` |
| lsh | set `ALU` operation to `Left Shift` |
| rsh | set `ALU` operation to `Right Shift` |

## Assembler
- The assembler translates human readable assembly progams to machine code.
- I wrote the `Assembler` in Python, it's pretty simple and intuitive ➡ [`assembler.py`](https://github.com/ascheufele/8-bit-cpu-simulator/blob/master/assembler.py)
- It works by scanning the lines of assembly programs and splitting them into instructions and immediate values.  
- Instructions are converted to their 8-bit opcodes, and immediate values are converted to base two.  
- These two components are concatenated as one line of machine code.  
- Right now, the assembler makes only ***one pass***. In the future, I forsee the possible need for implementing ***multiple passes*** to allow for things like using labels with `goto`, and implementing a `data` program section to store variables. If I go this direction, the first pass would be reserved for generating a symbol table.

## GUI
- I'm currently working on a GUI employing the [`Simple and Fast Multimedia Library`](https://www.sfml-dev.org/)
- The plan is to show realtime values of components during progam execution
- Clock speed will be modifiable, pausable, and steppable to help users view and understand how programs execute

#### My long-term goals for the GUI are...
- Show the program in memory, highlighting the current instruction
- Show the macrocode in the control unit, highlighting the current macroinstruction
- Allow users to write their own programs and to edit the macrocode
- Add more features that help people learn about computer architecture!
