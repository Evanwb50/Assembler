# Assembler
An assembler I built for a 16 bit mini architecture for a school project

Given an input text file containing the assembly code, the assembler takes the file and generates an output file containing machine code
which can be executed in something like the Xilinx iSim. There is a directions file in the project which contains information on how to make and run the code,
as well as an example of what the input should look like.

The assembler supports the follwing instructions:

  lo 	Rd, offset(Rs)		- loads data into register Rd from address in Rs
  st 	Rd, offset(Rs) 		- stores data from Rd into address in Rs
  ad 	Rd, Rs, FSrc 		- adds a register or immediate to Rs, stores in Rd
  sub 	Rd, Rs, FSrc 		- subtracts a register or immediate from Rs, stores in Rd
  lb	Rd, immediate 	- loads 8 bits into destination register
  br 	FSrc			- branches to address in register
  bl 	label 			- branch with link to label provided
  sl 	Rd, Rs, FSrc 		- set Rd to 0 if Rs >= FSrc, 1 otherwise
  ls 	Rd, Rs, immediate 	- left shifts value in Rs by an immediate and stores in Rd
  rs 	Rd, Rs, immediate 	- right shifts bits by immediate
  be	Rd, Rs, immediate	-branches to label if Rd is equal to Rs 
  bn	Rd, Rs, immediate	-branches to label if Rd is not equal to Rs
  or	Rd, Rs, FSrc		-Ors the value in Rs and the value, then stores it in Rd

The architecture makes use of a flexible source register which is capable of being either an immediate value (denoted with a * before it) or 
a register. 

For complete documentation of this architecture and the project overall, please reference the following link:
https://docs.google.com/document/d/1oDapB6MSb4uZ_dg7s16BStQtCtkva2_W5dx7l8ZytXY/edit?usp=sharing
