#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_yield(void){
    myproc()->queue_level = 0;
    myproc()->ticks = 0;
    yield();
    return 0;
}

int sys_getlev(void){
    return getlev();
}

int sys_setpriority(void){
    int pid;
    int priority;
    
    if(argint(0, &pid) < 0){
        return -1;
    }
    if(argint(1, &priority) < 0){
        return -1;
    }
    return setpriority(pid, priority);
}
