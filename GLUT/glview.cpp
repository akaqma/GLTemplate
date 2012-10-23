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
GLView::GLView()
    :_xsize(300),_ysize(300),_mouseF(0)
{
}


// ----------------------------------------------------------------
//  初期化
// ----------------------------------------------------------------
void GLView::init()
{
    
    glViewport( 0, 0, _xsize, _ysize );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 50.0, (double)_xsize/(double)_ysize, 500.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 500.0, 300.0, 500.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
    glGetFloatv(GL_MODELVIEW_MATRIX, _m);
    
}


// ----------------------------------------------------------------
//  描画
// ----------------------------------------------------------------
void GLView::display()
{
    draw();
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
    
    glViewport( 0, 0, _xsize, _ysize );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 50.0, (double)_xsize/(double)_ysize, 500.0, 2000.0);
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
    
}
 
    
} // end namespace GLV
