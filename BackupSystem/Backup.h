

#ifndef BACKUPS_BACKUP_H
#define BACKUPS_BACKUP_H

#include <time.h>
#include <vector>
#include "../PointSystem/RestorePoint.h"
#include <string>
#include <dir.h>
#include <ctime>

using namespace std;
class Backup{
    time_t CreationTime;
    size_t BackupSize;
    int LastVersion;
    vector<RestorePoint> points = vector<RestorePoint>();
    vector<string> objects_address;
public:
    Backup(vector<string> objects, size_t ID=1);
    ~Backup(){}
    vector<string> GetObjects(); // Хотел сделать указатель на вектор, но чтобы он мог быть использован только для чтения. Вопрос - как?
    vector<string> AddObject(string address);
    vector<string>  RemoveObject(string address);
    RestorePoint& CreatePoint(TypesOfPoints type, PointSavingType typesave, size_t PointSize);
    void UpdateBackupInfo();
    int GetID();

    vector<RestorePoint> GetPoints();
    void SetPoints(vector<RestorePoint> points);
    size_t GetSize();

    string AddressOfBackupPoints;
    int Id;
};


#endif