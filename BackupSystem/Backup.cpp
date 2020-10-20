#include <time.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Backup.h"
vector<string> Backup::GetObjects() {
    return objects_address;
}
vector<string> Backup::AddObject(string address) {
    //Проверка на существование и валидность пути
    if(std::find(objects_address.begin(), objects_address.end(), address) == objects_address.end()){
        objects_address.push_back(address);
    }
    return objects_address;
}
vector<string> Backup::RemoveObject(string address) {
    //Check for finding and validation patch of removing file
    if(std::find(objects_address.begin(), objects_address.end(), address) == objects_address.end()){
        return  objects_address;
    }

    for (auto it = objects_address.begin(); it != objects_address.end(); ++it) {
        if (*it == address) {
            objects_address.erase(it);
            break;
        }
    }

    return objects_address;
}
RestorePoint& Backup::CreatePoint(TypesOfPoints type, PointSavingType typesave){
    LastVersion++;
    RestorePoint NewPoint = RestorePoint(objects_address, type, LastVersion);
    points.push_back(NewPoint);
    BackupSize++;
    if(typesave == ToLibrary) {
        NewPoint.SavePointToLibrary(to_string(Id));
    }
    else {
        NewPoint.SavePointToBackup(AddressOfBackupPoints, to_string(Id));
    }

    return NewPoint;
}



Backup::Backup(vector<string> objects, size_t ID) : objects_address(objects), Id(ID){
    LastVersion = 0;
    mkdir(("Backup" + to_string(this->Id)).c_str());
    ifstream InputFile("config.cfg");

    ofstream BackupFile;
    AddressOfBackupPoints = ("Backup" + to_string(this->Id) + "\\brp").c_str();
    BackupFile.open(("Backup" + to_string(this->Id) + "\\BackUp.info").c_str());
    BackupFile << "ID=" << Id << endl;
    BackupFile << "CreationTime=" << "In Progress" << endl;

}
