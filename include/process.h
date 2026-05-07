#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 50

typedef enum {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
} ProcessState;

typedef struct {
    char ins;
    int n;
    char nome[50];
} Instruction;

typedef struct {
    int pid;
    int ppid;

    int pc;

    int start;
    int program_size;

    int variable;

    int priority;

    ProcessState state;

    int cpu_time_used;

    int start_time;
    int end_time;

    char program_name[50];

} PCB;

void execute_instruction(PCB *p, Instruction instr);
void execute_process(PCB *p, int quantum);
void context_switch(PCB *old_p, PCB *new_p);
void unblock_process();

#endif