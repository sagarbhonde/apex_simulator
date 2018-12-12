//
// @author: sonu 
// @date: 12/3/18.
//

#ifndef URF_URF_H
#define URF_URF_H

#include <queue>
#include <iostream>
#include <algorithm>
#include <string.h>
#include "helper.h"

struct URF_data{
    int B_RAT[ARCHITECTURAL_REG_SIZE]; // Back-end rename table
    int F_RAT[ARCHITECTURAL_REG_SIZE]; // Front-end rename table
    int URF_Table[URF_SIZE];           // Unified reg file.
    int URF_TABLE_valid[URF_SIZE];     // valid or not
    int URF_Z[URF_SIZE]; 				//zeroflag
    queue<int> free_register_list;
    int CFID;
    URF_data()
    {
        CFID = GARBAGE;
        memset(&F_RAT, GARBAGE, sizeof(F_RAT));
        memset(&URF_TABLE_valid, GARBAGE, sizeof(URF_TABLE_valid));
        memset(&B_RAT, GARBAGE, sizeof(B_RAT));
        memset(&URF_Table, GARBAGE, sizeof(URF_Table));
        memset(&URF_TABLE_valid, GARBAGE, sizeof(URF_TABLE_valid));
        memset(&URF_Z, GARBAGE, sizeof(URF_Z));
    }
};


class URF{
public:
    int B_RAT[ARCHITECTURAL_REG_SIZE]; // Back-end rename table
    int F_RAT[ARCHITECTURAL_REG_SIZE]; // Front-end rename table

    int URF_Table[URF_SIZE];           // Unified reg file.
    int URF_TABLE_valid[URF_SIZE];     // valid or not
    int URF_Z[URF_SIZE]; //zeroflag

    queue<int> free_register_list;                 // Free list(physical registers)

    URF();

    virtual ~URF();

    int get_next_free_register();

    bool add_to_free_list(int reg);

    URF& operator=(const URF& urf);

    friend ostream& operator<<(ostream& out, const URF* urf);

    void print_f_rat();

    void print_r_rat();

    void print_urf();

    URF_data* takeSnapshot(int cfid);

    int restoreSnapshot(URF_data urf_snap); // This will return CFID.

    };

#endif //URF_URF_H
