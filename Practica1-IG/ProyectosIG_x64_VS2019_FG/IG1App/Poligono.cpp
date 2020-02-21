#include "Poligono.h"

void Poligono::render() {

	if (mMesh != nullptr) {
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		
		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);

	}
	

}