//
// @author: sonu 
// @date: 12/10/18.
//

#include "LSQ.h"
#include "helper.h"
using namespace std;

bool LSQ::add_instruction_to_LSQ(LSQ_entry entry) {
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

    if(entry.getM_status() == UNALLOCATED) {

        entry.setM_index((tail)); // Assigning Slot ID here and then pushing in queue.
        lsq_queue[tail] = entry;    // Adding to queue
        lsq_queue[tail].setM_status(ALLOCATED);  // Mark slot status as 'ALLOCATED'
        pc_slot_map.insert(pair<int,int>(entry.getM_pc(), entry.getM_index())); // mapping pc -->index
    }
    return true;
}

LSQ_entry* LSQ::retire_instruction_from_LSQ() {

    LSQ_entry* entry;

    // Memory operation is performed here.

    if(isempty())
    {
        return NULL;
    }
    else
    {
        entry = &lsq_queue[head];

        // When retiring, Mark slot status as 'UNALLOCATED'.
        lsq_queue[head].setM_status(UNALLOCATED);
        pc_slot_map.erase(lsq_queue[head].getM_pc()); // remove from map

        if(head == tail)    // Last element
        {
            head = tail = -1;

        }
        else
        {
            head = (head+1)%size;       // head++
        }
    }
    return entry;
}

LSQ::LSQ()
{
    head = tail = -1;
    size = LSQ_SIZE;
}

bool LSQ::isFull() {
    if( (tail+1)%size == head)
        return true;
    else
        return false;
}

bool LSQ::isempty() {
    if(head == -1 && tail == -1)
        return true;
    else
        return false;
}

LSQ::~LSQ() {
}

void LSQ::print_slot_contents(int index) {

    if(index == -1)
    {
        cout<<"LSQ is Empty"<<endl;
    }
    else
    {
        cout<<"Slot No: "<<index<<endl;
        cout<<&lsq_queue[index];
    }
}

ostream& operator<<(std::ostream& out, const LSQ* rob)
{
    out<<" ** LSQ Circular Buffer Data ** "<<endl;
    for(int i = 0; i < LSQ_SIZE; ++i)
    {
        out<<"Slot No: "<<i<<endl;
        out<<&rob->lsq_queue[i]<<endl;
    }
    return out;
}

void LSQ::print_lsq(int limit)
{
    cout<<" ** LSQ Circular Buffer Data ** "<<endl;
    for(int i = 0; i < limit; ++i)
    {
        cout<<"Slot No: "<<i<<endl;
        cout<<&lsq_queue[i]<<endl;
    }
}

bool LSQ::update_LSQ_index(int index, int status, int memory_address) {

    // find the respective slot and update it.
    LSQ_entry* entry = &lsq_queue[index];

    if(entry->getM_status() != UNALLOCATED)
    {
        // Check LOAD/STORE instruction based on it, update slots.
        int type = entry->getM_which_ins(); // LOAD/STORE
        entry->setM_memory_addr(memory_address);
        entry->setM_is_memory_addr_valid(status);
    }
    else
        return false;

    return true;
}

bool LSQ::flush_LSQ_entries() {
    // Flushing LSQ means, just setting status as unallocated for all instructions from head to tail as 'UNALLOCATED'.
    for(int next = head+1; next != tail; next++)
        lsq_queue[next].setM_status(UNALLOCATED);

    // update tail. So, when new instruction is added, new 'slot_id' will be assigned to it.
    tail = head;

    return false;
}

LSQ_entry *LSQ::check_head_instruction_from_LSQ() {
    LSQ_entry* entry;

    if(isempty())
    {
        return NULL;
    }
    else
    {
        entry = &lsq_queue[head];
    }
    return entry;
}

