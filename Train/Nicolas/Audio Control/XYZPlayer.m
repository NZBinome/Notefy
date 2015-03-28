//
//  XYZPlayer.m
//  DoReMi
//
//  Created by Nicolas Jbeyli on 10/2/14.
//  Copyright (c) 2014 Nicolas Jbeyli. All rights reserved.
//

#import "XYZPlayer.h"

@interface XYZPlayer ()
@property AVAudioPlayer *player;
@property (getter = isPlaying) BOOL playing;
@property (nonatomic) UInt8 presetNumber;
@property (nonatomic) MusicPlayer musicPlayer;
@property (nonatomic) MusicSequence musicSequence;
@property (nonatomic) MusicTrack musicTrack;
@property (readwrite) AUGraph processingGraph;
@property (readwrite) AUNode samplerNode;
@property (readwrite) AUNode ioNode;
@property (readwrite) AudioUnit samplerUnit;
@property (readwrite) AudioUnit ioUnit;
@property int Tnumber;
@end

@implementation XYZPlayer
@synthesize player;
@synthesize playing = _playing;
@synthesize processingGraph = _processingGraph;
@synthesize samplerNode = _samplerNode;
@synthesize ioNode = _ioNode;
@synthesize ioUnit = _ioUnit;
@synthesize samplerUnit = _samplerUnit;
@synthesize presetNumber = _presetNumber;

@synthesize musicSequence = _musicSequence;
@synthesize musicTrack = _musicTrack;
@synthesize musicPlayer = _musicPlayer;
@synthesize Tnumber;




-(void)playerURL:(int)tracknumber
{
    Tnumber=tracknumber;
    NSLog(@"in playerURL");
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    NSString *pathToSave;
    pathToSave = [
                  [appdel.path stringByAppendingString:appdel.currentdirectory]
                  stringByAppendingPathComponent:[@"track" stringByAppendingString:[[NSString stringWithFormat:@"%d",Tnumber] stringByAppendingString:@".aif"]]
                  ];
    self.url = [NSURL fileURLWithPath:pathToSave];//FILEPATH];
}

-(void)updateURL:(NSString *)extension
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    NSString *pathToSave;
    pathToSave = [
                  [appdel.path stringByAppendingString:appdel.currentdirectory]
                  stringByAppendingPathComponent:[@"track" stringByAppendingString:[[NSString stringWithFormat:@"%d",Tnumber] stringByAppendingString:extension]]
                  ];
    self.url = [NSURL fileURLWithPath:pathToSave];//FILEPATH];

}

-(BOOL)XYZplay
{
    NSError *error;
    player = [[AVAudioPlayer alloc] initWithContentsOfURL:self.url error:&error];
    AVAudioSession *session = [AVAudioSession sharedInstance];
        [session setCategory:AVAudioSessionCategoryPlayback
                 withOptions:AVAudioSessionCategoryOptionMixWithOthers
                       error:&error];
    [session setActive:YES error:&error];

    if (!player)
    {
        NSLog(@"Failure to establish Player");
        return NO;
    }
    
    
    player.delegate = self;
    [player prepareToPlay];
    NSLog(@"after prepare to play");
    [player play];
    return  YES;
}


#pragma mark - Audio setup
- (BOOL) createAUGraph
{
    NSLog(@"Creating the graph");
    
    NewAUGraph(&_processingGraph);
    
    // create the sampler
    // for now, just have it play the default sine tone
	AudioComponentDescription cd = {};
	cd.componentType = kAudioUnitType_MusicDevice;
	cd.componentSubType = kAudioUnitSubType_Sampler;
	cd.componentManufacturer = kAudioUnitManufacturer_Apple;
	cd.componentFlags = 0;
	cd.componentFlagsMask = 0;
	AUGraphAddNode(self.processingGraph, &cd, &_samplerNode);
    
    
    // I/O unit
    AudioComponentDescription iOUnitDescription;
    iOUnitDescription.componentType          = kAudioUnitType_Output;
    iOUnitDescription.componentSubType       = kAudioUnitSubType_RemoteIO;
    iOUnitDescription.componentManufacturer  = kAudioUnitManufacturer_Apple;
    iOUnitDescription.componentFlags         = 0;
    iOUnitDescription.componentFlagsMask     = 0;
    
    AUGraphAddNode(self.processingGraph, &iOUnitDescription, &_ioNode);
    
    // now do the wiring. The graph needs to be open before you call AUGraphNodeInfo
	AUGraphOpen(self.processingGraph);
    
	AUGraphNodeInfo(self.processingGraph, self.samplerNode, NULL, &_samplerUnit);
    
    AUGraphNodeInfo(self.processingGraph, self.ioNode, NULL, &_ioUnit);
    
    AudioUnitElement ioUnitOutputElement = 0;
    AudioUnitElement samplerOutputElement = 0;
    AUGraphConnectNodeInput(self.processingGraph,
                                       self.samplerNode, samplerOutputElement, // srcnode, inSourceOutputNumber
                                       self.ioNode, ioUnitOutputElement);
    
    
	NSLog (@"AUGraph is configured");
	CAShow(self.processingGraph);
    
    return YES;
}

