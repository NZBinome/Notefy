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
@property (weak, nonatomic) IBOutlet UIButton *Comment;

@property (weak, nonatomic) IBOutlet UITextField *CommentText;
@property CGFloat offset;
@property BOOL isCommentFeed;
@property NSMutableArray* Comments;
@property XYZComment* CommentFeed;
@property (weak, nonatomic) IBOutlet UITableView *CommentTable;
@property BOOL isScript;
@property BOOL isPlaying;
@property (weak, nonatomic) IBOutlet UIButton *PlayPause;
@property BOOL isApplauseCount;
@property BOOL isCommentCount;
@property BOOL isShareCount;
@property (weak, nonatomic) IBOutlet UILabel *ApplauseCount;
@property (weak, nonatomic) IBOutlet UILabel *CommentCount;
@property (weak, nonatomic) IBOutlet UILabel *ShareCount;
@property CGPoint OriginalCenter;
@property (weak, nonatomic) IBOutlet UIButton *MyProfile;
@property (weak, nonatomic) IBOutlet UIImageView *ApplauseBackground;
@property (weak, nonatomic) IBOutlet UIImageView *ShareBackground;
@property (weak, nonatomic) IBOutlet UITextField *SearchBar;
@property NSString* SearchResult;
@property BOOL isSearchResult;



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
@synthesize CommentText;
@synthesize Comment;
@synthesize offset;
@synthesize isCommentFeed;
@synthesize CommentFeed;
@synthesize Comments;
@synthesize CommentTable;
@synthesize isScript;
@synthesize isPlaying;
@synthesize PlayPause;
@synthesize isApplauseCount;
@synthesize isCommentCount;
@synthesize isShareCount;
@synthesize ApplauseCount;
@synthesize ShareCount;
@synthesize CommentCount;
@synthesize MyProfile;
@synthesize ShareBackground;
@synthesize ApplauseBackground;
@synthesize SearchBar;
@synthesize SearchResult;
@synthesize isSearchResult;

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
    [self performSegueWithIdentifier:@"ProfileFromListen" sender:self];
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
    
    if (isCommentFeed) {
            isScript=[elementName isEqualToString:@"Script"];
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
    
    if ([elementName isEqualToString:@"CommentCount"]) {
        isCommentCount=true;
    }
    
    if ([elementName isEqualToString:@"ApplauseCount"]) {
        isApplauseCount=true;
    }
    
    if ([elementName isEqualToString:@"ShareCount"]) {
        isShareCount=true;
    }
    
    if ([elementName isEqualToString:@"Comment"]) {
        isCommentFeed=true;
        CommentFeed = [[XYZComment alloc]init];
    }
    if ([elementName isEqualToString:@"SearchResult"]) {
        isSearchResult=true;
    }
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    if (isSearchResult) {
        SearchResult=string;
        isSearchResult=false;
    }
    
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
    if (isScript) {
        CommentFeed.Script=string;
        isScript=false;
    }
    if (isCommentCount) {
        CommentCount.text=string;
        isCommentCount=false;
    }
    if (isShareCount) {
        ShareCount.text=string;
        isShareCount=false;
    }
    if (isApplauseCount) {
        ApplauseCount.text=string;
        isApplauseCount=false;
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
        //NSLog(Creator.Stage_Name);
        SelectedMelody = Melody;
    }
    if ([elementName isEqualToString:@"Applause"]) {
        isApplause=false;
    }
    if ([elementName isEqualToString:@"Share"]) {
        isApplause=false;
    }
    if ([elementName isEqualToString:@"Comment"]) {
        CommentFeed.User=User1;
        CommentFeed.Melody=Melody;
        [Comments addObject:CommentFeed];
        isCommentFeed = false;
    }
}

-(void)assign
{
    MelodyName.text = SelectedMelody.Title;
    [UserName setTitle:Creator.Stage_Name forState:UIControlStateNormal];
    Time.text = [self fixDate:SelectedMelody.Date];
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
        [Applause setAlpha:1.0];
        [ApplauseBackground setAlpha:1.0];
    }
    if ((AccountId==Sharer)&&(SelectedMelody.Id==SharedMelody)) {
        didShare = true;
        [Share setAlpha:1.0];
        [ShareBackground setAlpha:1.0];
    }
    
}

- (IBAction)Comment:(id)sender {
    NSString *path=[ServerLocation stringByAppendingString:@"WriteComment.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", SelectedMelody.Id]];
    path = [path stringByAppendingString:@"&Script="];
    path = [path stringByAppendingString:CommentText.text];
    CommentText.text=@"";
    XYZComment* demoComment;
    [self getData:path];
    long count = [CommentCount.text integerValue];
    count+=1;
    CommentCount.text = [NSString stringWithFormat:@"%ld",count];
    [self dismissKeyboard];
    [self getCommentsOfMelodies];
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
}

