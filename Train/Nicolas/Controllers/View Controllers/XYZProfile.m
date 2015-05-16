//
//  XYZProfile.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/10/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZProfile.h"

@interface XYZProfile ()
@property BOOL isUser;
@property BOOL isFirst_Name;
@property BOOL isLast_Name;
@property BOOL isStage_Name;
@property BOOL isPicture_Link;
@property XYZUser* User;
@property int AccountId;
@property NSString* ServerLocation;
@property BOOL isMelody;
@property BOOL isFile_Link;
@property BOOL isTitle;
@property BOOL isDate;
@property XYZMelody* Melody;
@property XYZUser* User1;
@property NSMutableArray* Feeds;
@property (weak, nonatomic) IBOutlet UITableView *MelodyTable;
@property int UserId;
@property int Followed;
@property int Follower;
@property BOOL isFollow;
@property BOOL isFollower;
@property BOOL isFollowed;
@property BOOL isFan;
@property BOOL isId;
@property XYZCreate* Create;
@property XYZShare* Share;
@property BOOL isFeed;
@property BOOL isCreate;
@property BOOL isShare;
@property int ChosenMelody;
@property BOOL isShareCount;
@property BOOL isCommentCount;
@property BOOL isApplauseCount;
@property BOOL isFanNumber;
@property (weak, nonatomic) IBOutlet UIButton *MyProfile;
@property (weak, nonatomic) IBOutlet UITextField *SearchBar;
@property NSString* SearchResult;
@property BOOL isSearchResult;


@end

@implementation XYZProfile
@synthesize isUser;
@synthesize isFirst_Name;
@synthesize isLast_Name;
@synthesize isStage_Name;
@synthesize User;
@synthesize AccountId;
@synthesize ServerLocation;
@synthesize isPicture_Link;
@synthesize isMelody;
@synthesize isFile_Link;
@synthesize isTitle;
@synthesize isDate;
@synthesize Melody;
@synthesize Feeds;
@synthesize MelodyTable;
@synthesize UserId;
@synthesize Followed;
@synthesize Follower;
@synthesize isFollow;
@synthesize isFollowed;
@synthesize isFollower;
@synthesize isFan;
@synthesize User1;
@synthesize isId;
@synthesize Create;
@synthesize Share;
@synthesize isFeed;
@synthesize isCreate;
@synthesize isShare;
@synthesize ChosenMelody;
@synthesize isShareCount;
@synthesize isCommentCount;
@synthesize isApplauseCount;
@synthesize isFanNumber;
@synthesize MyProfile;
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
    if (isFeed)
    {
        isDate=[elementName isEqualToString:@"Date"];
        isShareCount = [elementName isEqualToString:@"ShareCount"];
        isCommentCount = [elementName isEqualToString:@"CommentCount"];
        isApplauseCount = [elementName isEqualToString:@"ApplauseCount"];
    }
    if (isUser)
    {
        isId = [elementName isEqualToString:@"Id"];
        isFirst_Name=[elementName isEqualToString:@"First_Name"];
        isLast_Name=[elementName isEqualToString:@"Last_Name"];
        isStage_Name=[elementName isEqualToString:@"Stage_Name"];
        isPicture_Link=[elementName isEqualToString:@"Picture_Link"];
        isFanNumber = [elementName isEqualToString:@"FanCount"];
    }
    
    if ([elementName isEqualToString:@"SearchResult"]) {
        isSearchResult=true;
    }
    
    if (isMelody)
    {
        isId = [elementName isEqualToString:@"Id"];
        isDate=[elementName isEqualToString:@"Date"];
        isFile_Link=[elementName isEqualToString:@"File_Link"];
        isTitle=[elementName isEqualToString:@"Title"];
    }
    
    if (isFollow) {
        isFollowed = [elementName isEqualToString:@"Followed"];
        isFollower = [elementName isEqualToString:@"Follower"];
    }

    if ([elementName isEqualToString:@"User"])
    {
        User1 = [[XYZUser alloc]init];
        isUser=true;
    }
    
    if ([elementName isEqualToString:@"Follows"])
    {
        isFollow=true;
    }
    
    if ([elementName isEqualToString:@"Melody"])
    {
        isMelody=true;
        Melody=[[XYZMelody alloc]init];
    }
    if ([elementName isEqualToString:@"Share"]) {
        Share = [[XYZShare alloc]init];
        Share.FromProfile=true;
        isFeed=true;
        isShare=true;
    }
    if ([elementName isEqualToString:@"Create"]) {
        Create = [[XYZCreate alloc]init];
        isFeed=true;
        isCreate=true;
    }
}

