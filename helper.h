//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_HELPER_H
#define CIRCULAR_QUEUE_HELPER_H

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

#define ROB_SIZE    36


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
    EXEUTING,
    WAITING_FOR_INPUT,
    COMPLETED,
    UNALLOCATED
};

#endif //CIRCULAR_QUEUE_HELPER_H
