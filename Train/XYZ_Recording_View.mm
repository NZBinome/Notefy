//
//  XYZ_Recording_View.m
//  DoReMi
//
//  Created by Nicolas Jbeyli on 9/30/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZ_Recording_View.h"

@interface XYZ_Recording_View (){
    Z_audioMidiConverter amc;
}
@property XYZRecorder *recorder;
@property NSMutableArray *players;
@property XYZPlayer *metronomePLayer;
@property XYZSaver *saver;
@property NSURL *url;
@property NSString *name;
@property NSTimer *timer;
@property NSTimer *metronomeTimer;
@property (weak, nonatomic) IBOutlet UILabel *warninglabel;
@property int recordtime;
@property (weak, nonatomic) IBOutlet UILabel *slidervalue;
@property (weak, nonatomic) IBOutlet UISwitch *Switch;
@property (weak, nonatomic) IBOutlet UISlider *slider;
@property int trackCounter;
@property NSMutableArray *tracks;
@property (weak, nonatomic) IBOutlet UITableView *trackTable;
@property XYZTrack* track;
@property NSString* selectedfile;
@property (weak, nonatomic) IBOutlet UIButton *recordButton;
@property (weak, nonatomic) IBOutlet UITableView *trackTableView;
@property NSString* chosenInstrument;
@property XYZAppDelegate *appdel;

@end

@implementation XYZ_Recording_View
@synthesize recorder;
@synthesize metronomePLayer;
@synthesize players;
@synthesize saver;
@synthesize url;
@synthesize timer;
@synthesize metronomeTimer;
@synthesize recordtime;
@synthesize inputname;
@synthesize warninglabel;
@synthesize slidervalue;
@synthesize slider;
@synthesize Switch;
@synthesize trackCounter;
@synthesize tracks;
@synthesize trackTable;
@synthesize track;
@synthesize selectedfile;
@synthesize recordButton;
@synthesize trackTableView;
@synthesize chosenInstrument;
@synthesize appdel;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)recordingTime{
    recordtime-=1;
    [timer invalidate];
    if (recordtime<=0) {
        [recorder stopRecording];
    }
}

-(void)metronomePlay{
    NSLog(@"playing metronome");
    metronomePLayer=[[XYZPlayer alloc]init];
    [metronomePLayer metronomePlay];
}

- (IBAction)Scroll:(id)sender {
    slidervalue.text=[NSString stringWithFormat:@"%d",(int)slider.value];
}

- (IBAction)record:(id)sender {
    NSLog(@"record pressed");
    recordtime=15;
    trackCounter+=1;
    XYZPlayer* player;
    recorder = [[XYZRecorder alloc]init];
    track= [[XYZTrack alloc]init];
    track.instrument = [[XYZInstrument alloc]init];
    player=[[XYZPlayer alloc]init];
    [track initialize];
    track.instrument.Name=@"mic";
    track.trackName=[track.trackName stringByAppendingString:[NSString stringWithFormat:@"%d",trackCounter]];
    recorder.name=track.trackName;
    [player playerURL:trackCounter];
    [players addObject:player];
    NSLog(@"size of players : %d",[players count]);
    [recorder fixURL];
    if ([Switch isOn]) {
        NSLog(@"start metronome");
        metronomeTimer= [NSTimer scheduledTimerWithTimeInterval:(60/slider.value)
                                                target:self
                                              selector:@selector(metronomePlay)
                                              userInfo:nil
                                               repeats:YES];
    }
    if ([recorder startAudioSession]){
        NSLog(@"start audio session");
    }
    if([recorder record]){
        NSLog(@"recording");
    }
    timer= [NSTimer scheduledTimerWithTimeInterval:1.0
                                           target:self
                                         selector:@selector(recordingTime)
                                         userInfo:nil
                                          repeats:YES];
}

- (IBAction)stopRecord:(id)sender {
    if([recorder stopRecording]){
        NSLog(@"stopped recording");
        [metronomeTimer invalidate];
        [tracks addObject:track];
        NSLog(@"before adding rows");
        [trackTable reloadData];
        NSLog(@"rows added");
    }
}

- (IBAction)play:(id)sender {
    NSLog(@"play pressed");
    int i=0;
    while (i<[players count]) {
        XYZTrack* demotrack;
        demotrack=[[XYZTrack alloc]init];
        demotrack=[tracks objectAtIndex:i];
        if (demotrack.isSelected) {
            if ([demotrack.instrument.Name isEqualToString:@"mic"]) {
                [[players objectAtIndex:i] updateURL:@".aif"];
                if([[players objectAtIndex:i] XYZplay]){
                    NSLog(@"Playing");
                }

            }
            else{
                [[players objectAtIndex:i] updateURL:@".mid"];
                if([[players objectAtIndex:i] midiPlay]){
                    NSLog(@"Playing");
                }

            }
        }
        ++i;
    }
}

