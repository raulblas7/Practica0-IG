#include "Fondo.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>  


void Fondo::render() const
{
	if (malla != nullptr) {
		
		//mCamera->upload();
         //glMatrixMode(GL_MODELVIEW);
		//glLoadMatrixd(value_ptr(mCamera->viewMat()));		
		img->bind(GL_REPLACE);
		glPolygonMode(GL_FRONT, GL_FILL);
		malla->render();
		img->unbind();
	}
}
