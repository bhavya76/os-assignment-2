#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#define _OPEN_THREADS
#define _XOPEN_SOURCE 600

//cd , echo, pwd
void* mysyscall(void* s1){
	char* p = s1;
	system((char*)s1);
	pthread_exit(NULL);
	//printf("reached\n");fflush(stdout);
}
char* mystrtok(char* s, char d)
{
    // Stores the state of string
    static char* input = NULL;
 
    // Initialize the input string
    if (s != NULL)
        input = s;
 
    // Case for final token
    if (input == NULL)
        return NULL;
 
    // Stores the extracted string
    char *result = malloc( sizeof(char) * (strlen(input) + 1 ) );
    // char* result = malloc(new char[strlen(input) + 1]);
    int i = 0;
    // Start extracting string and
    // store it in array
    for (i = 0 ; input[i] != '\0'; i++) {
 
        // If delimiter is not reached
        // then add the current character
        // to result[i]
        if (input[i] != d)
            result[i] = input[i];
 
        // Else store the string formed
        else {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
 
    // Case when loop ends
    result[i] = '\0';
    input = NULL;
 
    // Return the resultant pointer
    // to the string
    return result;
}
int main(int argc, char* argv[]){
    char* newstr = "";
    int ran_var = 0;
    char defvar[3000];
    char* ogdir = getcwd(defvar, sizeof(defvar));
    while(ran_var == 0){
        printf("shell>>");
        char inp_comm[2000];
        fgets(inp_comm, 2000, stdin);
        if ((strlen(inp_comm) > 0) && (inp_comm[strlen(inp_comm) - 1] == '\n')){inp_comm[strlen(inp_comm) - 1] = '\0';}
        if(!strcmp("", argv[0])) {continue;}
        int i = 0;
        char *ptr;
        ptr = strtok(inp_comm, " ");
        char* myargv[1000];
        int myargc = 0;
        while(ptr != NULL){
            myargv[i] = ptr;
            myargc++;
            i++;
            ptr = strtok(NULL, " ");
            }

        char* buffer = (myargc==1)?" " : myargv[1];
        if (strcmp(myargv[0], "exit") == 0){
            printf("Goodbye!\n");
            return 0;
        }
        if (strcmp(myargv[0],"echo") == 0){
            //echo hey
            //echo -n hey
            //echo --help
            if (myargc == 0){
                printf("Retry");fflush(stdout);
                continue;
            }
            else if (myargv[1] == NULL){
                printf("Retry!\n");fflush(stdout);
                continue;
            }
            if (strcmp(myargv[1], "-n") == 0){
                int i = 0;
                int j = 2;
                while(myargv[j+1]!=NULL){
                    printf("%s ", myargv[j]);
                    fflush(stdout);
                    i++;j++;
                }
                printf("%s", myargv[j]);fflush(stdout);
                continue;
                // printf("%s",myargv[j]);fflush(stdout);
                // continue;
            }
            else if (strcmp(myargv[1], "--help") == 0){
                printf("Echo returns the string of user's input.\n");fflush(stdout);
                printf("The syntax echo -n 'input_string' will return without a trailing new line.\n");fflush(stdout);
                continue;
            }
            else if (strcmp(myargv[1], "-E") == 0){
                int i = 0; int j = 1;
            //char dol = "$";
                while(myargv[j+1]!=NULL){
                    printf("%s ", myargv[2]);
                    fflush(stdout);
                    i++;j++;
                }   
                printf("%s\n",myargv[j]);fflush(stdout);
                continue;
            }
            int i = 0; int j = 1;
            if (myargc == 2){
                printf("%s\n", myargv[1]);
                fflush(stdout);
                continue;
            }
            while(myargv[j+1]!=NULL){
                printf("%s ", myargv[j]);
                fflush(stdout);
                i++;j++;
            }
            printf("%s\n",myargv[j]);fflush(stdout);
            continue;
        }
        else if (strcmp(myargv[0], "pwd") == 0){
            //pwd
            //pwd -l -->not working
            //pwd -p -->not wroking
            if(myargc == 2){
                if((strcmp(argv[1],"-L")==0)||(strcmp(argv[1], "-l") == 0)){
                    // printf("if\n");fflush(stdout);
                    char defvar[1000];
                    char* buf = getcwd(defvar, sizeof(defvar));
                    printf("%s\n", buf);
                    fflush(stdout);
                    }
                else if((strcmp(argv[1],"-P")==0)||(strcmp(argv[1], "-p") == 0)){
                    // printf("else if\n");fflush(stdout);
                    char *home=getenv("HOME");
                    printf("%s\n",home );
                }
            }
            else{
                // printf("checkk\n");fflush(stdout);
                char defvar[1000];
			    char* buf = getcwd(defvar, sizeof(defvar));
			    printf("%s\n", buf);
			    fflush(stdout);
                }
            continue;
		}
        else if (strcmp(myargv[0],"cd") == 0){
            //cd
            //cd ..
            //cd newdir
            int c = 0;
            if ((myargv[1] == NULL) || (myargc == 1)){
                int c = chdir(getenv("HOME"));
                continue;
            }
            else{
                c = chdir(myargv[1]);
                // printf("%d", c);fflush(stdout);
                // DIR* dir = opendir(myargv[1]);
                // if (dir) {
                //     closedir(dir);
                    
                // } else{
                //     printf("Directory does not exist!\n");fflush(stdout);
                // }
            }
            continue;
        }
        if (strcmp(myargv[0], "&t") == 0){
			if((strcmp(myargv[1], "date") == 0)||(strcmp(myargv[1], "mkdir") == 0)||(strcmp(myargv[1], "rm") == 0)||(strcmp(myargv[1], "ls") == 0)||(strcmp(myargv[1], "cat") == 0)){
		        char cmdstr[1000];
                char newtemp[1000];
                // printf("myargc = %d", myargc);
                for (int o = 1; o<myargc; o++){
                    strcat(newtemp, myargv[o]);
                    if (o<(myargc - 1)){strcat(newtemp, " ");}
                }
			    strcpy(cmdstr, ogdir);
			    strcat(cmdstr, "/");
                strcat(cmdstr, newtemp);
                // printf("cmdstr = [%s]", cmdstr);fflush(stdout);
				pthread_t tid;
				int t = pthread_create(&tid, NULL, mysyscall(cmdstr), NULL);
				int jo = pthread_join(tid, NULL);
				continue;
			}
			else{
				printf("Invalid command!\n");fflush(stdout);
                continue;
			}
        }
        int rc = fork();
        fflush(stdout);
        if (rc < 0) { // fork failed; exit
            fprintf(stderr, "fork failed\n");
            fflush(stdout);
            exit(1);
            }
        else if (rc == 0) { // child (new process)
            // if (!strcmp(argv[0], "exit")){break;}
            if (!strcmp(myargv[0],"date")){
                // printf("myargc = %d\n",myargc);fflush(stdout);
                char* argvnew[200];
                char* temp = ogdir;
                strcat(temp, "/date");
                argvnew[0] = temp;
                for(int j = 1; j<myargc; j++){
                    argvnew[j] = myargv[j];
                }
                // argvnew[myargc] = '\0';
                execvp(argvnew[0], argvnew);
                continue;
            }
            else if (!strcmp(myargv[0], "ls")){
                char* argvnew[2000];
                char* temp = ogdir;
                strcat(temp, "/ls");
                argvnew[0] = temp;
                // printf("[%s]\n",argvnew[0]);fflush(stdout);
                for(int j = 1; j<myargc; j++){
                    argvnew[j] = myargv[j];
                    // printf("[%s]\n",argvnew[j]);fflush(stdout);
                }                
                // printf("argvnew[0] = [%s]", argvnew[0]);fflush(stdout);
                execvp(argvnew[0], argvnew);
                // printf("%s\n", explain_errno_execvp(errno, argvnew[0], argvnew));
                // int errcode=errno;
                // printf("%d", errcode);fflush(stdout);
                // argc = 0;
                continue;
            }
            else if (!strcmp(myargv[0],"mkdir")){
                char* argvnew[20];
                char* temp = ogdir;
                strcat(temp, "/mkdir");
                argvnew[0] = temp;
                for(int j = 1; j<myargc; j++){
                    argvnew[j] = myargv[j];
                }
                // argvnew[argc] = 0;
                execvp(argvnew[0], argvnew);
                continue;
            }
            else if (!strcmp(myargv[0], "cat")){
                char* argvnew[20];
                char* temp = ogdir;
                strcat(temp, "/cat");
                argvnew[0] = temp;
                for(int j = 1; j<myargc; j++){
                    argvnew[j] = myargv[j];
                }
                execvp(argvnew[0], argvnew);
                continue;
            }
            else if (!strcmp(myargv[0], "rm")){
                char* argvnew[20];
                char* temp = ogdir;
                strcat(temp, "/rm");
                argvnew[0] = temp;
                for(int j = 1; j<myargc; j++){
                    argvnew[j] = myargv[j];
                }
                execvp(argvnew[0], argvnew);
                continue;
            }
            else{
                printf("Invalid command, try again\n");fflush(stdout);
                continue;
            }
        }
    else { // parent goes down this path (main)
        // printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());

        wait(NULL);
        fflush(stdout);
        }
    }
    fflush(stdout);
    return 0;
}