//
//  XYZProfileInfo.m
//  Train
//
//  Created by Nicolas Jbeyli on 5/14/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZProfileInfo.h"

@implementation XYZProfileInfo
@synthesize BecomeAFan;
@synthesize LastName;
@synthesize FirstName;
@synthesize StageName;
@synthesize ProfilePic;
@synthesize FanNumber;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)awakeFromNib
{
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
