#define _POSIX_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#undef _POSIX_SOURCE
#include <unistd.h>
//rm -i 1.txt
//rm 1.txt
//rm -v 1.txt
void rem(char* filename, int op_v){
    if (access(filename, F_OK) == 0 ) {
        int status = remove(filename);
        /*Check if file has been properly deleted*/
        if (op_v == 1){
            if(status == 0){
                printf("Deleted successfully.\n");fflush(stdout);
            }
            else{
                printf("Unable to delete!\n");fflush(stdout);
            }
        }
        else if (status!=0){
            printf("Unable to delete!\n");fflush(stdout);
        }
        return;
    }
    else {
        if (op_v == 1){printf("Sorry! File doesn't exist\n");}
        return;
    }
}
int main(int argc, char* argv[]){
    if (argc == 1){printf("Filename not provided!");return 0;}
    if (strcmp(argv[1], "-i") == 0){
        char* perm[1];
        printf("Remove file '%s'? ", argv[1]);fflush(stdout);
        fscanf(stdin, "%c", perm[0]);
        if ((strcmp(perm[0], "y") == 0) || (strcmp(perm[0], "Y") == 0)){
            rem(argv[2], 0);
            return 0;
        }
        else{
            printf("Not removing...\n");
            fflush(stdout);
            return 0;
        }
    }
    else if (strcmp(argv[1], "-v") == 0){
        rem(argv[2], 1);
        return 0;
    }
    fflush(stdout);
    rem(argv[1], 0);
    return 0;
}