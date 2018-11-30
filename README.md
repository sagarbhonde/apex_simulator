---------------------------------------------------------------------------------
Out-of-order APEX Pipeline Simulator
---------------------------------------------------------------------------------

@NOTE:  VALID Assembly code' which terminates with HALT is necessary. If Invalid 'assembly code' is given, program prints error and exits.


Description:
----------------------------------------------------------------------------------
This code is a implementation of Variation3. The simulated processor makes use of register renaming with three function units, a centralized issue queue, a LSQ, a ROB and a unified register file (URF).


File-Info
----------------------------------------------------------------------------------
1) Makefile 	
2) file_parser.c 	- Contains Functions to parse input file. No need to change this file
3) cpu.c          - Contains Implementation of APEX cpu. You can edit as needed
4) cpu.h          - Contains various data structures declarations needed by 'cpu.c'. You can edit as needed
5) helper.h        - Contains helper function declarations, macros, constants etc.
6) helper.c        - Conatains helper function definitions
	 

How to compile and run
----------------------------------------------------------------------------------
1) go to terminal, cd into project directory and type 'make' to compile project

1. There are two functions – simulate () and display () 

2. There is a second command line argument (simulate/display) to distinguish these two functions:
	a. Second command line argument is “simulate” → only show State of Register File and Data Memory.
	b. Second command line argument is “display” → show Instruction Flow as well as State of Register File and Data Memory.
	
3. There is a third command line argument as “number of cycles” means up to this number of cycles simulation should run and produce output.

Example with three command line arguments while running the program:

	• make
	• ./apex_sim input.asm simulate 50
	
	o Simulate for 50 cycles and then show State of Register File and Data Memory at the end of 50 cycles or at the end of program (whichever comes first).
	• make
	• ./apex_sim input.asm display 10

	o Simulate for 10 cycles and then show Instruction Flow as well as State of Register File and Data Memory at the end of 10 cycles or at the end of program (whichever comes first).
