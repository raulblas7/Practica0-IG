//#pragma once
#ifndef _H_Texture_H_
#define _H_Texture_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"
#include <string>
//-------------------------------------------------------------------------

class Texture
{
public:
  Texture(){};
  ~Texture();

  Texture(const Texture & tex) = delete;  // no copy constructor
  Texture & operator=(const Texture & tex) = delete;  // no copy assignment

  void load(const std::string & BMP_Name, GLubyte alpha = 255); // load from file and upload to GPU
  
  void bind(GLuint mixMode);   // GL_REPLACE, GL_MODULATE, GL_ADD, ...
  void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

  GLuint width() const { return mWidth; };
  GLuint height() const { return mHeight; };
  
  void setWrap(GLuint wp);  // GL_REPEAT, GL_CLAMP 


  void loadColorBuffer()
  {
	  glBindTexture(GL_TEXTURE_2D, 5);
	  glReadBuffer(GL_FRONT); // por defecto GL_BACK 
	  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		  0, 0, 800, 600, 0);
  }

protected:

  void init();
  
  GLuint mWidth = 0;
  GLuint mHeight = 0;
  GLuint mId = 0;
  
};

//-------------------------------------------------------------------------

#endif //_H_Texture_H_

