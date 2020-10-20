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
RestorePoint& Backup::CreatePoint(TypesOfPoints type, PointSavingType typesave, size_t PointSize){
    LastVersion++;
    RestorePoint NewPoint = RestorePoint(objects_address, type, LastVersion, typesave);
    points.push_back(NewPoint);
    BackupSize+=PointSize;
    UpdateBackupInfo();
    if(typesave == ToLibrary) {
        NewPoint.SavePointToLibrary(to_string(Id));
    }
    else {
        NewPoint.SavePointToBackup(AddressOfBackupPoints, to_string(Id));
    }


    return points[points.size()-1];
}
void Backup::UpdateBackupInfo() {
    ifstream InputFile("config.cfg");

    ofstream BackupFile;
    AddressOfBackupPoints = ("Backup" + to_string(this->Id) + "\\brp").c_str();
    BackupFile.open(("Backup" + to_string(this->Id) + "\\BackUp.info").c_str());
    BackupFile << "ID=" << Id << endl;
    time_t  now = time(0);
    tm* ltm = localtime(&now);

    BackupFile << "UpdationTime=" << ltm->tm_mday << "." << 1 + ltm->tm_mon << "." << 1900 + ltm->tm_year << endl;
    BackupFile << "BackupSize=" << BackupSize << endl;
}
Backup::Backup(vector<string> objects, size_t ID) : objects_address(objects), Id(ID){
    LastVersion = 0;
    BackupSize = 0;
    mkdir(("Backup" + to_string(this->Id)).c_str());
    ifstream InputFile("config.cfg");

    ofstream BackupFile;
    AddressOfBackupPoints = ("Backup" + to_string(this->Id) + "\\brp").c_str();
    BackupFile.open(("Backup" + to_string(this->Id) + "\\BackUp.info").c_str());
    BackupFile << "ID=" << Id << endl;
    time_t  now = time(0);
    tm* ltm = localtime(&now);

    BackupFile << "CreationTime=" << ltm->tm_mday << "." << 1 + ltm->tm_mon << "." << 1900 + ltm->tm_year << endl;
    BackupFile << "BackupSize=" << BackupSize << endl;
}
bool IsFirstDateNewiest(tm Date1, tm Date2){
    if(Date1.tm_year > Date2.tm_year)
        return 0;
    if((Date1.tm_year == Date2.tm_year) && (Date1.tm_mon > Date2.tm_mon))
        return 0;
    if((Date1.tm_year == Date2.tm_year) && (Date1.tm_mon == Date2.tm_mon) &&
       (Date1.tm_mday > Date2.tm_mday))
        return 0;
    return 1;
}
size_t Backup::PointsTrimmingByCount(size_t count){
    if(points.size() <= count)
        return 0;
    size_t delta = points.size() - count;
    size_t delta_0 = delta;
    size_t removed = 0;
    if(points[delta].GetType() == IncrementPoint){
        for(int i = delta; i > 0; i--){
            if(points[i].GetType() == FullPoint) {
                delta = i;
                break;
            }
        }
    }
    for(size_t i = 0; i < delta; i++){
        if(points[i - removed].GetSavingType() == ToDirectory)
            remove((AddressOfBackupPoints + to_string(Id) + "." + to_string(points[i - removed].GetVersion())).c_str());
        else {
            ifstream InputFile("config.cfg");
            string LibraryPath;
            InputFile >> LibraryPath;

            if(LibraryPath.size() < 17)
                throw("Undefined exception!");// В класс запилить!
            LibraryPath = LibraryPath.substr(18);
            remove((LibraryPath + "\\" + to_string(Id) + "." + to_string(points[i - removed].GetVersion())).c_str());
        }

        points.erase(points.begin() + i - removed);
        removed++;
    }
    return delta_0 - delta;
}

void Backup::PointsTrimmingByDate(tm *Date) {
    for(auto iter = points.begin(); iter < points.end(); iter++){
        if(IsFirstDateNewiest(*Date, iter->GetDate()))
            continue;
        if(iter->GetSavingType() == ToDirectory)
            remove((AddressOfBackupPoints + to_string(Id) + "." + to_string(iter->GetVersion())).c_str());
        else {
            ifstream InputFile("config.cfg");
            string LibraryPath;
            InputFile >> LibraryPath;
            if(LibraryPath.size() < 17)
                throw("Undefined exception!");// В класс запилить!
            LibraryPath = LibraryPath.substr(18);
            remove((LibraryPath + "\\" + to_string(Id) + "." + to_string(iter->GetVersion())).c_str());
            iter->SetVersion(-1);
        }
    }
    for(auto iter = points.begin(); iter < points.end(); iter++){
        if(iter->GetVersion() == -1){
            points.erase(iter);
        }
    }

    return;
}
size_t Backup::GetSize(){
    return BackupSize;
}
int Backup::GetID(){
    return Id;
}

void Backup::PointsTrimmingMixed(vector<bool> TypesOfTrimming, PointLimits TypeOfSelection, size_t count, tm* Date) {
    if(TypesOfTrimming.size() != 2)
        throw "Expected 2 params, found not 2";

    if((TypeOfSelection == JustAll) && (TypesOfTrimming[0] == 1)){

        if(points.size() <= count)
            return;
        size_t delta = points.size() - count;
        size_t delta_0 = delta;
        size_t removed = 0;
        if(points[delta].GetType() == IncrementPoint){
            for(int i = delta; i > 0; i--){
                if(points[i].GetType() == FullPoint) {
                    delta = i;
                    break;
                }
            }
        }
        for(size_t i = 0; i < delta; i++){
            if ((IsFirstDateNewiest(*Date, points[i - removed].GetDate())) && (TypesOfTrimming[1] == 1))
                continue;
            if(points[i - removed].GetSavingType() == ToDirectory) {
                remove((AddressOfBackupPoints + to_string(Id) + "." +
                        to_string(points[i - removed].GetVersion())).c_str());
            }
            else {
                ifstream InputFile("config.cfg");
                string LibraryPath;
                InputFile >> LibraryPath;

                if(LibraryPath.size() < 17)
                    throw("Undefined exception!");// В класс запилить!
                LibraryPath = LibraryPath.substr(18);
                remove((LibraryPath + "\\" + to_string(Id) + "." + to_string(points[i - removed].GetVersion())).c_str());
            }
            points.erase(points.begin() + i - removed);
            removed++;
        }
        return;

    }
    else if(TypeOfSelection == JustAll){
        PointsTrimmingByDate(Date);
    }
    else{
        PointsTrimmingByCount(count);
        PointsTrimmingByDate(Date);
    }
}
