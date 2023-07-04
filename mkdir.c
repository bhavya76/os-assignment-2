#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//mkdir newdir
//mkdir -v newdir
//mkdir -m = rwx newdir
int main(int argc, char* argv[]){
    // char* temp = *argv[1][0];
        if (argc == 1){
            printf("Directory name not provided!");fflush(stdout);
            return 0;
        }
        if (!strcmp(argv[1],"-v")){
            int i = 2;
            while(i<argc && *argv[i]!='\n' && argv[i]!= NULL){
                // printf("argv[i] = [%s]\n", argv[i]);fflush(stdout);
                int res = mkdir(argv[i],0777);
                if (!res){printf("Successfully created directory %s!\n", argv[i]);}
                else{
                    printf("%s","Unable to create directory\n");
                    fflush(stdout);
                    printf("Now exitting\n");
                    fflush(stdout);
                    return 0;
                }
                i++;
            }
            return 0;
        }
        if (strcmp(argv[1],"-m") == 0){
            int res = mkdir(argv[4], *argv[3]);
            return 0;
        }
        else{
            for (int i = 1; i<argc; i++){
                int res = mkdir(argv[i],0777);
                if (!res){continue;}
                else{
                    printf("%s","Unable to create directory\n");
                    fflush(stdout);
                    printf("Now exitting\n");
                    fflush(stdout);
                    return -1;
                }
            }
            return 0;
        }
            // int i = 2;
            // while(i<argc && *argv[i]!='\n' && argv[i]!= NULL){
            //     int res = mkdir(argv[i],0777);
            //     if (!res){continue;}
            //     else{
            //         printf("%s","Unable to create directory\n");
            //         fflush(stdout);
            //         printf("Now exitting\n");
            //         fflush(stdout);
            //         return -1;
            //     }
            //     i++;
            // }
}
