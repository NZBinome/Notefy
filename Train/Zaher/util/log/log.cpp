//
//  log.cpp
//  Train
//
//  Created by Zaher Hamadeh on 5/16/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#include "log.h"
#include <stdio.h>
#include <string.h>

using namespace std;

Log::MyMap Log::_m;
const char Log::_path[]="/Users/zuz/JunkFolder/AppLog/";

Log::Log()
{

}

Log::Log(const Log &o)
{

}

Log & Log::operator =(const Log &o)
{
    return *this;
}

Log * Log::getLogger(const char *filename)
{
    MyMap::iterator iter=Log::_m.find(filename);
    if(iter!=Log::_m.end())
        return (*iter).second;
    Log * me=new Log();
    char path[30];
    sprintf(path, "%s%s",_path,filename);
    (me->_f).open(path,ios::app|ios::out);
    _m.insert(MyMap::value_type(filename,me));
    return me;
}

void Log::eraseLogger(const char *filename)
{
    delete _m[filename];
    _m.erase(filename);
}

Log & Log::operator<<(const char *text)
{
    _f<<text;
    return *this;
}

Log & Log::operator<<(int value)
{
    _f<<value;
    return *this;
}

Log & Log::operator<<(double value)
{
    _f<<value;
    return *this;
}

Log & Log::operator<<(char value)
{
    _f<<value;
    return *this;
}

Log::~Log()
{
    _f.close();
}
