//
//  XYZ_Recording_View.h
//  DoReMi
//
//  Created by Nicolas Jbeyli on 9/30/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import "XYZRecorder.h"
#import "XYZPlayer.h"
#import "XYZSaver.h"
#import "XYZAppDelegate.h"
#import "XYZTrack.h"
#import "XYZTrackCell.h"
#import "Zaher/midi/midicreator.h"
#import "Zaher/audiomidiconverter/z_audiomidiconverter.h"
#import "Zaher/midi/musicinstrument.h"


@interface XYZ_Recording_View : UIViewController<UITableViewDelegate,UITableViewDataSource>
@property (weak, nonatomic) IBOutlet UITextField *inputname;

@end
