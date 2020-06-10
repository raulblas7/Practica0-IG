#include "Camera.h"
#include "CheckML.h"


//#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
	setAxes();
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	mEye = dvec3(0, 0, mRadio);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	mAng = 0.0;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mEye = dvec3(mRadio, mRadio, mRadio);
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);
	mAng = 315.0;
	setVM();
}
//-------------------------------------------------------------------------

//void Camera::pitch(GLdouble a) 
//{  
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::yaw(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::roll(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	if (bOrto) {
		mScaleFact -= s;
		if (mScaleFact < 0) mScaleFact = 0.01;
		setPM();
	}
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		GLdouble mNear = yTop;
		mProjMat = glm::frustum(xLeft * 0.005, xRight * 0.005, yBot * 0.005, yTop * 0.005, mNear, mFarVal);
	}
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat));
	glMatrixMode(GL_MODELVIEW);
}

void Camera::moveLR(GLdouble cs) {
	setVM();
	mEye += mRight * cs;
	mLook += mRight * cs;
}
void Camera::moveFB(GLdouble cs) {
	setVM();
	mEye += mFront * cs;
	mLook += mFront * cs;
}
void Camera::moveUD(GLdouble cs) {
	setVM();
	mEye += mUpward * cs;
	mLook += mUpward * cs;
}
//-------------------------------------------------------------------------
void Camera::orbit(GLdouble incAng, GLdouble incY) {
	setVM();
	mAng += incAng;
	mEye.z = mLook.x + cos(glm::radians(mAng)) * mRadio;
	mEye.x = mLook.z - sin(glm::radians(mAng)) * mRadio;
	mEye.y -= incY;
}

void Camera::changePrj() {
	if (bOrto) {
		bOrto = false;
		mProjMat = glm::frustum(xLeft * 0.005, xRight * 0.005, yBot * 0.005, yTop * 0.005, mNearVal, mFarVal);
	}
	else { bOrto = true; setPM(); }
}

void Camera::setCenital() {
	mEye = glm::dvec3(0, 500, 0);
	mLook = glm::dvec3(0, 0, 0);
	mUp = glm::dvec3(1, 1, 0);
	setVM();
}

void Camera::setAxes() {
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}


