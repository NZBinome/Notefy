//
//  XYZCreateCell.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZCreateCell.h"

@implementation XYZCreateCell
@synthesize ProfilePic;
@synthesize MelodyName;
@synthesize UserName;
@synthesize Action;
@synthesize Time;
@synthesize CommentCount;
@synthesize ApplauseCount;
@synthesize ShareCount;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
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
