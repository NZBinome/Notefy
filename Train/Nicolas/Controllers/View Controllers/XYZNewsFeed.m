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
@property XYZFeed* Feed;
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
@synthesize Feed;
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
    [FeedTable reloadData];
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict
{
    if (isFeed)
    {
        isDate=[elementName isEqualToString:@"Date"];
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
    
    if (isScript) {
        Comment.Script=string;
        isScript=false;
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
        Share.User = User1;
        Share.Melody = Melody;
        [Feeds addObject:Share];
        isShare = false;
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

- (void)viewDidLoad
{
    [super viewDidLoad];
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    ServerLocation=appdel.ServerLocation;
    int AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];

    FeedTable.dataSource = self;
    FeedTable.delegate = self;
    Feeds = [[NSMutableArray alloc]init];
    // Do any additional setup after loading the view.
    
    
    NSString *path=[ServerLocation stringByAppendingString:@"NewsFeed.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        // Perform async operation
        // Call your method/function here
        // Example:
        // NSString *result = [anObject calculateSomething];
        [self getData:path];
        dispatch_sync(dispatch_get_main_queue(), ^{
            // Update UI
            // Example:
            // self.myLabel.text = result;
            [FeedTable reloadData];

        });
    });
    //[self getData:path];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
    XYZFeedCell *cell = [tableView dequeueReusableCellWithIdentifier:@"FeedCell" forIndexPath:indexPath];
    XYZFeed* DemoFeed;
    DemoFeed=[Feeds objectAtIndex:[Feeds count]-1-indexPath.row];
    [DemoFeed fillCell:cell];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    /*
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
     */
}



#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
 
    if ([segue.identifier isEqualToString:@"MyProfile"])
    {
        int AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
        [segue.destinationViewController setId:AccountId];
    }
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


@end
