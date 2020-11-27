//
// Created by Alexey on 20.10.2020.
//

#ifndef BACKUPS_TRIMMING_H
#define BACKUPS_TRIMMING_H
using namespace std;

#include <vector>
#include "Backup.h"
class Trimming{
protected:
    Backup backup;



public:
    Trimming(Backup backup) : backup(backup){};
    virtual vector<bool> FilterPointsForRemove();
    Backup Trim();
    Backup Trim(vector<bool> DeletingPositions);
    Backup AutoTrim();

    vector<bool> bools;
};
class PointsTrimmingByCount : public Trimming{

    int count;
public:
    PointsTrimmingByCount(Backup backup, size_t count) : Trimming(backup), count(count){};
    vector<bool> FilterPointsForRemove() override ;

};
class PointsTrimmingByDate : public Trimming{
    tm* Date;
public:
    PointsTrimmingByDate(Backup backup, tm* Date) : Trimming(backup), Date(Date){};
    vector<bool> FilterPointsForRemove() override;

};
class PointsTrimmingByShape : public Trimming{
    size_t shape;
public:
    PointsTrimmingByShape(Backup backup, size_t shape) : Trimming(backup), shape(shape){};
    vector<bool> FilterPointsForRemove() override;
};

class TrimmingMixed {
    Backup backup;
    vector<Trimming*> politics;
public:
    TrimmingMixed(Backup backup, vector<Trimming*> politics) : backup(backup), politics(politics){

    }
    Backup Trim(PointLimits limit);


};



#endif //BACKUPS_TRIMMING_H
