#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	// allocate memory and load resources
    // Lights
    // Textures
	
	gObjects.push_back(new EjesRGB(400.0));
	if (mId == 0) {
		////cabeza
		//Sphere* esfera = new Sphere(100.0, glm::fvec3(1.0, 0.6, 0));
		////esfera->setColor(glm::fvec3(2.30f, 0.25f, 0.25f));
		//gObjects.push_back(esfera);
		////ojos
		//Cylinder* cono = new Cylinder(10.0, 0, 30.0, glm::fvec3(0.0f, 0.0f, 2.55f));
		//glm::dmat4 mAux = cono->modelMat();
		//mAux = translate(mAux, dvec3(20, 50, 75));
		//mAux = rotate(mAux, radians(-60.0), dvec3(1.0, 0, 1.0));
		//mAux = rotate(mAux, radians(20.0), dvec3(0, 1.0, 0));
		//cono->setModelMat(mAux);
		//gObjects.push_back(cono);
		//Cylinder* cono2 = new Cylinder(10.0, 0, 30.0, glm::fvec3(0.0f, 1.50f, 2.20f));
		//glm::dmat4 mAuxx = cono2->modelMat();
		//mAuxx = translate(mAuxx, dvec3(70, 50, 35));
		//mAuxx = rotate(mAuxx, radians(-60.0), dvec3(1.0, 0, 1.0));
		//mAuxx = rotate(mAuxx, radians(20.0), dvec3(0, 1.0, 0));
		//cono2->setModelMat(mAuxx);
		//gObjects.push_back(cono2);

		////Gorro
		//Disk* gorro = new Disk(50.0, 90.0, glm::fvec3(2.30f, 0.25f, 0.25f));
		//glm::dmat4 mAuxg = gorro->modelMat();
		//mAuxg = translate(mAuxg, dvec3(0, 85, 0));
		//mAuxg = rotate(mAuxg, radians(-90.0), dvec3(0, 1.0, 0));
		//mAuxg = rotate(mAuxg, radians(-90.0), dvec3(1.0, 0, 0));
		//gorro->setModelMat(mAuxg);
		//gObjects.push_back(gorro);

		////sonrisa
		//PartialDisk* sonrisa = new PartialDisk(60.0, 80.0, 90, 180, glm::fvec3(0.67f, 2.55f, 0.06f));
		//glm::dmat4 mAuxs = sonrisa->modelMat();
		//mAuxs = translate(mAuxs, dvec3(58, 20, 58));
		//mAuxs = rotate(mAuxs, radians(45.0), dvec3(0, 1.0, 0));
		//sonrisa->setModelMat(mAuxs);
		//gObjects.push_back(sonrisa);
		/*Texture* grTex = new Texture();
	    grTex->load("..//Bmps//stones.bmp",121);	
		gTextures.push_back(grTex);
	Grid* grid = new Grid(1000, 10);
		gObjects.push_back(grid);
		grid->setTexture(grTex);*/
		GridCube* grida= new GridCube();
		gObjects.push_back(grida);


	}
	if (mId == 1) {
		AnilloCuadrado* anillo = new AnilloCuadrado();
		gObjects.push_back(anillo);
	}
	if (mId == 2) {
		Cubo* cubito = new Cubo(100.0);
		gObjects.push_back(cubito);
	}
	if (mId == 3) {
		CompoundEntity* avionsito = new CompoundEntity();
		gObjects.push_back(avionsito);
		//helices
		CompoundEntity* helices = new CompoundEntity();
		Cylinder* helice1 = new Cylinder(20.0, 10.0, 40.0, glm::fvec3(0.0f, 0.0f, 2.55f));
		glm::dmat4 mAuxhel = helice1->modelMat();
		mAuxhel = translate(mAuxhel, dvec3(0, 30, 80));
		mAuxhel = rotate(mAuxhel, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxhel = rotate(mAuxhel, radians(90.0), dvec3(0, 1.0, 0));
		helice1->setModelMat(mAuxhel);
		helices->addEntity(helice1);
		Cylinder* helice2 = new Cylinder(20.0, 10.0, 40.0, glm::fvec3(0.0f, 0.0f, 2.55f));
		glm::dmat4 mAuxhel2 = helice2->modelMat();
		mAuxhel2 = translate(mAuxhel2, dvec3(0, 30, 80));
		mAuxhel2 = rotate(mAuxhel2, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxhel2 = rotate(mAuxhel2, radians(-90.0), dvec3(0, 1.0, 0));
		helice2->setModelMat(mAuxhel2);
		helices->addEntity(helice2);
		//chasis
		CompoundEntity* chasis = new CompoundEntity();
		Sphere* bola = new Sphere(75.0, glm::fvec3(2.5, 0, 0));
		chasis->addEntity(helices);
		chasis->addEntity(bola);
		//avion
		CompoundEntity* avion = new CompoundEntity();
		avion->addEntity(chasis);
		Cubo* alas = new Cubo(100.0);
		glm::dmat4 mAuxalas = alas->modelMat();
		mAuxalas = scale(mAuxalas, dvec3(3.0, 0.3, 1.0));
		mAuxalas = rotate(mAuxalas, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxalas = rotate(mAuxalas, radians(90.0), dvec3(0, 1.0, 0));
		alas->setModelMat(mAuxalas);
		avion->addEntity(alas);
		avionsito->addEntity(avion);
	}
	if (mId == 4)
	{
		/*Cono* conito = new Cono(200.0,70.0,15.0);
		gObjects.push_back(conito);*/
		Esfera* esferita = new Esfera(100.0, 50.0, 50.0, glm::fvec3(0.0, 0.0, 1.0));
		glm::dmat4 mAuxesf = esferita->modelMat();
		mAuxesf = translate(mAuxesf, dvec3(0, 0, 180));
		esferita->setModelMat(mAuxesf);
		gObjects.push_back(esferita);
		Sphere* esferita2 = new Sphere(100.0, glm::fvec3(0.0, 0.0, 1.0));
		glm::dmat4 mAuxesf2 = esferita2->modelMat();
		mAuxesf2 = translate(mAuxesf2, dvec3(180, 0, 0));
		esferita2->setModelMat(mAuxesf2);
		gObjects.push_back(esferita2);
	}
	if (mId == 5) {
		//esfera
		Esfera* esferitafinal = new Esfera(200.0, 50, 50, glm::fvec3(0.93, 1.93, 1.85));
		Material* oro = new Material();
		oro->setGold();
		esferitafinal->setMaterial(oro);
		gObjects.push_back(esferitafinal);
		//////////
		//helice1 del avion 
		Cylinder* helicef1 = new Cylinder(20.0, 5.0, 60.0, glm::fvec3(0.0f, 0.0f, 2.55f));
		glm::dmat4 mAuxhelf = helicef1->modelMat();
		mAuxhelf = translate(mAuxhelf, dvec3(0, 0, 40));
		mAuxhelf = rotate(mAuxhelf, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxhelf = rotate(mAuxhelf, radians(90.0), dvec3(0, 1.0, 0));
		helicef1->setModelMat(mAuxhelf);
		//helice1 del avion 
		Cylinder* helicef2 = new Cylinder(20.0, 5.0, 60.0, glm::fvec3(0.0f, 0.0f, 2.55f));
		glm::dmat4 mAuxhelf2 = helicef2->modelMat();
		mAuxhelf2 = translate(mAuxhelf2, dvec3(0, 0, 40));
		mAuxhelf2 = rotate(mAuxhelf2, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxhelf2 = rotate(mAuxhelf2, radians(-90.0), dvec3(0, 1.0, 0));
		helicef2->setModelMat(mAuxhelf2);
		//cuerpo del avion 
		Sphere* bolafinal = new Sphere(40.0, glm::fvec3(2.5, 0, 0));
		glm::dmat4 mAuxbolf = bolafinal->modelMat();
		bolafinal->setModelMat(mAuxbolf);
		//alas del avion 
		Cubo* alasf = new Cubo(60.0);
		glm::dmat4 mAuxalasf = alasf->modelMat();
		mAuxalasf = scale(mAuxalasf, dvec3(2.0, 0.3, 1.0));
		mAuxalasf = rotate(mAuxalasf, radians(-180.0), dvec3(1.0, 0, 0));
		mAuxalasf = rotate(mAuxalasf, radians(90.0), dvec3(0, 1.0, 0));
		alasf->setModelMat(mAuxalasf);
		//compound entity de helices
		helicesfinal = new CompoundEntity();
		helicesfinal->addEntity(helicef2);
		helicesfinal->addEntity(helicef1);
		//compound entity de chasis(cuerpo +helices)
		CompoundEntity* chasisfinal = new CompoundEntity();
		chasisfinal->addEntity(helicesfinal);
		chasisfinal->addEntity(bolafinal);
		//AVION FINAL (chasis + alas )
		avionsitofinal = new Avion();
		avionsitofinal->addEntity(chasisfinal);
		avionsitofinal->addEntity(alasf);
		//Luces del avion 
		luzAvion = avionsitofinal->getLight();
		luzAvion->setSpot(fvec3(0, -1, 0), 60.0, 4);
		luzAvion->disable();
		//Transladar posicion completa del avion
		glm::dmat4 mAvioncitoFinal = avionsitofinal->modelMat();
		mAvioncitoFinal = translate(avionsitofinal->modelMat(), dvec3(0, radio, 0));
		avionsitofinal->setModelMat(mAvioncitoFinal);
		//
		gObjects.push_back(avionsitofinal);
	}
	if (mId==6)
	{

	}
	if (mId == 7)
	{
		Esfera* esferitafinal = new Esfera(200.0, 50, 50, glm::fvec3(0.93, 1.93, 1.85));
		Material* oro = new Material();
		oro->setGold();
		esferitafinal->setMaterial(oro);
		gObjects.push_back(esferitafinal);

		//sirena
		
		sir = new SirenCube();
		luzSirena = sir->getLight();
		luzSirena->setSpot(fvec3(0, -1, 0), 60.0, 4);
		luzSirena->disable();
		//Transladar posicion completa del avion
		glm::dmat4 mSir = sir->modelMat();
		mSir = translate(sir->modelMat(), dvec3(0, radio, 0));
		sir->setModelMat(mSir);
		//
		gObjects.push_back(sir);
	}
	//if (mId == 0) {
	//	// Graphics objects (entities) of the scene
	//	
	//	gObjects.push_back(new Poligono(100, 200.0, 128.0, 0.0, 128.0));
	//	gObjects.push_back(new Poligono(3, 200.0, 255.0, 255.0, 0.0));
	//	gObjects.push_back(new Sierpinski(200, 5000.0));

	//	auto r = new RectanguloRGB(1000.0, 1000.0);
	//	gObjects.push_back(r);
	//	r->setModelMat(translate(r->modelMat(), dvec3(0, 0, -100.0)));



	//	auto g = new TrianguloRGB(20.0);
	//	gObjects.push_back(g);

	//	g->setModelMat(translate(g->modelMat(), dvec3(1.0, 200.0, 0)));
	//	g->setModelMat(rotate(g->modelMat(), 25.0, dvec3(1.0, 0, 25.0)));
	//}

	/*else {
		*/

		//load textures
		//Texture* baldosaC = new Texture();
		//baldosaC->load("..//Bmps//baldosaC.bmp");
		//Texture* baldosaF = new Texture();
		//baldosaF->load("..//Bmps//baldosaF.bmp");
		//Texture* baldosaP = new Texture();
		//baldosaP->load("..//Bmps//baldosaP.bmp");
		//Texture* container = new Texture();
		//container->load("..//Bmps//container.bmp");
		//Texture* grass = new Texture();
		//grass->load("..//Bmps//grass.bmp");
		//Texture* papelC = new Texture();
		//papelC->load("..//Bmps//papelC.bmp");
		//Texture* papelE = new Texture();
		//papelE->load("..//Bmps//papelE.bmp");
		//Texture* windowC = new Texture();
		//windowC->load("..//Bmps//windowC.bmp");
		//Texture* windowV = new Texture();
		//windowV->load("..//Bmps//windowV.bmp",121);
		//Texture* foto = new Texture();
		//foto->loadColorBuffer();

		////push to the vector of textures
		//gTextures.push_back(baldosaC);
		//gTextures.push_back(baldosaP);
		//gTextures.push_back(container);
		//gTextures.push_back(windowV);
		//gTextures.push_back(foto);

		//auto g = new Estrella3D(100.0, 9, 100.0);
		//gObjects.push_back(g);
		//g->setTexture(baldosaP);
		//g->setModelMat(rotate(g->modelMat(), 25.0, dvec3(1.0, 0, 25.0)));
		//g->setModelMat(translate(dmat4(1), dvec3(-100.0, 200.0, -100.0)));
		//auto a = new Suelo(500.0, 500.0,9,9);
		//a->setTexture(baldosaC);
		//gObjects.push_back(a);
		//a->setModelMat(rotate(a->modelMat(),radians(90.0), dvec3(1.0, 0, 0)));
		//auto c = new Caja(100);
		//c->setTexture(container);
		//c->setTextureInt(papelE);
		//gObjects.push_back(c);
		//c->setModelMat(translate(dmat4(1), dvec3(-100.0, 50.0, -100.0)));
		//
		//auto d = new Habitacion(500.0);
		//d->setTexture(windowV);
		//gObjects.push_back(d);
		//d->setModelMat(translate(dmat4(1), dvec3(-1.0, 250.0, -1.0)));
		//
		//auto f = new Foto(100.0, 100.0, 1, 1);
		//f->setTexture(foto);
		//gObjects.push_back(f);
		//f->setModelMat(translate(dmat4(1.0), dvec3(200, 50, 0.0)));
		//f->setModelMat(rotate(f->modelMat(), radians(90.0), dvec3(1.0, 0, 0)));


}
//-------------------------------------------------------------------------
void Scene::sceneDirLight(Camera const& cam) const {
	
		if (dirLight)
		{
			glEnable(GL_LIGHT0);

		}
		else
		{
			glDisable(GL_LIGHT0);
		}
		glm::fvec4 posDir = { 1, 1, 1, 0 };

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(cam.viewMat()));
		glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
		glm::fvec4 ambient = { 0, 0, 0, 1 };
		glm::fvec4 diffuse = { 1, 1, 1, 1 };
		glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
		glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
		glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
	

	
}

void Scene::scenePosLight(Camera const& cam) const
{

	if (posLight)
	{
		glEnable(GL_LIGHT1);

	}
	else
	{
		glDisable(GL_LIGHT1);
	}
	glm::fvec4 v = { 1000, 1000, 0, 1 };

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT1, GL_POSITION, value_ptr(v));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 0, 2, 0, 1.0 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT1, GL_SPECULAR, value_ptr(specular));


}

void Scene::sceneSpotLight(Camera const& cam) const
{

	if (spotLight)
	{
		glEnable(GL_LIGHT2);

	}
	else
	{
		glDisable(GL_LIGHT2);
	}
	glm::fvec4 v = { 0, 500, 500, 1.0 };

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT2, GL_POSITION, value_ptr(v));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 0.1, 2, 0.1, 1.0 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT2, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT2, GL_SPECULAR, value_ptr(specular));

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 270.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5);
	glm::fvec3 dir = { 0, 0, -1.0 };
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, value_ptr(dir));
	
	
}

