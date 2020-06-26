#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = { "sh", 0 };

struct user{
    char id[15];
    char pwd[15];
};

int main(int argc, char *argv[]){
    struct user list[10];
    for(int i = 0; i < 10; i++){
        memset(list[i].id, 0, 15);
        memset(list[i].pwd, 0, 15);
    }
    int fd;
    int success = 0;
    strcpy(list[0].id, "root");
    strcpy(list[0].pwd, "1234");
    if((fd = open("userlist", O_RDWR)) < 0){
        //file does not exist
        fd = open("userlist", O_CREATE | O_RDWR);
        write(fd, list[0].id, 15);
        write(fd, list[0].pwd, 15);
        close(fd);
    }
    close(fd);
    int pid, wpid;
    /*fd = open("userlist", O_RDWR);
    for(int i = 0; i < 10; i++){
        if(read(fd, list[i].id, 15) <= 0)
            break;
        if(read(fd, list[i].pwd, 15) <= 0)
            break;
    }
    close(fd);*/
    while(1){
        fd = open("userlist", O_RDWR);
        for(int i = 0; i < 10; i++){
            if(read(fd, list[i].id, 15) <= 0)
                break;
            if(read(fd, list[i].pwd, 15) <= 0)
                break;
        }
        close(fd);
        char name[15] = {0};
        char password[15] = {0};

        printf(1, "Username: ");
        gets(name, 15);

        printf(1, "Password: ");
        gets(password, 15);
        success = 0;
        name[strlen(name)-1] = '\0';
        password[strlen(password)-1] = '\0';
        for(int i = 0; i < 10; i++){
            if((strcmp(name,list[i].id) == 0) && (strcmp(password, list[i].pwd) == 0)){
                success = 1;
                break;
            }
        }
        if(success){
            pid = fork();
            if(pid < 0){
                printf(1, "init: fork failed\n");
                exit();
            }
            if(pid == 0){
                exec("sh", argv);
                printf(1, "init: exec sh failed\n");
                exit();
            }
            while((wpid=wait()) >= 0 && wpid != pid)
                printf(1, "zombie!\n");
        }
        else{
            printf(1, "Wrong login information\n");
        }
        success = 0;
        close(fd);
    }
}
