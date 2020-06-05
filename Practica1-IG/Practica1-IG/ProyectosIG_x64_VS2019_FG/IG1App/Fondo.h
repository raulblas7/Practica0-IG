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
		malla = malla->generaRectanguloTexCor(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 1, 1); /*malla->setTwoUnits();*/
		img = new Texture(); zelda = new Texture();
		img->load("..//Bmps//noche.bmp"/*,100, GL_TEXTURE0*/); zelda->load("..//Bmps//Zelda.bmp", 50/*, GL_TEXTURE1*/);
		mViewPort = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		mCamera = new Camera(mViewPort); mCamera->set2D();
	}
	~Fondo() { delete img; delete malla; delete mCamera; delete mViewPort; }
	void render() const;
	void setSizeVP(GLdouble xw, GLdouble yh) { mViewPort->setSize(xw, yh); }
	Camera* getCamera() { return mCamera; }
	void upload(glm::dmat4 const& modelViewMat) const
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
	}
private:
	Texture* img = nullptr;
	Texture* zelda = nullptr;
	Mesh* malla = nullptr;
	Camera *mCamera = nullptr;
	Viewport* mViewPort = nullptr;
};

