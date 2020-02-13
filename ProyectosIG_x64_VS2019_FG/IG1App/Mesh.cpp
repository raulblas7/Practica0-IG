#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
	Mesh* mesh = new Mesh();

	mesh->mNumVertices = numL;
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->vVertices.reserve(numL);
	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < numL; i++)
	{
		mesh->vVertices.emplace_back(rd * cos(radians(90.0+(360.0/numL)*i)), rd * sin(radians(90.0+(360.0 / numL) * i)), 0.0);
		mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	}
	/*mesh->vVertices.emplace_back(rd * cos(radians(90.0)), rd * sin(radians(90.0)), 0.0);
	mesh->vVertices.emplace_back(rd * cos(radians(90.0 + 360.0/numL)), rd * sin(radians(90.0 + 360.0 / numL)), 0.0);
	mesh->vVertices.emplace_back(rd * cos(radians(90.0 + 360.0 / numL + 360.0 / numL)), rd * sin(radians(90.0 + 360.0 / numL + 360.0 / numL)), 0.0);
	*/
	
	return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
	Mesh* triangulo = generaPoligono(3, rd);
//	Mesh* circulo = generaPoligono(68, rd);
	Mesh* meshita = new Mesh();
	meshita->mPrimitive = GL_POINTS;

	meshita->mNumVertices = numP + 3;
	meshita->vVertices.reserve(meshita->mNumVertices);
	meshita->vColors.reserve(meshita->mNumVertices);

	//se meten los vertices del triangulo
	for (uint i = 0; i < triangulo->mNumVertices; i++) {
		meshita->vVertices.emplace_back(triangulo->vVertices[i]);
	}

	//calculo del primer punto medio
	glm::dvec3 pMedio = glm::dvec3((triangulo->vVertices[0].x + triangulo->vVertices[1].x) / 2,
		(triangulo->vVertices[0].y + triangulo->vVertices[1].y) / 2, 
		(triangulo->vVertices[0].z + triangulo->vVertices[1].z) / 2);

	meshita->vVertices.emplace_back(pMedio);
	//añadiendo todos los vertices - 4, uno del primer punto medio y 3 del triangulo principal
	for (int i = 0; i < numP - 1 - triangulo->mNumVertices; i++) {
		glm::dvec3 randomVertex = triangulo->vVertices[rand() % 3];
		pMedio = glm::dvec3((pMedio.x + randomVertex.x) / 2, (pMedio.y + randomVertex.y) / 2, (pMedio.z + randomVertex.z) / 2);
		meshita->vVertices.emplace_back(pMedio);
	}
	//añadiendo color a los puntos
	for (int i = 0; i < numP; i++) {
		meshita->vColors.emplace_back(255.0, 255.0, 0.0, 1.0);
	}

	delete triangulo; triangulo = nullptr;
	return meshita;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
	Mesh* rgbTriang = generaPoligono(3,rd);

	rgbTriang->mPrimitive = GL_TRIANGLES;
	//limpio primero el vector para que asi no salga los colores fijados por generaPoligono
	rgbTriang->vColors.clear();
	rgbTriang->vColors.emplace_back(255.0, 0.0,0.0,1.0);
	rgbTriang->vColors.emplace_back(0.0, 0.0, 255.0, 1.0);
	rgbTriang->vColors.emplace_back(0.0, 128.0, 0.0, 1.0);

	return rgbTriang;
}
 Mesh*  Mesh::generaRectangulo(GLdouble w, GLdouble h)
 {
	 Mesh* meshita = new Mesh();
	 meshita->mPrimitive = GL_TRIANGLE_STRIP;
	 meshita->mNumVertices = 4;
	 meshita->vVertices.reserve(meshita->mNumVertices);
	 meshita->vColors.reserve(meshita->mNumVertices);

	 
		 meshita->vVertices.emplace_back(0,0,0);
		 meshita->vVertices.emplace_back(0, h,0);
		 meshita->vVertices.emplace_back(w, 0, 0);

		 meshita->vVertices.emplace_back(w, h,0);


		 meshita->vColors.emplace_back(255.0, 255.0, 0.0, 1.0);	
		 meshita->vColors.emplace_back(255.0, 255.0, 0.0, 1.0);

		 meshita->vColors.emplace_back(255.0, 255.0, 0.0, 1.0);
		 meshita->vColors.emplace_back(255.0, 255.0, 0.0, 1.0);


		 return meshita;

 }
//-------------------------------------------------------------------------

