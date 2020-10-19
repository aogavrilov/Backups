//
// Created by Alexey on 19.10.2020.
//

#include "RestorePoint.h"
#include <fstream>
using namespace std;
/*
 *
 *  void SavePointToLibrary();
    void SavePointToBackup();
    vector<string> objects_list;
    TypesOfPoints type;
 */
void RestorePoint::SavePointToBackup(string path, string name) {
    ofstream file;
    file.open(path+name);
    for(auto iter = objects_list.begin(); iter != objects_list.end(); iter++){
        file << *iter << endl;
    }
}

void RestorePoint::SavePointToLibrary(string name) {
    ifstream InputFile("config.cfg");
    string LibraryPath;
    InputFile >> LibraryPath;
    LibraryPath = LibraryPath.substr(17);

    ofstream file;
    file.open(LibraryPath+name);
    for(auto iter = objects_list.begin(); iter != objects_list.end(); iter++){
        file << *iter << endl;
    }
}