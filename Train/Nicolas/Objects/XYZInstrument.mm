//
//  XYZInstrument.m
//  Train
//
//  Created by Nicolas Jbeyli on 2/20/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZInstrument.h"

@implementation XYZInstrument
@synthesize Name;
@synthesize number;
@synthesize ImageName;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

-(void)copyInstrument:(XYZInstrument *)Instrument
{
    Name=Instrument.Name;
    number=Instrument.number;
    ImageName=Instrument.ImageName;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
