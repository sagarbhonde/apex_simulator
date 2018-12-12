/*true
 * IQEntry.cpp
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */

#include "IQEntry.h"
#include "helper.h"
using namespace std;

IQEntry::IQEntry(int rd, int rs1, int rs2, int imm, int pc, int fuType,
		char *opcode, int clock) {
	this->allocated = 0;
	this->pc = pc;
	this->fuType = fuType;
	this->src1Valid = 0;
	this->src2Valid = 0;
	this->src1 = rs1;      //src1 address
	this->src2 = rs2;      //src2 address
	this->lsqIndex = GARBAGE;
	this->literal = imm;
	strcpy(this->opcode, opcode);
	this->src1Value = GARBAGE;
	this->src2Value = GARBAGE;
	this->status = 0;
	this->rd = rd;
	this->clock = clock;
	this->CFID = -1;
}

int IQEntry::getStatus() const {
	if (allocated == 1) {
		if (strcmp("MOVC", this->opcode) == 0 || strcmp("BZ", this->opcode) == 0
				|| strcmp("BNZ", this->opcode) == 0)
			return 1;
		return src1Valid == 1 && src2Valid == 1 ? 1 : 0;
	}
	return 0;
}

void IQEntry::setStatus() {
	if (allocated == 1) {
		if (strcmp("MOVC", this->opcode) == 0 || strcmp("BZ", this->opcode) == 0
				|| strcmp("BNZ", this->opcode) == 0)
			this->status = 1;
		else if (src1Valid == 1 && src2Valid == 1)
			this->status = 1;

	}
}

void IQEntry::printIQEntryOP() {
	if (strcmp(this->opcode, "ADD") == 0 || strcmp(this->opcode, "SUB") == 0
			|| strcmp(this->opcode, "AND") == 0
			|| strcmp(this->opcode, "OR") == 0
			|| strcmp(this->opcode, "EX-OR") == 0) {
		cout << this->opcode << ",U" << this->rd << ",U" << this->src1 << ",U"
				<< this->src2 << endl;
	}
	if (strcmp(this->opcode, "MOVC") == 0) {
		cout << this->opcode << ",U" << this->rd << ",#" << this->literal
				<< endl;
	}
}

void IQEntry::printIQEntry() {
	cout << "Allocated: " << this->allocated << endl << "PC: " << this->pc
			<< endl << "FU Type: " << this->fuType << endl << "SRC1 valid: "
			<< this->src1Valid << endl << "SRC2 valid: " << this->src2Valid
			<< endl << "SRC1 address: " << this->src1 << endl
			<< "SRC2 address: " << this->src2 << endl << "LSQ index: "
			<< this->lsqIndex << endl << "Literal: " << this->literal << endl
			<< "OPCODE: " << this->opcode << endl << "SRC1 value: "
			<< this->src1Value << endl << "SRC2 value: " << this->src2Value
			<< endl << "Status: " << this->status << endl << endl;
	cout.flush();
}

bool IQEntry::operator<(IQEntry &i1) {

	return this->clock < i1.clock;
}
