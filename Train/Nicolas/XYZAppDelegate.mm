//
//  XYZAppDelegate.m
//  Train
//
//  Created by Nicolas Jbeyli on 2/14/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZAppDelegate.h"

@implementation XYZAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    self.path=@"Users/nicolasjbeyli/Desktop/Git/Notefy/Train/audio_files";
    self.directory=@"/Saved";
    self.selectedfile=@"";
    self.selectedtrack=-1;
    self.newinstrument=[[XYZInstrument alloc]init];
    self.instruments=[[NSMutableArray alloc]init];
    [self createInstruments];
    
    
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

-(void)createInstruments
{
    XYZInstrument* instrument;
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"piano";
    instrument.number=1;
    instrument.ImageName=@"piano.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"guitar";
    instrument.number=26;
    instrument.ImageName=@"guitar.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"violin";
    instrument.number=49;
    instrument.ImageName=@"violin.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"trompette";
    instrument.number=57;
    instrument.ImageName=@"trompette.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"accordion";
    instrument.number=22;
    instrument.ImageName=@"accordion.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"drums";
    instrument.number=1;
    instrument.ImageName=@"drums.png";
    [self.instruments addObject:instrument];
    
    instrument=[[XYZInstrument alloc]init];
    instrument.Name=@"mic";
    instrument.number=1;
    instrument.ImageName=@"mic.png";
    [self.instruments addObject:instrument];
}

@end
