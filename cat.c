#include <stdio.h>
#include <string.h>
#include <unistd.h>
//cat 1.txt
//cat -n 1.txt
//cat -E 1.txt
int main(int argc, char* argv[]){
    if (argc == 1){
        printf("Filename not provided\n");
        fflush(stdout);
        return 0;
        }
    if (argc>2){
        if(argv[1] == NULL){
            printf("Filename not provided.\n");
            fflush(stdout);
            return 0;
        }
        if (strcmp(argv[1], "-n") == 0){
            FILE* fop = fopen(argv[2], "r");
            if(access(argv[2], F_OK) != 0){
                printf("File '%s' does not exist!\n", argv[2]);fflush(stdout);
                return 0;
            }
            // if (!fop){
            //     printf("Empty file created\n");
            //     printf("Exitting\n");
            //     return 0;
            // }
            int cur;
            int linenum = 1;
            printf("%d)", linenum);
            fflush(stdout);
            while((cur = getc(fop)) != EOF){
                putchar(cur);
                fflush(stdout);
                if (cur == '\n'){
                    linenum = linenum + 1;
                    printf("%d)", linenum);
                    fflush(stdout);
                }
            }
            fclose(fop);
            return 0;
        }
        if (strcmp(argv[1], "-E") == 0){
            FILE* fop = fopen(argv[2], "r");
            if(access(argv[2], F_OK) != 0){
                printf("File '%s' does not exist!\n", argv[2]);fflush(stdout);
                return 0;
            }
            // if (!fop){
            //     printf("Empty file created\n");
            //     printf("Exitting\n");
            //     return 0;
            // }
            int cur;
            //char* cur;
            cur = getc(fop);
            printf("$");
            fflush(stdout);
            while((cur = getc(fop)) != EOF){
                putchar(cur);
                fflush(stdout);
                if (cur == '\n'){
                    printf("$");
                    fflush(stdout);
                    cur = getc(fop);
                }
            }
            fclose(fop);
            return 0;
        }
        for(int i = 1; i<=argc; i++){
            FILE* fop = fopen(argv[i], "r");
            if(access(argv[i], F_OK) != 0){
                printf("File '%s' does not exist!\n", argv[i]);fflush(stdout);
                return 0;
            }
            int cur;
            while((cur = getc(fop)) != EOF){
                putchar(cur);
                fflush(stdout);
            }
            fclose(fop);
        }
        return 0;
        
    }
    else{
        FILE* fop = fopen(argv[1], "r");
        int cur;
        //char* cur;
        fflush(stdout);
        while((cur = getc(fop)) != EOF){
            putchar(cur);
            fflush(stdout);
            }
        fclose(fop);
        return 0;
    }
}