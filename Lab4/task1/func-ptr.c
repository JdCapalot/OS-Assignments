#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 0         //change this to 1 to enable verbose output

/**
 * Signature for an function pointer that can compare
 * You need to cast the input into its actual 
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer) (const void *a, const void *b);

/**
 * compares 2 processes
 * You can assume: 
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 */
int my_comparer(const void *this, const void *that)
{
    // Cast the void pointers to Process pointers
    const Process *process1 = (const Process *)this;
    const Process *process2 = (const Process *)that;

    // Calculate the difference in priorities
    int priority_difference = process1->priority - process2->priority;

    // Calculate the difference in arrival times
    int arrival_time_difference = process1->arrival_time - process2->arrival_time;

    // Return the priority difference unless they are equal, in which case return the arrival time difference
    return priority_difference ? priority_difference : arrival_time_difference;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
        fflush(stdout);
        return 1;
    }

    /*******************/
    /* Parse the input */
    /*******************/
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        fflush(stdout);
        return 1;
    }

    Process *processes = parse_file(input_file);

    /*******************/
    /* sort the input  */
    /*******************/
    Comparer process_comparer = &my_comparer;

#if DEBUG
    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d) ",
            processes[i].pid,
            processes[i].priority, processes[i].arrival_time);
    }
    printf("\n");
#endif

    qsort(processes, P_SIZE, sizeof(Process), process_comparer);

    /**************************/
    /* print the sorted data  */
    /**************************/

    for (int i = 0; i < P_SIZE; i++) {
        printf("%d (%d, %d)\n",
            processes[i].pid,
            processes[i].priority, processes[i].arrival_time);
    }
    fflush(stdout);
    fflush(stderr);

    /************/
    /* clean up */
    /************/
    free(processes);
    fclose(input_file);
    return 0;
}
