#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


extern char* strcpy(char *s, const char *t);

int sys_useradd(void){
    char* username;
    char* password;
    if(argstr(0, &username) < 0 || argstr(1, &password) < 0){
        return -1;    
    }
    return useradd(username, password);
}

int sys_userdel(void){
    char* username;
    if(argstr(0, &username) < 0){
        return -1;
    }
    return userdel(username);
}

int sys_owner(char* username){
    strcpy(myproc()->owner, username);
    return 0;
}
