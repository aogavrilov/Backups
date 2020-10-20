#include <iostream>

#include "PointSystem/RestorePoint.h"
#include "BackupSystem/Backup.h"
using namespace std;




int main() {
    Backup first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    vector<string> temp = first.RemoveObject("Backups.exe");
    first.CreatePoint(FullPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);
    first.CreatePoint(FullPoint, ToDirectory, 200);
    first.CreatePoint(IncrementPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);

    first.CreatePoint(IncrementPoint, ToLibrary, 100);
    first.CreatePoint(FullPoint, ToDirectory, 432);

    Backup second = Backup({"Backups.cbo", "Backups.exe"}, 1);
    second.CreatePoint(FullPoint, ToLibrary, 654);
    second.CreatePoint(FullPoint, ToDirectory, 654);
    second.CreatePoint(FullPoint, ToLibrary,7654);

    first.PointsTrimmingByCount(2);
    return 0;
}
