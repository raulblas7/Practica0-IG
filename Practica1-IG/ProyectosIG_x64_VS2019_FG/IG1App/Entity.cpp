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
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);



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
			glDisable(GL_COLOR_MATERIAL);

		}
	
}

AnilloCuadrado::~AnilloCuadrado() {
	delete mMesh; mMesh = nullptr;
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
		//glEnable(GL_COLOR_MATERIAL);
		setCopper();
		mMesh->render();
		glColor3f(1.0, 1.0, 1.0);
		//glDisable(GL_COLOR_MATERIAL);
	}
}

void Cubo::setCopper() const
{
	GLuint face = GL_FRONT_AND_BACK;

	glm::fvec4 ambient  = { 0.19125, 0.0735, 0.0225, 1 };
	glm::fvec4 diffuse  = { 0.7038, 0.27048, 0.0828, 1 };
	glm::fvec4 specular  = { 0.256777, 0.137622, 0.086014, 1 };
	GLfloat expF = 12.8;
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
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
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_COLOR_MATERIAL);
		mMesh->render();
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
	}
}

Esfera::Esfera(GLdouble r, GLuint p, GLuint m, glm::fvec3 color_)
{
	color = color_;
	glm::dvec3* perfil = new glm::dvec3[p];	
	for (int i = 0; i < p; i++) {
		f64 x = r * cos(radians(-90.0 + (180.0 / p) * i));
		f64 y = r * sin(radians(-90.0 + (180.0 / p) * i));
		perfil[i]= glm::dvec3(x,y,0.0);
	}
	perfil[(int)p-1] = glm::dvec3(0.0, r, 0.0);

	mMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
	delete[]perfil;
}

Esfera::~Esfera()
{
	delete mMesh; mMesh = nullptr;
}

void Esfera::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		if (material != nullptr)
		{
			Esfera::setGold();
		}
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(color.x, color.y, color.z);
		mMesh->render();
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
	}
}

void Esfera::setGold()const
{
	GLuint face = GL_FRONT_AND_BACK;

	glm::fvec4 ambient = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
	glm::fvec4 diffuse = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
	glm::fvec4 specular = { 0.628281f, 0.0555802f, 0.366064f, 1.0f };
	GLfloat expF = 52.1; 
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS,expF);

}
Avion::Avion()
{
	spotlight = new SpotLight();
}
Avion::~Avion()
{
	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	if (spotlight != nullptr)
	{
		delete spotlight;
		spotlight = nullptr;
	}
}
void Avion::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	
		spotlight->upload(aMat);
		upload(aMat);

	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}

void Avion::update()
{
}

void Avion::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

Grid::Grid(GLdouble l, GLint numRej)
{
	mMesh = IndexMesh::generateGridTex(l,numRej);

}

Grid::~Grid()
{
}

void Grid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		/*glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);*/
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

GridCube::GridCube()
{
	Texture* supinf = new Texture();
	supinf->load("..//Bmps//stones.bmp");
	Texture* otros = new Texture();
	otros->load("..//Bmps//checker.bmp");

	Grid* ab = new Grid(200, 20);
	ab->setTexture(supinf);
	
	Grid* ar = new Grid(200, 20);
	ar->setTexture(supinf);
	ar->setModelMat(translate(ar->modelMat(), glm::dvec3(0, 200, 0)));

	Grid* fr = new Grid(200, 20);
	fr->setTexture(otros);
	fr->setModelMat(translate(fr->modelMat(), glm::dvec3(0, 0, 200)));
	fr->setModelMat(rotate(fr->modelMat(), radians(90.0),glm::dvec3(-1, 0, 0)));


	Grid* at = new Grid(200, 20);
	at->setTexture(otros);
	at->setModelMat(rotate(at->modelMat(), radians(90.0), glm::dvec3(-1, 0, 0)));
	
	Grid* iz = new Grid(200, 20);
	iz->setTexture(otros);
	iz->setModelMat(rotate(iz->modelMat(), radians(90.0), glm::dvec3(0, 0, 1)));

	Grid* de = new Grid(200, 20);	
	de->setTexture(otros);
	de->setModelMat(translate(de->modelMat(), glm::dvec3(200, 0, 0)));
	de->setModelMat(rotate(de->modelMat(), radians(90.0), glm::dvec3(0, 0, 1)));


	addEntity(ar);
	addEntity(ab);
	addEntity(iz);
	addEntity(de);
	addEntity(fr);
	addEntity(at);
}

void GridCube::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

	upload(aMat);

	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}

SirenCube::SirenCube()
{
	Texture* supinf = new Texture();
	supinf->load("..//Bmps//stones.bmp");
	Texture* otros = new Texture();
	otros->load("..//Bmps//checker.bmp");

	Grid* ab = new Grid(200, 20);
	ab->setTexture(supinf);

	Grid* ar = new Grid(200, 20);
	ar->setTexture(supinf);
	ar->setModelMat(translate(ar->modelMat(), glm::dvec3(0, 200, 0)));

	Grid* fr = new Grid(200, 20);
	fr->setTexture(otros);
	fr->setModelMat(translate(fr->modelMat(), glm::dvec3(0, 0, 200)));
	fr->setModelMat(rotate(fr->modelMat(), radians(90.0), glm::dvec3(-1, 0, 0)));


	Grid* at = new Grid(200, 20);
	at->setTexture(otros);
	at->setModelMat(rotate(at->modelMat(), radians(90.0), glm::dvec3(-1, 0, 0)));

	Grid* iz = new Grid(200, 20);
	iz->setTexture(otros);
	iz->setModelMat(rotate(iz->modelMat(), radians(90.0), glm::dvec3(0, 0, 1)));

	Grid* de = new Grid(200, 20);
	de->setTexture(otros);
	de->setModelMat(translate(de->modelMat(), glm::dvec3(200, 0, 0)));
	de->setModelMat(rotate(de->modelMat(), radians(90.0), glm::dvec3(0, 0, 1)));


	addEntity(ar);
	addEntity(ab);
	addEntity(iz);
	addEntity(de);
	addEntity(fr);
	addEntity(at);
	Esfera* sir = new Esfera(50, 50, 50, fvec3(0, 0, 0));
	at->setModelMat(translate(fr->modelMat(), glm::dvec3(0, 200, 0)));
	addEntity(sir);
}

void SirenCube::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication

	spotlight->upload(aMat);
	upload(aMat);

	for (Abs_Entity* el : gObjects) {
		el->render(aMat);
	}
}