- (IBAction)play:(id)sender {
    if (isPlaying)
    {
        [Player pause];
        [PlayPause setImage:[UIImage imageNamed:@"Play.png"] forState:UIControlStateNormal];
    }
    else
    {
        [Player play];
        [PlayPause setImage:[UIImage imageNamed:@"Pause.png"] forState:UIControlStateNormal];
    }
    isPlaying=!isPlaying;
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
    [PlayPause setImage:[UIImage imageNamed:@"Play.png"] forState:UIControlStateNormal];
    isPlaying=false;
    AVPlayerItem* playerItem = [AVPlayerItem playerItemWithURL:URL];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(itemDidFinishPlaying:) name:AVPlayerItemDidPlayToEndTimeNotification object:playerItem];
    Player = [[AVPlayer alloc] initWithPlayerItem:playerItem];
}

- (void)viewDidLoad
{
    SearchResult=@"";
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    ServerLocation = appdel.ServerLocation;
    AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
    didApplaud=false;
    didShare=false;
    Comments = [[NSMutableArray alloc]init];
    [super viewDidLoad];
    SelectedMelody = [[XYZMelody alloc]init];
    Creator = [[XYZUser alloc]init];
    SelectedMelody.Id = MelodyId;
    CommentTable.dataSource = self;
    CommentTable.delegate = self;
    [self InitializeView];
    
    UserName.tag = Creator.Id;
    URL = [[NSURL alloc]init];
    
    ///////////////////To BE Added When Database Populated //////////////
    NSString* MelodyPath;

    MelodyPath = [@"Melodies/" stringByAppendingString:[NSString stringWithFormat:@"%d/%d/Melody.aif",Creator.Id,SelectedMelody.Id]];
    
    ///////////////////////////////////////////////////////////////////////
    
    URL = [NSURL URLWithString:[ServerLocation stringByAppendingString:MelodyPath]];
    [self startPlaybackForItemWithURL];
    isPlaying=true;
    [PlayPause setImage:[UIImage imageNamed:@"Pause.png"] forState:UIControlStateNormal];
    
    [self getCommentsOfMelodies];
    
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];
    [self registerForKeyboardNotifications];

    
    
    // Do any additional setup after loading the view.
    self.OriginalCenter = self.view.center;
    MyProfile.tag=AccountId;
}

-(void)getCommentsOfMelodies
{
    NSString* path;
    NSError *error;
    [Comments removeAllObjects];
    path=[ServerLocation stringByAppendingString:@"GetComments.php?MelodyId="];
    path=[path stringByAppendingString:[NSString stringWithFormat:@"%d", SelectedMelody.Id]];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString *content=[NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    NSData *data = [content dataUsingEncoding:NSUTF8StringEncoding];
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    [parser setDelegate:self];
    [parser parse];
    [CommentTable reloadData];
}

- (void)viewWillDisappear:(BOOL)animated
{
    
    [self deregisterFromKeyboardNotifications];
    [super viewWillDisappear:animated];
    [Player pause];
    
}

-(void)viewDidAppear:(BOOL)animated
{
    SearchBar.text=@"";
}

-(void)dismissKeyboard
{
    [CommentText resignFirstResponder];
    [SearchBar resignFirstResponder];
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
        //[Applause setTitle:@"Applaud" forState:UIControlStateNormal];
        [Applause setAlpha:0.3];
        [ApplauseBackground setAlpha:0.5];
        long count = [ApplauseCount.text integerValue];
        count-=1;
        ApplauseCount.text = [NSString stringWithFormat:@"%ld",count];

    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"InsertApplause.php?UserId="];
        //[Applause setTitle:@"You Applauded" forState:UIControlStateNormal];
        [Applause setAlpha:1.0];
        [ApplauseBackground setAlpha:1.0];
        long count = [ApplauseCount.text integerValue];
        count+=1;
        ApplauseCount.text = [NSString stringWithFormat:@"%ld",count];

    }
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d",SelectedMelody.Id]];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    [NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    didApplaud = !didApplaud;
}

- (IBAction)share:(id)sender {
    NSString* path;
    NSError *error;
    
    if (didShare) {
        path=[ServerLocation stringByAppendingString:@"DeleteShare.php?UserId="];
      //  [Share setTitle:@"Share" forState:UIControlStateNormal];
        [Share setAlpha:0.3];
        [ShareBackground setAlpha:0.5];
        long count = [ShareCount.text integerValue];
        count-=1;
        ShareCount.text = [NSString stringWithFormat:@"%ld",count];
    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"InsertShare.php?UserId="];
       // [Share setTitle:@"You Shared" forState:UIControlStateNormal];
        [Share setAlpha:1.0];
        [ShareBackground setAlpha:1.0];
        long count = [ShareCount.text integerValue];
        count+=1;
        ShareCount.text = [NSString stringWithFormat:@"%ld",count];
    }
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    path = [path stringByAppendingString:@"&MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d",SelectedMelody.Id]];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    [NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    didShare = !didShare;
}


- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}



- (void)registerForKeyboardNotifications {
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
    
}

