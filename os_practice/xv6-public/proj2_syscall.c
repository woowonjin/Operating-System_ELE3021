#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_getadmin(void){
    char* pwd;
    if(argstr(0, &pwd) < 0){
        return -1;    
    }
    return getadmin(pwd);
}

int sys_setmemorylimit(void){
    int pid, limit;
    if(argint(0, &pid) < 0){
        return -1;
    }
    if(argint(1, &limit) < 0){
        return -1;
    }
    return setmemorylimit(pid, limit);
}

int
sys_exec2(void)
{
  char *path, *argv[MAXARG];
  int i, stacksize;
  uint uargv, uarg;

  if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0 || argint(2, &stacksize) < 0){
    return -1;
  }
  memset(argv, 0, sizeof(argv));
  for(i=0;; i++){
    if(i >= NELEM(argv))
      return -1;
    if(fetchint(uargv+4*i, (int*)&uarg) < 0)
      return -1;
    if(uarg == 0){
      argv[i] = 0;
      break;
    }
    if(fetchstr(uarg, &argv[i]) < 0)
      return -1;
  }

  return exec2(path, argv, stacksize);
}
