//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_ENTRY_H
#define CIRCULAR_QUEUE_ROB_ENTRY_H

#include "helper.h"

class Rob_entry{
	int m_slot_id;        // used to update the ROB entry
    int m_status;         // indicates whether result is VALID or not
    int m_pc_value;       // pc value of instruction in code memory
    int m_excodes;        // conatins exception codes/ flags
    int m_CFID;           // Used for Conditinal isntructions
    int m_result;         // Computed result
    void* m_pv_saved_info;// pointer to structure having info about 'rename table' and 'URF'
    int m_architeture_register; // architectural register number [0-16]
    int m_unifier_register_value; // URF value
public:

    // Functions

    virtual ~Rob_entry();

    //@ note the sequence.
    Rob_entry(int status = 0, int pc_value = 0, int architeture_register = 0, int unifier_register_value = 0,
              int excodes = 0,int result = 0, int slot_status = UNALLOCATED, int CFID = -1, void* pv_saved_info = 0){
        m_status = status;
        m_pc_value = pc_value;
        m_architeture_register = architeture_register;
        m_unifier_register_value = unifier_register_value;
        m_excodes = excodes;
        m_result = result;
        m_slot_status = slot_status;
        m_CFID = CFID;
        m_pv_saved_info = pv_saved_info; // nullptr
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

    void setUnifier_register_value(int unifier_register_value);

    int getExcodes() const;

    void setExcodes(int excodes);

    int getslot_status() const;

    void setslot_status(SLOT_STATUS slot_status);

    int getCFID() const;

    void setCFID(int CFID);

    void *getPv_saved_info() const;

    void setPv_saved_info(void *pv_saved_info);

    Rob_entry& operator=(const Rob_entry& entry);

    friend ostream& operator<<(ostream &out, const Rob_entry& entry);

};

#endif //CIRCULAR_QUEUE_ROB_ENTRY_H
