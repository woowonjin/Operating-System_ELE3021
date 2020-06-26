#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_useradd(void){
    char* username;
    char* password;
    if(argstr(0, &username) < 0 || argstr(1, &password) < 0){
        return -1;    
    }
    return useradd(username, password);
}
