//
// Created by Alexey on 19.10.2020.
//

#ifndef BACKUPS_RESTOREPOINT_H
#define BACKUPS_RESTOREPOINT_H

#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include "Enums"
using namespace std;


class RestorePoint {
    vector<string> objects_list;
    TypesOfPoints type;
    PointSavingType typesave;
    int version;
    tm ltm;
    size_t size;
public:
    RestorePoint(vector<string> objects, TypesOfPoints type, size_t version, PointSavingType typesave, size_t size) : objects_list(objects), type(type),
    version(version), typesave(typesave), size(size){
        time_t  now = time(0);
        ltm = *localtime(&now);
    };
    void SavePointToLibrary(string name);
    void SavePointToBackup(string path, string name);
    int GetVersion();
    void SetVersion(int version);
    int GetSize();
    TypesOfPoints GetType();
    PointSavingType GetSavingType();
    tm  GetDate();
};


#endif //BACKUPS_RESTOREPOINT_H


