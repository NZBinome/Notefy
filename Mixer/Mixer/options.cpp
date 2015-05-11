//
//  Options.cpp
//  Mixer
//
//  Created by Zaher Hamadeh on 5/11/15.
//  Copyright (c) 2015 Zaher Hamadeh. All rights reserved.
//

#include "options.h"
#include "string.h"

using namespace std;

Options::Options()
{
    mop['h']=HELP;
    mop['i']=INPUT;
    mop['o']=OUTPUT;
    mop['s']=SOUNDFONT;
    mop['c']=CONVERTER;
    
    _is=_ie=_oi=_si=_ci=-1;
}

bool Options::is_anOption(const char *t)
{
    if (t[0]=='-')
    {
        return true;
    }
    return false;
}

Argument Options::whatOption(const char t)
{
    if (mop[t]==0)
    {
        return INVOPTION;
    }
    return mop[t];
}

void Options::setInputIndex(int index)
{
    if(_is==-1)
    {
        _is=_ie=index;
    }
    else
    {
        _ie=index;
    }
}

void Options::setIndex(int index,Argument arg)
{
    switch (arg) {
        case INPUT:
            setInputIndex(index);
            break;
        case OUTPUT:
            _oi=index;
            break;
        case SOUNDFONT:
            _si=index;
            break;
        case CONVERTER:
            _ci=index;
            break;
        default:
            break;
    }
}

int Options::inputStart()const
{
    return _is;
}

int Options::inputEnd()const
{
    return _ie;
}

int Options::outputInd()const
{
    return _oi;
}

int Options::soundFInd()const
{
    return _si;
}

int Options::convertInd()const
{
    return _ci;
}