void Scene::move()
{
	if (avionsitofinal != nullptr && helicesfinal != nullptr) {
		//Cambio en la rotacion de los  helices en el eje z  y del avion como compound entity rotamos en el eje x y aplicamos su correspondiente traslacion
		helicesfinal->setModelMat(rotate(helicesfinal->modelMat(), radians(helicesAngle), dvec3(0, 0, 1)));

		glm::dmat4 mAvioncitoFinal = avionsitofinal->modelMat();
		mAvioncitoFinal=translate(dmat4(1.0), dvec3(0.0, radio * cos(radians(avionAngle)), radio * sin(radians(avionAngle))));
		mAvioncitoFinal=rotate(mAvioncitoFinal, radians(avionAngle), dvec3(1, 0, 0));
		avionsitofinal->setModelMat(mAvioncitoFinal);
		avionAngle += 1.8;
		helicesAngle += 0.05;

	}

}

void Scene::sirenMove()
{
	if (sir != nullptr) {
		//Cambio en la rotacion de los  helices en el eje z  y del avion como compound entity rotamos en el eje x y aplicamos su correspondiente traslacion

		glm::dmat4 mSir = sir->modelMat();
		mSir = translate(dmat4(1.0), dvec3(0.0, radio * cos(radians(avionAngle)), radio * sin(radians(avionAngle))));
		mSir = rotate(mSir, radians(avionAngle), dvec3(1, 0, 0));
		avionsitofinal->setModelMat(mSir);
		avionAngle += 1.8;

	}
}

