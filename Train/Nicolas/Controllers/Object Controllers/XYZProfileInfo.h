//
//  XYZProfileInfo.h
//  Train
//
//  Created by Nicolas Jbeyli on 5/14/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XYZProfileInfo : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *ProfilePic;
@property (weak, nonatomic) IBOutlet UILabel *FirstName;
@property (weak, nonatomic) IBOutlet UILabel *LastName;
@property (weak, nonatomic) IBOutlet UILabel *StageName;
@property (weak, nonatomic) IBOutlet UIButton *BecomeAFan;
@property (weak, nonatomic) IBOutlet UILabel *FanNumber;

@end
