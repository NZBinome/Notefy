//
//  XYZFollow.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//


#import "../Controllers/Object Controllers/XYZFollowCell.h"
#import "XYZFeed.h"

@interface XYZFollow : XYZFeed
@property NSString* Date;
@property NSString* ServerLocation;
@property XYZUser* Follower;
@property XYZUser* Followed;
-(void)fillCell:(XYZFollowCell*)cell;

@end
