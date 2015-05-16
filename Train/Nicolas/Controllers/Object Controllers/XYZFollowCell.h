//
//  XYZFollowCell.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeedCell.h"

@interface XYZFollowCell : XYZFeedCell
@property (weak, nonatomic) IBOutlet UILabel *Time;
@property (weak, nonatomic) IBOutlet UIButton *Follower;
@property (weak, nonatomic) IBOutlet UIButton *Followed;
@property (weak, nonatomic) IBOutlet UILabel *Action;
@property (weak, nonatomic) IBOutlet UIImageView *FollowerPP;
@property (weak, nonatomic) IBOutlet UIImageView *FollowedPP;
@property (weak, nonatomic) IBOutlet UILabel *FollowedFanNumber;

@end
