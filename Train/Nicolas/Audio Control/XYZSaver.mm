//
//  XYZSaver.m
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZSaver.h"

@interface XYZSaver()
@property XYZAppDelegate* appdel;
@end
@implementation XYZSaver
@synthesize directory;
@synthesize newurl;
@synthesize oldname;
@synthesize appdel;

-(BOOL)save:(NSString *)filename
{
    NSError *error;
    NSFileManager *filemgr;
    newurl = [newurl URLByAppendingPathComponent:filename];
    filemgr = [NSFileManager defaultManager];
    [filemgr moveItemAtURL:self.url toURL:newurl error:&error];
    return YES;
}

-(void) initialize
{
    appdel=[UIApplication sharedApplication].delegate;
    directory = appdel.directory;
    oldname = @"Default";
    newurl = [NSURL fileURLWithPath:[appdel.path stringByAppendingPathComponent:directory]];
}

-(void) copyFromSaved:(NSString *)name
{
    NSError *error;
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr copyItemAtURL:[newurl URLByAppendingPathComponent:name]
                     toURL:[NSURL fileURLWithPath:[appdel.path stringByAppendingPathComponent:name]] error:&error];
}

-(void)removeNonSaved:(NSString *)name
{
    NSError *error;
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr removeItemAtURL:
        [NSURL fileURLWithPath:[appdel.path stringByAppendingPathComponent:name]]
        error:&error];
}

-(BOOL)nameExists:(NSString *)name
{
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    BOOL isDir;
    if ([filemgr fileExistsAtPath:[[appdel.path stringByAppendingPathComponent:directory]stringByAppendingPathComponent:name] isDirectory:&isDir])
    {
        return YES;
    }
    return NO;
}

-(void)removeExistsingFile:(NSString *)name
{
    NSError *error;
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr removeItemAtURL:
     [NSURL fileURLWithPath:[[appdel.path stringByAppendingPathComponent:directory]stringByAppendingPathComponent:name]]
                       error:&error];
}

-(void) testing{
    NSError *error;
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr removeItemAtURL:[newurl URLByAppendingPathComponent:@"theaudiofile2.aif"] error:&error];
}
@end