- (void)deregisterFromKeyboardNotifications {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardDidHideNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIKeyboardWillHideNotification
                                                  object:nil];
    
}



- (void)keyboardWasShown:(NSNotification *)notification
{
    NSDictionary* info = [notification userInfo];
    
    CGSize keyboardSize = [[info objectForKey:UIKeyboardFrameBeginUserInfoKey] CGRectValue].size;
    
    int HeightOfCommentText = self.view.frame.size.height - CommentText.frame.origin.y-CommentText.frame.size.height;
    if ([CommentText isEditing])
    {
        self.view.center = CGPointMake(self.OriginalCenter.x,self.OriginalCenter.y-keyboardSize.height+HeightOfCommentText);
    }
}

- (void)keyboardWillBeHidden:(NSNotification *)notification
{
    self.view.center = self.OriginalCenter;
}

- (IBAction)Search:(id)sender {
    NSString* path;
    NSError* error;
    [self dismissKeyboard];
    path=[ServerLocation stringByAppendingString:@"Search_by_StageName.php?StageName="];
    path = [path stringByAppendingString:SearchBar.text];
    NSString *furl=[[NSString stringWithFormat:@"%@",path]stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString *content=[NSString stringWithContentsOfURL:[[NSURL alloc] initWithString:furl]encoding:NSUTF8StringEncoding error:&error];
    NSData *data = [content dataUsingEncoding:NSUTF8StringEncoding];
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    [parser setDelegate:self];
    [parser parse];
    if (![SearchResult isEqualToString:@""]) {
        UserId = [SearchResult integerValue];
        [self performSegueWithIdentifier:@"ProfileFromListen" sender:self];
    }
}




- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [Comments count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    XYZCommentOfMelody *cell;
    cell = [tableView dequeueReusableCellWithIdentifier:@"Comment" forIndexPath:indexPath];
    if (indexPath.row<[Comments count]) {
    XYZComment* DemoComment;
    
    DemoComment = [Comments objectAtIndex:indexPath.row];
    [cell.Username setTitle:DemoComment.User.Stage_Name forState:UIControlStateNormal];
    cell.Username.tag=DemoComment.User.Id;
    cell.Script.text=DemoComment.Script;
    NSString* fullpath;
    if (!DemoComment.User.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:DemoComment.User.Picture_link];
    }
    cell.ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    }

    return cell;
}



-(NSString*)fixDate:(NSString*)Date
{
    unsigned Flags = NSYearCalendarUnit| NSMonthCalendarUnit| NSDayCalendarUnit| NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit;
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSLocale* currentLocale = [NSLocale currentLocale];
    
    
    
    NSDate *date = [dateFormat dateFromString:Date];
    
    NSDate* CurrentDate= [[NSDate alloc]init];
    [CurrentDate descriptionWithLocale:currentLocale];
    
    
    NSCalendar* CurrentCalendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    NSDateComponents* CurrentComponents = [CurrentCalendar components:Flags fromDate:CurrentDate];
    
    NSCalendar* Calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    NSDateComponents* Components = [Calendar components:Flags fromDate:date];
    
    if ([Components year]<[CurrentComponents year])
    {
        long Year = [CurrentComponents year] - [Components year];
        if (Year==1)
        {
            [NSString stringWithFormat:@"%ld year ago",Year];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld years ago",Year];
        }
    }
    
    else if ([Components month]<[CurrentComponents month])
    {
        long Month = [CurrentComponents month] - [Components month];
        if (Month==1)
        {
            return [NSString stringWithFormat:@"%ld month ago",Month];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld months ago",Month];
        }
    }
    
    else if ([Components day]<[CurrentComponents day])
    {
        long Day = [CurrentComponents day] - [Components day];
        if (Day==1)
        {
            return [NSString stringWithFormat:@"%ld day ago",Day];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld days ago",Day];
        }
    }
    else if ([Components hour]<[CurrentComponents hour])
    {
        long Hour = [CurrentComponents hour] - [Components hour];
        if (Hour==1)
        {
            return [NSString stringWithFormat:@"%ld hr ago",Hour];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld hrs ago",Hour];
        }
    }
    else if ([Components minute]<[CurrentComponents minute])
    {
        long Minute = [CurrentComponents minute] - [Components minute];
        if (Minute==1)
        {
            return [NSString stringWithFormat:@"%ld min ago",Minute];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld mins ago",Minute];
        }
    }
    else
    {
        long Second = [CurrentComponents second] - [Components second];
        if (Second==1)
        {
            return [NSString stringWithFormat:@"%ld sec ago",Second];
        }
        else
        {
            return [NSString stringWithFormat:@"%ld secs ago",Second];
        }
    }
    return @"";
}



#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"ProfileFromListen"])
    {
        [segue.destinationViewController setId:UserId];
    }
    
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


-(BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender
{
    /*
    if([identifier isEqualToString:@"ProfileFromListen"])
    {
        if (UserId == 0) {
            return NO;
        }
    }
     */
    return NO;
}


@end
