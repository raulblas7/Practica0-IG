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

    // Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));
	gObjects.push_back(new Poligono(100, 200.0, 128.0, 0.0, 128.0));
	gObjects.push_back(new Poligono(3, 200.0, 255.0, 255.0, 0.0));
	gObjects.push_back(new Sierpinski(200, 5000.0));

	auto r = new RectanguloRGB(1000.0, 1000.0);
	gObjects.push_back(r);
	r->setModelMat(translate(r->modelMat(), dvec3(0, 0, -100.0)));



	auto g=new TrianguloRGB(20.0);
	gObjects.push_back(g);

	g->setModelMat(translate(g->modelMat(), dvec3(1.0, 200.0, 0)));
	g->setModelMat(rotate(g->modelMat(),25.0, dvec3(1.0, 0, 25.0)));
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 0.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
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


