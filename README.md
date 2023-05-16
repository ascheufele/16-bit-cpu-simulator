# WIP of an 8-bit CPU Simulator

My goal is to make the code as close to hardware as possible.

I've made structs for the various parts of the CPU including:
  - Clock
  - Program Counter
  - Bus
  - ALU
  - Registers (MAR, IR, A, B, Output)
  - Memory (RAM, ROM)
  - Control Logic
  
I am writing my own microcode and macrocode for the CPU so it can run user programs.

Is this 8-bit or 16-bit? This is something I ask myself constantly
   - Each instruction is 16 bits wide, with 8 bits for the opcode and 8 bits for an immediate value.
   - The bus is 16-bits wide
   - The registers are 8-bits wide
   - Due to register size and immediate values being limited to 8-bits I tend to lean towards "8-bit", but I'm open to counter-arguments.

My end goal is to create a GUI with the SFML library to view in real time the values in the various components as the CPU runs a program.

Dependencies: SFML - https://www.sfml-dev.org/
