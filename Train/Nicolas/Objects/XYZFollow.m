//
//  XYZFollow.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/15/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFollow.h"

@implementation XYZFollow

@synthesize Date;
@synthesize Follower;
@synthesize Followed;
@synthesize ServerLocation;


- (id)init
{
    self = [super init];
    if (self)
    {
        XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
        Followed=[[XYZUser alloc]init];
        Follower=[[XYZUser alloc]init];
        ServerLocation=appdel.ServerLocation;
        
    }
    return self;
}


-(void)fillCell:(XYZFollowCell *)cell
{
    
    [cell.Follower setTitle:Follower.Stage_Name forState:UIControlStateNormal];
    [cell.Followed setTitle:Followed.Stage_Name forState:UIControlStateNormal];
    cell.Action.text=@"Became a fan of";
    
    cell.Time.text=[self fixDate:Date];
    
    cell.FollowedFanNumber.text=Followed.FanNumber;

    if ([Followed.FanNumber isEqualToString:@"1"])
    {
        cell.FollowedFanNumber.text=[cell.FollowedFanNumber.text stringByAppendingString:@" Fan"];
    }
    else
    {
        cell.FollowedFanNumber.text=[cell.FollowedFanNumber.text stringByAppendingString:@" Fans"];
    }
    
    NSString* fullpath;
    if (!Follower.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:Follower.Picture_link];
    }
    cell.FollowerPP.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    
    
    if (!Followed.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:Followed.Picture_link];
    }
    cell.FollowedPP.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    cell.Followed.tag = Followed.Id;
    cell.Follower.tag = Follower.Id;
    
}


@end
