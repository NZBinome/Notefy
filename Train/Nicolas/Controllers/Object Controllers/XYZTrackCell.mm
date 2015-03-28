//
//  XYZTrackCell.m
//  Train
//
//  Created by Nicolas Jbeyli on 2/21/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZTrackCell.h"

@implementation XYZTrackCell
@synthesize Button;
@synthesize row;

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
- (IBAction)OnClick:(id)sender {
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    appdel.selectedtrack=row;
}


@end
