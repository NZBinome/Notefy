//
//  Options.h
//  Mixer
//
//  Created by Zaher Hamadeh on 5/11/15.
//  Copyright (c) 2015 Zaher Hamadeh. All rights reserved.
//

#ifndef __Mixer__Options__
#define __Mixer__Options__

#include <stdio.h>
#include <map>

enum Argument
{
    INVOPTION,
    HELP,
    OUTPUT,
    INPUT,
    SOUNDFONT,
    CONVERTER,
};

class Options
{
    std::map<const char,Argument> mop;
    int _is,_ie;
    int _oi;
    int _si,_ci;
    void setInputIndex(int index);
public:
    Options();
    bool is_anOption(const char *t);
    Argument whatOption(const char t);
    void setIndex(int index, Argument arg);
    int inputStart()const;
    int inputEnd()const;
    int outputInd()const;
    int soundFInd()const;
    int convertInd()const;
};

#endif /* defined(__Mixer__Options__) */
