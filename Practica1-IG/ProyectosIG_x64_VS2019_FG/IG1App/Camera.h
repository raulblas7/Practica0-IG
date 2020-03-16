//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_access.hpp> 
#include "Viewport.h"
#include <ext\matrix_transform.hpp>


//-------------------------------------------------------------------------

class Camera {
public:
	explicit Camera(Viewport* vp);
	~Camera() {};

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix 
	glm::dmat4 const& viewMat() const { return mViewMat; };
	
	void set2D();
	void set3D();
	
	//void pitch(GLdouble a); // rotates a degrees on the X axis
	//void yaw(GLdouble a);   // rotates a degrees on the Y axis
	//void roll(GLdouble a);  // rotates a degrees on the Z axis
	void moveLR(GLdouble cs); // Left / Right
	void moveFB(GLdouble cs); // Forward / Backward
	void moveUD(GLdouble cs); // Up / Down 

	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };
	
	// sets scene visible area size 
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor 
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const { mViewPort->upload();  uploadVM(); uploadPM(); }; 

	void orbit(GLdouble incAng, GLdouble incY) {
		mAng += incAng;
		mEye.x = mLook.x + cos(glm::radians(mAng)) * mRadio;
		mEye.z = mLook.z - sin(glm::radians(mAng)) * mRadio;
		mEye.y += incY;
		setVM();
	}

	void changePrj() {
		if (bOrto) {
			bOrto = false;
			mProjMat = frustum(xLeft*mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
		}
		else { bOrto = true; setPM(); }
	}
protected:
	
	glm::dvec3 mEye = { 0.0, 0.0, 500.0 };  // camera's position
	glm::dvec3 mLook = { 0.0, 0.0, 0.0 };   // target's position
	glm::dvec3 mUp = { 0.0, 1.0, 0.0 };     // the up vector 

	glm::dmat4 mViewMat;    // view matrix = inverse of modeling matrix 
	void uploadVM() const;  // transfers viewMat to the GPU

	glm::dmat4 mProjMat;     // projection matrix
	void uploadPM() const;   // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;      // size of scene visible area
	glm::dvec3 mRight, mUpward, mFront;
	GLdouble mNearVal = 1, mFarVal = 10000;  // view volume
	GLdouble mScaleFact = 1;   // scale factor
	GLdouble mAng;
	GLdouble mRadio = 1000;
	bool bOrto = true;   // orthogonal or perspective projection

	Viewport* mViewPort;   // the viewport

	void setVM();
	void setPM();
	void setAxes() {
		mRight = row(mViewMat, 0);
		mUpward = row(mViewMat, 1);
		mFront = -row(mViewMat, 2);
	};
	void setViewMat() { setVM(); setAxes(); };
	
};
//-------------------------------------------------------------------------

#endif //_H_Camera_H_