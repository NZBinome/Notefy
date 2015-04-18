//
//  XYZFollowCell.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFollowCell.h"

@implementation XYZFollowCell
@synthesize Followed;
@synthesize FollowedPP;
@synthesize Follower;
@synthesize FollowerPP;
@synthesize Action;
@synthesize Time;


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
