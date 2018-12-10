//
// @author: sonu 
// @date: 12/10/18.
//

#include "lsq_entry.h"

int LSQ_entry::getM_index() const {
    return m_index;
}

void LSQ_entry::setM_index(int m_index) {
    LSQ_entry::m_index = m_index;
}

int LSQ_entry::getM_status() const {
    return m_status;
}

void LSQ_entry::setM_status(int m_status) {
    LSQ_entry::m_status = m_status;
}

int LSQ_entry::getM_which_ins() const {
    return m_which_ins;
}

void LSQ_entry::setM_which_ins(int m_which_ins) {
    LSQ_entry::m_which_ins = m_which_ins;
}

int LSQ_entry::getM_memory_addr() const {
    return m_memory_addr;
}

void LSQ_entry::setM_memory_addr(int m_memory_addr) {
    LSQ_entry::m_memory_addr = m_memory_addr;
}

bool LSQ_entry::getM_is_memory_addr_valid() const {
    return m_is_memory_addr_valid;
}

void LSQ_entry::setM_is_memory_addr_valid(int m_is_memory_addr_valid) {
    LSQ_entry::m_is_memory_addr_valid = m_is_memory_addr_valid;
}

int LSQ_entry::getM_dest_reg() const {
    return m_dest_reg;
}

void LSQ_entry::setM_dest_reg(int m_dest_reg) {
    LSQ_entry::m_dest_reg = m_dest_reg;
}

int LSQ_entry::getM_store_reg() const {
    return m_store_reg;
}

void LSQ_entry::setM_store_reg(int m_store_reg) {
    LSQ_entry::m_store_reg = m_store_reg;
}

bool LSQ_entry::getM_store_src1_data_valid() const {
    return m_is_register_valid;
}

void LSQ_entry::setM_store_src1_data_valid(int m_is_register_valid) {
    LSQ_entry::m_is_register_valid = m_is_register_valid;
}

int LSQ_entry::getM_store_reg_value() const {
    return m_store_reg_value;
}

void LSQ_entry::setM_store_reg_value(int m_store_reg_value) {
    LSQ_entry::m_store_reg_value = m_store_reg_value;
}

LSQ_entry &LSQ_entry::operator=(const LSQ_entry &lsq) {

    if(this == &lsq)
    {
        return *this;
    }

    m_index = lsq.m_index;
    m_pc = lsq.m_pc;
    m_status = lsq.m_status;
    m_which_ins = lsq.m_which_ins;
    m_memory_addr = lsq.m_memory_addr;
    m_is_memory_addr_valid = lsq.m_is_memory_addr_valid;
    m_dest_reg = lsq.m_dest_reg;
    m_store_reg = lsq.m_store_reg;
    m_is_register_valid = lsq.m_is_register_valid;
    m_store_reg_value = lsq.m_store_reg_value;

    return *this;
}

ostream& operator<<(ostream& out, const LSQ_entry* lsq)
{
    out<<"m_index: "<<lsq->getM_index()<<endl;
    out<<"m_pc: "<<lsq->getM_pc()<<endl;
    out<<"m_status: "<<lsq->getM_status()<<endl;
    out<<"m_which_ins: "<<lsq->getM_which_ins()<<endl;
    out<<"m_memory_addr: "<<lsq->getM_memory_addr()<<endl;
    out<<"m_is_memory_addr_valid: "<<lsq->getM_is_memory_addr_valid()<<endl;
    out<<"m_dest_reg: "<<lsq->getM_dest_reg()<<endl;
    out<<"m_store_reg: "<<lsq->getM_store_reg()<<endl;
    out<<"m_is_register_valid: "<<lsq->getM_store_src1_data_valid()<<endl;
    out<<"m_store_reg_value: "<<lsq->getM_store_reg_value()<<endl;

    return out;
}

int LSQ_entry::getM_pc() const {
    return m_pc;
}

void LSQ_entry::setM_pc(int m_pc) {
    LSQ_entry::m_pc = m_pc;
}
