#include "types.h"
#include "stat.h"
#include "user.h"
int i = 0;

int main(int argc, char *argv[]){
    int pid;

    pid = fork();

    if(pid<0) exit();
    else if(pid != 0){
        while(i < 50){
            printf(1, "Hello World!\n");
            i++;
        }
        exit();
    }
    else {
        while(i < 100){
            printf(1, "Hello World!\n");
            i++;
        }
        exit();
    }
    exit();
}
