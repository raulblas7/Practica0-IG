#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}


Poligono::Poligono(GLuint l, GLdouble r, GLdouble c1, GLdouble c2, GLdouble c3) : Abs_Entity()
{
	mMesh = Mesh::generaPoligono(l, r, c1, c2, c3);
}

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
};

void Poligono::render(dmat4 const& modelViewMat)const {

	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);

		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

Sierpinski::Sierpinski(GLdouble r,GLuint l) : Abs_Entity()
{
	mMesh = Mesh::generaSierpinski(r, l);
}

Sierpinski::~Sierpinski() {
	delete mMesh; mMesh = nullptr;
}

void Sierpinski::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPointSize(2);
		glColor4dv(value_ptr(mColor));
		mMesh->render();
		glPointSize(1);
		GLdouble* x =new GLdouble( 1.0);
		glColor4dv(x);
	}
}

TrianguloRGB::TrianguloRGB(GLdouble r) : Abs_Entity()
{
	rotation = 10.0;
	mMesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		
	}
}
void TrianguloRGB::update() {
	if (mMesh != nullptr) {
		mModelMat = translate(dmat4(1), dvec3(200.0 * cos(radians(rotation)), 200.0 * sin(radians(rotation)), 0));
		mModelMat = rotate(mModelMat, radians(rotation), dvec3(0, 0, 1));	
		rotation += 10.0;
	}
}
RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w,h);
}

RectanguloRGB::~RectanguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
	}
}
//-------------------------------------------------------------------------
 