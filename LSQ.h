//
// @author: sonu 
// @date: 12/10/18.
//

#ifndef LSQ_LSQ_H
#define LSQ_LSQ_H

#include "lsq_entry.h"
#include <queue>
#include <map>


class LSQ
{
public:
    LSQ_entry lsq_queue[LSQ_SIZE];
    map<int,int> pc_slot_map;

    int head;
    int tail;
    int size;

    LSQ();
    virtual ~LSQ();

    LSQ_entry* check_head_instruction_from_LSQ();
    int add_instruction_to_LSQ(LSQ_entry entry);//returns slot id
    LSQ_entry* retire_instruction_from_LSQ();  // gives the head instruction.
    bool update_LSQ_index(int index, int status, int memory_address);
    bool isFull();
    bool isempty();
    void print_slot_contents(int index); // For logging indivisual slot
    friend ostream& operator<<(ostream& out, const LSQ* lsq); // For logging whole ROB.
    void print_lsq(int limit);
    void flushLSQEntries(int cfid);
};

#endif //LSQ_LSQ_H
