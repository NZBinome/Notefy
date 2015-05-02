//
//  XYZMelodyListen.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/18/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZMelodyListen.h"

@import AVFoundation;
@interface XYZMelodyListen ()
@property int MelodyId;
@property NSString* ServerLocation;
@property XYZMelody* SelectedMelody;
@property XYZUser* Creator;
@property int UserId;
@property (weak, nonatomic) IBOutlet UIButton *UserName;
@property BOOL isUser;
@property BOOL isMelody;
@property BOOL isId;
@property BOOL isLast_Name;
@property BOOL isFirst_Name;
@property BOOL isStage_Name;
@property BOOL isTitle;
@property BOOL isPicture_Link;
@property BOOL isDate;
@property BOOL isMelody_Link;
@property XYZUser* User1;
@property XYZMelody* Melody;
@property (weak, nonatomic) IBOutlet UILabel *Time;
@property (weak, nonatomic) IBOutlet UILabel *MelodyName;
@property (weak, nonatomic) IBOutlet UIImageView *ProfilePicture;
@property AVPlayer* Player;
@property NSURL* URL;
@property int AccountId;
@property BOOL isApplause;
@property BOOL isShare;
@property int Spectator;
@property int ListenedMelody;
@property int Sharer;
@property int SharedMelody;
@property BOOL isSpectator;
@property BOOL isListenedMelody;
@property BOOL isSharer;
@property BOOL isSharedMelody;
@property (weak, nonatomic) IBOutlet UIButton *Applause;
@property (weak, nonatomic) IBOutlet UIButton *Share;
@property BOOL didApplaud;
@property BOOL didShare;



@end

@implementation XYZMelodyListen
@synthesize MelodyId;
@synthesize ServerLocation;
@synthesize SelectedMelody;
@synthesize Creator;
@synthesize UserId;
@synthesize UserName;
@synthesize isDate;
@synthesize isFirst_Name;
@synthesize isId;
@synthesize isLast_Name;
@synthesize isMelody;
@synthesize isMelody_Link;
@synthesize isPicture_Link;
@synthesize isStage_Name;
@synthesize isTitle;
@synthesize isUser;
@synthesize Melody;
@synthesize User1;
@synthesize MelodyName;
@synthesize Time;
@synthesize ProfilePicture;
@synthesize URL;
@synthesize AccountId;
@synthesize Player;
@synthesize  isShare;
@synthesize isApplause;
@synthesize SharedMelody;
@synthesize Sharer;
@synthesize Spectator;
@synthesize ListenedMelody;
@synthesize isSharedMelody;
@synthesize isSharer;
@synthesize isSpectator;
@synthesize isListenedMelody;
@synthesize Share;
@synthesize Applause;
@synthesize didApplaud;
@synthesize didShare;



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)initializeMelodyId:(int)_MelodyId
{
    MelodyId = _MelodyId;
}

-(IBAction)userPressed:(UIControl*)sender
{
    UserId = sender.tag;
    [self performSegueWithIdentifier:@"Profile" sender:self];
}



-(void)getData:(NSString*)path
{
    NSError *error;
    
    NSString *url=[[NSString stringWithFormat:@"%@",path]
                   stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString *content=[NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:url]
                                               encoding:NSUTF8StringEncoding error:&error];
    NSData *data = [content dataUsingEncoding:NSUTF8StringEncoding];
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    [parser setDelegate:self];
    [parser parse];
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict
{
    
    if (isShare) {
        isSharer = [elementName isEqualToString:@"Sharer"];
        isSharedMelody = [elementName isEqualToString:@"Melody"];
    }
    if (isApplause) {
        isSpectator = [elementName isEqualToString:@"Spectator"];
        isListenedMelody = [elementName isEqualToString:@"Melody"];
    }

    if (isUser)
    {
        isId = [elementName isEqualToString:@"Id"];
        isFirst_Name=[elementName isEqualToString:@"First_Name"];
        isLast_Name=[elementName isEqualToString:@"Last_Name"];
        isStage_Name=[elementName isEqualToString:@"Stage_Name"];
        isPicture_Link=[elementName isEqualToString:@"Picture_Link"];
    }
    
    if (isMelody)
    {
        isId = [elementName isEqualToString:@"Id"];
        isDate=[elementName isEqualToString:@"Date"];
        isTitle=[elementName isEqualToString:@"Title"];
    }
    
    if ([elementName isEqualToString:@"Applause"]) {
        isApplause = true;
    }
    
    if ([elementName isEqualToString:@"Share"]) {
        isShare = true;
    }
    
    if ([elementName isEqualToString:@"User"])
    {
        isUser=true;
        User1 = [[XYZUser alloc]init];
    }
    
    
    if ([elementName isEqualToString:@"Melody"])
    {
        isMelody=true;
        Melody=[[XYZMelody alloc]init];
    }
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    if (isStage_Name) {
        User1.Stage_Name=string;
        isStage_Name=false;
    }
    if (isLast_Name) {
        User1.Last_Name=string;
        isLast_Name=false;
    }
    if (isFirst_Name) {
        User1.First_Name=string;
        isFirst_Name=false;
    }
    if (isPicture_Link) {
        User1.Picture_link=string;
        isPicture_Link=false;
    }
    if (isDate) {
        if (isMelody)
        {
            Melody.Date=string;
        }
        isDate=false;
    }
    if (isId) {
        if (isUser) {
            User1.Id=[string intValue];
        }
        if (isMelody) {
            Melody.Id=[string intValue];
        }
        isId=false;
    }
    
    if (isTitle) {
        Melody.Title=string;
        isTitle=false;
    }
    if (isListenedMelody) {
        ListenedMelody = [string intValue];
        isListenedMelody = false;
    }
    if (isSpectator) {
        Spectator = [string intValue];
        isSpectator = false;
    }
    if (isSharedMelody) {
        SharedMelody = [string intValue];
        isSharedMelody=false;
    }
    if (isSharer) {
        Sharer = [string intValue];
        isSharer=false;
    }
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
    
    if ([elementName isEqualToString:@"User"])
    {
        isUser=false;
    }
    if ([elementName isEqualToString:@"Melody"])
    {
        isMelody=false;
    }
    if ([elementName isEqualToString:@"Header"]) {
        Creator = User1;
        SelectedMelody = Melody;
    }
    if ([elementName isEqualToString:@"Applause"]) {
        isApplause=false;
    }
    if ([elementName isEqualToString:@"Share"]) {
        isApplause=false;
    }
}

-(void)assign
{
    MelodyName.text = SelectedMelody.Title;
    [UserName setTitle:Creator.Stage_Name forState:UIControlStateNormal];
    Time.text = SelectedMelody.Date;
    NSString* fullpath;

    if (!Creator.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:Creator.Picture_link];
    }
    ProfilePicture.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    if ((AccountId==Spectator)&&(SelectedMelody.Id==ListenedMelody)) {
        didApplaud = true;
        [Applause setTitle:@"You Applauded" forState:UIControlStateNormal];
    }
    if ((AccountId==Sharer)&&(SelectedMelody.Id==SharedMelody)) {
        didShare = true;
        [Share setTitle:@"You Shared" forState:UIControlStateNormal];
    }
    
}

