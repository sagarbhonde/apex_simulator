//
// @author: sonu gupta
// @date: 12/1/18.
//

#include "rob_entry.h"

Rob_entry::Rob_entry(){
    status = 0;
    pc_value = 0;
    architeture_register = 0;
    unifier_register_value = 0;
    excodes = 0;
    result = 0;
    slot_status = UNALLOCATED;
    CFID = -1;
    pv_saved_info = 0; // nullptr
}

Rob_entry::~Rob_entry() {
    delete (Rob_entry*)pv_saved_info;
}

int Rob_entry::getStatus() const {
    return status;
}

int Rob_entry::getArchiteture_register() const {
    return architeture_register;
}

int Rob_entry::getPc_value() const {
    return pc_value;
}

int Rob_entry::getResult() const {
    return result;
}

int Rob_entry::getUnifier_register_value() const {
    return unifier_register_value;
}

int Rob_entry::getExcodes() const {
    return excodes;
}

int Rob_entry::getslot_status() const {
    return slot_status;
}

int Rob_entry::getCFID() const {
    return CFID;
}

void *Rob_entry::getPv_saved_info() const {
    return pv_saved_info;
}

void Rob_entry::setPv_saved_info(void *pv_saved_info) {
    Rob_entry::pv_saved_info = pv_saved_info;
}

void Rob_entry::setCFID(int CFID) {
    Rob_entry::CFID = CFID;
}

void Rob_entry::setslot_status(SLOT_STATUS slot_status) {
    Rob_entry::slot_status = slot_status;
}

void Rob_entry::setExcodes(int excodes) {
    Rob_entry::excodes = excodes;
}

void Rob_entry::setUnifier_register_value(int unifier_register_value) {
    Rob_entry::unifier_register_value = unifier_register_value;
}

void Rob_entry::setResult(int result) {
    Rob_entry::result = result;
}

void Rob_entry::setPc_value(int pc_value) {
    Rob_entry::pc_value = pc_value;
}

void Rob_entry::setArchiteture_register(int architeture_register) {
    Rob_entry::architeture_register = architeture_register;
}

void Rob_entry::setStatus(int status) {
    Rob_entry::status = status;
}

Rob_entry &Rob_entry::operator=(const Rob_entry &entry) {

    if(this == &entry)
    {
        return *this;
    }
    else
    {
        status = entry.status;
        pc_value = entry.pc_value;
        architeture_register = entry.architeture_register;
        unifier_register_value = entry.unifier_register_value;
        excodes = entry.excodes;
        result = entry.result;
        slot_status = entry.slot_status;
        CFID = entry.getCFID();
        pv_saved_info = entry.pv_saved_info; //todo: need to assign memory/ shallow copy
    }

    return *this;
}

ostream& operator<<(ostream &out, const Rob_entry& entry)
{
    // Using this for logging purpose
    out<<"================================================"<<endl;
    out<<"status: "<<entry.getStatus()<<endl;
    out<<"pc_value: "<<entry.getPc_value()<<endl;
    out<<"architecture register: "<<entry.getArchiteture_register()<<endl;
    out<<"unified_register_value: "<<entry.getUnifier_register_value()<<endl;
    out<<"excodes: "<<entry.getExcodes()<<endl;
    out<<"result: "<<entry.getResult()<<endl;
    out<<"slot_status: "<<entry.getslot_status()<<endl;
    out<<"CFID: "<<entry.getCFID()<<endl;
    out<<"================================================"<<endl;

    return out;
}

