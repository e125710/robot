//
//  App.h
//  rge_sample
//
//  Created by Yuhei Akamine on 2014/10/28.
//  Copyright (c) 2014年 Yuhei Akamine. All rights reserved.
//

#ifndef __rge_sample__App__
#define __rge_sample__App__
#include "RGE.h"
#include "Frame.h"

class App
{
public:
    App();
    void init();
    void applyWindowSize(int w, int h);
    void update();
    void display();
    
    void mouseLeftPressed(int x, int y);
    void mouseLeftReleased(int x, int y);
    void mouseLeftDragged(int x, int y);
private:
    rge::FrameRef workHiyokoFrame;
    rge::FrameRef jumpHiyokoFrame;
    
};


#endif /* defined(__rge_sample__App__) */
