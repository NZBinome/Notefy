//
//  XYZFeed.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../Controllers/Object Controllers/XYZFeedCell.h"
#import "../XYZAppDelegate.h"
#import "XYZUser.h"
#import "XYZMelody.h"

@interface XYZFeed : NSObject
-(void)fillCell:(XYZFeedCell*)cell;
-(NSString*)fixDate:(NSString*)Date;

@end
