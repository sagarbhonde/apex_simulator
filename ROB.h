//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_H
#define CIRCULAR_QUEUE_ROB_H

#include "rob_entry.h"
#include "helper.h"
#include <map>
class ROB
{
public:
    Rob_entry rob_queue[ROB_SIZE];
    map<int,int> pc_slot_map;

    int head;
    int tail;
    int size;

    //functions

    ROB();

    virtual ~ROB();

    int add_instruction_to_ROB(Rob_entry entry);
    bool retire_instruction_from_ROB();
    bool update_ROB_slot(int pc_value, int curr_cfid, int flag, int status, int result);
    bool isFull();
    bool isempty();
    void print_slot_contents(int index); // For logging indivisual slot
    friend ostream& operator<<(ostream& out, const ROB* rob); // For logging whole ROB.
    void print_rob(int limit);
    bool flush_ROB_entries(int from_slot_id,  void* cpu);
    bool check_with_rob_head(int pc_value);
    int get_slot_id_from_cfid(int cfid, int pc);
    int get_zero_flag_at_slot_id(int slot_id);
    Rob_entry* get_head_instruction_from_ROB();
    };

#endif //CIRCULAR_QUEUE_ROB_H
