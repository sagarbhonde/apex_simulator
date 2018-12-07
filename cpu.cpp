/*
 *  cpu.c
 *  Contains APEX cpu pipeline implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "helper.h"

/* Set this flag to 1 to enable debug messages */
#define ENABLE_DEBUG_MESSAGES 1

/*
 * This function creates and initializes APEX cpu.
 *
 * Note : You are free to edit this function according to your
 * 				implementation
 */
APEX_CPU*
APEX_cpu_init(const char* filename) {
	if (!filename) {
		return NULL;
	}

	APEX_CPU* cpu = (APEX_CPU*) malloc(sizeof(*cpu));
	if (!cpu) {
		return NULL;
	}

	/* Initialize IssueQueue */
	cpu->iq = new IQ();

	/* Initialize ROB */
	cpu->rob = new ROB();

	/*Initialize URF */
	cpu->urf = new URF();

	/* Initialize PC, Registers and all pipeline stages */
	cpu->pc = 4000;
	memset(cpu->stage, 0, sizeof(CPU_Stage) * NUM_STAGES);
	memset(cpu->data_memory, 0, sizeof(int) * 4000);

	/* Parse input file and create code memory */
	cpu->code_memory = create_code_memory(filename, &cpu->code_memory_size);

	if (!cpu->code_memory) {
		free(cpu);
		return NULL;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		fprintf(stderr,
				"APEX_CPU : Initialized APEX CPU, loaded %d instructions\n",
				cpu->code_memory_size);
		fprintf(stderr, "APEX_CPU : Printing Code Memory\n");
		printf("%-9s %-9s %-9s %-9s %-9s\n", "opcode", "rd", "rs1", "rs2",
				"imm");

		for (int i = 0; i < cpu->code_memory_size; ++i) {
			printf("%-9s %-9d %-9d %-9d %-9d\n", cpu->code_memory[i].opcode,
					cpu->code_memory[i].rd, cpu->code_memory[i].rs1,
					cpu->code_memory[i].rs2, cpu->code_memory[i].imm);
		}
	}

	/* Make all stages busy except Fetch stage, initally to start the pipeline */
	for (int i = 1; i < NUM_STAGES; ++i) {
		cpu->stage[i].busy = 1;
	}

	return cpu;
}

/*
 * This function de-allocates APEX cpu.
 *
 * Note : You are free to edit this function according to your
 * 				implementation
 */
void APEX_cpu_stop(APEX_CPU* cpu) {
	printf("\n\n\n\n");

	printf(
			"=============== STATE OF ARCHITECTURAL REGISTER FILE ==========\n\n");
	/*for (int i = 0; i < 16; i++) {
	 char* status;
	 status = cpu->regs_valid[i] == 1 ? "INVALID" : "VALID";
	 printf("|\tREG[%d]\t|\tValue = %d\t|\tStatus=%s\t|\n", i, cpu->regs[i],
	 status);
	 }*/

	printf("=============== STATE OF ISSUE QUEUE ==========\n\n");
	for (int i = 0; i < IQ_SIZE; i++) {
		(cpu->iq->issueQueue[i]).printIQEntry();
		cout << endl;
	}

	printf("=============== STATE OF ROB ==========\n\n");

	cout << cpu->rob << endl;

	//TODO this function is not working print_urf()
	printf("=============== URF ==========\n\n");
	cpu->urf->print_urf();

	/*printf("\n\n============== STATE OF DATA MEMORY =============\n\n");
	 for (int i = 0; i < 100; i++) {
	 printf("|\tMEM[%d]\t|\tData Value = %d\t|\n", i, cpu->data_memory[i]);
	 }*/

	free(cpu->code_memory);

	// delete IQ and ROB
	delete cpu->urf;
	delete cpu->iq;
	delete cpu->rob;

	free(cpu);
	printf("ALL CLEAR!!");
}

/* Converts the PC(4000 series) into
 * array index for code memory
 *
 * Note : You are not supposed to edit this function
 *
 */
int get_code_index(int pc) {
	return (pc - 4000) / 4;
}

