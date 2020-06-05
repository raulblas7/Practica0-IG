#include "Fondo.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>  


void Fondo::render() const
{
	if (malla != nullptr) {
		
		mCamera->upload();
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		mCamera->viewMat();
		img->bind(GL_DECAL);
		zelda->bind(GL_DECAL);
		glPolygonMode(GL_BACK, GL_FILL);
		malla->render();
		img->unbind();
		zelda->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}