- (void) startGraph
{
    if (self.processingGraph) {
        // this calls the AudioUnitInitialize function of each AU in the graph.
        // validates the graph's connections and audio data stream formats.
        // propagates stream formats across the connections
        Boolean outIsInitialized;
        AUGraphIsInitialized(self.processingGraph,
                                        &outIsInitialized);
        if(!outIsInitialized)
            AUGraphInitialize(self.processingGraph);
        
        Boolean isRunning;
        AUGraphIsRunning(self.processingGraph,
                                    &isRunning);
        if(!isRunning)
            AUGraphStart(self.processingGraph);
        self.playing = YES;
    }
}
- (void) stopAUGraph {
    
    NSLog (@"Stopping audio processing graph");
    Boolean isRunning = false;
    AUGraphIsRunning (self.processingGraph, &isRunning);
    
    if (isRunning) {
        AUGraphStop(self.processingGraph);
        self.playing = NO;
    }
}

#pragma mark - Sampler

- (void) setupSampler:(UInt8) pn;
{
    // propagates stream formats across the connections
    Boolean outIsInitialized;
    AUGraphIsInitialized(self.processingGraph,
                                    &outIsInitialized);
    if(!outIsInitialized) {
        return;
    }
    if(pn < 0 || pn > 127) {
        return;
    }
    NSURL *bankURL;
    /*
     bankURL = [[NSURL alloc] initFileURLWithPath:[[NSBundle mainBundle]
     pathForResource:@"FluidR3_GM" ofType:@"sf2"]];
     */
    bankURL = [[NSURL alloc] initFileURLWithPath:[[NSBundle mainBundle]
                                                  pathForResource:@"gs_instruments" ofType:@"dls"]];
    NSLog(@"set pn %d", pn);
    
    // fill out a bank preset data structure
    AUSamplerBankPresetData bpdata;
    bpdata.bankURL  = (__bridge CFURLRef) bankURL;
    bpdata.bankMSB  = kAUSampler_DefaultMelodicBankMSB;
    bpdata.bankLSB  = kAUSampler_DefaultBankLSB;
    bpdata.presetID = (UInt8) pn;
    
    // set the kAUSamplerProperty_LoadPresetFromBank property
    AudioUnitSetProperty(self.samplerUnit,
                                    kAUSamplerProperty_LoadPresetFromBank,
                                    kAudioUnitScope_Global,
                                    0,
                                    &bpdata,
                                    sizeof(bpdata));
    
    NSLog (@"sampler ready");
}

- (void) setPresetNumber:(UInt8) p
{
    NSLog(@"setPresetNumber %d", p);
    
    _presetNumber = p;
    
    if(self.processingGraph)
        [self setupSampler:p];
}

#pragma mark -
#pragma mark Audio control
- (void)playNoteOn:(UInt32)noteNum :(UInt32)velocity
{
    UInt32 noteCommand = 0x90 | 0;
    NSLog(@"playNoteOn %lu %lu cmd %lx", noteNum, velocity, noteCommand);
	MusicDeviceMIDIEvent(self.samplerUnit, noteCommand, noteNum, velocity, 0);
}

- (void)playNoteOff:(UInt32)noteNum
{
	UInt32 noteCommand = 0x80 | 0;
	MusicDeviceMIDIEvent(self.samplerUnit, noteCommand, noteNum, 0, 0);
}

- (void) loadMIDIFile
{
    NewMusicPlayer(&_musicPlayer);
    
    NewMusicSequence(&_musicSequence);
    
    MusicPlayerSetSequence(self.musicPlayer, self.musicSequence);
    
    
    MusicSequenceFileLoad(self.musicSequence,
                                     (__bridge CFURLRef) self.url,
                                     0, // can be zero in many cases
                                     kMusicSequenceLoadSMF_ChannelsToTracks);
    MusicSequenceSetAUGraph(self.musicSequence, self.processingGraph);
    
    CAShow(self.musicSequence);
    
    UInt32 trackCount;
    MusicSequenceGetTrackCount(self.musicSequence, &trackCount);
    NSLog(@"Number of tracks: %lu", trackCount);
    MusicTrack track;
    for(int i = 0; i < trackCount; i++)
    {
        MusicSequenceGetIndTrack (self.musicSequence, i, &track);
        
        MusicTimeStamp track_length;
        UInt32 tracklength_size = sizeof(MusicTimeStamp);
        MusicTrackGetProperty(track, kSequenceTrackProperty_TrackLength, &track_length, &tracklength_size);
        NSLog(@"Track length %f", track_length);
        
        MusicTrackLoopInfo loopInfo;
        UInt32 lisize = sizeof(MusicTrackLoopInfo);
        MusicTrackGetProperty(track,kSequenceTrackProperty_LoopInfo, &loopInfo, &lisize );
        NSLog(@"Loop info: duration %f", loopInfo.loopDuration);
        
        [self iterate:track];
    }
    
    MusicPlayerPreroll(self.musicPlayer);
}


