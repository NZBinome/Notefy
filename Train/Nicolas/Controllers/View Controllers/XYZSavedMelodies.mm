//
//  XYZSavedMelodies.m
//  Train
//
//  Created by Nicolas Jbeyli on 4/25/15.
//  Copyright (c) 2015 Nicolas Jbeyli. All rights reserved.
//

#import "XYZSavedMelodies.h"

@interface XYZSavedMelodies ()
@property (weak, nonatomic) IBOutlet UIButton *Back;
@property (weak, nonatomic) IBOutlet UITableView *MelodiesTable;
@property NSMutableArray *savedfiles;
@property NSString *path;
@property NSString *filename;

@end

@implementation XYZSavedMelodies
@synthesize Back;
@synthesize MelodiesTable;
@synthesize path;
@synthesize savedfiles;
@synthesize filename;

-(void)loadSavedFiles
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    path = [appdel.path stringByAppendingPathComponent:appdel.directory];
    NSArray* dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path
                                                                        error:NULL];
    savedfiles = [[NSMutableArray alloc] init];
    [dirs enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop)
     {
         NSString *name = (NSString *)obj;
         if (![[name substringToIndex:1] isEqualToString:@"."])
         {
             [savedfiles addObject:[name substringToIndex:[name length]]];
         }
     }];
}

- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    MelodiesTable.dataSource = self;
    MelodiesTable.delegate = self;
    // Do any additional setup after loading the view.
}


-(void)viewDidAppear:(BOOL)animated
{
    [self loadSavedFiles];
    [MelodiesTable reloadData];
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
    return [savedfiles count];
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ListPrototypeCell" forIndexPath:indexPath];
    NSString *name= [savedfiles objectAtIndex:indexPath.row];
    cell.textLabel.text = name;
    cell.textLabel.textColor = [UIColor whiteColor];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    XYZAppDelegate *appdel=[UIApplication sharedApplication].delegate;
    appdel.selectedfile = [tableView cellForRowAtIndexPath:indexPath].textLabel.text;
    //NSLog(appdel.selectedfile);
    //[self performSegueWithIdentifier:@"fileselected" sender:indexPath];
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
