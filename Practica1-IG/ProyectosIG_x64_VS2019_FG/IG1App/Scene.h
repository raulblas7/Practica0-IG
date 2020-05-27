//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "QuadricEntity.h"

#include <vector>
#include "Light.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

	void sceneDirLight(Camera const& cam) const;
	void scenePosLight(Camera const& cam) const;
	void sceneSpotLight(Camera const& cam)const;
	void sceneBlack(){
		GLfloat amb[] = {0, 0, 0, 1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	}

    void render(Camera const& cam) const;
	void update();
	void setState(int id) {
		mId = id;
	};
	void setDirLight(bool active)
	{
		dirLight = active;
	}
	void setPosLight(bool active)
	{
		posLight = active;
	}
	void setSpotLight(bool active)
	{
		spotLight = active;
	}
	DirLight* directionalLight;
	PosLight* positionalLight;
	SpotLight* spotSceneLight;
	PosLight* luzMinero;
	SpotLight* luzAvion=nullptr;

	void move();

protected:
	void free();
	void setGL();
	void resetGL();
	void setLights();
	int mId = 0;
	bool dirLight = false;
	bool posLight = false;
	bool spotLight = false;
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*>gTextures;
	CompoundEntity* avionsitofinal;
	CompoundEntity* helicesfinal;
	double rotation = 90;

	
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

