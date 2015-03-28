//
//  XYZInstrumentController.m
//  Train
//
//  Created by Nicolas Jbeyli on 2/20/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZInstrumentController.h"

@interface XYZInstrumentController ()
@property (strong, nonatomic) NSArray *InstrumentImages;
@property unsigned short Piano;
@property unsigned short Guitar;
@property unsigned short Trompette;
@property unsigned short Violin;
@property unsigned short accordion;
@end

@implementation XYZInstrumentController
@synthesize InstrumentImages;
@synthesize Piano;
@synthesize Guitar;
@synthesize Trompette;
@synthesize Violin;
@synthesize accordion;

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

    InstrumentImages=@[@"piano.png",@"guitar.png",@"violin.png",@"drums.png",@"trompette.png",@"mic.png",@"accordion.png"];
    Piano=1;
    Guitar=26;
    Trompette=57;
    Violin=49;
    accordion=22;
    
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
    return InstrumentImages.count;
}

// The cell that is returned must be retrieved from a call to - dequeueReusableCellWithReuseIdentifier:forIndexPath:
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    XYZInstrument *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"Instrument" forIndexPath:indexPath];
    UIImage *InstrumentImage = [[UIImage alloc] init];
    InstrumentImage = [UIImage imageNamed:[InstrumentImages objectAtIndex:indexPath.row]];
    cell.Image.image = InstrumentImage;
    return cell;
}

-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    XYZInstrument* selectedInstrument;
    XYZInstrument* demoInstrument;
    selectedInstrument=[[XYZInstrument alloc]init];
    selectedInstrument.Name=[[InstrumentImages objectAtIndex:indexPath.item] substringToIndex:[[InstrumentImages objectAtIndex:indexPath.item] length]-4];
    int i=0;
    while (i<[appdel.instruments count]) {
        demoInstrument=[[XYZInstrument alloc]init];
        demoInstrument=[appdel.instruments objectAtIndex:i];
        if ([selectedInstrument.Name isEqualToString:demoInstrument.Name]) {
            appdel.newinstrument=demoInstrument;
            break;
        }
        i++;
    }
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
