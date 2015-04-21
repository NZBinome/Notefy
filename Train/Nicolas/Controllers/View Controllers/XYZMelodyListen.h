//
//  XYZMelodyListen.h
//  Train
//
//  Created by Nicolas Jbeyli on 4/18/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "../../XYZAppDelegate.h"
#import "../../Objects/XYZMelody.h"
#import "../../Objects/XYZUser.h"


@interface XYZMelodyListen : UIViewController<NSXMLParserDelegate>

-(void)initializeMelodyId:(int)_MelodyId;

@end
