// C program for implementation of Simulation 
#include <stdio.h> 
#include <limits.h>
#include <stdlib.h>
#include "process.h"
#include "util.h"

// Function to find the waiting time for all processes
void findWaitingTimeRR(ProcessType plist[], int n, int quantum) 
{ 
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = plist[i].bt;

    int t = 0;
    while (1) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    plist[i].wt = t - plist[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done) break;
    }
}

void findWaitingTimeSJF(ProcessType plist[], int n)
{ 
      /*
       * 1 Traverse until all process gets completely executed.
         - Find process with minimum remaining time at every single time lap.
         - Reduce its time by 1.
         - Check if its remaining time becomes 0 
         - Increment the counter of process completion.
         - Completion time of *current process = current_time +1;*
         - Calculate waiting time for each completed process. *wt[i]= Completion time - arrival_time-burst_time*
         - Increment time lap by one.
 
     */
} 

// Function to find the waiting time for all  
// processes 

void findWaitingTime(ProcessType plist[], int n)
{
    plist[0].wt = plist[0].art; 
    for (int i = 1; i < n; i++) 
        plist[i].wt = plist[i-1].bt + plist[i-1].wt; 
}

void findTurnAroundTime(ProcessType plist[], int n)
{
    for (int i = 0; i < n; i++) 
        plist[i].tat = plist[i].bt + plist[i].wt; 
}

int my_comparer(const void *this, const void *that)
{
    ProcessType *thisProc = (ProcessType *)this;
    ProcessType *thatProc = (ProcessType *)that;
    return thisProc->pri - thatProc->pri;
}

void findavgTimeFCFS(ProcessType plist[], int n)
{
    findWaitingTime(plist, n); 
    findTurnAroundTime(plist, n); 
    printf("\n*********\nFCFS\n");
}

void findavgTimeSJF(ProcessType plist[], int n)
{
    findWaitingTimeSJF(plist, n); 
    findTurnAroundTime(plist, n); 
    printf("\n*********\nSJF\n");
}

void findavgTimeRR(ProcessType plist[], int n, int quantum)
{
    findWaitingTimeRR(plist, n, quantum); 
    findTurnAroundTime(plist, n); 
    printf("\n*********\nRR Quantum = %d\n", quantum);
}

void findavgTimePriority(ProcessType plist[], int n)
{
    qsort(plist, n, sizeof(ProcessType), my_comparer);
    findWaitingTime(plist, n);
    findTurnAroundTime(plist, n);
    printf("\n*********\nPriority\n");
}

void printMetrics(ProcessType plist[], int n)
{
    int total_wt = 0, total_tat = 0; 
    float awt, att;
    printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n"); 
    for (int i = 0; i < n; i++) 
    { 
        total_wt += plist[i].wt; 
        total_tat += plist[i].tat; 
        printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
    } 
    awt = ((float)total_wt / (float)n);
    att = ((float)total_tat / (float)n);
    printf("\nAverage waiting time = %.2f", awt); 
    printf("\nAverage turn around time = %.2f\n", att); 
}

ProcessType *initProc(char *filename, int *n) 
{
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Invalid filepath\n");
        fflush(stdout);
        exit(0);
    }
    ProcessType *plist = parse_file(input_file, n);
    fclose(input_file);
    return plist;
}

int main(int argc, char *argv[]) 
{
    int n; 
    int quantum = 2;
    ProcessType *proc_list;

    if (argc < 2) {
        fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
        fflush(stdout);
        return 1;
    }

    // FCFS
    n = 0;
    proc_list = initProc(argv[1], &n);
    findavgTimeFCFS(proc_list, n);
    printMetrics(proc_list, n);

    // SJF
    n = 0;
    proc_list = initProc(argv[1], &n);
    findavgTimeSJF(proc_list, n); 
    printMetrics(proc_list, n);

    // Priority
    n = 0; 
    proc_list = initProc(argv[1], &n);
    findavgTimePriority(proc_list, n); 
    printMetrics(proc_list, n);

    // RR
    n = 0;
    proc_list = initProc(argv[1], &n);
    findavgTimeRR(proc_list, n, quantum); 
    printMetrics(proc_list, n);

    return 0; 
}