void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	for (Texture* tx : gTextures)
	{
		delete tx;  tx = nullptr;
	}
	delete spotSceneLight;
	delete directionalLight;
	delete positionalLight;
	delete luzMinero;

}
//-------------------------------------------------------------------------
void Scene::setGL() 
{

	// OpenGL basic setting
	//glClearColor(0.0, 0.0, 0.0, 0.0);  // background color (alpha=1 -> opaque)
	glClearColor(0.7, 0.8, 0.9, 0.0);
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  //enable texture
	// Se activa la iluminación
	glEnable(GL_LIGHTING);
	// Se activa la normalización de los vectores normales
	glEnable(GL_NORMALIZE);
	setLights();

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D); //disable texture
	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);

}
void Scene::setLights()
{
	GLfloat amb[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	directionalLight = new DirLight();

	positionalLight = new PosLight();
	glm::fvec3 v = { 1000, 1000, 0 };
	positionalLight->setPosDir(v);
	positionalLight->setDiff(glm::fvec4(0, 2, 0,1));

	spotSceneLight = new SpotLight(glm::fvec3(0, 0, 300));
	spotSceneLight->setDiff(glm::fvec4(1, 1, 1, 1));
	spotSceneLight->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1));


	luzMinero = new PosLight();
	luzMinero->setPosDir(glm::fvec3(0, 0, -1));
	
	directionalLight->disable();
	positionalLight->disable();
	spotSceneLight->disable();
	luzMinero->disable();
}

//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	//sceneDirLight(cam);
	//scenePosLight(cam);
	//sceneSpotLight(cam);
	directionalLight->upload(cam.viewMat());
	positionalLight->upload(cam.viewMat());
	spotSceneLight->upload(cam.viewMat());
	luzMinero->upload(dmat4(1.0));
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
	
}
void Scene::update()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------


