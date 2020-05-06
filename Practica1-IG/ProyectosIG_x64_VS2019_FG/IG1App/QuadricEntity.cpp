#include "QuadricEntity.h"

QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr, glm::fvec3 color_) { r = rr; color = color_; }

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.x,color.y,color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Cylinder::Cylinder(GLdouble rr, GLdouble rr2, GLdouble height, glm::fvec3 color_) { r = rr;  r2 = rr2; h = height; color = color_; }

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.x, color.y, color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, r, r2, h, 50, 50);
	// Aquí se debe recuperar el color:
    glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble  innerRadius_, GLdouble  outerRadius_, glm::fvec3 color_) { innerRadius = innerRadius_; outerRadius = outerRadius_; color = color_; }

void Disk::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.x, color.y, color.z);
	//glColor3f(color.r,color.g,color.b);
	
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluDisk(q, innerRadius, outerRadius, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

PartialDisk::PartialDisk(GLdouble  innerRadius_, GLdouble  outerRadius_, GLdouble startAngle_, GLdouble sweepAngle_, glm::fvec3 color_)
{ innerRadius = innerRadius_; outerRadius = outerRadius_;
startAngle = startAngle_; sweepAngle = sweepAngle_; color = color_;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color.x, color.y, color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);
	// Aquí se debe recuperar el color:
	 glColor3f(1.0, 1.0, 1.0);
}
	