// memory
#include <stdio.h>
#include <string.h>

#include "../include/memory.h"
#include "../include/globals.h"

int find_free_memory(int size)
{
    int count = 0;

    for(int i = 0; i < MEMORY_SIZE; i++)
    {
        if(memory_used[i] == 0)
        {
            count++;

            if(count == size)
            {
                return i - size + 1;
            }
        }
        else
        {
            count = 0;
        }
    }

    return -1;
}

int load_program(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Error opening %s\n", filename);

        return -1;
    }

    Instruction temp[100];

    int size = 0;

    while(fscanf(fp, " %c", &temp[size].ins) == 1)
    {
        if(temp[size].ins == 'L')
        {
            fscanf(fp, "%s", temp[size].nome);

            temp[size].n = 0;
        }

        else if(temp[size].ins == 'B' ||
                temp[size].ins == 'T')
        {
            temp[size].n = 0;

            strcpy(temp[size].nome, "");
        }

        else
        {
            fscanf(fp, "%d", &temp[size].n);

            strcpy(temp[size].nome, "");
        }

        size++;
    }

    fclose(fp);

    int start = find_free_memory(size);

    if(start == -1)
    {
        printf("No memory available\n");

        return -1;
    }

    for(int i = 0; i < size; i++)
    {
        memory[start + i] = temp[i];

        memory_used[start + i] = 1;
    }

    printf("Program %s loaded at %d\n",
           filename,
           start);

    return start;
}

void free_program_memory(int start, int size)
{
    for(int i = 0; i < size; i++)
    {
        memory_used[start + i] = 0;

        memory[start + i].ins = ' ';

        memory[start + i].n = 0;

        strcpy(memory[start + i].nome, "");
    }
}

void execute_C_instruction(PCB *parent,
                           int jump)
{
    PCB child = *parent;

    child.pid = next_pid++;

    child.ppid = parent->pid;

    child.pc = parent->pc + 1;

    child.state = READY;

    pcb_table[process_count] = child;

    process_count++;

    parent->pc += jump;

    printf("Fork created: Parent %d -> Child %d\n",
           parent->pid,
           child.pid);
}

void execute_L_instruction(PCB *process,
                           const char *filename)
{
    free_program_memory(process->start,
                        process->program_size);

    int new_start = load_program(filename);

    if(new_start == -1)
    {
        return;
    }

    process->start = new_start;

    process->pc = new_start;

    strcpy(process->program_name,
           filename);

    printf("Process %d loaded %s\n",
           process->pid,
           filename);
}