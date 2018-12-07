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

IQEntry IQ::getNextInstructionToIssue() {
	IQEntry e;
	for(int i=0;i<IQ_SIZE; i++) {
		e = issueQueue[i];
		if(e.getStatus() == 1)
			return e;
	}
	return e;
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
int IQ::addToIssueQueue(IQEntry* entry) {
	int result = 0;
	int i = 0;
	while (result == 0 && i < IQ_SIZE) {
		if (issueQueue[i].allocated == 0) {
			entry->allocated = 1;
			issueQueue[i] = entry;
			result = 1;
		}
		i++;
	}
	return result;
}
