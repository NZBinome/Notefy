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

@interface XYZProfile : UIViewController<UITableViewDelegate,UITableViewDataSource>

-(void)setId:(int)Id;

@end
