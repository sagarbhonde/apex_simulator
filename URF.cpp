//
// @author: sonu 
// @date: 12/3/18.
//

#include "URF.h"
using namespace std;

URF::URF() {

	memset(&F_RAT, 0, sizeof(F_RAT));
	memset(&URF_TABLE_valid, 0, sizeof(URF_TABLE_valid));
	memset(&B_RAT, -1, sizeof(B_RAT));
	memset(&URF_Table, GARBAGE, sizeof(URF_Table));
	memset(&URF_Z, -1, sizeof(URF_Z));
	for (int i = 0; i < ARCHITECTURAL_REG_SIZE; i++) {
		F_RAT[i] = i;
//		B_RAT[i] = i;
	}

	// Initializing free list here.
	// 0 to 39.
	for (int start = 0; start < 40; start++) {
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

	if (!free_register_list.empty()) {
		reg = free_register_list.front();
		free_register_list.pop();
	}

	return reg;
}

URF &URF::operator=(const URF &urf) {
	if (this == &urf) {
		return *this;
	} else {
		copy(urf.B_RAT, urf.B_RAT + ARCHITECTURAL_REG_SIZE, B_RAT);
		copy(urf.F_RAT, urf.F_RAT + ARCHITECTURAL_REG_SIZE, F_RAT);
		copy(urf.URF_Table, urf.URF_Table + URF_SIZE, URF_Table);
		free_register_list = urf.free_register_list;
	}
	return *this;
}

void URF::print_f_rat() {
//	RAT[00] --> U0
	for (int i = 0; i < ARCHITECTURAL_REG_SIZE; i++) {
		cout << "RAT[" << i << "] --> U" << F_RAT[i] << "" << endl;
	}
}

void URF::print_r_rat() {

	for (int i = 0; i < ARCHITECTURAL_REG_SIZE; i++) {
		if (B_RAT[i] != -1)
			cout << "R-RAT[" << i << "] --> U" << B_RAT[i] << "" << endl;
	}
}

void URF::print_urf() {
	for (int i = 0; i < URF_SIZE; i++) {
		cout << " |U " << i << "       | ->    " << URF_Table[i] << " |";
		if(URF_Table[i] == -1)
		    cout<<" INVALID "<<endl;
		else
		    cout<<" VALID"<<endl;
	}

}

ostream& operator<<(ostream& out, const URF* urf) {
	out
			<< "====================================================================="
			<< endl;

	out << "     FRONT End Rename Table:   " << endl;
	for (int i = 0; i < ARCHITECTURAL_REG_SIZE; i++) {
		out << " | " << i << "  |  " << urf->F_RAT[i] << " |" << endl;
	}
	out << endl;

	out << "     BACK End Rename Table:   " << endl;
	for (int i = 0; i < ARCHITECTURAL_REG_SIZE; i++) {
		out << " | " << i << "  |  " << urf->B_RAT[i] << " |" << endl;
	}
	out << endl;

	out << "     UNIFIED REGISTER FILE   " << endl;
	for (int i = 0; i < URF_SIZE; i++) {
		out << " | " << i << "  |  " << urf->URF_Table[i] << " |" << endl;
	}

	out
			<< "====================================================================="
			<< endl;

	return out;
}

URF_data* URF::takeSnapshot(int cfid) {
	URF_data *urf_snap = new URF_data;

	urf_snap->CFID = cfid;
	copy(F_RAT, F_RAT + ARCHITECTURAL_REG_SIZE, urf_snap->F_RAT);
	copy(B_RAT, B_RAT + ARCHITECTURAL_REG_SIZE, urf_snap->B_RAT);
	copy(URF_Table, URF_Table + URF_SIZE, urf_snap->URF_Table);
	copy(URF_TABLE_valid, URF_TABLE_valid + URF_SIZE, urf_snap->URF_TABLE_valid);
	copy(URF_Z, URF_Z + URF_SIZE, urf_snap->URF_Z);
	urf_snap->free_register_list = free_register_list;

	return urf_snap;
}

int URF::restoreSnapshot(URF_data urf_snap) {

    copy(urf_snap.F_RAT, urf_snap.F_RAT + ARCHITECTURAL_REG_SIZE, F_RAT);
    copy(urf_snap.B_RAT, urf_snap.B_RAT + ARCHITECTURAL_REG_SIZE, B_RAT);
    copy(urf_snap.URF_Table, urf_snap.URF_Table + URF_SIZE, URF_Table);
    copy(urf_snap.URF_TABLE_valid, urf_snap.URF_TABLE_valid + URF_SIZE, URF_TABLE_valid);
    copy(urf_snap.URF_Z, urf_snap.URF_Z + URF_SIZE, URF_Z);
    free_register_list = urf_snap.free_register_list;

    return urf_snap.CFID;
}

