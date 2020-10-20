#include <iostream>

#include "PointSystem/RestorePoint.h"

#include "BackupSystem/Backups.h"
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
    time_t  now = time(0);
    tm* lt = localtime(&now);
   // lt->tm_mday +=1;
    first.PointsTrimmingMixed({0, 1}, JustAll, 2, lt);
    Backups console = Backups({first, second});
    //console.TrimmingByShape(50000);

    return 0;
}
