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
#import "../Object Controllers/XYZFeedCell.h"
#import "../../Objects/XYZComment.h"
#import "../../Objects/XYZApplause.h"

@interface XYZNewsFeed : UIViewController<UITableViewDelegate,UITableViewDataSource,NSXMLParserDelegate>

@end
