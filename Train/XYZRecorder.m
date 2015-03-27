//
//  XYZRecorder.m
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZRecorder.h"

@interface XYZRecorder ()
@property AVAudioRecorder *recorder;
@end

@implementation XYZRecorder
@synthesize recorder;

- (BOOL) startAudioSession
{
    // Prepare the audio session
    NSLog(@"AUDIO");
    NSError *error;
    AVAudioSession *session = [AVAudioSession sharedInstance];
    [session setCategory:AVAudioSessionCategoryRecord error:&error];
    [session setActive:YES error:&error];
    NSLog(@"active audio");
    return YES;
}

- (BOOL) record
{
    NSError *error;
    
    // Recording settings
    NSMutableDictionary *settings = [NSMutableDictionary dictionary];
    
    [settings setValue: [NSNumber numberWithInt:kAudioFormatLinearPCM] forKey:AVFormatIDKey];
    [settings setValue: [NSNumber numberWithFloat:44100.0] forKey:AVSampleRateKey];
    [settings setValue: [NSNumber numberWithInt: 1] forKey:AVNumberOfChannelsKey];
    [settings setValue: [NSNumber numberWithInt:16] forKey:AVLinearPCMBitDepthKey];
    [settings setValue: [NSNumber numberWithBool:NO] forKey:AVLinearPCMIsBigEndianKey];
    [settings setValue: [NSNumber numberWithBool:NO] forKey:AVLinearPCMIsFloatKey];
    [settings setValue:  [NSNumber numberWithInt: AVAudioQualityMax] forKey:AVEncoderAudioQualityKey];
    
    // Create recorder
    recorder = [[AVAudioRecorder alloc] initWithURL:self.url settings:settings error:&error];
  //  NSLog([self.url absoluteString]);
    if (!recorder)
    {
        NSLog(@"Error establishing recorder: %@", error.localizedFailureReason);
        return NO;
    }
    
    // Initialize degate, metering, etc.
    recorder.delegate = self;
    recorder.meteringEnabled = YES;
    //self.title = @"0:00";
    
    if (![recorder prepareToRecord])
    {
        NSLog(@"Error: Prepare to record failed");
        //[self say:@"Error while preparing recording"];
        return NO;
    }
    
    if (![recorder record])
    {
        NSLog(@"Error: Record failed");
        //  [self say:@"Error while attempting to record audio"];
        return NO;
    }
    
    // Set a timer to monitor levels, current time
   // timer = [NSTimer scheduledTimerWithTimeInterval:0.1f target:self selector:@selector(updateMeters) userInfo:nil repeats:YES];
    
    return YES;
}

- (BOOL) stopRecording
{
    // This causes the didFinishRecording delegate method to fire
    [recorder stop];
    return YES;
}

- (void) continueRecording
{
    // resume from a paused recording
    [recorder record];
    
}

- (void) pauseRecording
{  // pause an ongoing recording
    [recorder pause];
    
}
@end
