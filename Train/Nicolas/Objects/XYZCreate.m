//
//  XYZCreate.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZCreate.h"

@implementation XYZCreate
@synthesize User;
@synthesize Melody;

- (id)init
{
    self = [super init];
    if (self)
    {
        User=[[XYZUser alloc]init];
        Melody=[[XYZMelody alloc]init];
    }
    return self;
}

-(void)fillCell:(XYZFeedCell *)cell
{
    
}

@end
