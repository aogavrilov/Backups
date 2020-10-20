#include <iostream>

#include "PointSystem/RestorePoint.h"
#include "BackupSystem/Backup.h"
using namespace std;




int main() {
    Backup first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    vector<string> temp = first.RemoveObject("Backups.exe");
    first.CreatePoint(FullPoint, ToLibrary);
    first.CreatePoint(IncrementPoint, ToDirectory);
    first.CreatePoint(FullPoint, ToDirectory);

    Backup second = Backup({"Backups.cbo", "Backups.exe"}, 1);
    second.CreatePoint(FullPoint, ToLibrary);
    second.CreatePoint(FullPoint, ToLibrary);
    second.CreatePoint(FullPoint, ToDirectory);
//    for(auto iter = temp.begin(); iter != temp.end(); iter++){
  //      cout << *iter;
    //}
    return 0;
}
