/*
 * IQEntry.cpp
 *
 *  Created on: 30-Nov-2018
 *      Author: sagar
 */

#include "IQEntry.h"
using namespace std;

int IQEntry::getFuType() const {
	return fuType;
}

void IQEntry::setFuType(int fuType) {
	this->fuType = fuType;
}

int IQEntry::getLsqIndex() const {
	return lsqIndex;
}

void IQEntry::setLsqIndex(int lsqIndex) {
	this->lsqIndex = lsqIndex;
}

int IQEntry::getSrc1() const {
	return src1;
}

void IQEntry::setSrc1(int src1) {
	this->src1 = src1;
}

int IQEntry::getSrc1Valid() const {
	return src1Valid;
}

void IQEntry::setSrc1Valid(int src1Valid) {
	this->src1Valid = src1Valid;
}

int IQEntry::getSrc1Value() const {
	return src1Value;
}

void IQEntry::setSrc1Value(int src1Value) {
	this->src1Value = src1Value;
}

int IQEntry::getSrc2() const {
	return src2;
}

void IQEntry::setSrc2(int src2) {
	this->src2 = src2;
}

int IQEntry::getSrc2Valid() const {
	return src2Valid;
}

void IQEntry::setSrc2Valid(int src2Valid) {
	this->src2Valid = src2Valid;
}

int IQEntry::getSrc2Value() const {
	return src2Value;
}

void IQEntry:: setSrc2Value(int src2Value) {
	this->src2Value = src2Value;
}

int IQEntry:: getStatus() const {
	return status;
}

void setStatus(int status) {
	this->status = status;
}
