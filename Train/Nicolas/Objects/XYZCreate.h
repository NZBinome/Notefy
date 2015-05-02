//
//  XYZCreate.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZUser.h"
#import "XYZMelody.h"
#import "../XYZAppDelegate.h"
#import "XYZFeed.h"
#import "../Controllers/Object Controllers/XYZCreateCell.h"

@interface XYZCreate : XYZFeed
@property NSString* Date;
@property NSString* ServerLocation;
@property XYZUser* User;
@property XYZMelody* Melody;
@property NSString* ApplauseCount;
@property NSString* ShareCount;
@property NSString* CommentCount;
-(void)fillCell:(XYZCreateCell*)cell;

@end
