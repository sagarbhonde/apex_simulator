//
// @author: sonu gupta
// @date: 12/1/18.
//

#include "ROB.h"
#include "helper.h"
using namespace std;

int ROB::add_instruction_to_ROB(Rob_entry entry1) {
	Rob_entry entry = entry1;
	if (isFull()) {
		return false;
	} else if (isempty()) {
		head = tail = 0;
	} else {
		tail = (tail + 1) % size;   // tail++
	}

	// entry is added if and only if slot is UNALLOCATED

	if (entry.getslot_status() == UNALLOCATED) {

		entry.set_slot_id((tail)); // Assigning Slot ID here and then pushing in queue.
		rob_queue[tail] = entry;    // Adding to queue
		rob_queue[tail].setslot_status(ALLOCATED); // Mark slot status as 'ALLOCATED'
		pc_slot_map.insert(
				pair<int, int>(entry.getPc_value(), entry.get_slot_id())); // mapping pc -->slot id

	}
	return tail;
}

int ROB::get_slot_id_from_cfid(int cfid, int pc) {
	if (head == tail)
		if (rob_queue[head].m_pc_value == pc && rob_queue[head].m_CFID == cfid)
			return head;

	for (int i = head; i != tail; i++)
		if (rob_queue[i].m_pc_value == pc && rob_queue[i].m_CFID == cfid)
			return i;

	return -1;
}

int ROB::get_zero_flag_at_slot_id(int slot_id) {
	if (rob_queue[slot_id].allocated == ALLOCATED)
		return rob_queue[slot_id].m_excodes;
	return -1;
}

bool ROB::retire_instruction_from_ROB() {
	if (isempty()) {
		return false;
	} else {
		// When retiring, Mark slot status as 'UNALLOCATED'.
		rob_queue[head].setslot_status(UNALLOCATED);
		pc_slot_map.erase(rob_queue[head].getPc_value()); // remove from map

		// For Control Flow instructions, we had allocated memory for storing snapshot.
		// During retirement, we dont need it. So de-allocating that.

		if (rob_queue[head].m_pv_saved_info) {
			delete rob_queue[head].m_pv_saved_info;
			rob_queue[head].m_pv_saved_info = 0;
		}

		if (head == tail)    // Last element
				{
			head = tail = -1;

		} else {
			head = (head + 1) % size;       // head++
		}
	}
	return true;
}

ROB::ROB() {
	head = tail = -1;
	size = ROB_SIZE;
}

bool ROB::isFull() {
	if ((tail + 1) % size == head)
		return true;
	else
		return false;
}

bool ROB::check_with_rob_head(int pc_value) {
	return rob_queue[head].m_pc_value == pc_value;
}

bool ROB::isempty() {
	if (head == -1 && tail == -1)
		return true;
	else
		return false;
}

ROB::~ROB() {
}

void ROB::print_slot_contents(int index) {

	if (index == -1) {
		cout << "ROB is Empty" << endl;
	} else {
		cout << "Slot No: " << index << endl;
		cout << &rob_queue[index];
	}
}

ostream& operator<<(std::ostream& out, const ROB* rob) {
	out << " ** ROB Circular Buffer Data ** " << endl;
	for (int i = 0; i < ROB_SIZE; ++i) {
		out << "Slot No: " << i << endl;
		out << &rob->rob_queue[i] << endl;
	}
	return out;
}

void ROB::print_rob(int limit) {
	cout << " ** ROB Circular Buffer Data ** " << endl;
	for (int i = 0; i < limit; ++i) {
		cout << "Slot No: " << i << endl;
		cout << &rob_queue[i] << endl;
	}
}

bool ROB::update_ROB_slot(int pc_value, int unified_reg, int flag, int status,
		int result) {

	/*
	 // find the respective slot and update it.
	 map<int, int>::iterator itr;
	 itr = pc_slot_map.find(pc_value);
	 int slot_id = itr->second;

	 // get the entry at given slot index.

	 */

	int slot_id = get_slot_id_from_cfid(unified_reg, pc_value);
	Rob_entry* entry = &rob_queue[slot_id];

	if (entry->getslot_status() != UNALLOCATED) {
		// Check if UR is same.
//            entry->setUnifier_register_value(unified_reg_val); // Updating URF val
		entry->setExcodes(flag);

		// marking result as valid.
		entry->setStatus(status);
		entry->setResult(result);

		//@discuss: Since URF value is ready, Marking slot's status as COMPLETED.
		// other status WAITING, EXECUTING will be marked by respective stages.
		entry->setslot_status(COMPLETED);

	}

	return true;
}

bool ROB::flush_ROB_entries(int from_slot_id) {
	// Flushing ROB means, just setting status as unallocated for all instructions from head to tail as 'UNALLOCATED'.
	for (int next = from_slot_id + 1; next != tail; next++)
		rob_queue[next].setslot_status(UNALLOCATED);

	// update tail. So, when new instruction is added, new 'slot_id' will be assigned to it.
	tail = from_slot_id;
	return true;
}
