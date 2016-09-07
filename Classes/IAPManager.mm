
#import "IAPManager.h"
#include "cocos2d.h"
#include "DefaultHeader.h"
using namespace cocos2d;

@implementation IAPManager
@synthesize products,productIdentifiers;


#pragma mark - SKProductsRequestd代理方法
/**
 *  产品请求完成后的响应方法
 *
 *  @param request  请求对象
 *  @param response 响应对象，其中包含产品信息
 */
-(void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    //保存有效的产品
    self.products=[NSMutableDictionary dictionary];

    for (SKProduct *product in response.products)
    {
        [products setObject:product forKey:product.productIdentifier];
    }
    
}
-(void)requestDidFinish:(SKRequest *)request{
    NSLog(@"请求商品完成.");
}
-(void)request:(SKRequest *)request didFailWithError:(NSError *)error{
    if (error) {
        NSLog(@"请求商品过程中发生错误，错误信息：%@",error.localizedDescription);
    }
}

#pragma mark - SKPaymentQueue监听方法
/**
 *  交易状态更新后执行
 *
 *  @param queue        支付队列
 *  @param transactions 交易数组，里面存储了本次请求的所有交易对象
 */
-(void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions{
    for (SKPaymentTransaction *paymentTransaction in transactions)
    {
        switch (paymentTransaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://购买成功
                 //进行验证
                [self verifyPurchaseWithPaymentTransaction:paymentTransaction.payment.productIdentifier];
                
                [self dismissConnecting];
                
                [queue finishTransaction:paymentTransaction];//结束支付交易
                break;
                
            case SKPaymentTransactionStateRestored://恢复成功，对于非消耗品才能恢复
                NSLog(@"恢复交易\"%@\"成功.",paymentTransaction.payment.productIdentifier);
                [queue finishTransaction:paymentTransaction];//结束支付交易
                
                [self purchaseSucceed:paymentTransaction.payment.productIdentifier];
                
                break;

            case SKPaymentTransactionStateFailed:
//                if (paymentTransaction.error.code==SKErrorPaymentCancelled) {//用户点击取消
//                    NSLog(@"用户取消购买.");
//                }
                NSLog(@"错误:%@",paymentTransaction.error.localizedDescription);
                
                [self dismissConnecting];
                
                break;

        }
    }
}

//恢复购买失败
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    NSLog(@"恢复失败.%@",error.localizedDescription);
    [self dismissConnecting];
    
    UIAlertController* alertController = [UIAlertController alertControllerWithTitle:@"Restore Failed!" message:error.localizedDescription preferredStyle:UIAlertControllerStyleAlert];
    [alertController addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleCancel handler:nil]];
    UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [appRootVC presentViewController:alertController animated:YES completion:nil];
    
}
//恢复购买完成
-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue{
    NSLog(@"恢复完成.");
    [self dismissConnecting];
    
    if(queue.transactions.count!=0)
    {
        UIAlertController* alertController = [UIAlertController alertControllerWithTitle:@"Purchases Restored!" message:@"Your previous purchases are being restored.Thank you!" preferredStyle:UIAlertControllerStyleAlert];
        [alertController addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleCancel handler:nil]];
        UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
        [appRootVC presentViewController:alertController animated:YES completion:nil];
    }
    else
    {
        UIAlertController* alertController = [UIAlertController alertControllerWithTitle:@"There is nothing to restore." message:nil preferredStyle:UIAlertControllerStyleAlert];
        [alertController addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleCancel handler:nil]];
        UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
        [appRootVC presentViewController:alertController animated:YES completion:nil];
    }
    
}

#pragma mark - 静态方法

static IAPManager * Iap;
/**
 *  程序一开始就使用[[SKPaymentQueue defaultQueue] addTransactionObserver:[IAPManager getInstance]]指定观察者对象
 */
+ (IAPManager *) getInstance {
    if (nil == Iap)
    {
        Iap = [[IAPManager alloc] init];
    }
    return Iap;
}

#pragma mark - 公有方法

/**
 *  恢复购买
 */
- (void) restorePurchases{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    [self presentConnecting];
}

/**
 *  恢复购买
 *  
 *  @param productIndex     需要购买产品的索引，0代表第一个商品
 */
- (void) purchaseProduct:(int) productIndex{
    if (![SKPaymentQueue canMakePayments]) {
        NSLog(@"设备不支持购买.");
        return;
    }
    NSString *productIdentifier=[productIdentifiers objectAtIndex:productIndex];
    
    //---测试 成功购买
//#ifdef COCOS2D_DEBUG
//    [self purchaseSucceed:productIdentifier];
//#endif
    
    SKProduct *product=[products objectForKey:productIdentifier];
    if (product==nil){
    
        UIAlertController* alertController = [UIAlertController alertControllerWithTitle:@"No Product." message:productIdentifier preferredStyle:UIAlertControllerStyleAlert];
        [alertController addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleCancel handler:nil]];
        UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
        [appRootVC presentViewController:alertController animated:YES completion:nil];

        return;
    }
    
    [self presentConnecting];
    
    NSLog(@"购买商品%@",productIdentifier);
    SKPayment *payment=[SKPayment paymentWithProduct:product];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

#pragma mark - 私有方法

- (id)init {
    self=[super init];
    if (self){
      [self loadProducts];
    }
    return self;
}

