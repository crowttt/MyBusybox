#include <iostream>
#include <sys/stat.h>

#include "include.hpp"

using namespace std;

bool srcExist(string src){
    struct stat buffer;   
    return (stat(src.c_str(), &buffer) == 0);
}

bool distDirExist(string dist){

    if(dist.find_last_of("/\\") != string::npos){
        struct stat buffer;
        string path = dist.substr(0, dist.find_last_of("/\\"));
        return (stat(path.c_str(), &buffer) == 0);
    }
    return true;
}

void cp_main(string src, string dist){

    if(src.compare(dist) == 0){
        cout << "cp: " << src << "and " << dist << " are the same file";
    }

    if(!srcExist(src)){
        cout << "cp: cannot stat " << src << ": No such file or directory" << endl;
        return;
    }

    if(!distDirExist(dist)){
        cout << "cp: cannot create regular file " << dist << ": No such file or directory" << endl;
        return;
    }

    FILE* source = fopen(src.c_str(), "rb");
    FILE* distance = fopen(dist.c_str(), "wb");

    char ch;
    while(!feof(source))
    {
        fread(&ch, sizeof(char), 1, source);

        if(!feof(source))
        {
            fwrite(&ch, sizeof(char), 1, distance);
        }
    }

    fclose(source);
    fclose(distance);

}