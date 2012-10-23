//
//  GLView.h
//
//  Created by Akaguma on 12/10/23.
//  Copyright (c) 2012年 Akaguma. All rights reserved.
//

#ifndef __GLView__
#define __GLView__

#include <iostream>
#include <opencv2/opencv.hpp>


#include <cmath>
#include <cstdlib>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <GLUT/GLUT.h>  // Teapotを描画するのみに使用


namespace GLV {
    
enum MouseBtn {
    LEFT = 0,
    MIDDLE,
    RIGHT
};

enum MouseState {
    DOWN = 0,
    UP
};


class GLView
{
    int _xsize;
    int _ysize;
    int _mouseF;
    int _ox;
    int _oy;
    float _m[16];
    
public:
    GLView();
    void display();
    void update();
    void reshape(int width, int height);
    void keyboard(unsigned char key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    
    void init();
    void loop();
    
    int xsize() const { return _xsize; }
    int ysize() const { return _ysize; }
    
private:
    void draw();
};
    
}   // end namespace GLV

#endif /* defined(__GLView__) */
