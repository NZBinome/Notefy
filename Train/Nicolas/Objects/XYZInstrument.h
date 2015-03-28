//
//  XYZInstrument.h
//  Train
//
//  Created by Nicolas Jbeyli on 2/20/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface XYZInstrument : UICollectionViewCell
@property (weak, nonatomic) IBOutlet UIImageView *Image;
@property NSString* Name;
@property unsigned short number;
@property NSString* ImageName;

@end
