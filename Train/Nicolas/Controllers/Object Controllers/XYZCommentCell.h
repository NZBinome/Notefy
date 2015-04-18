//
//  XYZCommentCell.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeedCell.h"

@interface XYZCommentCell : XYZFeedCell
@property (weak, nonatomic) IBOutlet UILabel *Time;
@property (weak, nonatomic) IBOutlet UIButton *MelodyName;
@property (weak, nonatomic) IBOutlet UIButton *UserName;
@property (weak, nonatomic) IBOutlet UIImageView *ProfilePic;
@property (weak, nonatomic) IBOutlet UILabel *Action;
@property (weak, nonatomic) IBOutlet UILabel *Comment;

@end
