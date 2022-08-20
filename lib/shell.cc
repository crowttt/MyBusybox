#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "include.hpp"

void shell_main(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/bin/");
    rl_bind_key('\t', rl_complete);

    while(1) {
        char* command = readline("MyShell$  ");
        add_history(command);

        if (strncmp(command,"exit",4)==0){
            break;
        }
        else if(strncmp(command,"cd ",3)==0){
            char cd[10], dir[1024];
            sscanf(command,"%s %s" ,cd, dir );
            chdir(dir);
        }
        else {
            system((string(cwd) + string(command)).c_str());
        }

        free(command);
    }
}