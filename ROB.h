//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_H
#define CIRCULAR_QUEUE_ROB_H

#include "rob_entry.h"

class ROB
{
public:
    Rob_entry rob_queue[ROB_SIZE];

    int head;
    int tail;
    int size;

    //functions

    ROB();

    virtual ~ROB();

    bool add_instruction_to_ROB(Rob_entry entry);
    bool retire_instruction_from_ROB();
    bool update_ROB_slot(int slot_id, int unified_reg, int unified_reg_val, int flag);
    bool isFull();
    bool isempty();
    void print_slot_contents(int index); // For logging indivisual slot
    friend ostream& operator<<(ostream& out, const ROB* rob); // For logging whole ROB.
    bool flush_ROB_entries();
};

#endif //CIRCULAR_QUEUE_ROB_H
