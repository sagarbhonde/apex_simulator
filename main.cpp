/*
 *  main.c
 *
 *  Author :
 *  Gaurav Kothari (gkothar1@binghamton.edu)
 *  State University of New York, Binghamton
 */
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "IQ.h"
#include "ROB.h"

int
main(int argc, char const* argv[])
{
    if (argc != 4) {
        fprintf(stderr, "APEX_Help : Usage %s <input_file>\n", argv[0]);
        exit(1);
    }
    APEX_CPU* cpu = APEX_cpu_init(argv[1]);
    if (!cpu) {
        fprintf(stderr, "APEX_Error : Unable to initialize CPU\n");
        exit(1);
    }

    // print simulate and display logic
    int iAction = -1;
    if(strcmp(argv[2],"simulate") == 0)
    {
        iAction = 1;
    }
    else if(strcmp(argv[2],"display") == 0)
    {
        iAction = 2;
    }

    int cycles = atoi(argv[3]);
    APEX_cpu_run_for_cycles(cpu, cycles, iAction);
    APEX_cpu_stop(cpu);
    return 0;
}