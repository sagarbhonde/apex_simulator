//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_ENTRY_H
#define CIRCULAR_QUEUE_ROB_ENTRY_H

#include "helper.h"

class Rob_entry{
public:
	int m_slot_id;        // used to update the ROB entry
	int m_slot_status;    // indicated if slot is allocated or not
    int m_status;         // indicates whether result is VALID or not
    int m_pc_value;       // pc value of instruction in code memory
    int m_excodes;        // conatins exception codes/ flags
    int m_CFID;           // Used for Conditinal isntructions
    int m_result;         // Computed result
    void* m_pv_saved_info;// pointer to structure having info about 'rename table' and 'URF'
    int m_architeture_register; // architectural register number [0-16]
    int m_unified_register;


    // Functions

    virtual ~Rob_entry();

    //@ note the sequence.

    Rob_entry(){
        m_status = GARBAGE;
        m_slot_id = GARBAGE;
        m_pc_value = GARBAGE;
        m_architeture_register = GARBAGE;
        m_excodes = GARBAGE;
        m_result = GARBAGE;
        m_slot_status = UNALLOCATED;
        m_CFID = GARBAGE;
        m_pv_saved_info = 0; // nullptr
        m_unified_register = GARBAGE;
    }

    int getStatus() const;

    void setStatus(int status);

    int getArchiteture_register() const;

    void setArchiteture_register(int architeture_register);

    int getPc_value() const;

    void setPc_value(int pc_value);

    int getResult() const;

    void setResult(int result);

    int getUnifier_register_value() const;

    int getExcodes() const;

    void setExcodes(int excodes);

    int getslot_status() const;

    void setslot_status(SLOT_STATUS slot_status);

    int getCFID() const;

    void setCFID(int CFID);

    void *getPv_saved_info() const;

    void setPv_saved_info(void *pv_saved_info);

    Rob_entry& operator=(const Rob_entry& entry);

    friend ostream& operator<<(ostream &out, const Rob_entry* entry);

    int get_slot_id() const;

    void set_slot_id(int slot_id);

    int getM_unifier_register() const;

    void setM_unifier_register(int unified_register);

};

#endif //CIRCULAR_QUEUE_ROB_ENTRY_H
