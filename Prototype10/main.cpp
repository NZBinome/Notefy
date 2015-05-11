#include <stdio.h>
#include "../Train/Zaher/audiomidiconverter/z_audiomidiconverter.h"
int main(int argc, char **argv)
{
    Z_audioMidiConverter amc;

    amc.mix(argv,argc-1,argv[argc-1]);

    return 0;
}