-(void)setId:(int)Id
{
    UserId=Id;
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
    if (isFanNumber) {
        User1.FanNumber=string;
        isFanNumber=false;
    }
    if (isDate) {
        if (isMelody)
        {
            Melody.Date=string;
        }
        
        else
        {
            if (isShare) {
                Share.Date=string;
            }
            if (isCreate) {
                Create.Date=string;
            }
        }
        isDate=false;
    }
    if (isFile_Link) {
        Melody.File_Link=string;
        isFile_Link=false;
    }
    if (isTitle) {
        Melody.Title=string;
        isTitle=false;
    }
    if (isFollowed)
    {
        Followed=[string intValue];
        isFollowed=false;
    }
    if (isFollower)
    {
        Follower=[string intValue];
        isFollower=false;
    }
    
    if (isShareCount) {
        if (isShare) {
            Share.ShareCount=string;
        }
        if (isCreate) {
            Create.ShareCount=string;
        }
        isShareCount=false;
    }
    if (isApplauseCount) {
        if (isShare) {
            Share.ApplauseCount=string;
        }
        if (isCreate) {
            Create.ApplauseCount=string;
        }
        isApplauseCount=false;
    }
    if (isCommentCount) {
        if (isShare) {
            Share.CommentCount=string;
        }
        if (isCreate) {
            Create.CommentCount=string;
        }
        isCommentCount=false;
    }
    
    if (isId) {
        if (isUser) {
            User1.Id=[string intValue];
        }
        if (isMelody) {
            Melody.Id=[string intValue];
        }
    }
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
    
    if ([elementName isEqualToString:@"User"])
    {
        isUser=false;
    }
    
    if ([elementName isEqualToString:@"Sharer"]) {
        Share.Sharer = User1;
    }
    
    if ([elementName isEqualToString:@"Original"]) {
        Share.User = User1;
    }
    
    if ([elementName isEqualToString:@"Melody"])
    {
        isMelody=false;
    }
    if ([elementName isEqualToString:@"Create"]) {

        Create.User=User1;
        Create.Melody = Melody;
        [Feeds addObject:Create];
        isCreate=false;
    }
    if ([elementName isEqualToString:@"Share"]) {

        Share.Melody = Melody;
        [Feeds addObject:Share];
        isShare=false;
    }
    if ([elementName isEqualToString:@"Header"]) {
        User.Id = User1.Id;
        User.Stage_Name = User1.Stage_Name;
        User.Picture_link = User1.Picture_link;
        User.Last_Name = User1.Last_Name;
        User.First_Name = User1.First_Name;
        User.FanNumber = User1.FanNumber;
    }
    if ([elementName isEqualToString:@"Follows"])
    {
        isFollow=false;
    }

}

-(void)viewDidAppear:(BOOL)animated
{
    SearchBar.text=@"";
}

-(void)assign:(XYZProfileInfo*)cell
{
    NSString* fullpath;
    cell.LastName.text = User.Last_Name;
    cell.FirstName.text=User.First_Name;
    cell.StageName.text=User.Stage_Name;
    cell.FanNumber.text=User.FanNumber;
    if ([User.FanNumber isEqualToString:@"1"])
    {
        cell.FanNumber.text=[cell.FanNumber.text stringByAppendingString:@" Fan"];
    }
    else
    {
        cell.FanNumber.text=[cell.FanNumber.text stringByAppendingString:@" Fans"];
    }
    if (!User.Picture_link)
    {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:User.Picture_link];
    }
    cell.ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
    if (AccountId == User.Id)
    {
        cell.BecomeAFan.hidden=true;
        cell.BecomeAFan.enabled=NO;
    }
    else
    {
        if ((Follower==AccountId)&&(Followed==User.Id))
        {
            isFan=true;
            cell.BecomeAFan.hidden=false;
            [cell.BecomeAFan setImage:[UIImage imageNamed:@"You're a fan.png"] forState:UIControlStateNormal];
        }
    }
}
- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)search:(id)sender {
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
        [self performSegueWithIdentifier:@"ProfileToProfile" sender:self];
    }
}


- (void)viewDidLoad
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    [super viewDidLoad];
    AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
    MyProfile.tag=AccountId;
    MelodyTable.dataSource = self;
    MelodyTable.delegate = self;
    ServerLocation=appdel.ServerLocation;
    User=[[XYZUser alloc]init];
    Feeds=[[NSMutableArray alloc]init];
    User.Id=UserId;
    UserId=0;
    ChosenMelody=0;

    ///////////////////////////////////// TO BE REMOVED /////////////////
    
    //User.Id=2;
    
    /////////////////////////////////////
    
    [self InitializeView];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];
    
}

