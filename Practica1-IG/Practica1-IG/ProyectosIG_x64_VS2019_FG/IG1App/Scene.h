//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include "GLinclude.h"

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;
	void update();
	void setState(int id) {
		mId = id;
	};
protected:
	void free();
	void setGL();
	void resetGL();
	int mId = 0;
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*>gTextures;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_
