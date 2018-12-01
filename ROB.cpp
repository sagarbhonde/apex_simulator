//
// @author: sonu gupta
// @date: 12/1/18.
//

#include "ROB.h"

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

    rob_queue[tail] = entry;
    return true;
}

bool ROB::retire_instruction_from_ROB() {
    if(isempty())
    {
        return false;
    }
    else
    {
        if(head == tail)    // Last element
        {
            // Either memset or mark status bit as unallocated.
            //memset(&rob_queue[head], 0, sizeof(Rob_entry)); //@note: might cause memory issue
            rob_queue[head].setslot_status(UNALLOCATED);

            head = tail = -1;

        }
        else
        {
            // Either memset or mark status bit as unallocated.
            //memset(&rob_queue[head], 0, sizeof(Rob_entry)); // @note: might cause memory issue
            rob_queue[head].setslot_status(UNALLOCATED);

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

ostream& operator<<(ostream& out, const ROB& rob)
{
    out<<" ** ROB Circular Buffer Data ** "<<endl;
    for(int i = 0; i < ROB_SIZE; ++i)
    {
        cout<<"Slot No: "<<i<<endl;
        cout<<rob.rob_queue[i]<<endl;
    }
    return out;
}
