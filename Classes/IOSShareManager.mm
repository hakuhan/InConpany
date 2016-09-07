
#import "IOSShareManager.h"
#include "cocos2d.h"

using namespace cocos2d;

@implementation IOSShareManager

+ (IOSShareManager *) getInstance
{
    static IOSShareManager* gameMgr = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        gameMgr = [[self alloc] init];
    });
    return gameMgr;
}

- (id)init
{
    self=[super init];
    if (self){
        self.viewController=[UIApplication sharedApplication].keyWindow.rootViewController;
    }
    return self;
}

- (void)share
{
     CGPoint center=self.viewController.view.center;
    [self share: center];
}

- (void)share:(CGPoint)pos
{

    // 你可以先截屏保存到document下，这里的image读取document下面。
    //UIImage *image = [UIImage imageNamed:@"GameLoading/diqiu.png"];
#pragma mark -游戏地址
    NSURL *url= [NSURL URLWithString:@GameUrl];
    
    NSString *mesg;
    NSString *language = [[NSLocale preferredLanguages] objectAtIndex:0];
    if ([language isEqualToString:@"zh_Hans"]) {
        mesg = @"可爱的美甲！";
    }
    mesg = @"Lovely Manicure game!";
    
    UIActivityViewController *activityViewController = [[UIActivityViewController alloc] initWithActivityItems:@[mesg,url] applicationActivities:nil];
    
    activityViewController.excludedActivityTypes = @[UIActivityTypePrint,UIActivityTypeAssignToContact,UIActivityTypeAddToReadingList,UIActivityTypeAirDrop,UIActivityTypeOpenInIBooks,@"com.apple.reminders.RemindersEditorExtension",@"com.apple.mobilenotes.SharingExtension"];
    
    [self presentViewController:activityViewController ipadPos:pos];
}

/**
 *  显示表单形式的ViewController  Ipad需要弹出
 */
-(void) presentViewController:(UIViewController *)viewController ipadPos:(CGPoint)pos
{
    
    UIPopoverPresentationController *popPresenter = [viewController popoverPresentationController];
    if (popPresenter)
    {
        popPresenter.sourceView = self.viewController.view;
        popPresenter.sourceRect = CGRectMake(pos.x, pos.y+50, 0, 0);
        popPresenter.permittedArrowDirections = UIPopoverArrowDirectionDown;
    }
    
    [self.viewController presentViewController:viewController animated:YES completion:nil];
}



@end