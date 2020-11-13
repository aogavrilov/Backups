#include <iostream>
#include "Exception.h"
#include "PointSystem/RestorePoint.h"

#include "BackupSystem/Backups.h"
#include <cassert>
using namespace std;




int main() {

    ///=========================================================CASE 1===========================================================
    Backup first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    first.CreatePoint(FullPoint, ToLibrary, 345);
    //See to build/Backup0/point0.0 for files
    first.CreatePoint(FullPoint, ToLibrary, 54);
    first.PointsTrimmingByCount(1);


    assert(first.GetPoints().size() == 1);

    ///==============================================================CASE 2==============================
    Backup second = Backup({"Test.fd", "Thmd.md"}, 1);
    second.CreatePoint(FullPoint, ToLibrary,  100 * 1024 * 1024);
    second.CreatePoint(IncrementPoint, ToDirectory,  100 * 1024 * 1024);
    assert(second.GetPoints().size() == 2);
    assert(second.GetSize() == 2 * 100 * 1024 * 1024);
    second.PointsTrimmingByShape(1.5 * 1024 * 1024 * 100);
    assert(second.GetPoints().size() == 1);

    ///=================================================================CASE 3===================================
    second.PointsTrimmingByShape(0);

    first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    vector<string> temp = first.RemoveObject("Backups.exe");
    first.CreatePoint(FullPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);
    first.CreatePoint(FullPoint, ToDirectory, 200);
    first.CreatePoint(IncrementPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);
    first.CreatePoint(IncrementPoint, ToLibrary, 100);
    first.CreatePoint(FullPoint, ToDirectory, 432);

    assert(first.PointsTrimmingByCount(2) == 3);

    ///=====================================================================CASE 4===================================

    ///:1
    Backup secod = Backup({"Backups.cbo", "Backups.exe", "gf.fd"}, 1);
    secod.CreatePoint(FullPoint, ToLibrary, 654);
    secod.CreatePoint(FullPoint, ToLibrary, 657);
    secod.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now = time(0);
    tm* lt = localtime(&now);
    lt->tm_mday +=1;
    secod.PointsTrimmingMixed(JustAll, 2, 500, lt);
    assert(secod.GetPoints().size() == 2);


    ///:2
    Backup third = Backup({"Backups.cbo", "Backups.exe"}, 2);
    third.CreatePoint(FullPoint, ToLibrary, 654);
    third.CreatePoint(FullPoint, ToDirectory, 654);
    third.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now1 = time(0);
    tm* lt1 = localtime(&now1);
    lt1->tm_mday -=1;
    third.PointsTrimmingMixed(JustAll, 2, 500, lt1);
    assert(third.GetPoints().size() == 3);
    ///:3
    Backup fourth = Backup({"Backups.cbo", "Backups.exe"}, 3);
    fourth.CreatePoint(FullPoint, ToLibrary, 654);
    fourth.CreatePoint(FullPoint, ToDirectory, 654);
    fourth.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now2 = time(0);
    tm* lt2 = localtime(&now2);
    lt2->tm_mday +=3;
    fourth.PointsTrimmingMixed(JustAll, 2, 500, lt2);
    assert(fourth.GetPoints().size() == 2);

    ///:4

    Backup fifth = Backup({"Backups.cbo", "Backups.exe"}, 4);
    fifth.CreatePoint(FullPoint, ToLibrary, 654);
    fifth.CreatePoint(FullPoint, ToDirectory, 654);
    fifth.CreatePoint(FullPoint, ToLibrary,7654);
    fifth.PointsTrimmingMixed(JustAll, 1, 500, lt2);
    assert(fifth.GetPoints().size() == 3);

    ///:5

    Backup sixth = Backup({"Backups.cbo", "Backups.exe"}, 5);
    sixth.CreatePoint(FullPoint, ToLibrary, 654);
    sixth.CreatePoint(FullPoint, ToDirectory, 654);
    sixth.CreatePoint(FullPoint, ToLibrary,7654);
    sixth.PointsTrimmingMixed(JustAll, 5, 500, lt);
    assert(sixth.GetPoints().size() == 3);




    //console.TrimmingByShape(50000);

    return 0;

}
