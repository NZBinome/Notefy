//
//  XYZButtons.m
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZButtons.h"

@interface XYZButtons ()
@end
@implementation XYZButtons
@synthesize url;
@synthesize name;
-(void)fixURL
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    NSString *pathToSave;
        pathToSave = [
            [appdel.path stringByAppendingString:appdel.currentdirectory]
            stringByAppendingPathComponent:[name stringByAppendingString:@".aif"]
        ];
    url = [NSURL fileURLWithPath:pathToSave];//FILEPATH];
}

-(void)directoryURL
{
        XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
        NSString *pathToSave;
        pathToSave = [appdel.path
                      stringByAppendingPathComponent:name];
        url = [NSURL fileURLWithPath:pathToSave];//FILEPATH];
}

@end
