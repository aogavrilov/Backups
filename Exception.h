//
// Created by Alexey on 02.11.2020.
//

#ifndef BACKUPS_EXCEPTION_H
#define BACKUPS_EXCEPTION_H
#include <string>
using namespace std;

class MyException : exception{
private:
    string m_error;
public:
    MyException(string reason) : m_error(reason){}
    const char* getError() { return m_error.c_str(); }
};


#endif //BACKUPS_EXCEPTION_H
