//
//  XYZApplause.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/13/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZApplause.h"

@implementation XYZApplause
@synthesize User;
@synthesize Melody;
@synthesize Date;
@synthesize ServerLocation;


- (id)init
{
    self = [super init];
    if (self)
    {
        XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
        User=[[XYZUser alloc]init];
        Melody=[[XYZMelody alloc]init];
        ServerLocation=appdel.ServerLocation;
        
    }
    return self;
}


-(void)fillCell:(XYZFeedCell *)cell
{
    [cell.UserName setTitle:User.Stage_Name forState:UIControlStateNormal];
    [cell.MelodyName setTitle:Melody.Title forState:UIControlStateNormal];
    cell.Action.text=@"Applause";
    cell.Time.text=Date;
    
    NSString* fullpath;
    if (!User.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:User.Picture_link];
    }
    cell.ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    
}


@end
