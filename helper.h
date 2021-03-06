//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_HELPER_H
#define CIRCULAR_QUEUE_HELPER_H

#include <iostream>
#include <string.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define GARBAGE 2147483647

#define ROB_SIZE    36
#define GARBAGE 2147483647
#define ARCHITECTURAL_REG_SIZE  16
#define URF_SIZE  40
#define TRUE 1
#define FALSE 0
#define LSQ_SIZE 20
#define CFID_SIZE 8

enum Intruction_type
{
    ARITHMATIC
    ,LOGICAL
    ,MEMORY
    ,BRANCH
    ,MOV
    ,INVALID // Not supported
};

enum SLOT_STATUS
{
    //todo:need to discuss. dummy now
    EXECUTING,
    WAITING_FOR_INPUT,
    COMPLETED,
    UNALLOCATED,
    ALLOCATED
};

enum MISC
{
    VALID=1,
    LOAD,
    STORE
};

#endif //CIRCULAR_QUEUE_HELPER_H
