//
// @author: sonu 
// @date: 12/10/18.
//

#include "LSQ.h"
#include "lsq_entry.h"
#include "helper.h"
using namespace std;

/*returns slot id
 * if slot id = -1
 * 		couldn't insert into lsq
 */
int LSQ::add_instruction_to_LSQ(LSQ_entry entry) {
	if (isFull()) {
		return -1;
	} else if (isempty()) {
		head = tail = 0;
	} else {
		tail = (tail + 1) % size;   // tail++
	}

	// entry is added if and only if slot is UNALLOCATED

	if (entry.allocated == UNALLOCATED) {
		entry.setM_status(1);
		entry.setM_index((tail)); // Assigning Slot ID here and then pushing in queue.
		lsq_queue[tail] = entry;    // Adding to queue
		lsq_queue[tail].allocated = ALLOCATED; // Mark slot status as 'ALLOCATED'
		entry.allocated = ALLOCATED;
		pc_slot_map.insert(pair<int, int>(entry.getM_pc(), entry.getM_index())); // mapping pc -->index
	}
	return entry.getM_index();
}

LSQ_entry* LSQ::retire_instruction_from_LSQ() {

	LSQ_entry* entry;

	// Memory operation is performed here.

	if (isempty()) {
		return NULL;
	} else {
		entry = &lsq_queue[head];

		// When retiring, Mark slot status as 'UNALLOCATED'.
		lsq_queue[head].allocated = UNALLOCATED;
		pc_slot_map.erase(lsq_queue[head].getM_pc()); // remove from map

		if (head == tail)    // Last element
				{
			head = tail = -1;

		} else {
			head = (head + 1) % size;       // head++
		}
	}
	return entry;
}

void LSQ::flushLSQEntries(int cfid) {
	for (int i = 0; i < LSQ_SIZE; i++) {
		if (lsq_queue[i].CFID == cfid) {
			lsq_queue[i].allocated = 0;
		}
	}
}

LSQ::LSQ() {
	head = tail = -1;
	size = LSQ_SIZE;
}

bool LSQ::isFull() {
	if ((tail + 1) % size == head)
		return true;
	else
		return false;
}

bool LSQ::isempty() {
	if (head == -1 && tail == -1)
		return true;
	else
		return false;
}

LSQ::~LSQ() {
}

void LSQ::print_slot_contents(int index) {

	if (index == -1) {
		cout << "LSQ is Empty" << endl;
	} else {
		cout << "Slot No: " << index << endl;
		cout << &lsq_queue[index];
	}
}

ostream& operator<<(std::ostream& out, const LSQ* rob) {
	out << " ** LSQ Circular Buffer Data ** " << endl;
	for (int i = 0; i < LSQ_SIZE; ++i) {
		out << "Slot No: " << i << endl;
		out << &rob->lsq_queue[i] << endl;
	}
	return out;
}

void LSQ::print_lsq(int limit) {
	cout << " ** LSQ Circular Buffer Data ** " << endl;
	for (int i = 0; i < limit; ++i) {
		cout << "Slot No: " << i << endl;
		cout << &lsq_queue[i] << endl;
	}
}

bool LSQ::update_LSQ_index(int index, int status, int memory_address) {

	// find the respective slot and update it.
	LSQ_entry* entry = &lsq_queue[index];

	if (entry->allocated != UNALLOCATED) {
		// Check LOAD/STORE instruction based on it, update slots.
		int type = entry->getM_which_ins(); // LOAD/STORE
		entry->setM_memory_addr(memory_address);
		entry->setM_is_memory_addr_valid(status);
		entry->setM_status(1);
	} else
		return false;

	return true;
}

LSQ_entry *LSQ::check_head_instruction_from_LSQ() {
	LSQ_entry* entry;

	if (isempty()) {
		return NULL;
	} else {
		entry = &lsq_queue[head];
	}
	return entry;
}

