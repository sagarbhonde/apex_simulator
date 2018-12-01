//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_H
#define CIRCULAR_QUEUE_ROB_H

#include "rob_entry.h"

class ROB
{
    Rob_entry rob_queue[ROB_SIZE];
public:

    int head;
    int tail;
    int size;

    //functions

    ROB();

    virtual ~ROB();

    bool add_instruction_to_ROB(Rob_entry entry);
    bool retire_instruction_from_ROB();
    bool isFull();
    bool isempty();
    void print_slot_contents(int index); // For logging indivisual slot
    friend ostream& operator<<(ostream& out, const ROB& rob); // For logging whole ROB .
};

#endif //CIRCULAR_QUEUE_ROB_H
