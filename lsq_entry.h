//
// @author: sonu 
// @date: 12/10/18.
//

#ifndef LSQ_LSQ_ENTRY_H
#define LSQ_LSQ_ENTRY_H

#include <iostream>
#include "helper.h"
using namespace std;

class LSQ_entry{
public:
    int m_index;
    int m_pc;
    int allocated; // indicates LSQ entry  is allocated/free
    int m_status;    //indicates if ready to execute
    int m_which_ins; // Load/Store?
    int m_memory_addr;  // memory address. This will be updated by IQ
    bool m_is_memory_addr_valid; // Is memory address valid?
    int m_dest_reg;         // for LOAD, its destination reg
    int m_store_reg;        //for STORE, src1
    bool m_is_register_valid; // for STORE, is src1 valid?
    int m_store_reg_value; // for STORE, src1 value.
    int CFID;
    LSQ_entry(int which_ins, int dest_reg, int store_reg, int store_reg_value, int is_store_reg_valid);

    LSQ_entry()
    {
        m_index = GARBAGE;
        m_status = GARBAGE;
        m_which_ins = GARBAGE;
        m_memory_addr = GARBAGE;
        m_is_memory_addr_valid = GARBAGE;
        m_dest_reg = GARBAGE;
        m_store_reg = GARBAGE;
        m_is_register_valid = GARBAGE;
        m_store_reg_value = GARBAGE;
        CFID = -1;
    }


    // methods
    int getM_index() const;

    void setM_index(int m_index);

    int getM_pc() const;

    void setM_pc(int m_pc);

    int getM_status() const;

    void setM_status(int m_status);

    int getM_which_ins() const;

    int getM_memory_addr() const;

    void setM_memory_addr(int m_memory_addr);

    void setM_which_ins(int m_which_ins);

    bool getM_is_memory_addr_valid() const;

    void setM_is_memory_addr_valid(int m_is_memory_addr_valid);

    int getM_store_reg_value() const;

    void setM_store_reg_value(int m_store_reg_value);

    bool getM_store_src1_data_valid() const;

    void setM_store_src1_data_valid(int m_is_register_valid);

    int getM_store_reg() const;

    void setM_store_reg(int m_store_reg);

    int getM_dest_reg() const;

    void setM_dest_reg(int m_dest_reg);

    LSQ_entry& operator=(const LSQ_entry& lsq);

    friend ostream& operator<<(ostream& out, const LSQ_entry* lsq);
};

#endif //LSQ_LSQ_ENTRY_H
