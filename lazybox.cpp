#include <iostream>
#include <unistd.h>
#include <vector>

#include "lib/include.hpp"

using namespace std;

int main(int args, char* argv[]){
    string exePath = argv[0];
    string exe = exePath.substr(exePath.find_last_of("/\\") + 1);

    if(exe.compare("ls") == 0){
        string path = ".";
        vector<string> argList;
        int argNum = args - 1;

        while(argNum--){
            string arg(*(++argv));
            if(arg.front() == '-'){
                if(arg.substr(2).find('-')!=string::npos){
                    cout << exe << ": invalid option -- '-'";
                    return 0;
                }
                if(arg[2]!='-' && arg.length() > 2){
                    for(int i=1;i<arg.length();++i){
                        argList.push_back(string(1, arg[i]));
                    }
                }
                else{
                    argList.push_back(arg.substr(arg.find_last_of("-") + 1));
                }
            }
            else{
                path = arg;
            }
        }
        ls_main(path, argList);
    }
    else if(exe.compare("ln") == 0){
        vector<string> argList;
        vector<string> link;
        int argNum = args - 1;
        while(argNum--){
            string arg(*(++argv));
            if(arg.front() == '-'){
                if(arg.substr(2).find('-')!=string::npos){
                    cout << exe << ": invalid option -- '-'";
                    return 0;
                }
                if(arg[2]!='-' && arg.length() > 2){
                    for(int i=1;i<arg.length();++i){
                        argList.push_back(string(1, arg[i]));
                    }
                }
                else{
                    argList.push_back(arg.substr(arg.find_last_of("-") + 1));
                }   
            }
            else{
                if(link.size() > 2){
                    cout << "ln: target 'secmybusybox' is not a directory" << endl;
                    return 0;
                }
                
                link.push_back(arg);
            }
        }
        ln_main(link, argList);
    }
    else if(exe.compare("cp") == 0){
        if(args > 3){
            cout << "too many arguments" << endl;
            return 0;
        }
        else if(args == 2){
            cout << "cp: missing destination file operand after " << argv[1] << endl;
            return 0;
        }
        else if(args == 1){
            cout << "cp: missing file operand" << endl;
            return 0;
        }
        string src(argv[1]);
        string dist(argv[2]);
        cp_main(src, dist);
    }

    return 0;
}