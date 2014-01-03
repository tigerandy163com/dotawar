//
//  __warAppController.h
//  三国war
//
//  Created by chunyu.wang on 13-10-31.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import "dragButton.h"
#import "topModelViewController.h"
@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate,dragBtnDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    dragButton* dragbut;
    topModelViewController* modelVC;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

