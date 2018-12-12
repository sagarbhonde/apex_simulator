/*
 * IQ.h
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */

#ifndef IQ_H_
#define IQ_H_
#define IQ_SIZE 16
#include "IQEntry.h"
#include "vector"

using namespace std;

class IQ {

public:
	IQEntry issueQueue[IQ_SIZE];

	IQ();
	IQEntry getNextInstructionToIssue(int funType);
	int addToIssueQueue(IQEntry *iqEntry, int funType);
	int removeEntry(IQEntry * entry);
	void printIssueQueue();
	void updateIssueQueueEntries(int u_reg, int u_reg_value);
	IQEntry sortTemporary(IQEntry selected_entries[]);
	void flushIQEntries(int cfid);
};


#endif /* IQ_H_ */
