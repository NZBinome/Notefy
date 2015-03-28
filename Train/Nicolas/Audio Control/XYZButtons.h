//
//  XYBbuttons.h
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XYZAppDelegate.h"

@interface XYZButtons : NSObject
@property NSURL *url;
@property NSString *name;
-(void)fixURL;
-(void)directoryURL;
@end

