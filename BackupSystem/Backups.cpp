//
// Created by Alexey on 20.10.2020.
//

#include "Backups.h"

void Backups::AddBackup(Backup NewBackup){
    backups.push_back(NewBackup);
}

void Backups::DeleteBackup(int id){
    for(auto iter = backups.begin(); iter < backups.end(); iter ++){

        if(iter->GetID() == id){
            iter->PointsTrimmingByCount(0);
            //BackupFile.open();
            remove(("Backup" + to_string(id) + "\\BackUp.info").c_str());
            cout << "Backup" + to_string(id);
            int result = rmdir(("Backup" + to_string(id)).c_str());
            if(result)
                throw "Backup directory isn't empty!";//в класс ошибки
            backups.erase(iter);
        }
    }
}
void Backups::TrimmingByShape(size_t LimitSize) {
        for(auto iter = backups.begin(); iter < backups.end(); iter++){
            if(iter->GetSize() > LimitSize){
                DeleteBackup(iter->GetID());
            }
        }
}