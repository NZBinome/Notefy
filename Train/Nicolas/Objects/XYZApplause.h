//
//  XYZApplause.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeed.h"
#import "XYZUser.h"
#import "XYZMelody.h"
#import "../Controllers/Object Controllers/XYZApplauseCell.h"


@interface XYZApplause : XYZFeed
@property NSString* Date;
@property NSString* ServerLocation;
@property XYZUser* User;
@property XYZMelody* Melody;
@property NSString* ApplauseCount;
@property NSString* ShareCount;
@property NSString* CommentCount;
-(void)fillCell:(XYZApplauseCell*)cell;
@end