- (IBAction)save:(id)sender {
    if (![inputname.text  isEqual: @""]) {
        if ([selectedfile isEqualToString:@""]) {
            if ([saver nameExists:inputname.text]) {
                warninglabel.text=@"Name already exists";
            }
            else{
                if([saver save:inputname.text]){
                    NSLog(@"Saved");
                    [self.navigationController popViewControllerAnimated:YES];
                }
            }
        }
        else{
            [saver removeExistsingFile:selectedfile];
            [saver save:inputname.text];
            [self.navigationController popViewControllerAnimated:YES];
        }
    }
    else{
        warninglabel.text=@"Please insert a name";
    }

}

-(void)dismissKeyboard {
     [self.inputname resignFirstResponder];
}

-(void)cleanAudioFiles{
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    NSError *error;
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:appdel.path
                                                                        error:NULL];
    NSLog(appdel.path);
    NSLog(@"%@", dirs);
    NSMutableArray* Audiofiles;
    Audiofiles = [[NSMutableArray alloc] init];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSString *name = (NSString *)obj;
        if (![[name substringToIndex:1] isEqualToString:@"."]) {
            [Audiofiles addObject:[name substringToIndex:[name length]]];
        }
    }];
    NSLog(@"%@",Audiofiles);
    int i=0;
    while (i<[Audiofiles count]) {
        NSString* file=[Audiofiles objectAtIndex:i];
        if (!([file isEqualToString:@"Saved"] || [file isEqualToString:@"beat.aif"])) {
            NSString* path=[appdel.path stringByAppendingPathComponent:file];
            [filemgr removeItemAtURL:[NSURL fileURLWithPath:path] error:&error];
        }
        i+=1;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    appdel=[UIApplication sharedApplication].delegate;
    [self cleanAudioFiles];
    NSLog(@"new track did load");
    amc=Z_audioMidiConverter();
    selectedfile=appdel.selectedfile;
    appdel.selectedfile = @"";
    tracks=[[NSMutableArray alloc] init];
    players=[[NSMutableArray alloc]init];
    trackCounter=0;
    trackTable.dataSource = self;
    trackTable.delegate = self;
    NSString* path;

    saver = [[XYZSaver alloc]init];
    [saver initialize];
    if ([selectedfile isEqualToString:@""]) {
        appdel.currentdirectory=@"/Default";
        NSFileManager* FM;
        FM = [NSFileManager defaultManager];
        path=[appdel.path stringByAppendingString:@"/Default"];
        [FM createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:NULL];
    }
    
    if (![selectedfile isEqualToString:@""]){
        inputname.text = selectedfile;
        saver.oldname = selectedfile;
        appdel.currentdirectory=[@"/" stringByAppendingString:selectedfile];
        [saver copyFromSaved:selectedfile];
        path=[appdel.path stringByAppendingString:appdel.currentdirectory];
        NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                            error:NULL];
        [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            NSString *name = (NSString *)obj;
            if ([[name substringFromIndex:[name length]-4] isEqualToString:@".aif"]) {
                trackCounter+=1;
                XYZTrack* demotrack;
                XYZPlayer* player;
                demotrack=[[XYZTrack alloc]init];
                demotrack.instrument=[[XYZInstrument alloc]init];
                player=[[XYZPlayer alloc]init];
                [player playerURL:trackCounter];
                [players addObject:player];
                demotrack.trackName=[name substringToIndex:[name length]-4];
                demotrack.isSelected=TRUE;
                [tracks addObject:demotrack];
                }
            if([[name substringFromIndex:[name length]-4] isEqualToString:@".mid"]){
                NSString* midipath=[path stringByAppendingString:name];
                amc.getInstrument((char*)[midipath UTF8String]);
            }
        }];
        [self getInstrument:path];
    }
    
    slidervalue.text=[NSString stringWithFormat:@"%d",(int)slider.value];
    saver.name = saver.oldname;
    [saver directoryURL];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];

}

