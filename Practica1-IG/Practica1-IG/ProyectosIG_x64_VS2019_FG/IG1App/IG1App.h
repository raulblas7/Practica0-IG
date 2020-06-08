﻿//#pragma once
#ifndef _H_IG1App_H_
#define _H_IG1App_H_

//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include "GLinclude.h"
#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "Fondo.h"
//-------------------------------------------------------------------------

class IG1App
{
public:  
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const & J) = delete; // no copy constructor
	void operator =(IG1App const & J) = delete; // no copy assignment
	
	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	Scene const& scene() { return *mScene; };


	void run();    // the main event processing loop
	void close();  // the application
protected:

	IG1App() {};
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void free();

	
 
	void display() const;   // the scene
	void display2vistas() const;
	void resize(int newWidth, int newHeight);   // the viewport (without changing the scale) 
	void key(unsigned char key, int x, int y);  // keypress event
	void specialKey(int key, int x, int y);     // keypress event for special characters

	// static callbacks 
	static void s_display() { s_ig1app.display(); };
	static void s_resize(int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(unsigned char key, int x, int y) { s_ig1app.key(key, x, y); };
	static void s_specialKey(int key, int x, int y) { s_ig1app.specialKey(key, x, y); };
	static void s_mouse(int button, int state, int x, int y) { s_ig1app.mouse(button, state, x, y); };
	static void s_motion(int x, int y) { s_ig1app.motion(x, y); };
	static void s_mouseWheel(int wheelNumber, int direction, int x, int y) { s_ig1app.mouseWheel(wheelNumber, direction, x, y); };

	
	// Viewport position and size
	Viewport *mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera* mCamera = nullptr;
	// Graphics objects of the scene
	Scene *mScene = nullptr;

	Fondo* mFondo = nullptr;
	
	bool mStop = false; // main event processing loop
	int mWinId = 0;	    // window's identifier
	int mWinW = 800;    // window's width 
	int mWinH = 600;    // window's height
	glm::dvec2 mMouseCoord;
	int mMouseButt;
	bool m2Vistas = false;

	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
	void mouseWheel(int whellNumber, int direction, int x, int y);
};
//-------------------------------------------------------------------------

#endif //_H_IG1App_H_