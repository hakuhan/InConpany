
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#define kProductPurchasedNotification       @"ProductPurchased"

@interface IAPManager : NSObject <SKProductsRequestDelegate,SKPaymentTransactionObserver> {
    UIAlertController *_alertController;
}


@property (strong,nonatomic) NSMutableDictionary *products;
@property (strong,nonatomic) NSArray *productIdentifiers;

+ (IAPManager *) getInstance;

- (void) restorePurchases;
- (void) purchaseProduct:(int) productIndex;

@end
