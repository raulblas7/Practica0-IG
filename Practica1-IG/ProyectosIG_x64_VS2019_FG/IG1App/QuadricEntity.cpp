#include "QuadricEntity.h"

QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr) { r = rr; }

void Sphere::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	/*glEnable(GL_COLOR_MATERIAL);
	glColor3f(250.0, 1.0, 1.0);*/
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Cylinder::Cylinder(GLdouble rr, GLdouble rr2, GLdouble height) { r = rr;  r2 = rr2; h = height; }

void Cylinder::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable(GL_COLOR_MATERIAL);
	// glColor3f(...);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, r, r2, h, 50, 50);
	// Aquí se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble  innerRadius_, GLdouble  outerRadius_) {innerRadius = innerRadius_; outerRadius = outerRadius_; }

void Disk::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	/*glEnable(GL_COLOR_MATERIAL);
	glColor3f(255, 108, 0);*/
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluDisk(q, innerRadius, outerRadius, 50, 50);
	// Aquí se debe recuperar el color:
	//glColor3f(1.0, 1.0, 1.0);
}

PartialDisk::PartialDisk(GLdouble  innerRadius_, GLdouble  outerRadius_, GLdouble startAngle_, GLdouble sweepAngle_)
{ innerRadius = innerRadius_; outerRadius = outerRadius_;
startAngle = startAngle_; sweepAngle = sweepAngle_;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const {
	glm::dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	// glEnable(GL_COLOR_MATERIAL);
	// glColor3f(...);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);
	// Aquí se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}
	