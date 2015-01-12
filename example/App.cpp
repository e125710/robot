//
//  App.cpp
//  rge_sample
//
//  Created by Yuhei Akamine on 2014/10/28.
//  Copyright (c) 2014年 Yuhei Akamine. All rights reserved.
//

#include "App.h"

#include <fstream>
using namespace std;

#include <rge/RGE.h>
#include "trackball.h"
#include "rge/RgeReader.h"
using namespace rge;

App::App()
{
}

//kobitoのChileを生成・消去
void moveHiyokoFrame(FrameRef src,FrameRef dst,FrameRef child){
    dst->addChild(child);
    src->removeChild(child);
}


void App::init()
{
    //背景クリア色
    glClearColor(0.0, 0.0, 1.0, 1.0);
			 
    RGE::getInstance()->init();
    
    RgeReader reader;
    reader.read("/Users/e125710/Desktop/3rdG/AR/blend2/8test.rge");
    
    if(RGE::getInstance()->findFrame("Armature"))
        RGE::getInstance()->findFrame("Armature")->setBonesVisibility(false);
    
    ofstream os("/tmp/ipo.csv");
    os << RGE::getInstance()->rootFrame()->getActionsDump() << endl;
    
    RGE::getInstance()->rootFrame()->printChildren();
    
    RGE::getInstance()->setBackgroundColor(color3(0,0,1));
    //RGE::getInstance()->rootFrame()->stopAnimation();
    RGE::getInstance()->rootFrame()->anim()->setLooping(true, true);// loopのありなし
    
    //LAYER_2に属するオブジェクトを描画しない
    RGE::getInstance()->setLayerVisibility(LAYER_2, false);
    //rootを介して子供生成
    workHiyokoFrame = RGE::getInstance()->rootFrame()->createChild();
    jumpHiyokoFrame = RGE::getInstance()->rootFrame()->createChild();
    
    FrameRef root = RGE::getInstance()->rootFrame();
    
    
    moveHiyokoFrame(root,workHiyokoFrame ,RGE::getInstance()->findFrame("body"));
        //RGE::getInstance()->rootFrame()->removeChild(jumpHiyokoFrame);
    moveHiyokoFrame(root,jumpHiyokoFrame ,RGE::getInstance()->findFrame("body.001"));
    //jumpKobitoFrame->setVelocity(rgeVector3(1,0,0));
    
    //FrameRef kobito = RGE::getInstance()->findFrame("Head");
    //RGE::getInstance()->rootFrame()->removeChild(kobito);

    //kobitoBase->addChild(kobito);
}

void App::applyWindowSize(int w, int h)
{
    /* トラックボールする範囲 */
    trackballRegion(w, h);
    
    /* ウィンドウ全体をビューポートにする */
    //	glViewport(0, 0, w, h);
    RGE::getInstance()->setViewport(0, 0, w, h);
    
    //ウインドウのアスペクト比を設定
    RGE::getInstance()->setAspectRatio((double)w/h);
}

void App::update()
{
    RGE::getInstance()->update();
    
    //setVelocityは移動速度,1秒毎にどれだけ進むか
    //rotateは回転を指定
    workHiyokoFrame->rotate(0,0,1);
    jumpHiyokoFrame->setVelocity(0,0,1);
    

}

void App::display()
{
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* モデルビュー変換行列の初期化 */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    /* トラックボール処理による回転(デバッグ用) */
    trackballRotation("Camera");
    
    //RGE(グラフィックエンジン）による描画
    glDisable(GL_BLEND);
    
    if(RGE::getInstance()->findLight("Spot"))
        SpotLight::upcast(RGE::getInstance()->findLight("Spot"))->setCastShadow(true);
    
    RGE::getInstance()->render();
}

void App::mouseLeftPressed(int x, int y)
{
    trackballStart(x, y);
}

void App::mouseLeftReleased(int x, int y)
{
    trackballStop(x,y);
}

void App::mouseLeftDragged(int x, int y)
{
    trackballMotion(x, y);
}
