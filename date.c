#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
// ./date -u
// ./date
// ./date -r filename -- showing could not find file; will show wrong time as well because system time not set
void dispdate(time_t T, int op_u, int op_r, char* filename){
    if (op_r == 1){
        if(access(filename, F_OK) != 0){
            printf("File '%s' could not be found!\n", argv[2]);fflush(stdout);
            return;
        }
        struct stat filestat;
        int check = stat(filename,&filestat);
        // if(check != 0){
        //     // printf("errno = %d",errno);
        //     printf("Could not find file\n");
        //     fflush(stdout);
        //     return;
        // }
        //newline included in ctime() output //
        printf("File accessed last at time %s",ctime(&filestat.st_atime));fflush(stdout);
        printf("File modified last at time %s",ctime(&filestat.st_mtime));fflush(stdout);
        // printf("File changed time %s",ctime(&filestat.st_ctime));fflush(stdout);
        // printf("File birth time %s",ctime(&filestat.st_birthtime));fflush(stdout);
        return;
    }
    if (op_u == 1){
        struct tm utctm = *gmtime(&T);
        printf("UTC 2022\t");
        printf("System Date is: %02d/%02d/%04d\n", utctm.tm_mday, utctm.tm_mon + 1, utctm.tm_year + 1900);
        printf("System Time is: %02d:%02d:%02d\n", utctm.tm_hour, utctm.tm_min, utctm.tm_sec);
    }
    else{
        struct tm tm = *localtime(&T);
        printf("IST 2022\t");
        printf("System Date is: %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        printf("System Time is: %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    return;
}
int main(int argc, char* argv[])
{
    int op_u;
    int op_r;
    time_t T = time(NULL);
    
    if (argc == 1){
        dispdate(T, 0, 0, argv[0]);
        return 0;
    }
    else if (argc > 1){
        if (argv[1][0] == '-'){
            char *p = (char*)(argv[1] + 1);
            while(*p){
                if(*p == 'u') {op_u = 1;}
                else if(*p == 'r') {op_r = 1;}
                else{
                    printf("Invalid option\n");
                    fflush(stdout);
                    return -1;
                    }
                p++;
                }
            }
            dispdate(T, op_u, op_r, argv[2]);
            return 0;
        }
    fflush(stdout);
    return 0;
}