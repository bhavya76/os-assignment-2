#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//ls
//ls -a --> not working
//ls -l --> not working
void lsf(const char *dir, int op_a, int op_l){
    fflush(stdout);
    struct dirent *d;
    DIR *dirread = opendir(dir);
    if (dirread == 0)
    {
        if (errno = ENOENT)
        {
            //If the directory is not found
            printf("Directory doesn't exist\n");
        }
        else
        {
            //If the directory is not readable then throw error and exit
            printf("Unable to read directory\n");
        }
        fflush(stdout);
        return;
    }
    //While the next entry is not readable we will print directory files
    while ((d = readdir(dirread)) != NULL)
    {
        if (op_a != 1){
            char check = '.';
            if((d->d_name)[0] == check){
                continue;
            }
            else{
                printf("%s  ", d->d_name);
                fflush(stdout);
                if(op_l){
                    printf("\n");
                    fflush(stdout);
                }
                continue;
            }
        }
        printf("%s  ", d->d_name);
        fflush(stdout);
        if(op_l) {
            printf("\n");
            fflush(stdout);
        }
    }
    printf("\n");
    fflush(stdout);
    return;
}
int main(int argc, const char *argv[]){
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);fflush(stdout);
        }
    else{
        printf("getcwd() failed\n");fflush(stdout);
    }
    // printf("entered ls\n");fflush(stdout);
    if (argc == 1){
        // printf("argc = 1\n");fflush(stdout);
        lsf(".",0,0);
        }
    else if (argc > 1){
        int op_a = 0, op_l = 0;
        //if (argv[1] == '--help'){} // explain functionality
        if (argv[1][0] == '-'){
            char *p = (char*)(argv[1] + 1);
            while(*p){
                if(*p == 'a') {op_a = 1;}
                else if(*p == 'l') {op_l = 1;}
                else{
                    printf("Invalid option\n");
                    fflush(stdout);
                    return -1;
                    }
                p++;
                }
            //lsf(".",op_a,op_l);
            }
            lsf(".",op_a,op_l);
        }
    fflush(stdout);
    return 0;
}