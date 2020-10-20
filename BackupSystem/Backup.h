

#ifndef BACKUPS_BACKUP_H
#define BACKUPS_BACKUP_H

#include <time.h>
#include <vector>
#include "../PointSystem/RestorePoint.h"
#include <string>
#include <dir.h>
using namespace std;
enum PointSavingType{
    ToLibrary,
    ToDirectory
};
class Backup{
//To config: Global link for saving restore points!!!
    int Id;
    time_t CreationTime;
    size_t BackupSize;
    string AddressOfBackupPoints;
    int LastVersion;
    vector<RestorePoint> points;
    vector<string> objects_address;
public:
    Backup(vector<string> objects, size_t ID=1);
    ~Backup(){
        //rmdir(("Backup" + to_string(this->Id)).c_str());
    }
    vector<string> GetObjects(); // Хотел сделать указатель на вектор, но чтобы он мог быть использован только для чтения. Вопрос - как?
    vector<string> AddObject(string address);
    vector<string>  RemoveObject(string address);
    RestorePoint& CreatePoint(TypesOfPoints type, PointSavingType typesave);
    RestorePoint& SavePoint(PointSavingType type);
};


#endif //BACKUPS_BACKUP_H
