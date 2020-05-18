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
		glEnable(GL_COLOR_MATERIAL);
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

Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) {
	rotation = 10.0;
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}
Estrella3D::~Estrella3D() {
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		
		if (mTexture != nullptr) {
			mTexture->bind(GL_REPLACE);
		}
		else {
			glLineWidth(2);
		}

		mMesh->render();

		aMat = rotate(aMat, radians(180.0), glm::dvec3(1, 0, 0));
		upload(aMat);
		mMesh->render();

		if (mTexture != nullptr) {
			mTexture->unbind();
		}

	}
}

void Estrella3D::update() {
	if (mMesh != nullptr) {
		rotation += 2.5;
		setModelMat(translate(dmat4(1.0), dvec3(-100.0, 200.0, -100.0)));
		dmat4 aMat = (rotate(modelMat(), radians(rotation), dvec3(0, 1, 0)));
		setModelMat(rotate(aMat, radians(rotation), dvec3(0, 0, 1)));
	}
}

Suelo::Suelo(GLdouble w,GLdouble h, GLuint rw, GLuint rh) {
	mMesh = Mesh::generaRectanguloTexCor(w, h,rw,rh);
}
Suelo::~Suelo() {
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(dmat4 const& modelViewMat)const {

		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
			upload(aMat);

			mTexture->bind(GL_REPLACE);
			
			mMesh->render();
			
			mTexture->unbind();
		}
}
Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCubo(ld);
}
Caja::~Caja() {
	delete mMesh; mMesh = nullptr;
}

void Caja::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;		// glm matrix multiplication
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		mTexture->bind(GL_REPLACE);
		upload(aMat);
		mMesh->render();
		mTexture->unbind();


		glCullFace(GL_FRONT);

		TextureInt->bind(GL_REPLACE);
		upload(aMat);
		mMesh->render();
		TextureInt->unbind();

		glDisable(GL_CULL_FACE);
	}
}

Foto::Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
}

Foto::~Foto() {
	delete mMesh; mMesh = nullptr;
}

void Foto::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		mTexture->bind(GL_REPLACE);
		mTexture->loadColorBuffer();
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);

		mTexture->unbind();
	}
}

Habitacion::Habitacion(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCubo(ld);
}

void Habitacion::render(dmat4 const& modelViewMat)const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;		// glm matrix multiplication
		mTexture->bind(GL_REPLACE);
		upload(aMat);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		mMesh->render();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glBlendFunc(1, 0);
		mTexture->unbind();
	}
}

Habitacion::~Habitacion() {
	delete mMesh; mMesh = nullptr;
}


//-------------------------------------------------------------------------
AnilloCuadrado::AnilloCuadrado() {
	mMesh = Mesh::generaAnilloCuadrado();
}

void AnilloCuadrado::render(dmat4 const& modelViewMat)const {
	
		if (mMesh != nullptr) {
			dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
			glEnable(GL_COLOR_MATERIAL);
			upload(aMat);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);
			mMesh->render();
			glColor3f(1.0, 1.0, 1.0);

		}
	
}

AnilloCuadrado::~AnilloCuadrado() {
	delete mMesh; mMesh = nullptr;
}

EntityWithIndexMesh::EntityWithIndexMesh()
{
}

Cubo::Cubo(GLdouble l)
{
	mMesh = IndexMesh::generaIndexCuboConTapas(l);
}

Cubo::~Cubo()
{
	delete mMesh; mMesh = nullptr;
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mMesh->render();
	}
}

CompoundEntity::CompoundEntity()
{
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}

void CompoundEntity::update()
{
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

Cono::Cono(GLdouble h, GLdouble r, GLuint n)
{
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, h, 0.0);
	this->mMesh= MbR::generaIndexMeshByRevolution(m,n,perfil);

}

Cono::~Cono()
{
	delete mMesh; mMesh = nullptr;

}

void Cono::render(glm::dmat4 const& modelViewMat) const
{

}

Esfera::Esfera(GLdouble r, GLdouble p, GLdouble m)
{
	int m_ = p;
	dvec3* perfil = new dvec3[m_];
	perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.5, r, 0.0);
	perfil[3] = dvec3(0.5, 0.0, 0.0);
	perfil[4] = dvec3(r, 0.0, 0.0);
	perfil[5] = dvec3(0.5, r, 0.0);perfil[0] = dvec3(0.5, 0.0, 0.0);
	perfil[6] = dvec3(r, 0.0, 0.0);
	perfil[7] = dvec3(0.5, r, 0.0);
	perfil[8] = dvec3(0.5, 0.0, 0.0);
	perfil[9] = dvec3(r, 0.0, 0.0);
	perfil[10] = dvec3(0.5, r, 0.0);
//	this->mMesh = new MbR(m_, n, perfil);
}

Esfera::~Esfera()
{
	delete mMesh; mMesh = nullptr;

}

void Esfera::render(glm::dmat4 const& modelViewMat) const
{

}
