#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	// allocate memory and load resources
    // Lights
    // Textures
	glEnable(GL_DEPTH_TEST);
	
	gObjects.push_back(new EjesRGB(400.0));
	//cabeza
	Sphere* esfera = new Sphere(100.0);
	gObjects.push_back(esfera);
	//ojos
	Cylinder* cono = new Cylinder(10.0, 0, 30.0);
	glm::dmat4 mAux = cono->modelMat();
	mAux = translate(mAux, dvec3(20, 50, 75));
	mAux = rotate(mAux, radians(-60.0), dvec3(1.0,0,1.0));
	mAux = rotate(mAux, radians(20.0), dvec3(0, 1.0, 0));
	cono->setModelMat(mAux);
	gObjects.push_back(cono);
	Cylinder* cono2 = new Cylinder(10.0, 0, 30.0);
	glm::dmat4 mAuxx = cono2->modelMat();
	mAuxx = translate(mAuxx, dvec3(70, 50, 35));
	mAuxx = rotate(mAuxx, radians(-60.0), dvec3(1.0,0,1.0));
	mAuxx = rotate(mAuxx, radians(20.0), dvec3(0, 1.0, 0));
	cono2->setModelMat(mAuxx);
	gObjects.push_back(cono2);

	//Gorro
	Disk* gorro = new Disk(50.0, 90.0);
	glm::dmat4 mAuxg = gorro->modelMat();
	mAuxg = translate(mAuxg, dvec3(0, 85, 0));
	mAuxg = rotate(mAuxg, radians(-90.0), dvec3(0, 1.0, 0));
	mAuxg = rotate(mAuxg, radians(-90.0), dvec3(1.0, 0, 0));
	gorro->setModelMat(mAuxg);
	gObjects.push_back(gorro);

	//sonrisa
	PartialDisk* sonrisa = new PartialDisk(60.0, 80.0, 90, 180);
	glm::dmat4 mAuxs = sonrisa->modelMat();
	mAuxs = translate(mAuxs, dvec3(60, 20, 60));
	mAuxs = rotate(mAuxs, radians(45.0), dvec3(0, 1.0, 0));
	sonrisa->setModelMat(mAuxs);
	gObjects.push_back(sonrisa);
	//if (mId == 0) {
	//	// Graphics objects (entities) of the scene
	//	
	//	gObjects.push_back(new Poligono(100, 200.0, 128.0, 0.0, 128.0));
	//	gObjects.push_back(new Poligono(3, 200.0, 255.0, 255.0, 0.0));
	//	gObjects.push_back(new Sierpinski(200, 5000.0));

	//	auto r = new RectanguloRGB(1000.0, 1000.0);
	//	gObjects.push_back(r);
	//	r->setModelMat(translate(r->modelMat(), dvec3(0, 0, -100.0)));



	//	auto g = new TrianguloRGB(20.0);
	//	gObjects.push_back(g);

	//	g->setModelMat(translate(g->modelMat(), dvec3(1.0, 200.0, 0)));
	//	g->setModelMat(rotate(g->modelMat(), 25.0, dvec3(1.0, 0, 25.0)));
	//}

	/*else {
		*/

		//load textures
		//Texture* baldosaC = new Texture();
		//baldosaC->load("..//Bmps//baldosaC.bmp");
		//Texture* baldosaF = new Texture();
		//baldosaF->load("..//Bmps//baldosaF.bmp");
		//Texture* baldosaP = new Texture();
		//baldosaP->load("..//Bmps//baldosaP.bmp");
		//Texture* container = new Texture();
		//container->load("..//Bmps//container.bmp");
		//Texture* grass = new Texture();
		//grass->load("..//Bmps//grass.bmp");
		//Texture* papelC = new Texture();
		//papelC->load("..//Bmps//papelC.bmp");
		//Texture* papelE = new Texture();
		//papelE->load("..//Bmps//papelE.bmp");
		//Texture* windowC = new Texture();
		//windowC->load("..//Bmps//windowC.bmp");
		//Texture* windowV = new Texture();
		//windowV->load("..//Bmps//windowV.bmp",121);
		//Texture* foto = new Texture();
		//foto->loadColorBuffer();

		////push to the vector of textures
		//gTextures.push_back(baldosaC);
		//gTextures.push_back(baldosaP);
		//gTextures.push_back(container);
		//gTextures.push_back(windowV);
		//gTextures.push_back(foto);

		//auto g = new Estrella3D(100.0, 9, 100.0);
		//gObjects.push_back(g);
		//g->setTexture(baldosaP);
		//g->setModelMat(rotate(g->modelMat(), 25.0, dvec3(1.0, 0, 25.0)));
		//g->setModelMat(translate(dmat4(1), dvec3(-100.0, 200.0, -100.0)));
		//auto a = new Suelo(500.0, 500.0,9,9);
		//a->setTexture(baldosaC);
		//gObjects.push_back(a);
		//a->setModelMat(rotate(a->modelMat(),radians(90.0), dvec3(1.0, 0, 0)));
		//auto c = new Caja(100);
		//c->setTexture(container);
		//c->setTextureInt(papelE);
		//gObjects.push_back(c);
		//c->setModelMat(translate(dmat4(1), dvec3(-100.0, 50.0, -100.0)));
		//
		//auto d = new Habitacion(500.0);
		//d->setTexture(windowV);
		//gObjects.push_back(d);
		//d->setModelMat(translate(dmat4(1), dvec3(-1.0, 250.0, -1.0)));
		//
		//auto f = new Foto(100.0, 100.0, 1, 1);
		//f->setTexture(foto);
		//gObjects.push_back(f);
		//f->setModelMat(translate(dmat4(1.0), dvec3(200, 50, 0.0)));
		//f->setModelMat(rotate(f->modelMat(), radians(90.0), dvec3(1.0, 0, 0)));


}
//-------------------------------------------------------------------------
void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}

void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Texture* tx : gTextures)
	{
		delete tx;  tx = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	//glClearColor(0.0, 0.0, 0.0, 0.0);  // background color (alpha=1 -> opaque)
	glClearColor(0.7, 0.8, 0.9, 0.0);
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  //enable texture

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D); //disable texture
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	sceneDirLight(cam);
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
void Scene::update()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------


