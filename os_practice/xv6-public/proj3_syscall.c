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

int sys_owner(void){
    char* username;
    if(argstr(0, &username) < 0){
        return -1;
    }
    return owner(username);
}

int sys_chmod(void){
    char* path;
    int mode;
    if((argstr(0, &path) < 0) || argint(1, &mode)){
        return -1;
    }
    return chmod(path, mode);

}
