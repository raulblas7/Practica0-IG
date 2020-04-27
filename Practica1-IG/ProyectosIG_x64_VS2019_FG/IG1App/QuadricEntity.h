#pragma once
#include "Entity.h"

class QuadricEntity : public Abs_Entity
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
	virtual void update() {};

protected:
	GLUquadricObj* q;
	glm::fvec3 color = glm::fvec3(-1, -1, -1);

};

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r, glm::fvec3 color); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble r, GLdouble r2, GLdouble h, glm::fvec3 color); // radios de las bases del cilindro
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
	GLdouble r2;
	GLdouble h;
};

class  Disk : public QuadricEntity {
public:
	Disk(GLdouble  innerRadius, GLdouble  outerRadius, glm::fvec3 color); // radios del disco
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
};

class  PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble  innerRadius, GLdouble  outerRadius, GLdouble startAngle, GLdouble sweepAngle, glm::fvec3 color); // radios del disco y angulos
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLdouble startAngle, sweepAngle;
};

