//
//  XYZFeed.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZFeed.h"

@implementation XYZFeed


-(NSString*)fixDate:(NSString*)Date
{
    unsigned Flags = NSYearCalendarUnit| NSMonthCalendarUnit| NSDayCalendarUnit| NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSLocale* currentLocale = [NSLocale currentLocale];
    
    
    
    NSDate *date = [dateFormat dateFromString:Date];
    
    NSDate* CurrentDate= [[NSDate alloc]init];
    [CurrentDate descriptionWithLocale:currentLocale];
    
    
    NSCalendar* CurrentCalendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    NSDateComponents* CurrentComponents = [CurrentCalendar components:Flags fromDate:CurrentDate];
    
    NSCalendar* Calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    NSDateComponents* Components = [Calendar components:Flags fromDate:date];
    
    if ([Components year]<[CurrentComponents year])
    {
        long Year = [CurrentComponents year] - [Components year];
        if (Year==1)
        {
            [NSString stringWithFormat:@"%ld year ago",Year];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld years ago",Year];
        }
    }
    
    else if ([Components month]<[CurrentComponents month])
    {
        long Month = [CurrentComponents month] - [Components month];
        if (Month==1)
        {
            return [NSString stringWithFormat:@"%ld month ago",Month];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld months ago",Month];
        }
    }
    
    else if ([Components day]<[CurrentComponents day])
    {
        long Day = [CurrentComponents day] - [Components day];
        if (Day==1)
        {
            return [NSString stringWithFormat:@"%ld day ago",Day];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld days ago",Day];
        }
    }
    else if ([Components hour]<[CurrentComponents hour])
    {
        long Hour = [CurrentComponents hour] - [Components hour];
        if (Hour==1)
        {
            return [NSString stringWithFormat:@"%ld hr ago",Hour];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld hrs ago",Hour];
        }
    }
    else if ([Components minute]<[CurrentComponents minute])
    {
        long Minute = [CurrentComponents minute] - [Components minute];
        if (Minute==1)
        {
            return [NSString stringWithFormat:@"%ld min ago",Minute];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld mins ago",Minute];
        }
    }
    else
    {
        long Second = [CurrentComponents second] - [Components second];
        if (Second==1)
        {
            return [NSString stringWithFormat:@"%ld sec ago",Second];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld secs ago",Second];
        }
    }
    return @"";
}

@end
