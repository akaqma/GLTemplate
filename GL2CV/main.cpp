//
//  main.cpp
//
//  Created by Akaguma on 12/10/23.
//  Copyright (c) 2012年 Akaguma. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include "GLView.h"

const int FPS = 30;
const int WIN_W = 300;
const int WIN_H = 300;

static void  displayFunc(void);
static void  idleFunc(void);
static void  reshapeFunc(int width, int height);
static void  keyboardFunc(unsigned char key, int x, int y);
static void  mouseFunc(int button, int state, int x, int y);
static void  motionFunc(int x, int y);

static int _currentTime = 0;
static GLV::GLView _gl(WIN_W, WIN_H);


// ----------------------------------------------------------------
//  Main
// ----------------------------------------------------------------
int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
	glutInitWindowSize (WIN_W, WIN_H);
    
	glutCreateWindow ("OpenGL Window");
    
    
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutIdleFunc(idleFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    
    _gl.init();
    
    glutMainLoop();
    
    
    return 0;
}


// ----------------------------------------------------------------
//  Idle
// ----------------------------------------------------------------
void idleFunc()
{
    while(_currentTime<glutGet(GLUT_ELAPSED_TIME)){
		_currentTime+=1000/FPS;
        
        _gl.update();
	}
    
	glutPostRedisplay();
}


// ----------------------------------------------------------------
//  display
// ----------------------------------------------------------------
void displayFunc()
{
    _gl.display();
    glutSwapBuffers();
}


// ----------------------------------------------------------------
//  reshape
// ----------------------------------------------------------------
void reshapeFunc(int width, int height)
{
    _gl.reshape(width, height);
}


// ----------------------------------------------------------------
//  keyboard
// ----------------------------------------------------------------
void keyboardFunc(unsigned char key, int x, int y)
{
    _gl.keyboard(key, x, y);
}


// ----------------------------------------------------------------
//  mouse
// ----------------------------------------------------------------
void mouseFunc(int button, int state, int x, int y)
{
    _gl.mouse(button, state, x, y);
}


// ----------------------------------------------------------------
//  motion
// ----------------------------------------------------------------
void motionFunc(int x, int y)
{
    _gl.motion(x, y);
    glutPostRedisplay();
}
