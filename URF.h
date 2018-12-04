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

using namespace std;

#define ARCHITECTURAL_REG_SIZE  16
#define URF_SIZE  40

#define GARBAGE 99999

class URF{
public:
    int B_RAT[ARCHITECTURAL_REG_SIZE]; // Back-end rename table
    int F_RAT[ARCHITECTURAL_REG_SIZE]; // Front-end rename table
    int URF_Table[URF_SIZE];           // Unified reg file.

    queue<int> free_register_list;                 // Free list(physical registers)

    URF();

    virtual ~URF();

    int get_next_free_register();

    bool add_to_free_list(int reg);

    URF& operator=(const URF& urf);

    friend ostream& operator<<(ostream& out, const URF* urf);

    URF takeSnapshot();

    };

#endif //URF_URF_H
