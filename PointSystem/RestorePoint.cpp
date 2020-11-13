//
// Created by Alexey on 19.10.2020.
//

#include "RestorePoint.h"
#include "../Exception.h"
#include <fstream>
#include <iostream>
#include <dir.h>
#include <ctime>
using namespace std;

void RestorePoint::SavePointToBackup(string path, string name) {
    ofstream file;
    file.open(path+name+"."+to_string(version));
    file << "Type=" << type << endl;
    for(auto iter = objects_list.begin(); iter != objects_list.end(); iter++){
        file << *iter << endl;
    }
}
int RestorePoint::GetSize() {
    return this->size;
}
void RestorePoint::SavePointToLibrary(string name) {
    ifstream InputFile("config.cfg");
    string LibraryPath;
    InputFile >> LibraryPath;

    if(LibraryPath.size() < 17)
        throw MyException("Some exception for invalid config");// В класс запилить!
    LibraryPath = LibraryPath.substr(18);
    mkdir(LibraryPath.c_str());

    ofstream file;
    file.open(LibraryPath + "\\" + name + "." + to_string(version));
    file << "Type=" << type << endl;
    for(auto iter = objects_list.begin(); iter != objects_list.end(); iter++){
        file << *iter << endl;
    }

}
int RestorePoint::GetVersion(){
    return version;
}
TypesOfPoints RestorePoint::GetType(){
    return type;
}
PointSavingType RestorePoint::GetSavingType() {
    return typesave;
}
void RestorePoint::SetVersion(int version) {
    this->version = version;
}
tm  RestorePoint::GetDate(){
    return ltm;
}