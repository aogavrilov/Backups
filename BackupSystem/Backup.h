//
// Created by Alexey on 19.10.2020.
//

#ifndef BACKUPS_BACKUP_H
#define BACKUPS_BACKUP_H

#include <time.h>
#include <vector>
#include "../PointSystem/RestorePoint.h"
#include <string>
using namespace std;
class Backup{

    size_t Id;
    time_t CreationTime;
    size_t BackupSize;
    vector<RestorePoint> points;
    vector<string> objects_address;
public:
    vector<string> GetObjects(); // Хотел сделать указатель на вектор, но чтобы он мог быть использован только для чтения. Вопрос - как?
    vector<string> AddObject(string address);
    vector<string>  RemoveObject(string address);

};


#endif //BACKUPS_BACKUP_H
