#include <time.h>
#include <vector>
#include <algorithm>
//
// Created by Alexey on 19.10.2020.
//
/*
 *     vector<string> const* GetObjects();
    vector<string> const* AddObject(string address);
    vector<string> const*  RemoveObject(string address);
 *
 *
 */
#include "Backup.h"
vector<string> Backup::GetObjects() {
    return objects_address;
}
vector<string> Backup::AddObject(string address) {
    //Проверка на существование и валидность пути
    if(std::find(objects_address.begin(), objects_address.end(), address) == objects_address.end()){
        objects_address.push_back(address);
    }
    return objects_address;
}
vector<string> Backup::RemoveObject(string address) {
    //Check for finding and validation patch of removing file
    if(std::find(objects_address.begin(), objects_address.end(), address) == objects_address.end()){
        return  objects_address;
    }

    for (auto it = objects_address.begin(); it != objects_address.end(); ++it) {
        if (*it == address) {
            objects_address.erase(it);
            break;
        }
    }

    return objects_address;
}