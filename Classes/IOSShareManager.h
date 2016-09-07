
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


#define GameUrl "https://itunes.apple.com/app/id1059348579"

@interface IOSShareManager : NSObject <UINavigationControllerDelegate,UIImagePickerControllerDelegate>

+ (IOSShareManager *) getInstance;
- (void)share:(CGPoint)pos;
- (void)share;

@property (nonatomic, readwrite, retain) UIViewController* viewController;


@end