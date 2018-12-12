/*
 * IQEntry.h
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */
#include <iostream>
#include <cstdlib>
#include <string.h>

#define GARBAGE 2147483647
#ifndef IQENTRY_H_
#define IQENTRY_H_
using namespace std;

class IQEntry {
public:
	int status;    //status = 1 (Instruction is ready to dispatch) else not
	int allocated; //allocated = 1 (Slot is allocated) else free
	int pc;
	int fuType;    //enum value
	int src1Valid; //src1Valid = 1 (value of src1 is valid) else not
	int src2Valid; //src2Valid = 1 (value of src2 is valid) else not
	int src1Value;
	int src2Value;
	int src1;      //renamed src1 address
	int src2;      //renamed src2 address
	int rd;        //renamed rd address
	int lsqIndex;
	int literal;
	int clock;     // to decide earliest instruction to issue
	int CFID;
	int rob_slot_id;
	char opcode[128];

	//status
	int getStatus() const;
	//Default Constructor
	IQEntry() {
	}
	//Parameterized Constructor
	IQEntry(int rd, int rs1, int rs2, int imm, int pc, int fuType, char opcode[128],
			int clock);
	void printIQEntry();

	void printIQEntryOP();
	void setStatus();
	IQEntry* operator =(IQEntry *b) {
		this->allocated = b->allocated;
		this->pc = b->pc;
		this->rd = b->rd;
		this->fuType = b->fuType;
		this->src1Valid = b->src1Valid;
		this->src2Valid = b->src2Valid;
		this->src1 = b->src1;      //src1 address
		this->src2 = b->src2;      //src2 address
		this->lsqIndex = b->lsqIndex;
		this->literal = b->literal;
		strcpy(this->opcode, b->opcode);
		this->src1Value = b->src1Value;
		this->src2Value = b->src2Value;
		this->status = b->status;
		this->clock = b->clock;
		this->CFID = b->CFID;
		this->rob_slot_id = b->rob_slot_id;
		return this;
	}

	bool operator<(IQEntry &i1);

};

#endif /* IQENTRY_H_ */
