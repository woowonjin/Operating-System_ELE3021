#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

#define MAXARGS 10

int fork1(void);  // Fork but panics on failure.
void panic(char*);
struct cmd* custom_parsecmd(char*);

int running = 1;

struct cmd {
  int type;
  char* arg1;
  char* arg2;
};

void
runcmd(struct cmd *cmd)
{
  if(cmd == 0)
    exit();

  if(cmd->type == 0){
    list();
  }
  else if(cmd->type == 1){
      if(cmd->arg1 == 0){
        printf(2, "Input Fail\n");
      }
      if(kill(atoi(cmd->arg1)) == 0){
        printf(2, "Success to kill %d\n", atoi(cmd->arg1));
      }
      else{
        printf(2, "Fail to kill %d\n", atoi(cmd->arg1));
      }
  }
  else if(cmd->type == 2){
      if(cmd->arg1 == 0 || cmd->arg2 == 0){
        printf(2, "Wrong Input\n");
      }
      else{
        if(fork1() == 0){
            *(cmd->arg2-1) = 0;
            int n = exec2(cmd->arg1, &cmd->arg1, atoi(cmd->arg2));
            if(n == -1){
                printf(2, "Exec2 fail!!\n");
            }
            else{
                printf(1, "Success to exec2\n");
            }
        }
      }
  }
  else if(cmd->type == 3){
      if(cmd->arg1 == 0 || cmd->arg2 == 0){
        printf(2, "Wrong Input\n");
      }
      else{
        int n = setmemorylimit(atoi(cmd->arg1), atoi(cmd->arg2));
        if(n == -1){
            printf(2, "SetMemoryLimit Fail!!\n"); 
        }
        else{
            printf(1, "SetMemoryLimit Success!!\n");
        }
      }
  }
  else if(cmd->type == 4){
    running = 0;
    printf(2, "Bye!\n");
  }
  else{
    printf(2, "Wrong Command\n");
  }
}
struct cmd*
custom_parsecmd(char *s){
    struct cmd* command;
    command = malloc(sizeof(struct cmd));
    command->type = -1;
    memset(command, 0, sizeof(*command));
    memset(command->arg1, 0, sizeof(char*));
    memset(command->arg2, 0, sizeof(char*));

    char type[7];
    memset(type, 0, 7);
    int i = 0;
    int blank = 0;
    int idx = 0;
    while(1){
        if(s[i] == '\0'){
            break;
        }
        if(s[i] == ' '){
            if(blank == 0){
                type[idx] = '\0';
                command->arg1 = &s[i+1];
            }
            else if(blank == 1){
                command->arg2 = &s[i+1];
            }
            else{
                printf(1, "Input Error!!\n");
                exit();
            }
            blank++;
            idx = 0;
        }
        else{
            if(blank == 0){
               type[idx] = s[i]; 
            }
        }
        i++;
        idx++;
    }
    if(type[0] == 'l' && type[1] == 'i' && type[2] == 's' && type[3] == 't'){
        command->type = 0;
    }
    else if(type[0] == 'k' && type[1] == 'i' && type[2] == 'l' && type[3] == 'l'){
        command->type = 1;
    }
    else if(type[0] == 'e' && type[1] == 'x' && type[2] == 'e' && type[3] == 'c' && type[4] == 'u' && type[5] == 't' && type[6] == 'e'){
        command->type = 2;
    }
    else if(type[0] == 'm' && type[1] == 'e' && type[2] == 'm' && type[3] == 'l' && type[4] == 'i' && type[5] == 'm'){
        command->type = 3;
    }
    else if(type[0] == 'e' && type[1] == 'x' && type[2] == 'i' && type[3] == 't'){
        command->type = 4;
    }
    return command;
}

int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

void
panic(char *s)
{
  printf(2, "%s\n", s);
  exit();
}

int
main(void)
{
  static char buf[100];
  int fd;
  int admin = getadmin("2017029970");
  if(admin == -1){
      printf(1, "Password is not correct\n");
      exit();
  }
  printf(1, "[Process Manager]\n");        
  // Ensure that three file descriptors are open.
  while((fd = open("console", O_RDWR)) >= 0){
    if(fd >= 3){
      close(fd);
      break;
    }
  }
  
  while(running){
      gets(buf, 100);
      runcmd(custom_parsecmd(buf));
  }
  exit();
}