static void print_instruction(CPU_Stage* stage, int is_fetch) {

	if (strcmp(stage->opcode, "STORE") == 0) {
		printf("%s,R%d,R%d,#%d ", stage->opcode, stage->rs1, stage->rs2,
				stage->imm);
	}

	if (strcmp(stage->opcode, "HALT") == 0) {
		printf("%s ", stage->opcode);
	}

	if (strcmp(stage->opcode, "NOP") == 0) {
		printf("%s ", stage->opcode);
	}

	if (strcmp(stage->opcode, "BZ") == 0) {
		printf("%s,#%d ", stage->opcode, stage->imm);
	}

	if (strcmp(stage->opcode, "BNZ") == 0) {
		printf("%s,#%d ", stage->opcode, stage->imm);
	}

	if (strcmp(stage->opcode, "JUMP") == 0) {
		printf("%s,R%d,#%d ", stage->opcode, stage->rs1, stage->imm);
	}

	if (strcmp(stage->opcode, "LOAD") == 0) {
		printf("%s,R%d,R%d,#%d ", stage->opcode, stage->rd, stage->rs1,
				stage->imm);
	}

	if (strcmp(stage->opcode, "MOVC") == 0) {
		if (is_fetch == 1)
			printf("%s,R%d,#%d", stage->opcode, stage->rd, stage->imm);
		else
			printf("%s,R%d,#%d \t [%s,U%d,#%d]", stage->opcode, stage->rd,
					stage->imm, stage->opcode, stage->u_rd, stage->imm);
	}

	if (strcmp(stage->opcode, "SUB") == 0 || strcmp(stage->opcode, "MUL") == 0
			|| strcmp(stage->opcode, "ADD") == 0
			|| strcmp(stage->opcode, "EX-OR") == 0
			|| strcmp(stage->opcode, "OR") == 0
			|| strcmp(stage->opcode, "AND") == 0) {
		if (is_fetch == 1)
			printf("%s,R%d,R%d,R%d", stage->opcode, stage->rd, stage->rs1,
					stage->rs2);
		else
			printf("%s,R%d,R%d,R%d \t [%s,U%d,U%d,U%d]", stage->opcode,
					stage->rd, stage->rs1, stage->rs2, stage->opcode,
					stage->u_rd, stage->u_rs1, stage->u_rs2);
	}
}

/* Debug function which dumps the cpu stage
 * content
 *
 * Note : You are not supposed to edit this function
 *
 */
static void print_stage_content(char* name, CPU_Stage* stage) {
	printf("%-15s: pc(%d) ", name, stage->pc);
	if (strcmp("Fetch", name) == 0) {
		print_instruction(stage, 1);
	} else
		print_instruction(stage, 0);

	printf("\n");
}

/*
 *  Fetch Stage of APEX Pipeline
 *
 *  Note : You are free to edit this function according to your
 * 				 implementation
 */
int fetch(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[F];
	CPU_Stage * drf_stage = &cpu->stage[DRF];
	if (!stage->busy && !stage->stalled) {
		/* Store current PC in fetch latch */
		stage->pc = cpu->pc;

		/* Index into code memory using this pc and copy all instruction fields into
		 * fetch latch
		 */
		APEX_Instruction* current_ins = &cpu->code_memory[get_code_index(
				cpu->pc)];
		strcpy(stage->opcode, current_ins->opcode);
		stage->rd = current_ins->rd;
		stage->rs1 = current_ins->rs1;
		stage->rs2 = current_ins->rs2;
		stage->imm = current_ins->imm;

		/* Update PC for next instruction */
		if (!drf_stage->stalled) {
			cpu->pc += 4;
			cpu->stage[DRF] = cpu->stage[F];
			if (ENABLE_DEBUG_MESSAGES) {
				print_stage_content("Fetch", stage);
			}
			return 0;
		} else {
			stage->stalled = 1;
		}
	}
	return 0;
}

