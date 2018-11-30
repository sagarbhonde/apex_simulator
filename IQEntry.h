/*
 * IQEntry.h
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */


#include <cstdlib>

#ifndef IQENTRY_H_
#define IQENTRY_H_
using namespace std;

class IQEntry {
private:
	int status;
	int fuType;
	int src1Valid;
	int src2Valid;
	int src1Value;
	int src2Value;
	int src1;
	int src2;
	int lsqIndex;
public:
	//fuType
	void setFuType(int fuType);
	int getFuType() const;
	//lsqIndex
	int getLsqIndex() const;
	void setLsqIndex(int lsqIndex);
	//src1
	int getSrc1() const;
	void setSrc1(int src1);
	//src1Valid
	int getSrc1Valid() const;
	void setSrc1Valid(int src1Valid);
	//src1Value
	int getSrc1Value() const;
	void setSrc1Value(int src1Value);
	//src2
	int getSrc2() const;
	void setSrc2(int src2);
	//src2Valid
	int getSrc2Valid() const;
	void setSrc2Valid(int src2Valid);
	//src2Value
	int getSrc2Value() const;
	void setSrc2Value(int src2Value);
	//status
	int getStatus() const;
	void setStatus(int status);
};

#endif /* IQENTRY_H_ */
