#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
	if (drawElements)
	{
		unsigned int stripIndices[] =
		{ 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
		glDrawElements(mPrimitive, 10, GL_UNSIGNED_INT,
			stripIndices);
	}
	else
	{
		glDrawArrays(mPrimitive, 0, size());
	}	
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
		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}
		// se añaden comandos para la tabla de normales :
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd, GLdouble c1, GLdouble c2, GLdouble c3) {
	Mesh* mesh = new Mesh();

	mesh->mNumVertices = numL;
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->vVertices.reserve(numL);
	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < numL; i++)
	{
		mesh->vVertices.emplace_back(rd * cos(radians(90.0+(360.0/numL)*i)), rd * sin(radians(90.0+(360.0 / numL) * i)), 0.0);
		mesh->vColors.emplace_back(c1,c2,c3,1.0);
	}
	/*mesh->vVertices.emplace_back(rd * cos(radians(90.0)), rd * sin(radians(90.0)), 0.0);
	mesh->vVertices.emplace_back(rd * cos(radians(90.0 + 360.0/numL)), rd * sin(radians(90.0 + 360.0 / numL)), 0.0);
	mesh->vVertices.emplace_back(rd * cos(radians(90.0 + 360.0 / numL + 360.0 / numL)), rd * sin(radians(90.0 + 360.0 / numL + 360.0 / numL)), 0.0);
	*/
	
	return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
	Mesh* triangulo = generaPoligono(3, rd, 255.0,255.0,0.0);
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
	Mesh* rgbTriang = generaPoligono(3,rd, 0.0,0.0,0.0);

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
	 //meshita->vVertices.reserve(meshita->mNumVertices);
	 meshita->vColors.reserve(meshita->mNumVertices);

	 //estas coordenadas para que la figure este centrada en los planos
	 meshita->vVertices.emplace_back(-w/2, h/2, 0.0);
	 meshita->vVertices.emplace_back(-w/2, -h/2, 0.0);
	 meshita->vVertices.emplace_back(w/2, h/2, 0.0);
	 meshita->vVertices.emplace_back(w/2, -h/2, 0.0);

	 return meshita;
 }

 Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	 Mesh* rectRGB = generaRectangulo(w, h);

	 //limpio primero el vector para que asi no salga los colores fijados por generaRectangulo
	 rectRGB->vColors.clear();
	 rectRGB->vColors.emplace_back(255.0, 0.0, 0.0, 1.0);
	 rectRGB->vColors.emplace_back(0.0, 0.0, 255.0, 1.0);
	 rectRGB->vColors.emplace_back(0.0, 128.0, 0.0, 1.0);
	 rectRGB->vColors.emplace_back(0.0, 0.0, 0.0, 1.0);

	 return rectRGB;
 }

 Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h) {
	 Mesh* estrella = new Mesh();
	 estrella->mPrimitive = GL_TRIANGLE_FAN;
	 estrella->mNumVertices = 2 * np + 2;
	 estrella->vVertices.reserve(estrella->mNumVertices);

	 estrella->vVertices.emplace_back(0.0, 0.0, 0.0);
	 double angulo = 90;
	for (int i = 0; i < np; i++) {

		 estrella->vVertices.emplace_back(re * cos(radians(angulo)), re * sin(radians(angulo)), h);
		 angulo = angulo + (360 / (np * 2));
		 estrella->vVertices.emplace_back((re/2) * cos(radians(angulo)), (re / 2) * sin(radians(angulo)), h);
		 angulo = angulo + (360 / (np * 2));

	}
	
	 
	 estrella->vVertices.emplace_back(re * cos(radians(angulo)), re * sin(radians(angulo)), h);
	 return estrella;
 }

 Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h) {
	 Mesh* estTex = generaEstrella3D(re, np, h);

	 estTex->vTexCoords.reserve(estTex->mNumVertices);
	 estTex->vTexCoords.emplace_back(0.5, 0.5);
	 double angulo = 90;
	 for (int i = 0; i < estTex->mNumVertices - 1; i++) {

		 estTex->vTexCoords.emplace_back(0.5 * cos(radians(angulo)) + 0.5, 0.5 * sin(radians(angulo))+0.5);
		 angulo = angulo + (360 / (estTex->mNumVertices - 2));

	 }
	 //estTex->vTexCoords.emplace_back(0.5 * cos(radians(angulo)) +0.5, 0.5 * sin(radians(angulo))+0.5);
	 return estTex;
 }

 Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh){

	 Mesh* m = generaRectangulo(w, h);

	 m->vTexCoords.reserve(72);
	 m->vTexCoords.emplace_back(0, rh);
	 m->vTexCoords.emplace_back(0, 0);
	 m->vTexCoords.emplace_back(rw, rh);
	 m->vTexCoords.emplace_back(rw, 0);

	 return m;
 }

 Mesh* Mesh::generaContCubo(GLdouble ld) {
	 Mesh* cubito = new Mesh();
	 cubito->mPrimitive = GL_TRIANGLE_STRIP;
	 cubito->mNumVertices = 10;
	 cubito->vVertices.reserve(cubito->mNumVertices);
	 int half = ld / 2;
	 
	 cubito->vVertices.emplace_back(-half, half, half);
	 cubito->vVertices.emplace_back(-half, -half, half);
	 cubito->vVertices.emplace_back(half, half , half );
	 cubito->vVertices.emplace_back(half, -half, half );
	 cubito->vVertices.emplace_back(half, half , -half);
	 cubito->vVertices.emplace_back(half, -half ,- half );
	 cubito->vVertices.emplace_back(-half, half, -half);
	 cubito->vVertices.emplace_back(-half, -half, -half);
	 cubito->vVertices.emplace_back(-half, half, half);
	 cubito->vVertices.emplace_back(-half, -half, half);

	 return cubito;
 }

 Mesh* Mesh::generaCajaTexCubo(GLdouble nl) {
	 Mesh* cubito = generaContCubo(nl);
	 cubito->vTexCoords.reserve(cubito->mNumVertices);
	
		 cubito->vTexCoords.emplace_back(0, 1);
		 cubito->vTexCoords.emplace_back(0, 0);
		 cubito->vTexCoords.emplace_back(1,1);
		 cubito->vTexCoords.emplace_back(1, 0);

		 cubito->vTexCoords.emplace_back(2,1 );
		 cubito->vTexCoords.emplace_back(2, 0);
		 cubito->vTexCoords.emplace_back(3, 1);
		 cubito->vTexCoords.emplace_back(3, 0);
	 
		 cubito->vTexCoords.emplace_back(4, 1);
		 cubito->vTexCoords.emplace_back(4, 0);
	

	 return cubito;
 }
