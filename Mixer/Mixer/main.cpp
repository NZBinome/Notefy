//
//  main.cpp
//  Mixer
//
//  Created by Zaher Hamadeh on 5/9/15.
//  Copyright (c) 2015 Zaher Hamadeh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "../../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"

void listHelp()
{
    printf("Mixer\n\
           command that mixes audio files (aif and wav currently supported)\n\
           and midi files, and mix them in a single audio file\n\n\
           Options:\n\
           -i <file name> ...: select input files,\n\
           -o <file name> : select output file,\n\
           -c <path> : select the command that converts midi to audio,\n\
           -s <path> : select a library or a soundfont containing midi sample used in conversion\n");
}

int main(int argc, const char * argv[]) {
    
    Options o;
    if(argc<2)
    {
        printf("use h to see options");
        return 1;
    }
    if (argc==2)
    {
        if(o.whatOption(argv[1][0])!=HELP)
        {
            printf("use h to see options");
            return 1;
        }
        listHelp();
        return 0;
    }
    
    int it=1;
    Argument last;
    while (it<argc)
    {
        if (o.is_anOption(argv[it]))
        {
            last=o.whatOption(argv[it][1]);
            
            if(last==INVOPTION)
            {
                printf("unkown option %s\n",argv[it]);
                exit(0);
            }
        }
        else
        {
            o.setIndex(it, last);
        }
        ++it;
    }
        
    Z_audioMidiConverter amc;
    if(o.convertInd()>-1)
        amc.setConverterPath(argv[o.convertInd()]);
    if(o.soundFInd()>-1)
        amc.setSoundFontPath(argv[o.soundFInd()]);
    try {
        amc.mix(argv+o.inputStart(), o.inputEnd()-o.inputStart()+1, argv[o.outputInd()]);
    } catch (const char * exception) {
        printf("%s\n",exception);
    }
    
    return 0;
}
