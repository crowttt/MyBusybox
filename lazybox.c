# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

char lazyBox_path[4096] = {0};

int lazyshall_main();

char** command_split(char* , char*);

int main(int args, char** argv){
    getcwd(&lazyBox_path[0], 4096);
    if (!strcmp(argv[0], "./lazybox")){
        lazyshall_main();
    }
    return 0;
}

int lazyshall_main(){
    char **cmd;
    while(1){
        printf("lazybox$ ");
        char command[4096];
        fgets(command, 4096, stdin);
        cmd = command_split(command, " ");

        if (!strcmp(cmd[0], "exit")){
            exit(0);
        }
        else if(!strcmp(cmd[0], "cd")){
            if(chdir(cmd[1]) != 0)
                printf("cd: no such file or directory: %s\n", cmd[1]);
        }
        else{
            system(command);
        }   
    }
}

char** command_split(char* cmd, char* delimiters){
    char** res = calloc(128, sizeof(char*));
    char* ptr_cmd;
    char** ptr_res;

    ptr_res = res;
    ptr_cmd = cmd;
    ptr_cmd = strtok(cmd, delimiters);
    while(ptr_cmd != NULL){
        *ptr_res = ptr_cmd;
        ptr_res = ptr_res + 1;
        ptr_cmd = strtok(NULL, delimiters);
    }
    ptr_res[-1][strlen(ptr_res[-1])-1] = '\0';
    return res;
}