//-------------------------------------------------------------------------

 Mesh* Mesh::generaAnilloCuadrado() {
	 Mesh* anillo = new Mesh();
	 anillo->mPrimitive = GL_TRIANGLE_STRIP;
	 anillo->mNumVertices = 10;
	anillo->drawElements = true;
	 anillo->vVertices.reserve(anillo->mNumVertices);
	 anillo->vColors.reserve(anillo->mNumVertices);
	 anillo->vNormals.reserve(anillo->mNumVertices);

	 anillo->vVertices.emplace_back( 300.0, 300.0, 0.0 );
	 anillo->vVertices.emplace_back( 100.0, 100.0, 0.0);
	 anillo->vVertices.emplace_back(700.0, 300.0, 0.0 );
	 anillo->vVertices.emplace_back( 900.0, 100.0, 0.0 );
	 anillo->vVertices.emplace_back( 700.0, 700.0, 0.0 );
	 anillo->vVertices.emplace_back( 900.0, 900.0, 0.0 );
	 anillo->vVertices.emplace_back( 300.0, 700.0, 0.0 );
	 anillo->vVertices.emplace_back( 100.0, 900.0, 0.0 );
	//anillo->vVertices.emplace_back( 30.0, 30.0, 0.0 );
	 //anillo->vVertices.emplace_back( 10.0, 10.0, 0.0 );

	 anillo->vColors.emplace_back(0.0, 0.0, 0.0, 1.0);
	 anillo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 anillo->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	 anillo->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	 anillo->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
	 anillo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 anillo->vColors.emplace_back(0.0, 1.0, 1.0, 1.0);
	 anillo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	  //anillo->vColors.emplace_back( 0.0, 0.0, 0.0,1.0 );
	  //anillo->vColors.emplace_back( 1.0, 0.0, 0.0,1.0 );

	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	 anillo->vNormals.emplace_back(0.0,0.0,1.0);
	//anillo->vNormals.emplace_back(0.0, 0.0, 1.0);
	// anillo->vNormals.emplace_back(0.0, 0.0, 1.0);
	 return anillo;
 }

 void IndexMesh::render() const {
	 Mesh::render();
	 // Comandos OpenGL para enviar datos de arrays a GPU
	 // Nuevos comandos para la tabla de índices
		 if (vIndices != nullptr) {
			 glEnableClientState(GL_INDEX_ARRAY);
			 glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		 }
	 // Comandos OpenGL para deshabilitar datos enviados
	// Nuevo comando para la tabla de índices:
		 glDisableClientState(GL_INDEX_ARRAY);
 }
 // Comando para renderizar la malla indexada enviada
 void IndexMesh::draw() const {
	 glDrawElements(mPrimitive, nNumIndices,
		 GL_UNSIGNED_INT, vIndices);
 }

 IndexMesh* IndexMesh::generaIndexCuboConTapas(GLdouble l)
 {
	 IndexMesh* cubitoConTapa = new IndexMesh();
	 cubitoConTapa->mPrimitive = GL_TRIANGLES;
	 cubitoConTapa->nNumIndices = 36;
	 //indices de los vertices de los triangulos
	 GLuint indices[] = {
		 0,1,2, 2,1,3,
		 2,3,4, 4,3,5,
		 4,5,6, 6,5,7,
		 6,7,0, 0,7,1,
		 4,6,2, 2,6,0,
		 1,7,3, 3,7, 5
	 };
	 //vIndices del tamaño de nNumIndices y se inicializa
	 cubitoConTapa->vIndices = new GLuint[cubitoConTapa->nNumIndices];
	 for (int i = 0; i < cubitoConTapa->nNumIndices; i++) {
		 cubitoConTapa->vIndices[i] = indices[i];
	 }
	 //hacemos el cubo poniendo los vertices y los colores en su lugar
	int half = l / 2;

	cubitoConTapa->mNumVertices = 8;
	 cubitoConTapa->vVertices.reserve(cubitoConTapa->mNumVertices);
	 cubitoConTapa->vVertices.emplace_back(-half, half, half);
	 cubitoConTapa->vVertices.emplace_back(-half, -half, half);
	 cubitoConTapa->vVertices.emplace_back(half, half, half);
	 cubitoConTapa->vVertices.emplace_back(half, -half, half);
	 cubitoConTapa->vVertices.emplace_back(half, half, -half);
	 cubitoConTapa->vVertices.emplace_back(half, -half, -half);
	 cubitoConTapa->vVertices.emplace_back(-half, half, -half);
	 cubitoConTapa->vVertices.emplace_back(-half, -half, -half);

	 cubitoConTapa->vColors.reserve(cubitoConTapa->mNumVertices);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	 cubitoConTapa->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);

	 //construimos el vector de normales
	 cubitoConTapa->buildNormalVectors();

	 return cubitoConTapa;
 }

 void IndexMesh::buildNormalVectors()
 {
	 //vNormals le ponemos del mismo tamaño que vVertices usando mNumVertices
	 vNormals.reserve(mNumVertices);
	 //lo inicializamos a 0
	 for (int i = 0; i < mNumVertices; i++) {
		 vNormals.emplace_back(0.0, 0.0, 0.0);
	 }
	 //recorremos los indices de tres en tres para acceder a los indices de los triangulos
	 for (int j = 0; j < nNumIndices; j = j + 3) {
		 glm::dvec3 cara = dvec3(vIndices[j], vIndices[j + 1], vIndices[j + 2]);
		 
		 dvec3 n = cross(vVertices[cara.z] - vVertices[cara.y], vVertices[cara.x] - vVertices[cara.y]);
		 vNormals[vIndices[j]] += n;
		 vNormals[vIndices[j + 1]] += n;
		vNormals[vIndices[j + 2]] += n; 
	 }
	 //nos aseguramos que se normalizan 
	 for (int k = 0; k < vNormals.size(); k++) {
		 vNormals[k] = normalize(vNormals[k]);
	 }
 }
 IndexMesh* IndexMesh::generaCompoundEntity()
 {
	 IndexMesh* compound = new IndexMesh();

	 return compound;
 }


