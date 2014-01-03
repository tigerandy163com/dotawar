//
//  dragButton.m
//  三国war
//
//  Created by sssst on 13-12-24.
//
//

#import "dragButton.h"

@implementation dragButton

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
       // self.frame = CGRectMake(10, 10, 50, 50);
        
        [self setTitle:@"触摸" forState:UIControlStateNormal];
        [self setTitle:@"移动" forState:UIControlEventTouchDown];
        [self addTarget:self action:@selector(dragClick:) forControlEvents:UIControlStateHighlighted];
        [self addTarget:self action:@selector(dragMoving:withEvent: )forControlEvents: UIControlEventTouchDragInside];
        [self addTarget:self action:@selector(dragEnded:withEvent: )forControlEvents: UIControlEventTouchUpInside |
         UIControlEventTouchUpOutside|UIControlEventTouchCancel];
        
    }
    return self;
}
-(void)dragClick:(id)sender
{
    if (_delegate!=nil&&[_delegate respondsToSelector:@selector(BtnClicked:)]) {
        [_delegate BtnClicked:sender];
    }
}
- (void) dragMoving: (UIControl *) c withEvent:ev
{
    CGPoint pos = [[[ev allTouches] anyObject] locationInView:self.superview];
    
    CGRect boundes = self.superview.bounds;
    
    if (CGRectContainsPoint(boundes, pos)) {
        c.center = pos;
    }
    
}

- (void) dragEnded: (UIControl *) c withEvent:ev
{
    CGPoint pos = [[[ev allTouches] anyObject] locationInView:self.superview];
    CGRect boundes = self.superview.bounds;
    
    if (CGRectContainsRect(boundes, self.bounds)) {
        if (pos.y >= boundes.size.height/2 && pos.x <=boundes.size.width/2) {
            pos.y =boundes.size.height - self.bounds.size.height/2;
            pos.x = self.bounds.size.width/2;
        }else if(pos.y >= boundes.size.height/2 && pos.x >boundes.size.width/2)
        {
            pos.y =boundes.size.height - self.bounds.size.height/2;
            pos.x =boundes.size.width - self.bounds.size.width/2;
        }else if(pos.y < boundes.size.height/2 && pos.x <=boundes.size.width/2)
        {
            pos.y =self.bounds.size.height/2;
            pos.x =self.bounds.size.width/2;
        }else if(pos.y < boundes.size.height/2 && pos.x >boundes.size.width/2)
        {
            pos.y =self.bounds.size.height/2;
            pos.x =boundes.size.width - self.bounds.size.width/2;
        }
        c.center = pos;
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