int renamer(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[DRF];
	if (strcmp(stage->opcode, "MOVC") == 0) {
		int urfRd = cpu->urf->get_next_free_register();
		if (urfRd != -1) {
			stage->u_rd = urfRd;
			//Mark destination register invalid
			cpu->urf->URF_TABLE_valid[urfRd] = 0;
			//Update F-RAT
			cpu->urf->F_RAT[stage->rd] = urfRd;
			//Add entry of newly renamed register to F-RAT
			cpu->urf->F_RAT[stage->rd] = urfRd;
			return 1;
		}
	}

	if (strcmp(stage->opcode, "ADD") == 0 || strcmp(stage->opcode, "SUB") == 0
			|| strcmp(stage->opcode, "AND") == 0
			|| strcmp(stage->opcode, "OR") == 0
			|| strcmp(stage->opcode, "EX-OR") == 0) {
		int urfRd = cpu->urf->get_next_free_register();
		if (urfRd != -1) {
			stage->u_rd = urfRd;
			cpu->urf->F_RAT[stage->rd] = urfRd;
			int urfsrc1 = cpu->urf->F_RAT[stage->rs1];
			int urfsrc2 = cpu->urf->F_RAT[stage->rs2];

			stage->u_rs1 = urfsrc1;
			stage->u_rs2 = urfsrc2;
			//Mark destination register invalid
			cpu->urf->URF_TABLE_valid[urfRd] = 0;
			//Add entry of newly renamed register to F-RAT
			cpu->urf->F_RAT[stage->rd] = urfRd;
			return 1;
		}
	}
	return 0;
}

/*
 *  Decode Stage of APEX Pipeline
 */
int decode(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[DRF];
	if (!stage->busy && !stage->stalled) {

		/* No Register file read needed for MOVC */
		if (strcmp(stage->opcode, "MOVC") == 0) {
			stage->fuType = INT_FU;
			if (renamer(cpu) == 1) {
				// Go to next stage
				cpu->stage[QUEUE] = cpu->stage[DRF];
				if (ENABLE_DEBUG_MESSAGES)
					print_stage_content("Decode/RF", stage);
				return 0;
			}
		}

		if (strcmp(stage->opcode, "ADD") == 0
				|| strcmp(stage->opcode, "SUB") == 0
				|| strcmp(stage->opcode, "AND") == 0
				|| strcmp(stage->opcode, "OR") == 0
				|| strcmp(stage->opcode, "EX-OR") == 0) {
			stage->fuType = INT_FU;
			if (renamer(cpu) == 1) {
				// Go to next stage
				cpu->stage[QUEUE] = cpu->stage[DRF];
				if (ENABLE_DEBUG_MESSAGES)
					print_stage_content("Decode/RF", stage);
				return 0;
			}
		}

		if (ENABLE_DEBUG_MESSAGES) {
			print_stage_content("Decode/RF", stage);
		}
	}
	return 0;
}

/*
 * Make the entry in IQ, ROB and LSQ(If neeeded)
 * */
int addToQueues(APEX_CPU* cpu) {
	CPU_Stage * stage = &cpu->stage[QUEUE];
	CPU_Stage * int_stage = &cpu->stage[INT_EX];
	if (!stage->busy && !stage->stalled) {

		IQEntry *entry = new IQEntry(stage->rd, stage->rs1, stage->rs2,
				stage->imm, stage->pc, stage->fuType, stage->opcode);
		if (cpu->iq->addToIssueQueue(entry) == 1) {
//		cout << "entry added to IQ" << endl;
		}

		Rob_entry rob_entry;
		rob_entry.setPc_value(stage->pc);
		rob_entry.setArchiteture_register(stage->rd);
		rob_entry.setM_unifier_register(stage->u_rd);
		if (cpu->rob->add_instruction_to_ROB(rob_entry)) {
//		cout << "entry added to ROB" << endl;
		}

		if (!int_stage->stalled) {
			cpu->stage[INT_EX] = cpu->stage[DRF];
			//Print before removing it
			if (ENABLE_DEBUG_MESSAGES) {
				cout << "Details of RENAME TABLE (F-RAT) State --" << endl;
				cpu->urf->print_f_rat();
				cout << "---------------------------------------------" << endl;
				cout << "Details of RENAME TABLE (R-RAT) State --" << endl;
				cpu->urf->print_r_rat();
				cout << "---------------------------------------------" << endl;
				cout << "Details of IQ (Issue Queue) State --" << endl;
				cpu->iq->printIssueQueue();
			}
			cpu->iq->removeEntry(entry);

		}

	}
	return 0;
}

