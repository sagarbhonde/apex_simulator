//
// @author: sonu 
// @date: 12/3/18.
//

#include "URF.h"

URF::URF()
{

    memset(&F_RAT, GARBAGE, sizeof(F_RAT));
    memset(&B_RAT, GARBAGE, sizeof(F_RAT));
    memset(&URF_Table, GARBAGE, sizeof(URF_Table));

    // Initializing free list here.
    // 17 to 39.
    for(int start = 17; start<40; start++)
    {
        free_register_list.push(start);
    }

    // till 39& then 0 to 16.
    for(int start = 0; start<17; start++)
    {
        free_register_list.push(start);
    }
}

URF::~URF() {

}

bool URF::add_to_free_list(int reg) {

    free_register_list.push((reg));

    return true;
}

int URF::get_next_free_register() {

    int reg = -1;

    if(!free_register_list.empty())
    {
        reg = free_register_list.front();
        free_register_list.pop();
    }

    return reg;
}

URF &URF::operator=(const URF &urf) {
    if(this == &urf)
    {
        return *this;
    }
    else
    {
        copy(urf.B_RAT, urf.B_RAT + ARCHITECTURAL_REG_SIZE,  B_RAT);
        copy(urf.F_RAT, urf.F_RAT + ARCHITECTURAL_REG_SIZE,  F_RAT);
        copy(urf.URF_Table, urf.URF_Table + URF_SIZE,  URF_Table);
        free_register_list = urf.free_register_list;
    }
    return *this;
}

ostream& operator<<(ostream& out, const URF* urf)
{
    out<<"====================================================================="<<endl;

    out<<"     FRONT End Rename Table:   "<<endl;
    for(int i = 0 ;i<ARCHITECTURAL_REG_SIZE;i++)
    {
        out<<" | "<<i<<"  |  "<<urf->F_RAT[i]<<" |"<<endl;
    }
    out<<endl;

    out<<"     BACK End Rename Table:   "<<endl;
    for(int i = 0 ;i<ARCHITECTURAL_REG_SIZE;i++)
    {
        out<<" | "<<i<<"  |  "<<urf->B_RAT[i]<<" |"<<endl;
    }
    out<<endl;

    out<<"     UNIFIED REGISTER FILE   "<<endl;
    for(int i = 0 ;i<URF_SIZE;i++)
    {
        out<<" | "<<i<<"  |  "<<urf->URF_Table[i]<<" |"<<endl;
    }

    out<<"====================================================================="<<endl;

    return out;
}

URF URF::takeSnapshot() {
    URF urf_snap;

    copy(F_RAT, F_RAT + ARCHITECTURAL_REG_SIZE, urf_snap.F_RAT);
    copy(B_RAT, B_RAT + ARCHITECTURAL_REG_SIZE, urf_snap.B_RAT);
    copy(URF_Table, URF_Table + URF_SIZE, urf_snap.URF_Table);
    urf_snap.free_register_list = free_register_list;

    return urf_snap;
}
