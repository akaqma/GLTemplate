//
//  GLView.cpp
//
//  Created by Akaguma on 12/10/23.
//  Copyright (c) 2012年 Akaguma. All rights reserved.
//

#include "GLView.h"

namespace GLV {
    
    // ----------------------------------------------------------------
    //  コンストラクタ
    // ----------------------------------------------------------------
    GLView::GLView(int width, int height)
    :_xsize(width),_ysize(height),_mouseF(0),
     _texNum(0), _mode(TEX_MODE_BLANK), _state(TEX_STATE_STOP), _sphere(NULL)
    {
        _img = cv::Mat(_ysize, _xsize, CV_8UC3);
        
    }
    
    
    // ----------------------------------------------------------------
    //  初期化
    // ----------------------------------------------------------------
    void GLView::init()
    {
        
        glClearColor(0.92, 0.92, 0.92, 0.92);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (GLfloat)_xsize / (GLfloat)_ysize, 1.0, 100.0);
        
        _sphere = gluNewQuadric();
        gluQuadricDrawStyle(_sphere, GLU_FILL);
        gluQuadricNormals(_sphere, GLU_SMOOTH);
        gluQuadricTexture(_sphere, GL_TRUE);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glGenTextures(1, _textures);
        
        glGetFloatv(GL_MODELVIEW_MATRIX, _m);
    }
    
    
    // ----------------------------------------------------------------
    //  描画
    // ----------------------------------------------------------------
    void GLView::display()
    {
        //draw();
        glMatrixMode(GL_MODELVIEW);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);
        
        glEnable( GL_TEXTURE_2D );
        
        if (_mode != TEX_MODE_BLANK) {
            setTex();
            
            glPushMatrix();
                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf( _m );
                gluSphere(_sphere, 2,128,128);
            glPopMatrix();
        }
        
        glDisable(GL_TEXTURE_2D);
        
        
        glFlush ();

    }
    
    
    // ----------------------------------------------------------------
    //  キー入力
    // ----------------------------------------------------------------
    void GLView::keyboard (unsigned char key, int x, int y)
    {
        switch (key) {
            case 27:
                exit(0);
                break;
            default:
                break;
        }
        glFlush ();
    }
    
    
    // ----------------------------------------------------------------
    //  データ更新
    // ----------------------------------------------------------------
    void GLView::update()
    {
    }
    
    
    // ----------------------------------------------------------------
    //  サイズ変更
    // ----------------------------------------------------------------
    void GLView::reshape(int width, int height)
    {
        _xsize = width;
        _ysize = height;
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    }
    
    
    // ----------------------------------------------------------------
    //  マウス座標
    // ----------------------------------------------------------------
    void GLView::mouse(int button, int state, int x, int y)
    {
        if( button == LEFT ) {
            if( state == DOWN ) {
                _mouseF = 1;
                _ox = x;
                _oy = y;
            }
            else if( state == UP ) {
                _mouseF = 0;
            }
        }
    }
    
    
    // ----------------------------------------------------------------
    //  マウス変化量
    // ----------------------------------------------------------------
    void GLView::motion(int x, int y)
    {
        float   x_angle = 0.0;
        float   y_angle = 0.0;
        
        x_angle += (float)(x - _ox)/_xsize * 360.0;
        y_angle += (float)(y - _oy)/_xsize * 360.0;
        _ox = x;
        _oy = y;
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef( _m[12], _m[13], _m[14] );
        glRotatef( y_angle, 1, 0, 0 );
        glRotatef( x_angle, 0, 1, 0 );
        _m[12] = _m[13] = _m[14] = 0.0;
        glMultMatrixf( _m );
        glGetFloatv(GL_MODELVIEW_MATRIX, _m);
        glPopMatrix();
    }
    
    
    // ----------------------------------------------------------------
    //  パッチ描画
    // ----------------------------------------------------------------
    void GLView::draw(void)
    {
        float  ambiColor[4] = {0.0, 0.0, 0.0, 0.0};
        float  lightPos[4] = {200.0, -200.0, 500.0, 1.0};
        float  lightAmbi[4] = {0.2, 0.2, 0.2, 0.0};
        float  lightDiff[4] = {1.0, 1.0, 1.0, 0.0};
        float  lightSpec[4] = {1.0, 1.0, 1.0, 0.0};
        float  diffColor[4] = {0.0, 0.0, 1.0, 1.0};
        float  specColor[4] = {1.0, 1.0, 1.0, 1.0};
        
        glClearColor( 0.7, 0.7, 0.7, 0.0 );
        glClearDepth( 1.0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(500,0,0);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,500,0);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,500);
        glEnd();
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        glEnable( GL_LIGHTING );
        glShadeModel(GL_SMOOTH);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiColor);
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_TRUE);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
        glEnable( GL_LIGHT0 );
        glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
        glLightfv( GL_LIGHT0, GL_AMBIENT, lightAmbi );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiff );
        glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpec );
        
        
        glFrontFace(GL_CW);
        glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffColor );
        glMaterialfv( GL_FRONT, GL_SPECULAR, specColor );
        glMaterialf( GL_FRONT, GL_SHININESS, 10.0 );
        
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf( _m );
        glutSolidTeapot( 100.0 );
        glPopMatrix();
        
        glDisable( GL_LIGHTING );
        
        cvView();
        
    }
    
    void GLView::setTex()
    {
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        
        // image
        if(_mode == TEX_MODE_IMAGE && !_img.empty()) {
            glBindTexture(GL_TEXTURE_2D, _textures[_texNum]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _img.cols, _img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, _img.data);
        }
        // movie
        else if(_mode == TEX_MODE_MOVIE && _video_cap.isOpened()) {
            if(_state == TEX_STATE_START) {
                _texNum =(++_texNum)%TEX_BUF;
                glBindTexture(GL_TEXTURE_2D, _textures[_texNum]);
                _video_cap >> _img;
                cv::flip(_img, _img, 0);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _img.cols, _img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, _img.data);
            }
        }
    }
    
    
    // ----------------------------------------------------------------
    //  画像を読み込む
    // ----------------------------------------------------------------
    bool GLView::openImage(const string &filename)
    {
        bool result = false;
        
        cv::Mat img = cv::imread(filename.c_str());
        if (img.empty()) {
            cout << "Error" << endl;
            return false;
        }
        // size check
        if((img.cols == TEX_WIDTH && img.rows == TEX_HEIGHT)
           || (img.cols == 5400 && img.rows == 2700)
           ) {
            cv::flip(img, img, 0);
            _img = img.clone();
            result = true;
        }
        _mode = TEX_MODE_IMAGE;
        
        return result;
    }
    
    // ----------------------------------------------------------------
    //  CVの描画
    // ----------------------------------------------------------------
    void GLView::cvView()
    {
        glReadBuffer(GL_BACK);
        glPixelStorei( GL_PACK_ALIGNMENT,1 );
        glReadPixels( 0,
                     0,
                     _xsize,
                     _ysize,
                     GL_BGR,
                     GL_UNSIGNED_BYTE,
                     _img.data
        );
        
        if (!_img.empty()) {
            cv::flip(_img, _img, 0);
            cv::imshow("CV", _img);
        }
    }
    
    // ----------------------------------------------------------------
    //  画像保存
    // ----------------------------------------------------------------
    void GLView::cvSaveImage(const string &filename)
    {
        
    }
    
    // ----------------------------------------------------------------
    //  動画保存
    // ----------------------------------------------------------------
    void GLView::cvSaveMovie(const string &filename)
    {
        
    }
    
} // end namespace GLV