-(void)getInstrument:(NSString*)path{
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                        error:NULL];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSString *name = (NSString *)obj;
        if([[name substringFromIndex:[name length]-4] isEqualToString:@".mid"]){
            NSString* midipath=[path stringByAppendingString:[@"/" stringByAppendingString:name]];
            unsigned short instrument;
            instrument=amc.getInstrument((char*)[midipath UTF8String]);
            int i=0;
            while (i<[tracks count]) {
                XYZTrack* demotrack;
                demotrack=[tracks objectAtIndex:i];
                if([demotrack.trackName isEqualToString:[name substringToIndex:[name length]-4]]){
                    if (instrument==1) {
                        demotrack.instrument.Name=@"piano";
                    }
                    if (instrument==26) {
                        demotrack.instrument.Name=@"guitar";
                    }
                    if (instrument==57) {
                        demotrack.instrument.Name=@"trompette";
                    }
                    if (instrument==49) {
                        demotrack.instrument.Name=@"violin";
                    }
                    if (instrument==22) {
                        demotrack.instrument.Name=@"accordion";
                    }
                    [tracks replaceObjectAtIndex:i withObject:demotrack];
                }
                ++i;
            }
        }
    }];
}

-(void)viewDidAppear:(BOOL)animated{
    chosenInstrument=appdel.newinstrument.Name;
    appdel.newinstrument.Name=@"";
        if (appdel.selectedtrack!=-1){
            XYZTrack* demotrack;
            demotrack=[tracks objectAtIndex:appdel.selectedtrack];
            demotrack.instrument.Name=chosenInstrument;
            [tracks replaceObjectAtIndex:appdel.selectedtrack withObject:demotrack];
            [trackTable reloadData];
            NSString* path;
            char array [96];
                if ([selectedfile isEqualToString:@""]) {
                path=[appdel.path stringByAppendingString:[@"/Default/track" stringByAppendingString:[[NSString stringWithFormat:@"%d",appdel.selectedtrack+1] stringByAppendingString:@".aif"]]];
            }
                else{
                    path=[appdel.path stringByAppendingString:[[[@"/" stringByAppendingString:selectedfile] stringByAppendingString:@"/track" ] stringByAppendingString:[[NSString stringWithFormat:@"%d",appdel.selectedtrack+1] stringByAppendingString:@".aif"]]];
                }
            appdel.selectedtrack=-1;
            amc.convert((char*)[path UTF8String],array);
            amc.chooseInstrument(appdel.newinstrument.number,array);
        }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - TableView Control

-(void)viewWillDisappear:(BOOL)animated{
    [saver removeNonSaved:[saver.oldname stringByAppendingString:@".aif"]];

}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [tracks count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    XYZTrackCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ListPrototypeCell" forIndexPath:indexPath];
    XYZTrack* demotrack;
    demotrack=[[XYZTrack alloc]init];
    demotrack= [tracks objectAtIndex:indexPath.row];
    cell.label.text = demotrack.trackName;
    cell.row=indexPath.row;
    UIImage *InstrumentImage = [[UIImage alloc] init];
    InstrumentImage = [UIImage imageNamed:[demotrack.instrument.Name stringByAppendingString:@".png"]];
    [cell.Button setImage:InstrumentImage forState:UIControlStateNormal];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if([tableView cellForRowAtIndexPath:indexPath].accessoryType == UITableViewCellAccessoryCheckmark){
        [tableView cellForRowAtIndexPath:indexPath].accessoryType = UITableViewCellAccessoryNone;
    }else{
        [tableView cellForRowAtIndexPath:indexPath].accessoryType = UITableViewCellAccessoryCheckmark;
    }
    XYZTrack* tempTrack;
    tempTrack=[tracks objectAtIndex:indexPath.row];
    tempTrack.isSelected=(!tempTrack.isSelected);
    [tracks replaceObjectAtIndex:indexPath.row withObject:tempTrack];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}



#pragma mark - Testing Functions

-(void)viewState
{
    int i=0;
    while (i<[tracks count]) {
        XYZTrack* tempTrack;
        tempTrack=[tracks objectAtIndex:i];
        if (tempTrack.isSelected) {
            NSLog(@"selected");
        }
        else{
            NSLog(@"not selected");
        }
        ++i;
    }
}

-(void)viewInstruments{
    int i=0;
    NSLog(@"haha");
    while (i<[tracks count]) {
        XYZTrack* tempTrack;
        tempTrack=[tracks objectAtIndex:i];
       // NSLog(tempTrack.instrument);
        i+=1;
    }
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([[segue identifier] isEqualToString:@"Instruments"]) {
    XYZTrack *demotrack;
    demotrack=[[XYZTrack alloc]init];
    demotrack=[tracks objectAtIndex:appdel.selectedtrack];
    appdel.newinstrument.Name=demotrack.instrument.Name;
    }
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


@end
