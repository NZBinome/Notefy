//
//  XYZCreate.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeed.h"
#import "XYZUser.h"
#import "XYZMelody.h"

@interface XYZCreate : XYZFeed
@property XYZUser* User;
@property XYZMelody *Melody;
-(void)fillCell:(XYZFeedCell*)cell;

@end
