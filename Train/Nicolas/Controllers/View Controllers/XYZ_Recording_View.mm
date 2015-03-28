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
@property NSFileManager *filemgr;


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
@synthesize filemgr;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

// (void)recordingTime checks if the recording time is exceeded. If yes, it stops the recording process.

-(void)recordingTime
{
    recordtime-=1;
    [timer invalidate];
    if (recordtime<=0)
    {
        [recorder stopRecording];
    }
}

// (void)metronomePlay Plays the metronome.

-(void)metronomePlay
{
    NSLog(@"playing metronome");
    metronomePLayer=[[XYZPlayer alloc]init];
    [metronomePLayer metronomePlay];
}

// (IBAction)Scroll:(id)sender Called when the value of the slider changes. Displays the value of the slider.

- (IBAction)Scroll:(id)sender {
    slidervalue.text=[NSString stringWithFormat:@"%d",(int)slider.value];
}

// (IBAction)record:(id)sender Called when record button is pressed. Creates a recorder, creates a player for that track, plays metronome if it is needed, starts the recording session.

- (IBAction)record:(id)sender
{
    recordtime=15;
    trackCounter+=1;
    [self addPlayer];
    recorder = [[XYZRecorder alloc]init];
    [self setTrack];
    recorder.name=track.trackName;
    [recorder fixURL];
    if ([Switch isOn])
    {
        [self startMetronome];
    }
    [recorder startAudioSession];
    [recorder record];
    [self startTimer];
}

// (void)setTrack Creates a default track with "mic" as an instrument.

-(void)setTrack
{
    track= [[XYZTrack alloc]init];
    track.instrument = [[XYZInstrument alloc]init];
    [track initialize];
    track.instrument.Name=@"mic";
    track.trackName=[track.trackName stringByAppendingString:[NSString stringWithFormat:@"%d",trackCounter]];
}

// (void)startMetronome Starts the timer for the metronome.

-(void)startMetronome
{
    metronomeTimer= [NSTimer scheduledTimerWithTimeInterval:(60/slider.value)
                                                     target:self
                                                   selector:@selector(metronomePlay)
                                                   userInfo:nil
                                                    repeats:YES];
}

// (void)addPlayer adds a player for a track.

-(void)addPlayer
{
    XYZPlayer* player;
    player=[[XYZPlayer alloc]init];
    [player playerURL:trackCounter];
    [players addObject:player];
}

// (void)startTimer Starts the timer for the recorder.

-(void)startTimer
{
    timer= [NSTimer scheduledTimerWithTimeInterval:1.0
                                            target:self
                                          selector:@selector(recordingTime)
                                          userInfo:nil
                                           repeats:YES];
}

// (IBAction)stopRecord:(id)sender is called when the record button is released or when the record time expires. Stops the recorder, adds the recorded tracks and refreshes the table.

- (IBAction)stopRecord:(id)sender
{
    [recorder stopRecording];
    [metronomeTimer invalidate];
    [tracks addObject:track];
    [trackTable reloadData];
}

// (IBAction)play:(id)sender is called when the play button is pressed. Plays the selected tracks of the melody.

- (IBAction)play:(id)sender
{
    int i=0;
    while (i<[players count])
    {
        XYZTrack* demotrack;
        demotrack=[[XYZTrack alloc]init];
        demotrack=[tracks objectAtIndex:i];
        if (demotrack.isSelected)
        {
            if ([demotrack.instrument.Name isEqualToString:@"mic"])
            {
                [[players objectAtIndex:i] updateURL:@".aif"];
                [[players objectAtIndex:i] XYZplay];
            }
            else
            {
                [[players objectAtIndex:i] updateURL:@".mid"];
                [[players objectAtIndex:i] midiPlay];
            }
        }
        ++i;
    }
}

// (IBAction)save:(id)sender Called when the save button is clicked. Saves the melody according to the given name.

- (IBAction)save:(id)sender
{
    if (![inputname.text  isEqual: @""])
    {
        if ([selectedfile isEqualToString:@""])
        {
            if ([saver nameExists:inputname.text])
            {
                warninglabel.text=@"Name already exists";
            }
            else
            {
                [saver save:inputname.text];
                [self.navigationController popViewControllerAnimated:YES];
            }
        }
        else
        {
            [saver removeExistsingFile:selectedfile];
            [saver save:inputname.text];
            [self.navigationController popViewControllerAnimated:YES];
        }
    }
    else
    {
        warninglabel.text=@"Please insert a name";
    }

}

// (void)dismissKeyboard dismisses the keyboard

-(void)dismissKeyboard
{
     [self.inputname resignFirstResponder];
}

// (void)cleanAudioFiles cleans the directory, keeping the saved folder as well as the file of the metronome.

-(void)cleanAudioFiles
{
    filemgr = [NSFileManager defaultManager];
    NSError *error;
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:appdel.path
                                                                        error:NULL];
    NSMutableArray* Audiofiles;
    Audiofiles = [[NSMutableArray alloc] init];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop)
    {
        NSString *name = (NSString *)obj;
        if (![[name substringToIndex:1] isEqualToString:@"."])
        {
            [Audiofiles addObject:[name substringToIndex:[name length]]];
        }
    }];
    int i=0;
    while (i<[Audiofiles count])
    {
        NSString* file=[Audiofiles objectAtIndex:i];
        if (!([file isEqualToString:@"Saved"] || [file isEqualToString:@"beat.aif"]))
        {
            NSString* path=[appdel.path stringByAppendingPathComponent:file];
            [filemgr removeItemAtURL:[NSURL fileURLWithPath:path] error:&error];
        }
        i+=1;
    }
}

