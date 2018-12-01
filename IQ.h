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

using namespace std;

class IQ {

public:
	IQEntry issueQueue[IQ_SIZE];

	IQ();
	IQEntry getNextInstructionToIssue();
	int addToIssueQueue(IQEntry *iqEntry);
	int removeEntry(IQEntry * entry);
};


#endif /* IQ_H_ */
