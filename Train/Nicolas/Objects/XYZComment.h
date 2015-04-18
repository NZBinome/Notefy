//
//  XYZComment.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeed.h"
#import "XYZUser.h"
#import "XYZMelody.h"
#import "../Controllers/Object Controllers/XYZCommentCell.h"


@interface XYZComment : XYZFeed
@property XYZUser* User;
@property XYZMelody* Melody;
@property NSString* Script;
@property int Id;
@property NSString* Date;
@property NSString* ServerLocation;
-(void)fillCell:(XYZCommentCell *)cell;
@end
