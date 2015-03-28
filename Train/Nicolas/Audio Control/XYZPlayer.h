//
//  XYZPlayer.h
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import "XYZButtons.h"

@interface XYZPlayer : XYZButtons<AVAudioPlayerDelegate>
- (BOOL) XYZplay;
- (BOOL) metronomePlay;
-(void)playerURL:(int)tracknumber;
-(BOOL)midiPlay;
-(void)updateURL:(NSString*)extension;


@end
