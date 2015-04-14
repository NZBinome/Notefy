//
//  XYZFeedCell.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XYZFeedCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *ProfilePic;
@property (weak, nonatomic) IBOutlet UIButton *UserName;
@property (weak, nonatomic) IBOutlet UILabel *Action;
@property (weak, nonatomic) IBOutlet UIButton *MelodyName;
@property (weak, nonatomic) IBOutlet UILabel *Time;
@property (weak, nonatomic) IBOutlet UILabel *NumberApplause;
@property (weak, nonatomic) IBOutlet UILabel *NumberComment;
@property (weak, nonatomic) IBOutlet UILabel *NumberShare;
@end