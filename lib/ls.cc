#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

#include "include.hpp"

using namespace std;
namespace fs = std::filesystem;

void deduplicate(vector<string>& argList){
    sort(argList.begin(), argList.end());
    argList.erase(unique(argList.begin(), argList.end()), argList.end());
}

void synoArgTrans(vector<string>& argList){
    for(auto& arg : argList){
        if(arg.compare("all") == 0){
            arg = "a";
        }
        else if(arg.compare("list") == 0){
            arg = "l";
        }
        else if(arg.compare("recursive") == 0){
            arg = "R";
        }
    }
}

string getPermission(fs::perms p, string path){
    stringstream perm;
    perm << (fs::is_directory(path) ? "d" : "-")
        << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        << '\t';
    return perm.str();
}

string getOwner(string path){
    struct stat info;
    stat(path.c_str(), &info);
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);
    stringstream owner;
    owner << pw->pw_name << "\t" << gr->gr_name << "\t";
    return owner.str();
}

string otherInfo(string path){
    struct stat info;
    time_t now = time(NULL);
    char buff[20];
    stat(path.c_str(), &info);
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

    stringstream otherInf;
    otherInf << buff << "\t" << info.st_size << "\t";
    return otherInf.str();
}


void ls_main(string path, vector<string> argList){
    synoArgTrans(argList);
    deduplicate(argList);

    vector<string> contents;
    for (const auto & entry : fs::directory_iterator(path)){
        string fileNames = entry.path().u8string();
        string relativeNames = fileNames.substr(fileNames.find_last_of("/\\") + 1);
        contents.push_back(relativeNames);
    }

    if(find(argList.begin(), argList.end(), "a") == argList.end()){
        auto hiddenFile = remove_if(contents.begin(), contents.end(), [](string file){ return file.front() == '.'; });
        contents.erase(hiddenFile, contents.end());
    }
    if(find(argList.begin(), argList.end(), "l") != argList.end()){
        for(auto& content : contents){
            string perm = getPermission(fs::status(path + "/" + content).permissions(), path + "/" + content);
            string owner = getOwner(path + "/" + content);
            string other = otherInfo(path + "/" + content);
            content = perm + owner + other + content;
        }
    }
    for(auto& content : contents){
        cout << content << endl;
    }
}