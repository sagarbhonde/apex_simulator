/*
 * IQ.cpp
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */

#include "IQ.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>    // std::sort
using namespace std;

IQ::IQ() {
	cout << "IQ Constructor called" << endl;
	memset(&issueQueue, 0, sizeof(IQEntry) * IQ_SIZE);
}

IQEntry IQ::sortTemporary(IQEntry selected_entries[]) {
	IQEntry e;
	IQEntry key;
	int j = 0;

	for (int i = 1; i < sizeof(selected_entries) / sizeof(selected_entries[0]);
			i++) {
		key = selected_entries[i];
		j = i - 1;
		while (key < selected_entries[j] && j >= 0) {
			selected_entries[j + 1] = selected_entries[j];
			j -= 1;
		}
		selected_entries[j + 1] = key;
	}
	return selected_entries[0];
}

void IQ::flushIQEntries(int cfid, int pc) {
	for(int i = 0; i < IQ_SIZE; i++) {
		if(issueQueue[i].CFID == cfid) {
			if(issueQueue[i].pc == pc)
				continue;

			issueQueue[i].allocated = 0;
		}
	}
}

IQEntry IQ::getNextInstructionToIssue(int funType) {

	IQEntry tempArray[IQ_SIZE] = {};
	IQEntry temp;
	temp.allocated = 0;
	tempArray[0] = temp;
	IQEntry e;
	int j = 0;
	for (int i = 0; i < IQ_SIZE; i++) {
//		tempArray[i] = temp;
		e = issueQueue[i];
		if ((e.getStatus() == 1) && (e.fuType == funType) && (e.allocated == 1)) {
			tempArray[j] = e;
			j++;
		}
	}
	if (tempArray != 0) {
		IQEntry first = sortTemporary(tempArray);
		if(first.allocated == 1)
			return first;
	}
	return e;
}

void IQ::updateIssueQueueEntries(int u_reg, int u_reg_value) {
	for (int i = 0; i < IQ_SIZE; i++) {
		IQEntry *e = &issueQueue[i];
		if (e->allocated == 1) {
			if (e->src1 == u_reg) {
				e->src1Value = u_reg_value;
				e->src1Valid = 1;
			} else if (e->src2 == u_reg) {
				e->src2Value = u_reg_value;
				e->src1Valid = 1;
			}

			if (e->src1Valid && e->src2Valid) // If both the sources are ready, means isntruction is ready to execute.
				e->setStatus();
		}
	}
}

/*
 * for (IQEntry iq : issueQueue) {
 if (iq.getStatus() == 1)
 return iq;
 }
 return NULL;
 * */

/*
 * mark entry's allocated bit 0
 * if result == 1 then entry is removed else it is not
 * */
int IQ::removeEntry(IQEntry * entry) {
	IQEntry* temp;
	int result = 0;
	int i = 0;
	while (result == 0 && i < IQ_SIZE) {
		temp = &issueQueue[i];
		if (temp->pc == entry->pc) {
			temp->allocated = 0;
			result = 1;
		}
		i++;
	}
	return result;
}

void IQ::printIssueQueue() {
	for (int i = 0; i < IQ_SIZE; i++) {
		if (issueQueue[i].allocated == 1) {
			issueQueue[i].printIQEntryOP();
		}
	}
}

/*
 *  mark entry's allocated bit 1
 *  if result == 1 then entry is added else it is not
 * */
int IQ::addToIssueQueue(IQEntry* entry1, int funType) {
	IQEntry* entry = entry1;
	int result = 0;
	int i = 0;
	while (result == 0 && i < IQ_SIZE) {
		if (issueQueue[i].allocated == 0) {
			entry->allocated = 1;

			if (strcmp(entry->opcode, "MOVC") == 0
					|| strcmp(entry->opcode, "BZ") == 0
					|| strcmp(entry->opcode, "BNZ") == 0)
				entry->setStatus();
			issueQueue[i] = entry;
			result = 1;
		}
		i++;
	}
	return result;
}
