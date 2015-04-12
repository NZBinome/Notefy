//
//  XYZFeed.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../Controllers/Object Controllers/XYZFeedCell.h"

@interface XYZFeed : NSObject
@property NSString* Date;
-(void)fillCell:(XYZFeedCell*)cell;

@end
