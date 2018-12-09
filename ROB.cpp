//
// @author: sonu gupta
// @date: 12/1/18.
//

#include "ROB.h"
#include "helper.h"
using namespace std;

bool ROB::add_instruction_to_ROB(Rob_entry entry) {
    if(isFull()) {
        return false;
    }
    else if(isempty())
    {
        head = tail = 0;
    }
    else
    {
        tail = (tail+1)%size;   // tail++
    }

    // entry is added if and only if slot is UNALLOCATED

    if(entry.getslot_status() == UNALLOCATED) {

        entry.set_slot_id((tail)); // Assigning Slot ID here and then pushing in queue.
        rob_queue[tail] = entry;    // Adding to queue
        rob_queue[tail].setslot_status(ALLOCATED);  // Mark slot status as 'ALLOCATED'
        pc_slot_map.insert(pair<int,int>(entry.getPc_value(), entry.get_slot_id())); // mapping pc -->slot id

    }
    return true;
}

bool ROB::retire_instruction_from_ROB() {
    if(isempty())
    {
        return false;
    }
    else
    {
        // When retiring, Mark slot status as 'UNALLOCATED'.
        rob_queue[head].setslot_status(UNALLOCATED);
        pc_slot_map.erase(rob_queue[head].getPc_value()); // remove from map

        if(head == tail)    // Last element
        {
            head = tail = -1;

        }
        else
        {
            head = (head+1)%size;       // head++
        }
    }
    return true;
}

ROB::ROB()
{
    head = tail = -1;
    size = ROB_SIZE;
}

bool ROB::isFull() {
    if( (tail+1)%size == head)
        return true;
    else
        return false;
}

bool ROB::isempty() {
    if(head == -1 && tail == -1)
        return true;
    else
        return false;
}

ROB::~ROB() {
}

void ROB::print_slot_contents(int index) {

    if(index == -1)
    {
        cout<<"ROB is Empty"<<endl;
    }
    else
    {
        cout<<"Slot No: "<<index<<endl;
        cout<<rob_queue[index];
    }
}

ostream& operator<<(std::ostream& out, const ROB* rob)
{
    out<<" ** ROB Circular Buffer Data ** "<<endl;
    for(int i = 0; i < ROB_SIZE; ++i)
    {
        out<<"Slot No: "<<i<<endl;
        out<<rob->rob_queue[i]<<endl;
    }
    return out;
}

void ROB::print_rob(int limit)
{
    cout<<" ** ROB Circular Buffer Data ** "<<endl;
    for(int i = 0; i < limit; ++i)
    {
        cout<<"Slot No: "<<i<<endl;
        cout<<rob_queue[i]<<endl;
    }
}

bool ROB::update_ROB_slot(int pc_value, int unified_reg, int flag, int status, int result) {

    // find the respective slot and update it.
    map<int,int>::iterator itr;
    itr = pc_slot_map.find(pc_value);
    int slot_id = itr->second;

    // get the entry at given slot index.
    Rob_entry* entry = &rob_queue[slot_id];

    if(entry->getslot_status() != UNALLOCATED)
    {
        // Check if UR is same.
        if(entry->getM_unifier_register() == unified_reg) {
//            entry->setUnifier_register_value(unified_reg_val); // Updating URF val
            entry->setExcodes(flag);

            // marking result as valid.
            entry->setStatus(status);
            entry->setResult(result);

            //@discuss: Since URF value is ready, Marking slot's status as COMPLETED.
            // other status WAITING, EXECUTING will be marked by respective stages.
            entry->setslot_status(COMPLETED);
        }
    }
    else
    {
        return false;
    }

return true;
}

bool ROB::flush_ROB_entries() {
    // Flushing ROB means, just setting status as unallocated for all instructions from head to tail as 'UNALLOCATED'.
    for(int next = head+1; next != tail; next++)
        rob_queue[next].setslot_status(UNALLOCATED);

    // update tail. So, when new instruction is added, new 'slot_id' will be assigned to it.
    tail = head;

    return false;
}
