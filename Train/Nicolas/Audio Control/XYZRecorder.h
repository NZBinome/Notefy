//
//  XYZRecorder.h
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import "XYZButtons.h"

@interface XYZRecorder : XYZButtons<AVAudioRecorderDelegate>
- (BOOL) startAudioSession;
- (BOOL) record;
- (BOOL) stopRecording;
@end
