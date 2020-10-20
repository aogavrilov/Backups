//
// Created by Alexey on 19.10.2020.
//

#ifndef BACKUPS_RESTOREPOINT_H
#define BACKUPS_RESTOREPOINT_H

#include <vector>
#include <string>
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
public:
    RestorePoint(vector<string> objects, TypesOfPoints type, size_t version, PointSavingType typesave) : objects_list(objects), type(type),
    version(version), typesave(typesave){};
    void SavePointToLibrary(string name);
    void SavePointToBackup(string path, string name);
    int GetVersion();
    TypesOfPoints GetType();
    PointSavingType GetSavingType();
};


#endif //BACKUPS_RESTOREPOINT_H