/**
 *  初始化时请求所有产品
 */
-(void)loadProducts{

    //所有产品ID
#pragma mark 商品id
    self.productIdentifiers =@[
                          @"com.bandou.guaji_buy0"];

    
    //定义要获取的产品标识集合
    NSSet *sets=[NSSet setWithArray:productIdentifiers];
    //定义请求用于获取产品
    SKProductsRequest *productRequest=[[SKProductsRequest alloc]initWithProductIdentifiers:sets];
    //设置代理,用于获取产品加载状态
    productRequest.delegate=self;
    //开始请求
    [productRequest start];
}

#ifdef COCOS2D_DEBUG
#define kVerifyURL @"https://sandbox.itunes.apple.com/verifyReceipt"//开发阶段沙盒验证URL
#else
#define kVerifyURL @"https://buy.itunes.apple.com/verifyReceipt" //实际购买验证URL
#endif

/**
 *  验证购买，避免越狱软件模拟苹果请求达到非法购买问题
 *
 */
-(void)verifyPurchaseWithPaymentTransaction:(NSString *)productIdentifier{
    //从沙盒中获取交易凭证并且拼接成请求体数据
    NSURL *receiptUrl=[[NSBundle mainBundle] appStoreReceiptURL];
    NSData *receiptData=[NSData dataWithContentsOfURL:receiptUrl];
    
    NSString *receiptString=[receiptData base64EncodedStringWithOptions:NSDataBase64EncodingEndLineWithLineFeed];//转化为base64字符串
    
    NSString *bodyString = [NSString stringWithFormat:@"{\"receipt-data\" : \"%@\"}", receiptString];//拼接请求数据
    NSData *bodyData = [bodyString dataUsingEncoding:NSUTF8StringEncoding];
    
    //创建请求到苹果官方进行购买验证
    NSURL *url=[NSURL URLWithString:kVerifyURL];
    NSMutableURLRequest *requestM=[NSMutableURLRequest requestWithURL:url];
    requestM.HTTPBody=bodyData;
    requestM.HTTPMethod=@"POST";
    //创建连接并发送同步请求
    NSError *error=nil;
    NSData *responseData=[NSURLConnection sendSynchronousRequest:requestM returningResponse:nil error:&error];
    if (error) {
        NSLog(@"验证购买过程中发生错误，错误信息：%@",error.localizedDescription);
        return;
    }
    NSDictionary *dic=[NSJSONSerialization JSONObjectWithData:responseData options:NSJSONReadingAllowFragments error:nil];
    NSLog(@"%@",dic);
    if([dic[@"status"] intValue]==0){
        NSDictionary *dicReceipt= dic[@"receipt"];
        
        //NSDictionary *dicInApp=[dicReceipt[@"in_app"] lastObject];
        //productIdentifier= dicInApp[@"product_id"];//读取产品标识
        
        for (NSDictionary *dicInApp in dicReceipt[@"in_app"])
        {
            if ([productIdentifier isEqualToString:dicInApp[@"product_id"]])
            {
                NSLog(@"购买\"%@\"成功！",productIdentifier);
                [self purchaseSucceed:productIdentifier];
                return;
            }
        }
        
        NSLog(@"验证失败，未找到\"%@\"购买凭证！",productIdentifier);
        
    }else{
        NSLog(@"购买失败，未通过验证！");
    }
}

/**
 *  显示Connecting
 */
-(void)presentConnecting{
    _alertController = [UIAlertController alertControllerWithTitle:@"Connecting..." message:nil preferredStyle:UIAlertControllerStyleAlert];

    UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [appRootVC presentViewController:_alertController animated:YES completion:nil];
}

/**
 *  关闭Connecting
 */
-(void)dismissConnecting{
    if (_alertController) {
        [_alertController dismissViewControllerAnimated:YES completion:nil];
        _alertController=nil;
    }
}



//#include "ReadXml.h"
/**
 *  购买或者恢复成功
 *
 *  @param productIdentifier    商品ID
 */
#pragma mark 购买成功
-(void) purchaseSucceed:(NSString *)productIdentifier{
    NSUInteger index=[productIdentifiers indexOfObject:productIdentifier];
    //关闭广告
    UserDefault::getInstance()->setBoolForKey(ISPURCHASE.c_str(), true);
    //设置界面
    NSString *aTitle = @"Remove Success";
    NSString *contant = @"Restart game affter no advertising";
    if (Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE) {
        aTitle = @"广告去除成功";
        contant = @"重启游戏后没有广告";
    }
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:aTitle message:contant preferredStyle:UIAlertControllerStyleActionSheet];
    UIViewController *appRootVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    [appRootVC presentViewController:alert animated:YES completion:nil];
    
    //购买第 index 号商品 成功
//    ReadXml::getInstance()->purchaseSucceed((int)index);
    

//    [[NSNotificationCenter defaultCenter]postNotificationName:kProductPurchasedNotification object:productIdentifier];
//    如果使用通知  需在别处添加监听：
//    [[NSNotificationCenter defaultCenter]addObserverForName:kProductPurchasedNotification object:nil queue:nil usingBlock:^(NSNotification *notification)
//     {
//         //---取巧 object 就是产品ID NSString
//         NSString *nsstr=notification.object;
//         
//         unsigned long index=[[IAPManager getInstance].productIdentifiers indexOfObject:nsstr];
//     }];
}


@end
