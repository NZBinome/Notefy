//
//  main.cpp
//  Mixer
//
//  Created by Zaher Hamadeh on 5/9/15.
//  Copyright (c) 2015 Zaher Hamadeh. All rights reserved.
//

#include <stdio.h>
#include "../../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"

int main(int argc, const char * argv[]) {
    
    Z_audioMidiConverter amc;
    amc.setConverterPath(argv[argc-2]);
    amc.setSoundFontPath(argv[argc-1]);
    try {
        amc.mix(argv+1, argc-4, argv[argc-3]);
    } catch (const char * exception) {
        printf("%s\n",exception);
    }
    
    return 0;
}