/*
 *  INT Function Unit Stage of APEX Pipeline
 */
int intFU(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[INT_EX];
	CPU_Stage * wb_stage = &cpu->stage[WB];
	if (!stage->busy && !stage->stalled) {

		if (strcmp(stage->opcode, "MOVC") == 0) {
			//Move the contents to the res[ective Unified register
			cpu->urf->URF_Table[stage->u_rd] = stage->imm;
			cpu->urf->URF_TABLE_valid[stage->u_rd] = 1;
		}

		if (strcmp(stage->opcode, "ADD") == 0) {
			cpu->urf->URF_Table[stage->u_rd] = cpu->urf->URF_Table[stage->u_rs1]
					+ cpu->urf->URF_Table[stage->u_rs2];
			cpu->urf->URF_TABLE_valid[stage->u_rd] = 1;
			//@TODO: Update ROB
		}

		if (ENABLE_DEBUG_MESSAGES) {
			print_stage_content("INT FU", stage);
			//TODO Empty this stage if the result has been calculated.
		}
	}
	return 0;
}

int mulFU(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[MUL_EX];
	if (!stage->busy && !stage->stalled) {

		if (ENABLE_DEBUG_MESSAGES) {
			print_stage_content("Execute", stage);
		}
	}
	return 0;
}

/*
 *  Memory Stage of APEX Pipeline
 *
 *  Note : You are free to edit this function according to your
 * 				 implementation
 */
int memFU(APEX_CPU* cpu) {
	CPU_Stage* stage = &cpu->stage[MEM_EX];
	if (!stage->busy && !stage->stalled) {

		if (ENABLE_DEBUG_MESSAGES) {
			print_stage_content("Memory", stage);
		}
	}
	return 0;
}

/*
 *  Retire Instruction Stage of APEX Pipeline (WB)
 */
int retireInstruction(APEX_CPU* cpu) {

	if (!cpu->rob->isempty()) {
		Rob_entry* headEntry = &cpu->rob->rob_queue[cpu->rob->head];
		int rd_status = headEntry->m_status;
		if (rd_status == 1) {
			headEntry->setslot_status(UNALLOCATED);

			//Dont free the register immediately unless it's renamer instruction comes.
			//Just update the register content to B-RAT

			cpu->urf->B_RAT[headEntry->m_architeture_register] =
					cpu->urf->URF_Table[headEntry->m_unified_register];
			cpu->rob->retire_instruction_from_ROB();

			cpu->ins_completed++;

			if (ENABLE_DEBUG_MESSAGES) {
				//TODO Print Retired Instruction using print guidelines
			}
		}
	}
	return 0;
}

/*
 *  APEX CPU simulation loop
 *
 *  Note : You are free to edit this function according to your
 * 				 implementation
 */
int APEX_cpu_run(APEX_CPU* cpu) {
	int i = 10;
	while (i > 0) {

		/* All the instructions committed, so exit */
		if (cpu->ins_completed == cpu->code_memory_size) {
			printf("(apex) >> Simulation Complete");
			break;
		}

		if (ENABLE_DEBUG_MESSAGES) {
			printf("\n\n\n\n\n");
			printf("--------------------------------\n");
			printf("Clock Cycle #: %d\n", cpu->clock);
			printf("--------------------------------\n");
		}

		retireInstruction(cpu);
		memFU(cpu);
		intFU(cpu);
		mulFU(cpu);
		addToQueues(cpu);
		decode(cpu);
		fetch(cpu);
		cpu->clock++;
		i--;
	}

	return 0;
}