- (void) iterate: (MusicTrack) track
{
	MusicEventIterator	iterator;
	NewMusicEventIterator (track, &iterator);
    
    
    MusicEventType eventType;
	MusicTimeStamp eventTimeStamp;
    UInt32 eventDataSize;
    const void *eventData;
    
    Boolean	hasCurrentEvent = NO;
    MusicEventIteratorHasCurrentEvent(iterator, &hasCurrentEvent);
    while (hasCurrentEvent)
    {
        MusicEventIteratorGetEventInfo(iterator, &eventTimeStamp, &eventType, &eventData, &eventDataSize);
        NSLog(@"event timeStamp %f ", eventTimeStamp);
        switch (eventType) {
                
            case kMusicEventType_ExtendedNote : {
                ExtendedNoteOnEvent* ext_note_evt = (ExtendedNoteOnEvent*)eventData;
                NSLog(@"extended note event, instrumentID %lu", ext_note_evt->instrumentID);
                
            }
                break ;
                
            case kMusicEventType_ExtendedTempo : {
                ExtendedTempoEvent* ext_tempo_evt = (ExtendedTempoEvent*)eventData;
                NSLog(@"ExtendedTempoEvent, bpm %f", ext_tempo_evt->bpm);
                
            }
                break ;
                
            case kMusicEventType_User : {
                MusicEventUserData* user_evt = (MusicEventUserData*)eventData;
                NSLog(@"MusicEventUserData, data length %lu", user_evt->length);
            }
                break ;
                
            case kMusicEventType_Meta : {
                MIDIMetaEvent* meta_evt = (MIDIMetaEvent*)eventData;
                NSLog(@"MIDIMetaEvent, event type %d", meta_evt->metaEventType);
                
            }
                break ;
                
            case kMusicEventType_MIDINoteMessage : {
                MIDINoteMessage* note_evt = (MIDINoteMessage*)eventData;
                NSLog(@"note event channel %d", note_evt->channel);
                NSLog(@"note event note %d", note_evt->note);
                NSLog(@"note event duration %f", note_evt->duration);
                NSLog(@"note event velocity %d", note_evt->velocity);}
                break ;
                
            case kMusicEventType_MIDIChannelMessage : {
                MIDIChannelMessage* channel_evt = (MIDIChannelMessage*)eventData;
                NSLog(@"channel event status %X", channel_evt->status);
                NSLog(@"channel event d1 %X", channel_evt->data1);
                NSLog(@"channel event d2 %X", channel_evt->data2);
                
                if(channel_evt->status == (0xC0 & 0xF0)) {
                    [self setPresetNumber:channel_evt->data1];
                }
            }
                break ;
                
            case kMusicEventType_MIDIRawData : {
                MIDIRawData* raw_data_evt = (MIDIRawData*)eventData;
                NSLog(@"MIDIRawData, length %lu", raw_data_evt->length);
                
            }
                break ;
                
            case kMusicEventType_Parameter : {
                ParameterEvent* parameter_evt = (ParameterEvent*)eventData;
                NSLog(@"ParameterEvent, parameterid %lu", parameter_evt->parameterID);
                
            }
                break ;
                
            default :
                break ;
        }
        
        MusicEventIteratorHasNextEvent(iterator, &hasCurrentEvent);
        MusicEventIteratorNextEvent(iterator);
    }
}

- (BOOL)midiPlay
{
    [self createAUGraph];
    [self startGraph];
    [self setupSampler:self.presetNumber];
    [self loadMIDIFile];
    NSLog(@"starting music player");
    MusicPlayerStart(self.musicPlayer);
    return 1;
}

-(BOOL)metronomePlay
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    NSString *pathToBeat = [appdel.path stringByAppendingPathComponent:
                            [@"beat" stringByAppendingString:@".aif"]];
    self.url = [NSURL fileURLWithPath:pathToBeat];//FILEPATH];
    if([self XYZplay])
    {
        NSLog(@"metronome play");
    }

    return YES;
}


@end