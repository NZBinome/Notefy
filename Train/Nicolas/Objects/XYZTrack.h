//
//  XYZTrack.h
//  Train
//
//  Created by Nicolas Jbeyli on 2/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XYZInstrument.h"

@interface XYZTrack : NSObject
@property NSString *trackName;
@property XYZInstrument* instrument;
@property BOOL isSelected;
@property BOOL isConverted;
-(void) initialize;

@end
