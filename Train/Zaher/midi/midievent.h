//
//  midievent.h
//  Train
//
//  Created by Zaher Hamadeh on 5/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#ifndef __Train__midievent__
#define __Train__midievent__

class MidiEvent
{
  
    unsigned int _l;  //time when event start
    unsigned char _t; //event type;
    
public:
    
    static const unsigned char _ME=0xFF; //metaEvent
    static const unsigned char _ME_tempo=0x51;
    //tempo starts with FF 51 03 tt tt tt, t represent the tempo in variable lengh quantity
    static const unsigned char _ME_EOT=0x2F;
    static const unsigned char _ME_TE=0x0F;
    static const unsigned char _NO=0x90; //note On
    static const unsigned char _PC=0xC0; //instrument changed
    
    
    int length()const;
    
    static MidiEvent * createMidiEvent(unsigned char * buff,int &s);
    void setL(unsigned char * vlq, int s); //read start time from variable length quantity
    void quantizeL(int base, int &offset, int &last);              //quantize _l, closer to multiple of base.
    
    static void vlqSize(unsigned char * buff, int &s);
    static unsigned int vlqInt(unsigned int vlq);
    static unsigned int intVlq(unsigned int l);
    static unsigned int ucharVlq(unsigned char * vlqc, int s);
    static void vlqUchar(unsigned char * vlqc, int &s, unsigned int vlq);
    
    unsigned char type();
    virtual int collectData(unsigned char * buff);
};


#endif /* defined(__Train__midievent__) */
