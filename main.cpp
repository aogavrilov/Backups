#include <iostream>
#include "Exception.h"
#include "PointSystem/RestorePoint.h"

#include "BackupSystem/Trimming.h"
#include <cassert>
using namespace std;




int main() {

    ///=========================================================CASE 1===========================================================
    Backup first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    first.CreatePoint(FullPoint, ToLibrary, 345);
    //See to build/Backup0/point0.0 for files
    first.CreatePoint(FullPoint, ToLibrary, 54);
    PointsTrimmingByCount tr = PointsTrimmingByCount(first, 1);
    tr.FilterPointsForRemove();
    first = tr.Trim();

    assert(first.GetPoints().size() == 1);

    ///==============================================================CASE 2==============================
    Backup second = Backup({"Test.fd", "Thmd.md"}, 1);
    second.CreatePoint(FullPoint, ToLibrary,  100 * 1024 * 1024);
    second.CreatePoint(IncrementPoint, ToDirectory,  100 * 1024 * 1024);
    assert(second.GetPoints().size() == 2);
    PointsTrimmingByShape tr4 = PointsTrimmingByShape(second, 1.5 * 1024 * 1024 * 100);
    tr4.FilterPointsForRemove();
    second = tr4.Trim();
    assert(second.GetPoints().size() == 1);
    ///=================================================================CASE 3===================================
    first = Backup({"Backups.cbo", "Backups.exe"}, 0);
    vector<string> temp = first.RemoveObject("Backups.exe");
    first.CreatePoint(FullPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);
    first.CreatePoint(FullPoint, ToDirectory, 200);
    first.CreatePoint(IncrementPoint, ToLibrary, 200);
    first.CreatePoint(IncrementPoint, ToDirectory, 200);
    first.CreatePoint(IncrementPoint, ToLibrary, 100);
    first.CreatePoint(FullPoint, ToDirectory, 432);
    PointsTrimmingByCount tr5 = PointsTrimmingByCount(first, 2);
    tr5.FilterPointsForRemove();
    first = tr5.Trim();
    assert(first.GetPoints().size() == 5);

    ///=====================================================================CASE 4===================================

    ///:1
    Backup secod = Backup({"Backups.cbo", "Backups.exe", "gf.fd"}, 1);
    secod.CreatePoint(FullPoint, ToLibrary, 654);
    secod.CreatePoint(FullPoint, ToLibrary, 657);
    secod.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now = time(0);
    tm* lt = localtime(&now);
    lt->tm_mday -= 1;
    PointsTrimmingByCount tr11 = PointsTrimmingByCount(secod, 2);
    PointsTrimmingByShape tr12 = PointsTrimmingByShape(secod, 5000);
    PointsTrimmingByDate tr13 = PointsTrimmingByDate(secod, lt);

    secod = TrimmingMixed(secod, {&tr11, &tr12, &tr13}).Trim(AtLeastOne);
    assert(secod.GetPoints().size() == 1);

    ///:2
    Backup third = Backup({"Backups.cbo", "Backups.exe"}, 2);
    third.CreatePoint(FullPoint, ToLibrary, 654);
    third.CreatePoint(FullPoint, ToDirectory, 654);
    third.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now1 = time(0);
    tm* lt1 = localtime(&now1);
    lt1->tm_mday -=1;
    PointsTrimmingByCount tr31 = PointsTrimmingByCount(third, 2);
    PointsTrimmingByShape tr32 = PointsTrimmingByShape(third, 500);
    PointsTrimmingByDate tr33 = PointsTrimmingByDate(third, lt1);
    third = TrimmingMixed(third, {&tr31, &tr32, &tr33}).Trim(JustAll);
    assert(third.GetPoints().size() == 3);
    ///:3
    Backup fourth = Backup({"Backups.cbo", "Backups.exe"}, 3);
    fourth.CreatePoint(FullPoint, ToLibrary, 654);
    fourth.CreatePoint(FullPoint, ToDirectory, 654);
    fourth.CreatePoint(FullPoint, ToLibrary,7654);
    time_t  now2 = time(0);
    tm* lt2 = localtime(&now2);
    lt2->tm_mday +=3;
    PointsTrimmingByCount tr41 = PointsTrimmingByCount(fourth, 2);
    PointsTrimmingByShape tr42 = PointsTrimmingByShape(fourth, 500);
    PointsTrimmingByDate tr43 = PointsTrimmingByDate(fourth, lt2);
    fourth = TrimmingMixed(fourth, {&tr41, &tr42, &tr43}).Trim(JustAll);
    assert(fourth.GetPoints().size() == 2);

    ///:4

    Backup fifth = Backup({"Backups.cbo", "Backups.exe"}, 4);
    fifth.CreatePoint(FullPoint, ToLibrary, 654);
    fifth.CreatePoint(FullPoint, ToDirectory, 654);
    fifth.CreatePoint(FullPoint, ToLibrary,7654);
    PointsTrimmingByCount tr51 = PointsTrimmingByCount(fifth, 1);
    PointsTrimmingByShape tr52 = PointsTrimmingByShape(fifth, 500);
    PointsTrimmingByDate tr53 = PointsTrimmingByDate(fifth, lt2);
    fifth = TrimmingMixed(fifth, {&tr51, &tr52, &tr53}).Trim(JustAll);

    assert(fifth.GetPoints().size() == 3);

    ///:5

    Backup sixth = Backup({"Backups.cbo", "Backups.exe"}, 5);
    sixth.CreatePoint(FullPoint, ToLibrary, 654);
    sixth.CreatePoint(FullPoint, ToDirectory, 654);
    sixth.CreatePoint(FullPoint, ToLibrary,7654);
    PointsTrimmingByCount tr61 = PointsTrimmingByCount(sixth, 5);
    PointsTrimmingByShape tr62 = PointsTrimmingByShape(sixth, 500);
    PointsTrimmingByDate tr63 = PointsTrimmingByDate(sixth, lt);
    sixth = TrimmingMixed(sixth, {&tr61, &tr62, &tr63}).Trim(JustAll);

    assert(sixth.GetPoints().size() == 3);




    //console.TrimmingByShape(50000);

    return 0;

}
