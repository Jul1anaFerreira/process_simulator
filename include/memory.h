#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"

#define MEMORY_SIZE 1000

int find_free_memory(int size);

int load_program(const char *filename);

void free_program_memory(int start, int size);

void execute_C_instruction(PCB *parent, int jump);

void execute_L_instruction(PCB *process,
                           const char *filename);

void print_memory();

void execute_L_instruction(PCB *process,
                           const char *filename);

#endif
