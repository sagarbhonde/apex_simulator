//
// @author: sonu gupta
// @date: 12/1/18.
//

#include "rob_entry.h"

Rob_entry::~Rob_entry() {
    delete (Rob_entry*)m_pv_saved_info;
}

int Rob_entry::getStatus() const {
    return m_status;
}

int Rob_entry::getArchiteture_register() const {
    return m_architeture_register;
}

int Rob_entry::getPc_value() const {
    return m_pc_value;
}

int Rob_entry::getResult() const {
    return m_result;
}

int Rob_entry::getExcodes() const {
    return m_excodes;
}

int Rob_entry::getslot_status() const {
    return m_slot_status;
}

int Rob_entry::getCFID() const {
    return m_CFID;
}

void *Rob_entry::getPv_saved_info() const {
    return m_pv_saved_info;
}

void Rob_entry::setPv_saved_info(void *pv_saved_info) {
    Rob_entry::m_pv_saved_info = pv_saved_info;
}

void Rob_entry::setCFID(int CFID) {
    Rob_entry::m_CFID = CFID;
}

void Rob_entry::setslot_status(SLOT_STATUS slot_status) {
    Rob_entry::m_slot_status = slot_status;
}

void Rob_entry::setExcodes(int excodes) {
    Rob_entry::m_excodes = excodes;
}

void Rob_entry::setResult(int result) {
    Rob_entry::m_result = result;
}

void Rob_entry::setPc_value(int pc_value) {
    Rob_entry::m_pc_value = pc_value;
}

void Rob_entry::setArchiteture_register(int architeture_register) {
    Rob_entry::m_architeture_register = architeture_register;
}

void Rob_entry::setStatus(int status) {
    Rob_entry::m_status = status;
}

Rob_entry &Rob_entry::operator=(const Rob_entry &entry) {

    if(this == &entry)
    {
        return *this;
    }
    else
    {
        m_slot_id = entry.m_slot_id;
        m_status = entry.m_status;
        m_pc_value = entry.m_pc_value;
        m_architeture_register = entry.m_architeture_register;
        m_excodes = entry.m_excodes;
        m_result = entry.m_result;
        m_slot_status = entry.m_slot_status;
        m_CFID = entry.getCFID();
        m_pv_saved_info = entry.m_pv_saved_info; //todo: need to assign memory/ shallow copy
        m_unified_register = entry.m_unified_register;
    }

    return *this;
}

ostream& operator<<(ostream &out, const Rob_entry& entry)
{
    // Using this for logging purpose
    out<<"================================================"<<endl;
    out<<"slot_id: "<<entry.get_slot_id()<<endl;
    out<<"status: "<<entry.getStatus()<<endl;
    out<<"pc_value: "<<entry.getPc_value()<<endl;
    out<<"architecture register: "<<entry.getArchiteture_register()<<endl;
    out<<"excodes: "<<entry.getExcodes()<<endl;
    out<<"result: "<<entry.getResult()<<endl;
    out<<"slot_status: "<<entry.getslot_status()<<endl;
    out<<"m_CFID: "<<entry.getCFID()<<endl;
    out<<"m_unified_reg: "<<entry.getM_unifier_register()<<endl;
    out<<"================================================"<<endl;

    return out;
}

int Rob_entry::get_slot_id() const {
    return m_slot_id;
}

void Rob_entry::set_slot_id(int slot_id) {
    Rob_entry::m_slot_id = slot_id;
}

int Rob_entry::getM_unifier_register() const {
    return m_unified_register;
}

void Rob_entry::setM_unifier_register(int unified_register) {
    Rob_entry::m_unified_register = unified_register;
}

