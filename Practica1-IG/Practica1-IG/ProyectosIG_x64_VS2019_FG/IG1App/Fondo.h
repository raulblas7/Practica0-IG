#pragma once
//Extra 1
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "Viewport.h"
class Fondo
{
public:
	Fondo() {
		malla= malla->generaRectanguloTexCor(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 1, 1);
		 img = new Texture();
		img->load("..//Bmps//noche.bmp");
		mViewPort = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		mCamera = new Camera(mViewPort);
	}
	~Fondo() { delete img; delete malla; delete mCamera; delete mViewPort; }
	void render() const;
	void setSizeVP(GLdouble xw, GLdouble yh) { mViewPort->setSize(xw, yh); }
	Camera* getCamera() { return mCamera; }
private:
	Texture* img = nullptr;
	Mesh* malla = nullptr;
	Camera *mCamera = nullptr;
	Viewport* mViewPort = nullptr;
};

