//
//  XYZNewsFeed.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "XYZProfile.h"
#import "../Object Controllers/XYZFeedCell.h"
#import "../../Objects/XYZCreate.h"
#import "../../Objects/XYZShare.h"
#import "../../Objects/XYZFollow.h"
#import "../Object Controllers/XYZFeedCell.h"
#import "../Object Controllers/XYZCommentCell.h"
#import "../Object Controllers/XYZCreateCell.h"
#import "../Object Controllers/XYZApplauseCell.h"
#import "../Object Controllers/XYZFollowCell.h"
#import "../Object Controllers/XYZShareCell.h"
#import "../../Objects/XYZComment.h"
#import "../../Objects/XYZApplause.h"
#import "XYZMelodyListen.h"

@interface XYZNewsFeed : UIViewController<UITableViewDelegate,UITableViewDataSource,NSXMLParserDelegate>

@end
