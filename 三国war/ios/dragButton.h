//
//  dragButton.h
//  三国war
//
//  Created by sssst on 13-12-24.
//
//

#import <UIKit/UIKit.h>


@protocol dragBtnDelegate <NSObject>

@required
-(void) BtnClicked:(id)sender;

@end

@interface dragButton : UIButton
@property(nonatomic,assign)IBOutlet id<dragBtnDelegate> delegate;
@end
