//
//  XYZInstrumentController.m
//  Train
//
//  Created by Nicolas Jbeyli on 2/20/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZInstrumentController.h"

@interface XYZInstrumentController ()
@property XYZAppDelegate* appdel;
@end

@implementation XYZInstrumentController
@synthesize appdel;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    appdel=[UIApplication sharedApplication].delegate;


    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Collection View Data Sources

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return appdel.instruments.count;
}

// The cell that is returned must be retrieved from a call to - dequeueReusableCellWithReuseIdentifier:forIndexPath:
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    XYZInstrument *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"Instrument" forIndexPath:indexPath];
    if (indexPath.row<[appdel.instruments count]) {
    UIImage *InstrumentImage = [[UIImage alloc] init];
    XYZInstrument* demoInstrument;
    demoInstrument=[[XYZInstrument alloc]init];
    demoInstrument=[appdel.instruments objectAtIndex:indexPath.row];
    InstrumentImage = [UIImage imageNamed:demoInstrument.ImageName];
    cell.Image.image = InstrumentImage;
    }
    return cell;
}

-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    XYZInstrument* selectedInstrument;
    selectedInstrument=[[XYZInstrument alloc]init];
    selectedInstrument=[appdel.instruments objectAtIndex:indexPath.item];
    appdel.newinstrument=selectedInstrument;
    [self.navigationController popViewControllerAnimated:YES];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
