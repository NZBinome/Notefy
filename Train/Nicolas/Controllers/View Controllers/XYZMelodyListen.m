//
//  XYZMelodyListen.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/18/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZMelodyListen.h"

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
}

-(void)InitializeView
{
    NSString *path=[ServerLocation stringByAppendingString:@"GetMelody.php?MelodyId="];
    path = [path stringByAppendingString:[NSString stringWithFormat:@"%d", SelectedMelody.Id]];
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

- (void)viewDidLoad
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    ServerLocation = appdel.ServerLocation;
    [super viewDidLoad];
    SelectedMelody = [[XYZMelody alloc]init];
    Creator = [[XYZUser alloc]init];
    SelectedMelody.Id = MelodyId;
    
    [self InitializeView];
    
    UserName.tag = Creator.Id;

    // Do any additional setup after loading the view.
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
