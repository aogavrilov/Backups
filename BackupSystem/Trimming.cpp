//
// Created by Alexey on 20.10.2020.
//

#include <fstream>
#include "Trimming.h"
#include "../Exception.h"
bool IsFirstDateNewest(tm Date1, tm Date2){
    if(Date1.tm_year > Date2.tm_year)
        return 0;
    if((Date1.tm_year == Date2.tm_year) && (Date1.tm_mon > Date2.tm_mon))
        return 0;
    if((Date1.tm_year == Date2.tm_year) && (Date1.tm_mon == Date2.tm_mon) &&
       (Date1.tm_mday > Date2.tm_mday))
        return 0;
    return 1;
}
vector<bool> PointsTrimmingByCount::FilterPointsForRemove(){
    vector<RestorePoint> points = backup.GetPoints();
    vector<bool> result = vector<bool>(points.size(), false);
    if(points.size() <= count)
        throw MyException("Error");
    size_t delta = points.size() - count;
    size_t delta_0 = delta;
    size_t removed = 0;
    if(points[delta].GetType() == IncrementPoint){
        for(int i = delta; i > 0; i--){
            if(points[i].GetType() == FullPoint) {
                delta = i;
                break;
            }
        }
    }
    for(size_t i = 0; i < delta; i++){
        result[i - removed] = true;
    }
    bools = result;
    return result;
}
vector<bool> PointsTrimmingByDate::FilterPointsForRemove() {
    vector<RestorePoint> points = backup.GetPoints();
    vector<bool> result = vector<bool>(points.size(), false);
    auto it = points.begin();
    while (it < points.end()) {
        if(IsFirstDateNewest(*Date, it->GetDate())) {
            it++;
            continue;
        }
        result[it - points.begin()] = true;
        it++;
    }
    bools = result;
    return result;
}
vector<bool> PointsTrimmingByShape::FilterPointsForRemove() {
    vector<RestorePoint> points = backup.GetPoints();
    vector<bool> result = vector<bool>(points.size(), false);

    auto it = points.begin();
    int sum = 0;
    while (it < points.end()) {
        if(it->GetSize() + sum > shape) {
            result[it - points.begin()] = true;
        }
        else{
            sum += it->GetSize();
        }
        it++;
    }
    bools = result;
    return result;
}
Backup Trimming::Trim() {
    auto points = backup.GetPoints();
    auto iter = points.begin();

    while (iter < points.end()) {
        if(bools[iter - points.begin()]){
            if(iter->GetSavingType() == ToDirectory)
                remove((backup.AddressOfBackupPoints + to_string(backup.Id) + "." + to_string(iter->GetVersion())).c_str());
            else {
                ifstream InputFile("config.cfg");
                string LibraryPath;
                InputFile >> LibraryPath;
                if(LibraryPath.size() < 17)
                    throw MyException("Undefined exception!");// В класс запилить!
                LibraryPath = LibraryPath.substr(18);
                remove((LibraryPath + "\\" + to_string(backup.Id) + "." + to_string(iter->GetVersion())).c_str());
            }
            bools[iter - points.begin()] = false;
            iter = points.erase(iter);
        }
        else{
            iter++;
        }
    }
    backup.SetPoints(points);
    return backup;
}
Backup Trimming::Trim(vector<bool> DeletingPositions) {
    auto points = backup.GetPoints();
    auto iter = points.begin();
    int deletedCount = 0;
    while (iter < points.end()) {
        if(DeletingPositions[iter - points.begin() + deletedCount]){
            if(iter->GetSavingType() == ToDirectory)
                remove((backup.AddressOfBackupPoints + to_string(backup.Id) + "." + to_string(iter->GetVersion())).c_str());
            else {
                ifstream InputFile("config.cfg");
                string LibraryPath;
                InputFile >> LibraryPath;
                if(LibraryPath.size() < 17)
                    throw MyException("Undefined exception!");// В класс запилить!
                LibraryPath = LibraryPath.substr(18);
                remove((LibraryPath + "\\" + to_string(backup.Id) + "." + to_string(iter->GetVersion())).c_str());
            }

            DeletingPositions[iter - points.begin() + deletedCount] = false;
            deletedCount++;
            iter = points.erase(iter);
        }
        else{
            iter++;
        }
    }
    backup.SetPoints(points);
    return backup;
}
Backup Trimming::AutoTrim(){
    this->FilterPointsForRemove();
    Backup backup1 = this->Trim();
    return backup1;
};
Backup TrimmingMixed::Trim(PointLimits limit) {
    vector<bool> ResultingBufferForDeleting;
    if(limit == JustAll){
        ResultingBufferForDeleting = vector<bool>(backup.GetPoints().size(), true);
        for(auto iter : politics){
            vector<bool> vb = iter->FilterPointsForRemove();
            for(int i = 0; i < ResultingBufferForDeleting.size(); i++) {
                ResultingBufferForDeleting[i] = ResultingBufferForDeleting[i] * vb[i];
            }
        }
    }
    else{
        ResultingBufferForDeleting = vector<bool>(backup.GetPoints().size(), false);
        for(int i = 0;  i < politics.size(); i++){

            vector<bool> tmp = politics[i]->FilterPointsForRemove();
            for(int j = 0; j < tmp.size(); j++){
                if(tmp[j] == 0)
                    continue;
                else
                    ResultingBufferForDeleting[j] = 1;
            }
        }

    }
    Trimming politic = Trimming(backup);
    backup = politic.Trim(ResultingBufferForDeleting);

    return backup;
}

vector<bool> Trimming::FilterPointsForRemove() {
    vector<RestorePoint> points = backup.GetPoints();
    vector<bool> result = vector<bool>(points.size(), false);
    return result;
}
