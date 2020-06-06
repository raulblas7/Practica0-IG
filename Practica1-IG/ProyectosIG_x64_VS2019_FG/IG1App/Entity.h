#pragma once


#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() = 0;
	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void setMColor(glm::dvec4 const& aCol) { mColor = aCol; };
	void setTexture(Texture* tex) { mTexture = tex; };
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;
	Texture* mTexture = nullptr; //the texture
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};

};

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint l, GLdouble r, GLdouble c1, GLdouble c2, GLdouble c3);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};

};

class Sierpinski : public Abs_Entity
{
public:
	explicit Sierpinski(GLdouble r, GLuint l);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};

};

class TrianguloRGB : public Abs_Entity
{
private:
	GLdouble rotation;
public:
	explicit TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

};
class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w,GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};

};

class Estrella3D : public Abs_Entity
{
private:
	GLdouble rotation;
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

};
class Suelo:public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};


};
class Caja :public Abs_Entity
{
public:
	Texture* TextureInt = nullptr; //the texture

	explicit Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
	void setTextureInt(Texture* tex) { TextureInt = tex; };


};
class Foto :public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

class Habitacion :public Abs_Entity
{
public:
	explicit Habitacion(GLdouble ld);
	~Habitacion();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

//-------------------------------------------------------------------------
class AnilloCuadrado :public Abs_Entity
{
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
private:

};

class EntityWithIndexMesh : public Abs_Entity {
public:
	explicit EntityWithIndexMesh() {};
	~EntityWithIndexMesh() {};
	virtual void render(glm::dmat4 const& modelViewMat) const = 0;
	virtual void update() = 0;
};

class Cubo : public EntityWithIndexMesh {
public:
	explicit Cubo(GLdouble l);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
	virtual void setCopper()const;

};

class CompoundEntity : public Abs_Entity {
public:
	explicit CompoundEntity();
	~CompoundEntity() {
		for (Abs_Entity* el : gObjects)
		{
			delete el;  el = nullptr;
		}
	};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	void addEntity(Abs_Entity* ae);
private:
	std::vector<Abs_Entity*> gObjects;

};

class Cono : public EntityWithIndexMesh {
public:
	explicit Cono(GLdouble h, GLdouble r, GLuint n);
	~Cono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { delete material; material = nullptr; };

	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};

class Esfera : public EntityWithMaterial {
public:
	explicit Esfera(GLdouble r, GLuint p, GLuint m, glm::fvec3 color);
	 virtual ~Esfera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
protected:
	virtual void setGold()const;

	glm::fvec3 color = glm::fvec3(-1, -1, -1);
};

class Avion : public CompoundEntity {
public:
	explicit Avion();
	 virtual ~Avion();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
	void addEntity(Abs_Entity* ae);
	SpotLight* getLight() { return spotlight; }
private:
	std::vector<Abs_Entity*> gObjects;
	SpotLight* spotlight = nullptr;

};

class Grid : public EntityWithIndexMesh{
public:
	explicit Grid(GLdouble l, GLint numRej);
	~Grid();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};
class GridCube : public CompoundEntity {
public:
	explicit GridCube();
	~GridCube() {
	};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};