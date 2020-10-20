//
// Created by Alexey on 19.10.2020.
//

#ifndef BACKUPS_RESTOREPOINT_H
#define BACKUPS_RESTOREPOINT_H

#include <vector>
#include <string>
#include <time.h>
#include <iostream>
using namespace std;

enum PointSavingType{
    ToLibrary,
    ToDirectory
};
enum TypesOfPoints{
    FullPoint,
    IncrementPoint
};
class RestorePoint {
    vector<string> objects_list;
    TypesOfPoints type;
    PointSavingType typesave;
    int version;
    tm ltm;
public:
    RestorePoint(vector<string> objects, TypesOfPoints type, size_t version, PointSavingType typesave) : objects_list(objects), type(type),
    version(version), typesave(typesave){
        time_t  now = time(0);
        ltm = *localtime(&now);
    };
    void SavePointToLibrary(string name);
    void SavePointToBackup(string path, string name);
    int GetVersion();
    void SetVersion(int version);
    TypesOfPoints GetType();
    PointSavingType GetSavingType();
    tm GetDate();
};


#endif //BACKUPS_RESTOREPOINT_H


