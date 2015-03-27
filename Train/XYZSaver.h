//
//  XYZSaver.h
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZButtons.h"
#import "XYZAppDelegate.h"

@interface XYZSaver : XYZButtons
@property NSString* directory;
@property NSURL* newurl;
@property NSString* oldname;
-(void) copyFromSaved:(NSString *)name;
-(BOOL) save:(NSString *)filename;
-(void) initialize;
-(void)testing;
-(void)removeNonSaved:(NSString *)name;
-(BOOL)nameExists:(NSString *)name;
-(void)removeExistsingFile:(NSString *)name;
@end
