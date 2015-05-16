//
//  XYZCreate.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZCreate.h"

@implementation XYZCreate
@synthesize User;
@synthesize Melody;
@synthesize Date;
@synthesize ApplauseCount;
@synthesize ShareCount;
@synthesize CommentCount;
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

-(void)fillCell:(XYZCreateCell *)cell
{
    [cell.UserName setTitle:User.Stage_Name forState:UIControlStateNormal];
    [cell.MelodyName setTitle:Melody.Title forState:UIControlStateNormal];
    cell.Action.text=@"Created";
    
    cell.Time.text=[self fixDate:Date];
    
    cell.ShareCount.text = ShareCount;
    cell.ApplauseCount.text = ApplauseCount;
    cell.CommentCount.text = CommentCount;
    NSString* fullpath;
    if (!User.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:User.Picture_link];
    }
    cell.ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    
    cell.MelodyName.tag = Melody.Id;
    cell.UserName.tag = User.Id;

}

@end
