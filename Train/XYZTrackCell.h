//
//  XYZTrackCell.h
//  Train
//
//  Created by Nicolas Jbeyli on 2/21/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "XYZAppDelegate.h"


@interface XYZTrackCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *label;
@property (weak, nonatomic) IBOutlet UIButton *Button;
@property NSInteger row;
@end
