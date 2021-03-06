//
//  XYZNewsFeed.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/12/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZNewsFeed.h"

@interface XYZNewsFeed ()
@property (weak, nonatomic) IBOutlet UITableView *FeedTable;
@property BOOL isUser;
@property BOOL isMelody;
@property BOOL isStage_Name;
@property BOOL isFirst_Name;
@property BOOL isLast_Name;
@property BOOL isDate;
@property BOOL isTitle;
@property BOOL isPicture_Link;
@property NSMutableArray* Feeds;
@property XYZCreate* Create;
@property XYZShare* Share;
@property NSString* ServerLocation;
@property BOOL isFeed;
@property BOOL isShare;
@property BOOL isCreate;
@property XYZUser* User1;
@property XYZMelody* Melody;
@property BOOL isId;
@property XYZComment* Comment;
@property BOOL isComment;
@property BOOL isScript;
@property XYZApplause* Applause;
@property BOOL isApplause;
@property BOOL isFollow;
@property XYZFollow* Follow;
@property (weak, nonatomic) IBOutlet UIButton *MyProfile;
@property int UserId;
@property int MelodyId;
@property BOOL isApplauseCount;
@property BOOL isCommentCount;
@property BOOL isShareCount;
@property BOOL isFanNumber;
@property (weak, nonatomic) IBOutlet UITextField *SearchBar;
@property NSString* SearchResult;
@property BOOL isSearchResult;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *ActivityIndicator;

@end

