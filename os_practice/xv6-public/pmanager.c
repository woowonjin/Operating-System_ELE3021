#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[]){
    int admin = getadmin("2017029970")
    if(admin == -1){
        printf(1, "Password is not correct\n");
        exit();
    }
    printf(1, "[Process Manager]\n");        
}
