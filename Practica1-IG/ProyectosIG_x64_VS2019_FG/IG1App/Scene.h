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
	    
	DirLight* getDirLight() { return directionalLight; }
	PosLight* getPosLight() { return positionalLight; }
	SpotLight* getSpotLight() { return spotSceneLight; }
	PosLight* getMineroLight() { return luzMinero; }
	SpotLight* getPlaneLight() { return luzAvion; }

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
	
private:
	DirLight* directionalLight = nullptr;
	PosLight* positionalLight = nullptr;
	SpotLight* spotSceneLight = nullptr;
	PosLight* luzMinero = nullptr;
	SpotLight* luzAvion = nullptr;
	Avion* avionsitofinal = nullptr;
	CompoundEntity* helicesfinal = nullptr;
	double helicesAngle = 0.0;
	double avionAngle = 0.0;
	int radio = 250;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

