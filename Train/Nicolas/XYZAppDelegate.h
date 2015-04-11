//
//  XYZAppDelegate.h
//  Train
//
//  Created by Nicolas Jbeyli on 2/14/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "XYZInstrument.h"

@interface XYZAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property NSString *directory;
@property NSString *path;
@property NSString *selectedfile;
@property NSString *currentdirectory;
@property NSInteger selectedtrack;
@property XYZInstrument *newinstrument;
@property NSMutableArray* instruments;
@property NSString* ServerLocation;

@end
