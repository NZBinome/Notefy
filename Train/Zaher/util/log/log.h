//
//  log.h
//  Train
//
//  Created by Zaher Hamadeh on 5/16/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__log__
#define __Train__log__

#include <fstream>
#include <map>
#include <string.h>

class Log
{
    struct cmp_str
    {
        bool operator()(const char *first, const char  *second)const
        {
            return strcmp(first, second) < 0;
        }
    };
    typedef std::map<const char *, Log *, cmp_str> MyMap;

    static MyMap _m;
    static const char _path[];
    std::fstream _f;


    Log();
    Log(const Log& o);
    Log & operator=(const Log& o);
    
public:
    static Log * getLogger(const char * filename);
    static void eraseLogger(const char * filename);
    Log & operator<<(const char * text);
    Log & operator<<(int value);
    Log & operator<<(double value);
    Log & operator<<(char value);
    ~Log();
};
#endif /* defined(__Train__log__) */
