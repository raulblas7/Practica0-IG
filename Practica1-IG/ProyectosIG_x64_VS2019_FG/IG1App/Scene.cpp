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
	if (mId == 0) {
		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(new Poligono(100, 200.0, 128.0, 0.0, 128.0));
		gObjects.push_back(new Poligono(3, 200.0, 255.0, 255.0, 0.0));
		gObjects.push_back(new Sierpinski(200, 5000.0));

		auto r = new RectanguloRGB(1000.0, 1000.0);
		gObjects.push_back(r);
		r->setModelMat(translate(r->modelMat(), dvec3(0, 0, -100.0)));



		auto g = new TrianguloRGB(20.0);
		gObjects.push_back(g);

		g->setModelMat(translate(g->modelMat(), dvec3(1.0, 200.0, 0)));
		g->setModelMat(rotate(g->modelMat(), 25.0, dvec3(1.0, 0, 25.0)));
	}

	else {
		//load textures
		Texture* baldosaC = new Texture();
		baldosaC->load("Bmps/baldosaC",255);
		Texture* baldosaF = new Texture();
		baldosaF->load("baldosaF.bmp");
		Texture* baldosaP = new Texture();
		baldosaP->load("baldosaP.bmp");
		Texture* container = new Texture();
		container->load("container.bmp");
		Texture* grass = new Texture();
		grass->load("grass.bmp");
		Texture* papelC = new Texture();
		papelC->load("papelC.bmp");
		Texture* papelE = new Texture();
		papelE->load("papelE.bmp");
		Texture* windowC = new Texture();
		windowC->load("windowC.bmp");
		Texture* windowV = new Texture();
		windowV->load("windowV.bmp");

		//push to the vector of textures
		gTextures.push_back(baldosaC);
		gTextures.push_back(baldosaF);
		gTextures.push_back(baldosaP);
		gTextures.push_back(container);
		gTextures.push_back(grass);
		gTextures.push_back(papelC);
		gTextures.push_back(papelE);
		gTextures.push_back(windowC);
		gTextures.push_back(windowV);
	}
}
//-------------------------------------------------------------------------
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
	glClearColor(0.0, 0.0, 0.0, 0.0);  // background color (alpha=1 -> opaque)
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