// (void)viewDidLoad executes the tsks when the view loads.

- (void)viewDidLoad
{
    [super viewDidLoad];
    appdel=[UIApplication sharedApplication].delegate;
    [self cleanAudioFiles];
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
    if ([selectedfile isEqualToString:@""])
    {
        appdel.currentdirectory=@"/Default";
        filemgr = [NSFileManager defaultManager];
        path=[appdel.path stringByAppendingString:@"/Default"];
        [filemgr createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:NULL];
    }
    
    if (![selectedfile isEqualToString:@""])
    {
        [self navigate_From_Saved:path];
    }
    slidervalue.text=[NSString stringWithFormat:@"%d",(int)slider.value];
    saver.name = saver.oldname;
    [saver directoryURL];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];

}

// (void)navigate_From_Saved Loads the selected saved track, creates the players

-(void)navigate_From_Saved:(NSString*)path
{
    inputname.text = selectedfile;
    saver.oldname = selectedfile;
    appdel.currentdirectory=[@"/" stringByAppendingString:selectedfile];
    [saver copyFromSaved:selectedfile];
    path=[appdel.path stringByAppendingString:appdel.currentdirectory];
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                        error:NULL];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSString *name = (NSString *)obj;
        if ([[name substringFromIndex:[name length]-4] isEqualToString:@".aif"])
        {
            trackCounter+=1;
            [self addPlayer];
            [self addTrack:name];
        }
        if([[name substringFromIndex:[name length]-4] isEqualToString:@".mid"])
        {
            NSString* midipath=[path stringByAppendingString:name];
            amc.getInstrument((char*)[midipath UTF8String]);
        }
    }];
    [self getInstrument:path];
}

// (void)addTrack adds a track with a given name.

-(void)addTrack:(NSString*)name
{
    XYZTrack* demotrack;
    demotrack=[[XYZTrack alloc]init];
    demotrack.instrument=[[XYZInstrument alloc]init];
    demotrack.trackName=[name substringToIndex:[name length]-4];
    demotrack.isSelected=TRUE;
    [tracks addObject:demotrack];
}

// (void)getInstrument For each track of a given melody, it retrieves the last selescted instrument.

-(void)getInstrument:(NSString*)path
{
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                        error:NULL];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop)
    {
        NSString *name = (NSString *)obj;
        if([[name substringFromIndex:[name length]-4] isEqualToString:@".mid"])
        {
            NSString* midipath=[path stringByAppendingString:[@"/" stringByAppendingString:name]];
            unsigned short instrument;
            instrument=amc.getInstrument((char*)[midipath UTF8String]);
            int i=0;
            while (i<[tracks count])
            {
                XYZTrack* demotrack;
                demotrack=[tracks objectAtIndex:i];
                XYZInstrument* demoInstrument;
                if([demotrack.trackName isEqualToString:[name substringToIndex:[name length]-4]])
                {
                    int j=0;
                    while (j<[appdel.instruments count])
                    {
                        demoInstrument=[[XYZInstrument alloc]init];
                        demoInstrument=[appdel.instruments objectAtIndex:j];
                        if (demoInstrument.number==instrument)
                        {
                            demotrack.instrument=demoInstrument;
                        }
                        j++;
                    }
                    [tracks replaceObjectAtIndex:i withObject:demotrack];
                }
                ++i;
            }
        }
    }];
}

// (void)viewDidAppear:(BOOL)animated Executes tasks when the view appears.

-(void)viewDidAppear:(BOOL)animated
{
    chosenInstrument=appdel.newinstrument.Name;
    appdel.newinstrument.Name=@"";
        if (appdel.selectedtrack!=-1)
        {
            XYZTrack* demotrack;
            demotrack=[tracks objectAtIndex:appdel.selectedtrack];
            demotrack.instrument.Name=chosenInstrument;
            [tracks replaceObjectAtIndex:appdel.selectedtrack withObject:demotrack];
            [trackTable reloadData];
            NSString* path;
            char array [96];
                if ([selectedfile isEqualToString:@""])
                {
                path=[appdel.path stringByAppendingString:[@"/Default/track" stringByAppendingString:[[NSString stringWithFormat:@"%d",appdel.selectedtrack+1] stringByAppendingString:@".aif"]]];
            }
                else
                {
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

-(void)viewWillDisappear:(BOOL)animated
{
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
    if([tableView cellForRowAtIndexPath:indexPath].accessoryType == UITableViewCellAccessoryCheckmark)
    {
        [tableView cellForRowAtIndexPath:indexPath].accessoryType = UITableViewCellAccessoryNone;
    }
    else
    {
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
    while (i<[tracks count])
    {
        XYZTrack* tempTrack;
        tempTrack=[tracks objectAtIndex:i];
        if (tempTrack.isSelected)
        {
            NSLog(@"selected");
        }
        else
        {
            NSLog(@"not selected");
        }
        ++i;
    }
}

-(void)viewInstruments
{
    int i=0;
    NSLog(@"haha");
    while (i<[tracks count])
    {
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
    if ([[segue identifier] isEqualToString:@"Instruments"])
    {
    XYZTrack *demotrack;
    demotrack=[[XYZTrack alloc]init];
    demotrack=[tracks objectAtIndex:appdel.selectedtrack];
    appdel.newinstrument.Name=demotrack.instrument.Name;
    }
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


@end
