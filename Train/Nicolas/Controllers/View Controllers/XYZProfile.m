//
//  XYZProfile.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/10/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZProfile.h"

@interface XYZProfile ()
@property (weak, nonatomic) IBOutlet UILabel *Last_Name;
@property (weak, nonatomic) IBOutlet UILabel *First_Name;
@property (weak, nonatomic) IBOutlet UILabel *Stage_Name;
@property BOOL isUser;
@property BOOL isFirst_Name;
@property BOOL isLast_Name;
@property BOOL isStage_Name;
@property BOOL isPicture_Link;
@property XYZUser* User;
@property int AccountId;
@property (weak, nonatomic) IBOutlet UIButton *BecomeAFan;
@property NSString* ServerLocation;
@property (weak, nonatomic) IBOutlet UIImageView *ProfilePic;
@property BOOL isMelody;
@property BOOL isFile_Link;
@property BOOL isTitle;
@property BOOL isDate;
@property XYZMelody* Melody;
@property NSMutableArray* Melodies;
@property (weak, nonatomic) IBOutlet UITableView *MelodyTable;
@property int UserId;
@property int Followed;
@property int Follower;
@property BOOL isFollow;
@property BOOL isFollower;
@property BOOL isFollowed;
@property BOOL isFan;

@end

@implementation XYZProfile
@synthesize Last_Name;
@synthesize First_Name;
@synthesize Stage_Name;
@synthesize isUser;
@synthesize isFirst_Name;
@synthesize isLast_Name;
@synthesize isStage_Name;
@synthesize User;
@synthesize AccountId;
@synthesize BecomeAFan;
@synthesize ServerLocation;
@synthesize isPicture_Link;
@synthesize ProfilePic;
@synthesize isMelody;
@synthesize isFile_Link;
@synthesize isTitle;
@synthesize isDate;
@synthesize Melody;
@synthesize Melodies;
@synthesize MelodyTable;
@synthesize UserId;
@synthesize Followed;
@synthesize Follower;
@synthesize isFollow;
@synthesize isFollowed;
@synthesize isFollower;
@synthesize isFan;


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
    [self assign];
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName attributes:(NSDictionary *)attributeDict
{
    if (isUser)
    {
        isFirst_Name=[elementName isEqualToString:@"First_Name"];
        isLast_Name=[elementName isEqualToString:@"Last_Name"];
        isStage_Name=[elementName isEqualToString:@"Stage_Name"];
        isPicture_Link=[elementName isEqualToString:@"Picture_Link"];
    }
    
    if (isMelody)
    {
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
}

-(void)setId:(int)Id
{
    UserId=Id;
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    if (isStage_Name) {
        User.Stage_Name=string;
        isStage_Name=false;
    }
    if (isLast_Name) {
        User.Last_Name=string;
        isLast_Name=false;
    }
    if (isFirst_Name) {
        User.First_Name=string;
        isFirst_Name=false;
    }
    if (isPicture_Link) {
        User.Picture_link=string;
        isPicture_Link=false;
    }
    if (isDate) {
        Melody.Date=string;
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
        [Melodies addObject:Melody];
    }
    if ([elementName isEqualToString:@"Follows"])
    {
        isFollow=false;
    }
}

-(void)assign
{
    NSString* fullpath;
    Last_Name.text = User.Last_Name;
    First_Name.text=User.First_Name;
    Stage_Name.text=User.Stage_Name;
    if (!User.Picture_link) {
        fullpath= [ServerLocation stringByAppendingString:@"Pictures/No_Profile_Picture.png"];
    }
    else
    {
        fullpath = [ServerLocation stringByAppendingString:User.Picture_link];
    }
    ProfilePic.image = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:fullpath]]];
}


- (void)viewDidLoad
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    [super viewDidLoad];
    AccountId=[[NSUserDefaults standardUserDefaults] integerForKey:@"AccountId"];
    MelodyTable.dataSource = self;
    MelodyTable.delegate = self;
    ServerLocation=appdel.ServerLocation;
    User=[[XYZUser alloc]init];
    Melodies=[[NSMutableArray alloc]init];
    User.Id=UserId;
    
    ///////////////////////////////////// TO BE REMOVED /////////////////
    
    User.Id=2;
    
    /////////////////////////////////////
    
    
    
    NSString *path=[ServerLocation stringByAppendingString:@"GetUser.php?UserId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", User.Id]];
    path = [path stringByAppendingString:@"&Follower="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    
    [self getData:path];

    if (AccountId == User.Id)
    {
        BecomeAFan.hidden=true;
        BecomeAFan.enabled=NO;
    }
    else
    {
        if ((Follower==AccountId)&&(Followed==User.Id))
        {
            isFan=true;
            [BecomeAFan setTitle:@"Already a Fan" forState:UIControlStateNormal];
        }
    }
}


- (IBAction)followUnfollow:(id)sender {
    NSString* path;
    if (isFan)
    {
        path=[ServerLocation stringByAppendingString:@"Unfollow.php?Followed="];
        [BecomeAFan setTitle:@"Become a Fan" forState:UIControlStateNormal];
    }
    else
    {
        path=[ServerLocation stringByAppendingString:@"Follow.php?Followed="];
        [BecomeAFan setTitle:@"Already a Fan" forState:UIControlStateNormal];
    }
    isFan=!isFan;
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", User.Id]];
    path = [path stringByAppendingString:@"&Follower="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", AccountId]];
    [self getData:path];
    
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [Melodies count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    XYZMelodyCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Melody" forIndexPath:indexPath];
    XYZMelody* DemoMel;
    DemoMel=[[XYZMelody alloc]init];
    DemoMel= [Melodies objectAtIndex:indexPath.row];
    cell.MelodyName.text = DemoMel.Title;
    cell.MelodyDate.text=DemoMel.Date;
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



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
