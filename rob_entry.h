//
// @author: sonu gupta
// @date: 12/1/18.
//

#ifndef CIRCULAR_QUEUE_ROB_ENTRY_H
#define CIRCULAR_QUEUE_ROB_ENTRY_H

#include "helper.h"

class Rob_entry{
    int status;         // indicates whether result is VALID or not
    int pc_value;       // pc value of instruction in code memory
    int excodes;        // conatins exception codes/ flags
    int CFID;           // Used for Conditinal isntructions
    int result;         // Computed result
    void* pv_saved_info;// pointer to structure having info about 'rename table' and 'URF'
    int architeture_register; // architectural register number [0-16]
    int unifier_register_value; // URF value
    int slot_status;    // Status whether slot is unallocated / executing / wating
public:

    // Functions

    virtual ~Rob_entry();

    Rob_entry();

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
