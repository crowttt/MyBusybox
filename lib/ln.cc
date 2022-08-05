#include <iostream>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <assert.h>
#include <unistd.h>

#include "include.hpp"

using namespace std;
namespace fs = std::filesystem;

void softLink(string target, string linkName){
   assert(symlink(target.c_str(), linkName.c_str())==0);
}

void hardLink(string target, string linkName){
    assert(link(target.c_str(), linkName.c_str())==0);
}

int targetNotExist(string target){
    string file = target.substr(target.find_last_of("/\\") + 1);
    string path = target.substr(0, target.find_last_of("/\\"));
    if(file.compare(path) == 0){
        path = ".";
    }
    for (const auto & entry : fs::directory_iterator(path)){
        string fileNames = entry.path().u8string();
        string existFile = fileNames.substr(fileNames.find_last_of("/\\") + 1);
        if(file.compare(existFile) == 0){
            return 0;
        }
    }
    cout << "ln: failed to access " << file << ": No such file or directory" << endl;
    return 1;
}

int linkExist(string link, string target){
    if(link.find_last_of("/\\") == link.size()){
        link = link.substr(0, link.find_last_of("/\\")-1);
    }
    if(fs::is_directory(link)){
        string targetName = link.substr(link.find_last_of("/\\"));
        link = link + targetName;
    }
    string file = link.substr(link.find_last_of("/\\") + 1);
    string path = link.substr(0, link.find_last_of("/\\"));

    if(file.compare(path) == 0){
        path = ".";
    }

    for (const auto & entry : fs::directory_iterator(path)){
        string fileNames = entry.path().u8string();
        string existFile = fileNames.substr(fileNames.find_last_of("/\\") + 1);
        if(file.compare(existFile) == 0){
            cout << "ln: failed to create symbolic link" << file << ": File exists" << endl;
            return 1;
        }
    }
    return 0;

}

void argDeduplicate(vector<string>& argList){
    sort(argList.begin(), argList.end());
    argList.erase(unique(argList.begin(), argList.end()), argList.end());
}

void ln_main(vector<string> link, vector<string> argList){
    string target = link[0];
    string linkName = link[1];

    for(auto& arg : argList){
        if(arg.compare("symbolic") == 0){
            arg = "s";
        }
    }

    argDeduplicate(argList);
    if(linkExist(linkName, target) || targetNotExist(target)) return;

    if(find(argList.begin(), argList.end(), "s") == argList.end()){
        softLink(target, linkName);
    }
    else{
        hardLink(target, linkName);
    }
}