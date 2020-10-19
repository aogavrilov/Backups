//
// Created by Alexey on 19.10.2020.
//

#ifndef BACKUPS_RESTOREPOINT_H
#define BACKUPS_RESTOREPOINT_H

#include <vector>
#include <string>
using namespace std;

enum TypesOfPoints{
    FullPoint,
    IncrementPoint
};
class RestorePoint {
    vector<string> objects_list;
    TypesOfPoints type;
    size_t version;
    RestorePoint();
    void SavePointToLibrary(string name);
    void SavePointToBackup(string path, string name);
};


#endif //BACKUPS_RESTOREPOINT_H


