/*
 * IQ.cpp
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */

#include "IQ.h"
#include <iostream>
#include <string.h>
using namespace std;

IQ::IQ() {
	cout << "IQ Constructor called" << endl;
	memset(&issueQueue, 0, sizeof(IQEntry) * IQ_SIZE);
}

IQEntry IQ::getNextInstructionToIssue(int funType) {
	IQEntry e;
	for(int i=0;i<IQ_SIZE; i++) {
		e = issueQueue[i];
		if(e.getStatus() == 1 && e.fuType == funType)
			return e;
	}
	return e;
}

void IQ:: updateIssueQueueEntries(int u_reg, int u_reg_value) {
	for(int i = 0; i<IQ_SIZE; i++) {
		IQEntry e = issueQueue[i];
		if(e.allocated == 1) {
			if(e.src1 == u_reg) {
				e.src1Value = u_reg_value;
				e.src1Valid = 1;
			} else if(e.src2 = u_reg) {
				e.src2Value = u_reg_value;
				e.src1Valid = 1;
			}

			if(e.src1Valid && e.src2Valid) // If both the sources are ready, means isntruction is ready to execute.
				e.setStatus();
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
	int result = 0;
	int i = 0;
	while (result == 0 && i < IQ_SIZE) {
		if (issueQueue[i].pc == entry->pc) {
			issueQueue[i].allocated = 0;
			result = 1;
		}
	}
	return result;
}

void IQ:: printIssueQueue(){
	for(int i=0; i< IQ_SIZE; i++) {
		if(issueQueue[i].allocated == 1) {
			issueQueue[i].printIQEntryOP();
		}
	}
}

/*
 *  mark entry's allocated bit 1
 *  if result == 1 then entry is added else it is not
 * */
int IQ::addToIssueQueue(IQEntry* entry, int funType) {
	int result = 0;
	int i = 0;
	while (result == 0 && i < IQ_SIZE) {
		if (issueQueue[i].allocated == 0) {
			entry->allocated = 1;

			if(strcmp("MOVC", entry->opcode) == 0)
				entry->setStatus();
			issueQueue[i] = entry;
			result = 1;
		}
		i++;
	}
	return result;
}
