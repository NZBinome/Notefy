//
//  XYZShare.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZShare.h"
@implementation XYZShare

@synthesize User;
@synthesize Melody;
@synthesize Date;
@synthesize ServerLocation;
@synthesize ApplauseCount;
@synthesize ShareCount;
@synthesize CommentCount;
@synthesize FromProfile;
@synthesize Sharer;

- (id)init
{
    self = [super init];
    if (self)
    {
        XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
        User=[[XYZUser alloc]init];
        Melody=[[XYZMelody alloc]init];
        FromProfile=NO;
        ServerLocation=appdel.ServerLocation;
        
    }
    return self;
}

-(void)fillCell:(XYZShareCell *)cell
{
    NSString* fullpath;
    if (FromProfile)
    {
        [cell.SharerName setTitle:User.Stage_Name forState:UIControlStateNormal];
        cell.Action.text=@"Created";
        if (!User.Picture_link) {
            fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
        }
        else
        {
            fullpath = [ServerLocation stringByAppendingString:User.Picture_link];
        }
        cell.UserName.tag = Sharer.Id;
        cell.SharerName.tag = User.Id;
    }
    
    else
    {
        [cell.SharerName setTitle:Sharer.Stage_Name forState:UIControlStateNormal];
        cell.Action.text=@"Amplified";
        if (!Sharer.Picture_link) {
            fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
        }
        else
        {
            fullpath = [ServerLocation stringByAppendingString:Sharer.Picture_link];
        }
        cell.UserName.tag = User.Id;
        cell.SharerName.tag = Sharer.Id;
    }
    
    [cell.UserName setTitle:User.Stage_Name forState:UIControlStateNormal];
    [cell.MelodyName setTitle:Melody.Title forState:UIControlStateNormal];
    cell.ShareCount.text = ShareCount;
    cell.ApplauseCount.text = ApplauseCount;
    cell.CommentCount.text = CommentCount;
    
    cell.Time.text=[self fixDate:Melody.Date];
    
    
    cell.ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    cell.MelodyName.tag = Melody.Id;
    
}

@end
