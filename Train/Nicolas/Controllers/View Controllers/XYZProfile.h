//
//  XYZProfile.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/10/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "../../Objects/XYZUser.h"
#import "../../Objects/XYZMelody.h"
#import "../Object Controllers/XYZMelodyCell.h"
#import "../../XYZAppDelegate.h"
#import "../../Objects/XYZCreate.h"
#import "../../Objects/XYZShare.h"
#import "XYZMelodyListen.h"

@interface XYZProfile : UIViewController<UITableViewDelegate,UITableViewDataSource,NSXMLParserDelegate>

-(void)setId:(int)Id;

@end
