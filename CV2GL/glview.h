//
//  GLView.h
//
//  Created by Akaguma on 12/10/23.
//  Copyright (c) 2012年 Akaguma. All rights reserved.
//

#ifndef __GLView__
#define __GLView__

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
//#include <opencv2/legacy/legacy.hpp>


#include <cmath>
#include <cstdlib>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <GLUT/GLUT.h>  // Teapotを描画するのみに使用


namespace GLV {
    
    using namespace std;
    
    
    const int TEX_HEIGHT    = 1024;
    const int TEX_WIDTH     = 2048;
    const int TEX_BUF = 2;
    
    enum TexMode {
        TEX_MODE_BLANK,
        TEX_MODE_IMAGE,
        TEX_MODE_MOVIE
    };
    
    enum TexState {
        TEX_STATE_START,
        TEX_STATE_STOP
    };
    
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
        cv::Mat _img;
        
        GLuint          _textures[TEX_BUF];
        int             _texNum;
        GLUquadricObj*  _sphere;
        TexMode         _mode;
        TexState        _state;
        cv::VideoCapture    _video_cap;
        
    public:
        GLView(int width, int height);
        void display();
        void update();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        
        void init();
        void loop();
        
        
//        int xsize() const { return _xsize; }
//        int ysize() const { return _ysize; }
        bool openImage(const string &filename);
        
    private:
        void draw();
        void cvView();
        void cvSaveImage(const string &filename);
        void cvSaveMovie(const string &filename);
        
        void setTex();
    };
    
}   // end namespace GLV

#endif /* defined(__GLView__) */
