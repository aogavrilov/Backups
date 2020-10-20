#include <iostream>

#include "PointSystem/RestorePoint.h"
#include "BackupSystem/Backup.h"
using namespace std;




int main() {
    Backup first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    vector<string> temp = first.RemoveObject("Backups.exe");
    first.CreatePoint(FullPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 100);
    first.CreatePoint(FullPoint, ToDirectory, 432);

    Backup second = Backup({"Backups.cbo", "Backups.exe"}, 1);
    second.CreatePoint(FullPoint, ToLibrary, 654);
    second.CreatePoint(FullPoint, ToLibrary, 654);
    second.CreatePoint(FullPoint, ToDirectory,7654);
//    for(auto iter = temp.begin(); iter != temp.end(); iter++){
  //      cout << *iter;
    //}
    return 0;
}
