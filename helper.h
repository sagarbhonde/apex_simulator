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
    EXEUTING,
    WAITING_FOR_INPUT,
    COMPLETED,
    UNALLOCATED,
    ALLOCATED
};

enum MISC
{
    VALID
};

#endif //CIRCULAR_QUEUE_HELPER_H
