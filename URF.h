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

    URF takeSnapshot();

    bool restoreSnapshot(URF urf_snap);

    };

#endif //URF_URF_H