-(void)InitializeView
{
    NSString *path=[ServerLocation stringByAppendingString:@"GetMelody.php?MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", SelectedMelody.Id]];
    [self getData:path];
    path=[ServerLocation stringByAppendingString:@"GetShareApplause.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d",SelectedMelody.Id]];
    [self getData:path];
    [self assign];
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        // Perform async operation
        // Call your method/function here
        // Example:
        // NSString *result = [anObject calculateSomething];
//        [self getData:path];
        dispatch_sync(dispatch_get_main_queue(), ^{
            // Update UI
            // Example:
            // self.myLabel.text = result;
           // [MelodyTable reloadData];
            //[self assign];
            
        });
    });
}

- (IBAction)play:(id)sender {
        [Player play];
}

- (IBAction)pause:(id)sender {
    [Player pause];
}


-(void)startPlaybackForItemWithURL
{
    
    // First create an AVPlayerItem
    AVPlayerItem* playerItem = [AVPlayerItem playerItemWithURL:URL];
    
    // Subscribe to the AVPlayerItem's DidPlayToEndTime notification.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(itemDidFinishPlaying:) name:AVPlayerItemDidPlayToEndTimeNotification object:playerItem];
    
    // Pass the AVPlayerItem to a new player
    Player = [[AVPlayer alloc] initWithPlayerItem:playerItem];
    
    // Begin playback
    [Player play];
    
}

-(void)itemDidFinishPlaying:(NSNotification *) notification {
    // Will be called when AVPlayer finishes playing playerItem
    AVPlayerItem* playerItem = [AVPlayerItem playerItemWithURL:URL];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(itemDidFinishPlaying:) name:AVPlayerItemDidPlayToEndTimeNotification object:playerItem];
    Player = [[AVPlayer alloc] initWithPlayerItem:playerItem];
}

- (void)viewDidLoad
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    ServerLocation = appdel.ServerLocation;
    AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
    didApplaud=false;
    didShare=false;
    [super viewDidLoad];
    SelectedMelody = [[XYZMelody alloc]init];
    Creator = [[XYZUser alloc]init];
    SelectedMelody.Id = MelodyId;
    
    [self InitializeView];
    
    UserName.tag = Creator.Id;
    URL = [[NSURL alloc]init];
    URL = [NSURL URLWithString:[ServerLocation stringByAppendingString:@"Melodies/1/HEllo/track1.aif"]];
    [self startPlaybackForItemWithURL];
    

    //[self createStreamer];
    //[streamer start];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)applause:(id)sender {
    NSString* path;
    NSError *error;

    if (didApplaud) {
        path=[ServerLocation stringByAppendingString:@"DeleteApplause.php?UserId="];
        [Applause setTitle:@"Applaud" forState:UIControlStateNormal];

    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"InsertApplause.php?UserId="];
        [Applause setTitle:@"You Applauded" forState:UIControlStateNormal];

    }
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d",SelectedMelody.Id]];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString *content=[NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    didApplaud = !didApplaud;

}

- (IBAction)share:(id)sender {
    NSString* path;
    NSError *error;
    
    if (didShare) {
        path=[ServerLocation stringByAppendingString:@"DeleteShare.php?UserId="];
        [Share setTitle:@"Share" forState:UIControlStateNormal];
        
    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"InsertShare.php?UserId="];
        [Share setTitle:@"You Shared" forState:UIControlStateNormal];
        
    }
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d",SelectedMelody.Id]];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString *content=[NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    didShare = !didShare;
}


- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"Profile"])
    {
        [segue.destinationViewController setId:UserId];
    }
    
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


-(BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender
{
    if([identifier isEqualToString:@"Profile"])
    {
        if (UserId == 0) {
            return NO;
        }
    }
    return YES;
}


@end
