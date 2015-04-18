//
//  XYZShare.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZUser.h"
#import "XYZMelody.h"
#import "XYZFeed.h"
#import "../XYZAppDelegate.h"
#import "../Controllers/Object Controllers/XYZShareCell.h"

@interface XYZShare : XYZFeed
@property NSString* Date;
@property NSString* ServerLocation;
@property XYZUser* User;
@property XYZMelody* Melody;
-(void)fillCell:(XYZShareCell*)cell;

@end
