//
// Created by Alexey on 20.10.2020.
//

#ifndef BACKUPS_BACKUPS_H
#define BACKUPS_BACKUPS_H

//#include "../main.cpp"
#include "../BackupSystem/Backup.h"

using namespace std;
class Backups {
    vector<Backup> backups;
public:
    Backups(vector<Backup> backups) : backups(backups){};
    void AddBackup(Backup NewBackup);
    void DeleteBackup(int id);

};


#endif //BACKUPS_BACKUPS_H