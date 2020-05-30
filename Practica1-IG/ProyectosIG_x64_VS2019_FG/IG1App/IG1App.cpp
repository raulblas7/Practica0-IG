#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()  
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();   

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;
	
	mCamera->set2D();
	mScene->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL() 
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);
		
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
	
	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 
	
	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutMouseFunc(s_mouse); // cuando se presiona o suelta un botón
	glutMotionFunc(s_motion); // cuando se mueve con un botón presionado
	glutMouseWheelFunc(s_mouseWheel); // cuando se gira una rueda
	
	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------
void IG1App::display2vistas() const {
	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;
	mViewPort->setSize(mWinW / 2, mWinH);
	// pero tenemos que cambiar la posición y orientación de la cámara
	auxCam.setSize(mViewPort->width(), mViewPort->height());
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene->render(auxCam);
	*mViewPort = auxVP;
}

void IG1App::display() const   
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer
	if (m2Vistas) display2vistas();
	else {
		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	}
	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 
}
//-------------------------------------------------------------------------
void IG1App::mouse(int button, int state, int x, int y) {
	mMouseButt = button;
	mMouseCoord = glm::dvec2(x, mWinH - y);
}
void IG1App::motion(int x, int y) {
	// guardamos la anterior posicion en var. temp.
	glm::dvec2 mp = mMouseCoord;
	// Guardamos la posicion actual
	mMouseCoord = glm::dvec2(x, mWinH - y);
	mp = mMouseCoord - mp; // calculamos el desplazamiento realizado
	if (mMouseButt == GLUT_LEFT_BUTTON) {
		mCamera->orbit(mp.x * 0.05, mp.y); // sensitivity = 0.05
		glutPostRedisplay();
	}
	//no va nada de lo que pide xd
	else if (mMouseButt == GLUT_RIGHT_BUTTON) {
		//Mueve la cámara en los ejes X, Y
		mCamera->moveLR(-mp.x);
		mCamera->moveUD(-mp.y);

		glutPostRedisplay();
	}
}
void IG1App::mouseWheel(int whellNumber, int direction, int x, int y) {
	if (glutGetModifiers() == 0) {    //Si ningún modificador está presionado
		mCamera->moveFB(direction * 10);    //Movemos la cámara pero no escalamos
	}
	else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {    //Si se presiona el control
		mCamera->setScale(direction * 0.1);    //Escalamos
	}
	glutPostRedisplay();
}
void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		mScene->update();
		break;
	case 'w':
		//mScene->setDirLight(false);
		mScene->getDirLight()->disable();

		break;
	case 'q':
		//mScene->setDirLight(true);
		mScene->getDirLight()->enable();
		break;
	case 's':
		//mScene->setPosLight(false);
		mScene->getPosLight()->disable();
		break;
	case 'a':
		//mScene->setPosLight(true);
		mScene->getPosLight()->enable();
		break;
	case 'x':
		//mScene->setSpotLight(false);
		mScene->getSpotLight()->disable();
		break;
	case 'z':
		//mScene->setSpotLight(true);
		mScene->getSpotLight()->enable();
		break;
	case 'g':
		if (mScene->getPlaneLight() != nullptr)
		{
		mScene->getPlaneLight()->disable();
		}
		break;
	case 't':
		if (mScene->getPlaneLight()!=nullptr)
		{
			mScene->getPlaneLight()->enable();
		}
		break;
	case 'y':
		mScene->move();
		break;
	case 'f':
		mScene->getMineroLight()->disable();
		break;
	case 'd':
		mScene->getMineroLight()->enable();
		break;
	case 'e':
		mScene->sceneBlack();
		break;
	case '5':

		delete mScene;
		mScene = new Scene;
		mScene->setState(5);
		mScene->init();
		break;
	case '4':

		delete mScene;
		mScene = new Scene;
		mScene->setState(4);
		mScene->init();
		break;
	case '3':

		delete mScene;
		mScene = new Scene;
		mScene->setState(3);
		mScene->init();
		break;
	case '2':

		delete mScene;
		mScene = new Scene;
		mScene->setState(2);
		mScene->init();
		break;
	case '1':
		delete mScene;
		mScene = new Scene;
		mScene->setState(1);
		mScene->init();
		break;
	case '0':
		delete mScene;
		mScene = new Scene;
		mScene->setState(0);
		mScene->init();
		break;
	case 'p':
		mCamera->changePrj();
		break;
	case 'k':
		if (!m2Vistas)m2Vistas = true;
		else m2Vistas = false;
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) 
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->pitch(-1);   // rotates -1 on the X axis
			mCamera->moveLR(-1);
		else
			//mCamera->pitch(1);    // rotates 1 on the X axis
			mCamera->moveLR(1);
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			// mCamera->yaw(1);      // rotates 1 on the Y axis 
			mCamera->moveFB(1);
		else
			//mCamera->yaw(-1);     // rotate -1 on the Y axis 
			mCamera->moveFB(-1);
		break;
	case GLUT_KEY_UP:
		//mCamera->roll(1);    // rotates 1 on the Z axis
		mCamera->moveUD(0.02);
		break;
	case GLUT_KEY_DOWN:
		//mCamera->roll(-1);   // rotates -1 on the Z axis
		mCamera->moveUD(-0.2);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//IG1App::s_ig1app.winWidth();
//-------------------------------------------------------------------------