-(void)viewDidDisappear:(BOOL)animated
{
    UserId=0;
    ChosenMelody=0;
}

-(void)dismissKeyboard
{
    [SearchBar resignFirstResponder];
}

-(void)InitializeView
{
    NSString *path=[ServerLocation stringByAppendingString:@"GetUser.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", User.Id]];
    path = [path stringByAppendingString:@"&Follower="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    [self getData:path];
   // [self assign];
    
    path=[ServerLocation stringByAppendingString:@"GetMelodies.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", User.Id]];
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        // Perform async operation
        // Call your method/function here
        // Example:
        // NSString *result = [anObject calculateSomething];
        [self getData:path];
        [MelodyTable reloadData];
        dispatch_sync(dispatch_get_main_queue(), ^{
            // Update UI
            // Example:
            // self.myLabel.text = result;
            [MelodyTable reloadData];
            //[self assign];
            
        });
    });
}

- (IBAction)melodyPressed:(UIControl*)sender
{
    ChosenMelody = sender.tag;
    [self performSegueWithIdentifier:@"ProfileMelodyPressed" sender:self];
    
}

-(IBAction)userPressed:(UIControl*)sender
{
    UserId = sender.tag;
    [self performSegueWithIdentifier:@"ProfileToProfile" sender:self];
}


- (IBAction)followUnfollow:(id)sender {
    NSString* path;
    if (isFan)
    {
        path=[ServerLocation stringByAppendingString:@"Unfollow.php?Followed="];
        [sender setImage:[UIImage imageNamed:@"Become a fan.png"] forState:UIControlStateNormal];
    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"Follow.php?Followed="];
        [sender setImage:[UIImage imageNamed:@"You're a fan.png"] forState:UIControlStateNormal];
    }
    isFan=!isFan;
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", User.Id]];
    path = [path stringByAppendingString:@"&Follower="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    [self getData:path];
    [MelodyTable reloadData];
    
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.

    return [Feeds count]+1;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell;
    //NSLog(@"Count of feeds in index path %d",[Feeds count]);
    //NSLog(@"index path  : %d",indexPath.row);
    if (indexPath.row==0)
    {
        cell =[[XYZProfileInfo alloc]init];
        cell = [tableView dequeueReusableCellWithIdentifier:@"ProfileInfo" forIndexPath:indexPath];
        [self assign:(XYZProfileInfo*)cell];
    }
    
    else
    {
        cell = [[XYZFeedCell alloc]init];
        XYZFeed* DemoFeed;
        DemoFeed=[Feeds objectAtIndex:[Feeds count]-(indexPath.row)];
        if ([DemoFeed isKindOfClass:[XYZShare class]])
        {
            cell = [tableView dequeueReusableCellWithIdentifier:@"ShareCell" forIndexPath:indexPath];
        }
        else if ([DemoFeed isKindOfClass:[XYZCreate class]])
        {
            cell = [tableView dequeueReusableCellWithIdentifier:@"CreateCell" forIndexPath:indexPath];
        }
        [DemoFeed fillCell:(XYZFeedCell*)cell];
    }
    return cell;
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row==0)
    {
        if (AccountId == User.Id)
        {
            return 230;
        }
        return 306;
    }
    else{
    XYZFeed* DemoFeed;
    DemoFeed=[Feeds objectAtIndex:[Feeds count]-(indexPath.row)];
    if ([DemoFeed isKindOfClass:[XYZShare class]]){
        return 122;
    }
    else if ([DemoFeed isKindOfClass:[XYZCreate class]]){
        return 122;
    }
    }
    return 102;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
    if ([segue.identifier isEqualToString:@"ProfileMelodyPressed"]) {
        [segue.destinationViewController initializeMelodyId:ChosenMelody];
    }
    if ([segue.identifier isEqualToString:@"ProfileToProfile"]) {
        [segue.destinationViewController setId:UserId];
    }
}

-(BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender
{
    /*
    NSLog(@"check segue : %d",ChosenMelody);

    if([identifier isEqualToString:@"ProfileMelodyPressed"])
    {
        if (ChosenMelody==0)
        {
            return NO;
        }
    }
    if ([identifier isEqualToString:@"ProfileToProfile"])
    {
        if (UserId==0)
        {
            return NO;
        }
    }
     */
    return NO;
}


@end