@implementation XYZNewsFeed
@synthesize FeedTable;
@synthesize isDate;
@synthesize isFirst_Name;
@synthesize isLast_Name;
@synthesize isMelody;
@synthesize isPicture_Link;
@synthesize isFeed;
@synthesize isStage_Name;
@synthesize isTitle;
@synthesize isUser;
@synthesize Feeds;
@synthesize ServerLocation;
@synthesize Share;
@synthesize Create;
@synthesize isCreate;
@synthesize  isShare;
@synthesize Melody;
@synthesize User1;
@synthesize isId;
@synthesize Comment;
@synthesize isComment;
@synthesize isScript;
@synthesize Applause;
@synthesize isApplause;
@synthesize isFollow;
@synthesize Follow;
@synthesize MyProfile;
@synthesize UserId;
@synthesize MelodyId;
@synthesize isApplauseCount;
@synthesize isCommentCount;
@synthesize isShareCount;
@synthesize isFanNumber;
@synthesize SearchBar;
@synthesize SearchResult;
@synthesize isSearchResult;
@synthesize ActivityIndicator;


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
    NSData* data = [content dataUsingEncoding:NSUTF8StringEncoding];
    NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];
    [parser setDelegate:self];
    [parser parse];
    [FeedTable reloadData];
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
    if (isComment) {
        isScript=[elementName isEqualToString:@"Script"];
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
        isTitle=[elementName isEqualToString:@"Title"];
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
    
    if ([elementName isEqualToString:@"Share"])
    {
        Share = [[XYZShare alloc]init];
        isShare = true;
        isFeed=true;
    }
    
    if ([elementName isEqualToString:@"Comment"]) {
        Comment = [[XYZComment alloc]init];
        isComment=true;
        isFeed = true;
    }
    
    if ([elementName isEqualToString:@"Create"])
    {
        Create = [[XYZCreate alloc]init];
        isCreate = true;
        isFeed=true;
    }
    if ([elementName isEqualToString:@"Applause"]) {
        Applause = [[XYZApplause alloc]init];
        isApplause = true;
        isFeed = true;
    }
    
    if ([elementName isEqualToString:@"Follow"]) {
        Follow = [[XYZFollow alloc]init];
        isFollow = true;
        isFeed = true;
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
    
    if (isScript) {
        Comment.Script=string;
        isScript=false;
    }
    if (isFirst_Name) {
        User1.First_Name=string;
        isFirst_Name=false;
    }
    if (isFanNumber) {
        User1.FanNumber=string;
        isFanNumber=false;
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
        
        else
        {
            if (isShare) {
                Share.Date=string;
            }
            if (isCreate) {
                Create.Date=string;
            }
            if (isComment) {
                Comment.Date=string;
            }
            if (isApplause) {
                Applause.Date=string;
            }
            if (isFollow) {
                Follow.Date=string;
            }
        }
        isDate=false;
    }
    if (isShareCount) {
        if (isShare) {
            Share.ShareCount=string;
        }
        if (isCreate) {
            Create.ShareCount=string;
        }
        if (isComment) {
            Comment.ShareCount=string;
        }
        if (isApplause) {
            Applause.ShareCount=string;
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
        if (isComment) {
            Comment.ApplauseCount=string;
        }
        if (isApplause) {
            Applause.ApplauseCount=string;
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
        if (isComment) {
            Comment.CommentCount=string;
        }
        if (isApplause) {
            Applause.CommentCount=string;
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
        else
        {
            if (isComment) {
                Comment.Id=[string intValue];
            }
        }
        isId=false;
    }

    if (isTitle) {
        Melody.Title=string;
        isTitle=false;
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
    if ([elementName isEqualToString:@"Share"])
    {
        Share.Melody = Melody;
        [Feeds addObject:Share];
        isShare = false;
        isFeed=false;
    }
    
    if ([elementName isEqualToString:@"Follower"]) {
            Follow.Follower = User1;
    }
    
    if ([elementName isEqualToString:@"Followed"]) {
        Follow.Followed=User1;
    }
    
    if ([elementName isEqualToString:@"Sharer"]) {
        Share.Sharer = User1;
    }
    
    if ([elementName isEqualToString:@"Original"]) {
        Share.User = User1;
    }
    
    if ([elementName isEqualToString:@"Follow"]) {
        [Feeds addObject:Follow];
        isFollow=false;
        isFeed=false;
    }
    
    if ([elementName isEqualToString:@"Create"])
    {
        Create.User = User1;
        Create.Melody = Melody;
        [Feeds addObject:Create];
        isCreate = false;
        isFeed=false;
    }
    if ([elementName isEqualToString:@"Comment"]) {
        Comment.User=User1;
        Comment.Melody=Melody;
        [Feeds addObject:Comment];
        isComment = false;
        isFeed = false;
    }
    if ([elementName isEqualToString:@"Applause"]) {
        Applause.User=User1;
        Applause.Melody=Melody;
        [Feeds addObject:Applause];
        isApplause=false;
        isFeed=false;
    }
}

-(void)viewDidAppear:(BOOL)animated
{
    SearchBar.text=@"";
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    ActivityIndicator.hidden=NO;
    [ActivityIndicator startAnimating];
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    ServerLocation=appdel.ServerLocation;
    int AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
    MyProfile.tag = AccountId;
    FeedTable.dataSource = self;
    FeedTable.delegate = self;
    Feeds = [[NSMutableArray alloc]init];
    // Do any additional setup after loading the view.
    SearchResult=@"";

    
    NSString *path=[ServerLocation stringByAppendingString:@"NewsFeed.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        // Perform async operation
        // Call your method/function here
        // Example:
        // NSString *result = [anObject calculateSomething];
        ActivityIndicator.hidden=NO;
        [ActivityIndicator startAnimating];

        [self getData:path];
        dispatch_sync(dispatch_get_main_queue(), ^{
            
            // Update UI
            // Example:
            // self.myLabel.text = result;
            [ActivityIndicator stopAnimating];
            ActivityIndicator.hidden=YES;
            [FeedTable reloadData];

        });
    });
        //[self getData:path];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]
                                   initWithTarget:self
                                   action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:tap];
}

-(void)dismissKeyboard
{
    [SearchBar resignFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)melodyPressed:(UIControl*)sender
{
    //NSLog(@"button tag : %d",sender.tag);
    MelodyId = sender.tag;
    [self performSegueWithIdentifier:@"MelodyPressed" sender:self];
    
}

-(IBAction)userPressed:(UIControl*)sender
{
    UserId = sender.tag;
    [self performSegueWithIdentifier:@"Profile" sender:self];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [Feeds count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    XYZFeedCell *cell;
    XYZFeed* DemoFeed;
    DemoFeed=[Feeds objectAtIndex:[Feeds count]-1-indexPath.row];
    
    if ([DemoFeed isKindOfClass:[XYZComment class]]) {
        cell = [tableView dequeueReusableCellWithIdentifier:@"CommentCell" forIndexPath:indexPath];
    }
    else if ([DemoFeed isKindOfClass:[XYZShare class]]){
        cell = [tableView dequeueReusableCellWithIdentifier:@"ShareCell" forIndexPath:indexPath];
    }
    else if ([DemoFeed isKindOfClass:[XYZApplause class]]){
        cell = [tableView dequeueReusableCellWithIdentifier:@"ApplauseCell" forIndexPath:indexPath];
    }
    else if ([DemoFeed isKindOfClass:[XYZCreate class]]){
        cell = [tableView dequeueReusableCellWithIdentifier:@"CreateCell" forIndexPath:indexPath];
    }
    else if ([DemoFeed isKindOfClass:[XYZFollow class]]){
        cell = [tableView dequeueReusableCellWithIdentifier:@"FollowCell" forIndexPath:indexPath];
    }
    [DemoFeed fillCell:cell];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    XYZFeed* DemoFeed;
    DemoFeed=[Feeds objectAtIndex:[Feeds count]-1-indexPath.row];
    if ([DemoFeed isKindOfClass:[XYZComment class]]) {
        return 153;
    }
    else if ([DemoFeed isKindOfClass:[XYZShare class]]){
        return 122;
    }
    else if ([DemoFeed isKindOfClass:[XYZApplause class]]){
        return 122;
    }
    else if ([DemoFeed isKindOfClass:[XYZCreate class]]){
        return 122;
    }
    else if ([DemoFeed isKindOfClass:[XYZFollow class]]){
        return 115;
    }
    return 102;
}

- (IBAction)back:(id)sender
{
    [self.navigationController popViewControllerAnimated:YES];
}


- (IBAction)Search:(id)sender
{
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
        [self performSegueWithIdentifier:@"Profile" sender:self];
    }
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
 
    if ([segue.identifier isEqualToString:@"Profile"])
    {
        [segue.destinationViewController setId:UserId];
    }
    if ([segue.identifier isEqualToString:@"MelodyPressed"]) {
        [segue.destinationViewController initializeMelodyId:MelodyId];
    }
    
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}

-(BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender
{
    /*
    if([identifier isEqualToString:@"Profile"])
    {
        if (UserId == 0) {
            return NO;
        }
    }
    
    if ([identifier isEqualToString:@"MelodyPressed"]) {
        if (MelodyId == 0) {
            return NO;
        }
    }
     */
    return NO;
}


@end
