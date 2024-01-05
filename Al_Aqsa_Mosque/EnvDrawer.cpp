#define cull glEnable(GL_CULL_FACE)
#define nocull glDisable(GL_CULL_FACE)
#define Front glCullFace(GL_FRONT)
#define Back glCullFace(GL_BACK)
#include "EnvDrawer.h"
#include <GL/glut.h>  
#include "Point.h"
#include "Color.h"
#include "Constants.h"
#include "Texture.h"
#include "Model_3DS.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Box.h"
#include <windows.h>
#include <iostream>
Model_3DS* EnvDrawer::tree1Model = new Model_3DS();
Model_3DS* EnvDrawer::tree2Model = new Model_3DS();
Model_3DS* EnvDrawer::tankModel = new Model_3DS();
Model_3DS* EnvDrawer::fountainModel = new Model_3DS();
EnvDrawer::EnvDrawer() {

}
EnvDrawer::EnvDrawer(HWND hWnd) {

	glEnable(GL_TEXTURE_2D);

	ground = LoadTexture((char*)"assets/materials/ground.bmp", 255);
	grass = LoadTexture((char*)"assets/materials/grass.bmp", 255);
	stone = LoadTexture((char*)"assets/materials/stone1.bmp", 255);
	wall = LoadTexture((char*)"assets/materials/wall1.bmp", 255);
	passage = LoadTexture((char*)"assets/materials/street2.bmp", 255);
	street = LoadTexture((char*)"assets/materials/road1.bmp", 255);
	sunTexture = LoadTexture((char*)"assets/materials/sun.bmp", 255);
	lightTexture = LoadTexture((char*)"assets/materials/yellowLight.bmp", 255);

	stonesTexture[0] = LoadTexture((char*)"assets/materials/stones1.bmp", 255);
	stonesTexture[1] = LoadTexture((char*)"assets/materials/stones2.bmp", 255);
	stonesTexture[2] = LoadTexture((char*)"assets/materials/stones3.bmp", 255);
	stonesTexture[3] = LoadTexture((char*)"assets/materials/stones4.bmp", 255);
	stonesTexture[4] = LoadTexture((char*)"assets/materials/stones5.bmp", 255);
	stonesTexture[5] = LoadTexture((char*)"assets/materials/stones6.bmp", 255);
	stonesTexture[6] = LoadTexture((char*)"assets/materials/stones7.bmp", 255);
	stonesTexture[7] = LoadTexture((char*)"assets/materials/stones8.bmp", 255);
	stonesTexture[8] = LoadTexture((char*)"assets/materials/stone3.bmp", 255);
	stonesTexture[9] = LoadTexture((char*)"assets/materials/wall1.bmp", 255);
	stonesTexture[10] = LoadTexture((char*)"assets/materials/AlQibli/block0.bmp", 255);
	stonesTexture[11] = LoadTexture((char*)"assets/materials/AlQibli/block1.bmp", 255);
	stonesTexture[12] = LoadTexture((char*)"assets/materials/AlQibli/block3.bmp", 255);
	stonesTexture[13] = LoadTexture((char*)"assets/materials/AlQibli/roof0.bmp", 255);

	buildingTexture[0] = LoadTexture((char*)"assets/materials/building1.bmp", 255);
	buildingTexture[1] = LoadTexture((char*)"assets/materials/building2.bmp", 255);
	buildingTexture[2] = LoadTexture((char*)"assets/materials/building3.bmp", 255);
	buildingTexture[3] = LoadTexture((char*)"assets/materials/building4.bmp", 255);
	buildingTexture[4] = LoadTexture((char*)"assets/materials/building5.bmp", 255);
	buildingTexture[5] = LoadTexture((char*)"assets/materials/building6.bmp", 255);

	skyBoxTextures[0][0]= LoadTexture((char*)"assets/skybox/SkyBox0Bottom.bmp", 255);
	skyBoxTextures[0][1] = LoadTexture((char*)"assets/skybox/SkyBox0Up.bmp", 255);
	skyBoxTextures[0][2] = LoadTexture((char*)"assets/skybox/SkyBox0Back.bmp", 255);
	skyBoxTextures[0][3] = LoadTexture((char*)"assets/skybox/SkyBox0Front.bmp", 255);
	skyBoxTextures[0][4] = LoadTexture((char*)"assets/skybox/SkyBox0Left.bmp", 255);
	skyBoxTextures[0][5] = LoadTexture((char*)"assets/skybox/SkyBox0Right.bmp", 255);

	skyBoxTextures[1][0] = LoadTexture((char*)"assets/skybox/SkyBox1Bottom.bmp", 255);
	skyBoxTextures[1][1] = LoadTexture((char*)"assets/skybox/SkyBox1Up.bmp", 255);
	skyBoxTextures[1][2] = LoadTexture((char*)"assets/skybox/SkyBox1Back.bmp", 255);
	skyBoxTextures[1][3] = LoadTexture((char*)"assets/skybox/SkyBox1Front.bmp", 255);
	skyBoxTextures[1][4] = LoadTexture((char*)"assets/skybox/SkyBox1Left.bmp", 255);
	skyBoxTextures[1][5] = LoadTexture((char*)"assets/skybox/SkyBox1Right.bmp", 255);

	skyBoxTextures[2][0] = LoadTexture((char*)"assets/skybox/SkyBox2Bottom.bmp", 255);
	skyBoxTextures[2][1] = LoadTexture((char*)"assets/skybox/SkyBox2Up.bmp", 255);
	skyBoxTextures[2][2] = LoadTexture((char*)"assets/skybox/SkyBox2Back.bmp", 255);
	skyBoxTextures[2][3] = LoadTexture((char*)"assets/skybox/SkyBox2Front.bmp", 255);
	skyBoxTextures[2][4] = LoadTexture((char*)"assets/skybox/SkyBox2Left.bmp", 255);
	skyBoxTextures[2][5] = LoadTexture((char*)"assets/skybox/SkyBox2Right.bmp", 255);

	CitySKYFRONT = LoadTexture((char*)"assets/skybox/CityFront.bmp", 255);
	CitySKYBACK = LoadTexture((char*)"assets/skybox/CityBack.bmp", 255);
	CitySKYLEFT = LoadTexture((char*)"assets/skybox/CityLeft.bmp", 255);
	CitySKYRIGHT = LoadTexture((char*)"assets/skybox/CityRight.bmp", 255);
	CitySKYUP = LoadTexture((char*)"assets/skybox/CityUp.bmp", 255);
	CitySKYDOWN = LoadTexture((char*)"assets/skybox/CityDown.bmp", 255);

	CloudsSKYFRONT = LoadTexture((char*)"assets/skybox/CloudsFront.bmp", 255);
	CloudsSKYBACK = LoadTexture((char*)"assets/skybox/CloudsBack.bmp", 255);
	CloudsSKYLEFT = LoadTexture((char*)"assets/skybox/CloudsLeft.bmp", 255);
	CloudsSKYRIGHT = LoadTexture((char*)"assets/skybox/CloudsRight.bmp", 255);
	CloudsSKYUP = LoadTexture((char*)"assets/skybox/CloudsUp.bmp", 255);
	CloudsSKYDOWN = LoadTexture((char*)"assets/skybox/CloudsDown.bmp", 255);

	SKYFRONT = 0
		, SKYBACK = 0
		, SKYLEFT = 0
		, SKYRIGHT = 0
		, SKYUP = 0
		, SKYDOWN = 0;

	glDisable(GL_TEXTURE_2D);

	tree1Model->Load((char*)"assets/models/tree1.3DS");
	tree1Model->Materials[0].tex.LoadBMP((char*)"assets/materials/tree1.bmp");
	tree1Model->Materials[1].tex.LoadBMP((char*)"assets/materials/leaf2.bmp");

	tree2Model->Load((char*)"assets/models/tree2.3DS");
	tree2Model->Materials[0].tex.LoadBMP((char*)"assets/materials/tree1.bmp");
	tree2Model->Materials[1].tex.LoadBMP((char*)"assets/materials/tree1.bmp");
	tree2Model->Materials[2].tex.LoadBMP((char*)"assets/materials/leaf2.bmp");
	tree2Model->Materials[3].tex.LoadBMP((char*)"assets/materials/leaf2.bmp");
	tree2Model->Materials[4].tex.LoadBMP((char*)"assets/materials/leaf2.bmp");
	tree2Model->Materials[5].tex.LoadBMP((char*)"assets/materials/leaf2.bmp");

	tankModel->Load((char*)"assets/models/tank.3DS");


	fountainModel->Load((char*)"assets/models/fountain.3DS");
	fountainModel->Materials[0].tex.LoadBMP((char*)"assets/materials/stones1.bmp");
	fountainModel->Materials[1].tex.LoadBMP((char*)"assets/materials/stones1.bmp");

	// Lighting Variables Initializing
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpec);

	/*glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 5.0);*/

	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);
	glEnable(GL_COLOR_MATERIAL);

	//// Add ambient light
	//GLfloat ambientColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Color (0.3, 0.3, 0.3)
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);  // Enable local viewer for more accurate lighting calculations

	SoundManager.Initialize(hWnd);
	// Tank sound
	SoundManager.CreateSound((char*)"assets/sounds/tankEngine.wav", sounds[0]);
	soundsData[0][0] = 12;	 // x
	soundsData[0][1] = -9;	// y
	soundsData[0][2] = 32;	// z
	soundsData[0][3] = 8;	// r
	// Bab Almgharebah Minart Sound
	SoundManager.CreateSound((char*)"assets/sounds/azan1.wav", sounds[1]);
	soundsData[1][0] = -22.5;	 // x
	soundsData[1][1] = -9;	// y
	soundsData[1][2] = 37;	// z
	soundsData[1][3] = 15;	// r
	// Bab Alsilselah Minart Sound
	SoundManager.CreateSound((char*)"assets/sounds/azan1.wav", sounds[2]);
	soundsData[2][0] = -22.9;	 // x
	soundsData[2][1] = -9;	// y
	soundsData[2][2] = 10;	// z
	soundsData[2][3] = 15;	// r
	// Bab Ghuanimah Minart Sound
	SoundManager.CreateSound((char*)"assets/sounds/azan1.wav", sounds[3]);
	soundsData[3][0] = -22.9;	 // x
	soundsData[3][1] = -9;	// y
	soundsData[3][2] = -38;	// z
	soundsData[3][3] = 15;	// r
	// Bab Alasbat Minart Sound
	SoundManager.CreateSound((char*)"assets/sounds/azan1.wav", sounds[4]);
	soundsData[4][0] = 15;	 // x
	soundsData[4][1] = -9;	// y
	soundsData[4][2] = -38;	// z
	soundsData[4][3] = 15;	// r
	// City Sound
	SoundManager.CreateSound((char*)"assets/sounds/city.wav", sounds[5]);
	soundsData[5][0] = 35;	 // x
	soundsData[5][1] = -10;	// y
	soundsData[5][2] = -7.5;	// z
	soundsData[5][3] = 10;	// r

	// City Sound
	SoundManager.CreateSound((char*)"assets/sounds/city.wav", sounds[6]);
	soundsData[6][0] = -35;	 // x
	soundsData[6][1] = -10;	// y
	soundsData[6][2] = -7.5;	// z
	soundsData[6][3] = 10;	// r

	// City Sound
	SoundManager.CreateSound((char*)"assets/sounds/city.wav", sounds[7]);
	soundsData[7][0] = -35;	 // x
	soundsData[7][1] = -10;	// y
	soundsData[7][2] = 25;	// z
	soundsData[7][3] = 10;	// r

	// Garden Sound
	SoundManager.CreateSound((char*)"assets/sounds/garden.wav", sounds[8]);
	soundsData[8][0] = -21;	 // x
	soundsData[8][1] = -8;	// y
	soundsData[8][2] = 10;	// z
	soundsData[8][3] = 15;	// r

	// Garden Sound
	SoundManager.CreateSound((char*)"assets/sounds/garden.wav", sounds[9]);
	soundsData[9][0] = 21;	 // x
	soundsData[9][1] = -8;	// y
	soundsData[9][2] = 10;	// z
	soundsData[9][3] = 15;	// r

	// Garden Sound
	SoundManager.CreateSound((char*)"assets/sounds/garden.wav", sounds[10]);
	soundsData[10][0] = -21;	 // x
	soundsData[10][1] = -8;	// y
	soundsData[10][2] = -25;	// z
	soundsData[10][3] = 15;	// r

	// Garden Sound
	SoundManager.CreateSound((char*)"assets/sounds/garden.wav", sounds[11]);
	soundsData[11][0] = 21;	 // x
	soundsData[11][1] = -8;	// y
	soundsData[11][2] = -25;	// z
	soundsData[11][3] = 15;	// r

	// AlQibli Mosque Sound
	SoundManager.CreateSound((char*)"assets/sounds/telawah.wav", sounds[12]);
	soundsData[12][0] = -6;	 // x
	soundsData[12][1] = -5;	// y
	soundsData[12][2] = 34.3;	// z
	soundsData[12][3] = 12;	// r

}

void EnvDrawer::drawModel(Model_3DS* model, const Point& position, const float size, const float scaleFactor) {
	glEnable(GL_TEXTURE_2D);
	model->pos.x = position.x;
	model->pos.y = position.y;
	model->pos.z = position.z;
	model->scale = scaleFactor * size;
	model->Draw();
	glDisable(GL_TEXTURE_2D);
}

void EnvDrawer::drawSmallTree(const Point& position, const float size) {
	drawModel(tree1Model, position, size, 0.1);
}

void EnvDrawer::drawBigTree(const Point& position, const float size) {
	drawModel(tree2Model, position, size, 0.5);
}

void EnvDrawer::drawTank(const Point& position, const float size) {
	drawModel(tankModel, position, size, 1);
}

void EnvDrawer::drawFountain(const Point& position, const float size) {
	drawModel(fountainModel, position, size, 1);
}

void EnvDrawer::drawLand(const Point points[4], const int count, const int textureID) {
	glPushMatrix();
	
	
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glNormal3f(0, 1, 0);
	cull;
	Front;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(points[0].x, points[0].y, points[0].z);
	glTexCoord2f(count, 0); glVertex3f(points[1].x, points[1].y, points[1].z);
	glTexCoord2f(count, count); glVertex3f(points[2].x, points[2].y, points[2].z);
	glTexCoord2f(0, count); glVertex3f(points[3].x, points[3].y, points[3].z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	Back;
	nocull;
	glPopMatrix();
}

void EnvDrawer::drawTiledLand(const Point points[4], const int count) {
	drawLand(points, count, ground);
}

void EnvDrawer::drawGrassLand(const Point points[4], const int count) {
	drawLand(points, count, grass);
}

void EnvDrawer::drawPassage(const Point points[4], const int count) {
	drawLand(points, count, passage);
}

void EnvDrawer::drawStreet(const Point points[4], const int count) {
	glPushMatrix();
	cull;
	Front;
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, street);
	glNormal3f(0, 1, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(points[0].x, points[0].y, points[0].z);
	glTexCoord2f(1, 0); glVertex3f(points[1].x, points[1].y, points[1].z);
	glTexCoord2f(1, count); glVertex3f(points[2].x, points[2].y, points[2].z);
	glTexCoord2f(0, count); glVertex3f(points[3].x, points[3].y, points[3].z);
	glEnd();
	Back;
	nocull;
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void EnvDrawer::drawSkyBox(const Point& position, const Constraints& constraints) {
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	float x = position.x, y = position.y, z = position.z;
	float width = constraints.width, height = constraints.height, length = constraints.length;
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);
	cull;

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SKYFRONT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SKYBACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SKYLEFT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SKYRIGHT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SKYUP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SKYDOWN);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	nocull;
	glDisable(GL_TEXTURE_2D);

}

void EnvDrawer::drawSkyBox(const Constraints& constraints) {
	SKYFRONT = skyBoxTextures[currentSkyBoxIndex][3],
		SKYBACK = skyBoxTextures[currentSkyBoxIndex][2],
		SKYLEFT = skyBoxTextures[currentSkyBoxIndex][4],
		SKYRIGHT = skyBoxTextures[currentSkyBoxIndex][5],
		SKYUP = skyBoxTextures[currentSkyBoxIndex][1],
		SKYDOWN = skyBoxTextures[currentSkyBoxIndex][0];
	drawSkyBox(Point(0, 0, 0), constraints);
}

void EnvDrawer::changeSkyBoxTexture() {
	currentSkyBoxIndex = (currentSkyBoxIndex + 1) % 3;
}

void EnvDrawer::drawCylindricMinaret(const float size, const int texture)
{
	//TODO: fix hight parameter
	float hight = 10;
	glPushMatrix();
	glScalef(size, size, size);
	EnvDrawer::drawPillar(0.7, hight, stonesTexture[10], 0.4,9,9);

	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[13]);
	Cylinder cyl = Cylinder(2.5, 2.5, 0.1,9);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, -6.6);
	cyl.draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[13]);
	Cylinder cyl2 = Cylinder(2, 2, 0.1, 9);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, -5.2);
	cyl2.draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	nocull;

	for (int i = 0; i <= 8; ++i)
	{
		glRotatef(i * 360 / 8, 0, 1, 0);
		glPushMatrix();
		glTranslatef(0, hight - 3.8, 1.8);
		drawHalfCylinderInRectangularPrism(0.35,
			Constraints(1.5, 0.4, 0.07), 5, texture);
		glPopMatrix();
		glPushMatrix();
		glRotatef(21, 0, 1, 0);
		glTranslatef(0, hight - 4.8, 1.86);
		Box().drawOutside(Constraints(0.10, 1.0, 0.05), texture);
		glPopMatrix();
	}

	cull;
	glTranslated(0, hight - 3.6, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[12]);
	cyl = Cylinder(0.7, 0.9, 2.5, 5);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	cyl.drawSide();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glTranslated(0, 1.5, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[13]);
	Sphere sphere = Sphere(0.75, 10, 18, true, 2, true,2);
	sphere.draw();
	glDisable(GL_TEXTURE_2D);
	nocull;

	// Top Cone
	glPushMatrix();
	cull;
	glTranslatef(0, 1, 0);
	glColor3b(74, 74, 74);
	Cylinder(0.07, 0.01, 0.7, 5, 1, true, 2).drawSide();
	glPopMatrix();

	// Top Spheres
	for (float yOffset = 0.2; yOffset <= 0.62; yOffset += 0.2) {
		glPushMatrix();
		glTranslatef(0, 0.6 + yOffset, 0);
		Sphere((0.1 - (yOffset * 0.1) + 0.02), 5, 5).draw();
		glPopMatrix();
	}
	nocull;
	glColor4f(1, 1, 1, 1);

	glPopMatrix();
}

void EnvDrawer::drawCubedMinaret(const float size)
{
	//TODO: fix hight param
	float height = 10;
	glPushMatrix();

	glScalef(size, size, size);
	EnvDrawer::drawPillar(1, height,
		stonesTexture[10], 0.4, 4, 4);

	glPushMatrix();
	glTranslated(-2, 6.6, -2);
	Box().drawOutside(Constraints(4, 0.1, 4), stonesTexture[13]);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.5, 5.2, -1.42);
	Box().drawOutside(Constraints(3, 0.1, 3), stonesTexture[13]);
	glPopMatrix();

	

	for (int i = 0; i <= 3; ++i)
	{
		glRotatef(i * 360 / 4, 0, 1, 0);
		glPushMatrix();
		glTranslatef(0, height - 4, 1.4);
		drawHalfCylinderInRectangularPrism(0.35,
			Constraints(2.8, 0.6, 0.07), 6, stonesTexture[10]);
		glPopMatrix();
		glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glTranslatef(0, height - 4.8, 1.9);
		Box().drawOutside(Constraints(0.10, .8, 0.05), stonesTexture[10]);
		glPopMatrix();
	}

	


	glTranslated(0, height - 3.8, 0);

	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[12]);
	Cylinder cyl = Cylinder(0.7, 0.9, 2.5, 5,1,true,3,false,true);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	cyl.drawSide();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glTranslated(0, 1.5, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[13]);
	Sphere sphere = Sphere(0.75, 5, 18, true, 2, true);
	sphere.draw();
	glDisable(GL_TEXTURE_2D);
	nocull;

	// Top Cone
	glPushMatrix();
	cull;
	glTranslatef(0, 1, 0);
	glColor3b(74, 74, 74);
	Cylinder(0.07, 0.01, 0.7, 3, 1, true, 2).drawSide();
	glPopMatrix();

	// Top Spheres
	for (float yOffset = 0.2; yOffset <= 0.62; yOffset += 0.2) {
		glPushMatrix();
		glTranslatef(0 , 0.6 + yOffset, 0 );
		Sphere((0.1 - (yOffset * 0.1) + 0.02), 3, 3).draw();
		glPopMatrix();
	}
	nocull;
	glColor4f(1, 1, 1, 1);

	glPopMatrix();
}

void EnvDrawer::drawWallWithDoor(const float length,const float wallHeight, const int texture)
{
	glPushMatrix();

	int i = 0;
	for (; 2*(i+1) < length; ++i)
	{
		glPushMatrix();
		glTranslated(2*i - (length - 2.5) / 2, wallHeight-4, -0.5);
		Box().drawOutside(Constraints(1.3, 1, 1), texture);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
	Box().drawOutside(Constraints(length-(2*i), 1, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,wallHeight-5,0);
	glPushMatrix();
	glTranslatef(-(length - 2.5) / 2, -wallHeight+1, -0.5);
	Box().drawOutside(Constraints((length-2.5)/2, wallHeight , 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -wallHeight+1, 0);

	glPushMatrix();
	glTranslatef(0,0, -1 * 0.5);
	Box().drawOutside(Constraints(0.25, wallHeight-2, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.25,0, -0.5);
	Box().drawOutside(Constraints(0.25, wallHeight-2, 1), texture);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.25, -1, 0);
	EnvDrawer::drawHalfCylinderInRectangularPrism(1, Constraints(2.5,2, 1), 5, texture);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(2.5, -wallHeight+1, -0.5);
	Box().drawOutside(Constraints((length - 2.5) / 2, wallHeight, 1), texture);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void EnvDrawer::drawWall(const float length, const float wallHeight, const int texture)
{
	glPushMatrix();

	int i = 0;
	for (; 2 * (i + 1) < length; ++i)
	{
		glPushMatrix();
		glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
		Box().drawOutside(Constraints(1.3, 1, 1), texture);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
	Box().drawOutside(Constraints(length - (2 * i), 1, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-(length - 2.5)/2,-wallHeight,-0.5);
	Box().drawOutside(Constraints(length,wallHeight,1), texture,5.0f);
	glPopMatrix();

	glPopMatrix();
}

void EnvDrawer::drawCitySkyBox(const Point& position, const Constraints& constraints) {
	SKYFRONT = CitySKYFRONT,
		SKYBACK = CitySKYBACK,
		SKYLEFT = CitySKYLEFT,
		SKYRIGHT = CitySKYRIGHT,
		SKYUP = CitySKYUP,
		SKYDOWN = CitySKYDOWN;
	drawSkyBox(position, constraints);
}

void EnvDrawer::drawCloudsSkyBox(const Point& position, const Constraints& constraints) {
	SKYFRONT = CloudsSKYFRONT,
		SKYBACK = CloudsSKYBACK,
		SKYLEFT = CloudsSKYLEFT,
		SKYRIGHT = CloudsSKYRIGHT,
		SKYUP = CloudsSKYUP,
		SKYDOWN = CloudsSKYDOWN;
	drawSkyBox(position, constraints);
}

void EnvDrawer::drawGarden(const Point& point, const float width, const float length, const int grassTilesCount, const float treeSize, bool isSmall) {
	Point points[4];
	points[2].x = point.x, points[0].y = point.y, points[0].z = point.z;
	points[3].x = point.x - width, points[1].y = point.y, points[1].z = point.z;
	points[0].x = point.x - width, points[2].y = point.y, points[2].z = point.z + length;
	points[1].x = point.x, points[3].y = point.y, points[3].z = point.z + length;
	drawGrassLand(points, grassTilesCount);
	float stepSize;
	if (isSmall) {
		// step size is size of small tree
		stepSize = 4 * treeSize;
	}
	else {
		// step size is size of big tree
		stepSize = 6 * treeSize;
	}
	for (float i = point.x - stepSize / 4; i >= (point.x - width) + stepSize / 4; i -= stepSize) {
		for (float j = point.z + stepSize / 4; j <= (point.z + length - stepSize / 4); j += stepSize) {
			float x = i, y = point.y, z = j;
			Point treePosition = Point(x, y, z);
			if (isSmall) {
				drawSmallTree(treePosition, treeSize);
			}
			else {
				drawBigTree(treePosition, treeSize);
			}
		}
	}
}

void EnvDrawer::drawPillar(const float radius, const float height, int texture, const float baseHeight, const int cylinderSector, const int baseSector) {
	cull;
	if (baseHeight)
	{
		glPushMatrix();
		glTranslatef(0, height * 0.5, 0);
		glRotatef(45, 0, 1, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		Cylinder topBase = Cylinder(radius, 2 * radius, baseHeight, baseSector);
		topBase.setUpAxis(2);
		topBase.draw();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	Cylinder column = Cylinder(radius, radius, height, cylinderSector);
	column.setUpAxis(2);
	column.draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, (-height * 0.5), 0);
	glRotatef(45, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	Cylinder bottomBase = Cylinder(2 * radius, 1 * radius, baseHeight, baseSector);
	bottomBase.setUpAxis(2);
	bottomBase.draw();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	nocull;
}

void EnvDrawer::drawHalfCylinderInRectangularPrism(const float radius, const Constraints& constraints, const int sectors, const int texture) {
	
	float width = 60, height = 30, length = 30;
	length = constraints.length;
	width = max(constraints.width, radius * 2);
	/*if (constraints.width >= radius * 2) {
		width = constraints.width;
	}
	else {
		width = radius * 2;
	}*/

	height = max(constraints.height, radius);
	//if (constraints.height >= radius) {
	//	height = constraints.height;
	//}
	//else {
	//	height = radius;
	//}

	int sectorCount = sectors; // for dividing cylinder and circle ( increase for more quality )

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Fill the bottom gab
	//glPushMatrix();
	//glTranslatef(radius, 0, -length / 2);
	//Box().drawOutside(Constraints(width / 2 - radius, 1, length), texture);
	//glPopMatrix();
	//
	//glPushMatrix();
	//glTranslatef(-width / 2, 0, -length / 2);
	//Box().drawOutside(Constraints(width / 2 - radius, 1, length), texture);
	//glPopMatrix();


	//the front face

	// Fill the gab

	// top
	//glPushMatrix();
	//glTranslatef(-width / 2, radius, length / 2 - 1);
	////Box().drawOutside(Constraints(width, height - radius, 1), texture);
	//glPopMatrix();
	//
	//// right
	//glPushMatrix();
	//glTranslatef(radius, 0, length / 2 - 1);
	////Box().drawOutside(Constraints(width / 2 - radius, radius, 1), texture);
	//glPopMatrix();
	//
	//// left
	//glPushMatrix();
	//glTranslatef(-width / 2, 0, length / 2 - 1);
	////Box().drawOutside(Constraints(width / 2 - radius, radius, 1), texture);
	//glPopMatrix();

	// Start drawing cylinder
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
	cull;
	Front;
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);

	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (float(i) / sectorCount) * PI;
		GLfloat x = radius * cos(angle);
		GLfloat y = radius * sin(angle);

		glTexCoord2d(1, 1);
		if (angle <= PI / 2) {
			glVertex3d(radius, radius, length);
			glTexCoord2d(x / radius, y / radius);
		}
		else {
			glVertex3d(-radius, radius, length);
			glTexCoord2d(fabs(x) / radius, fabs(y) / radius);
		}
		glVertex3f(x, y, length);

	}

	glEnd();
	Back;
	nocull;
	glPopMatrix();

	//the back face

	// Fill the gab

	//top
	glPushMatrix();
	glTranslatef(-width / 2, radius, -length / 2);
	Box().drawOutside(Constraints(width, height - radius, length), texture);
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(radius, 0, -length / 2);
	Box().drawOutside(Constraints(width / 2 - radius, radius, length), texture);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslatef(-width / 2, 0, -length / 2);
	Box().drawOutside(Constraints(width / 2 - radius, radius, length), texture);
	glPopMatrix();

	// Start drawing cylinder
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	cull;
	glTranslatef(0, 0, -length * 1.5);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, -1);

	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (float(i) / sectorCount) * PI;
		GLfloat x = radius * cos(angle);
		GLfloat y = radius * sin(angle);

		if (angle <= PI / 2) {
			glTexCoord2d(1, 1);
			glVertex3d(radius, radius, length);
			glTexCoord2d(x / radius, y / radius);
			glVertex3f(x, y, length);
		}
		else {
			glTexCoord2d(1, 1);
			glVertex3d(-radius, radius, length);
			glTexCoord2d(fabs(x) / radius, fabs(y) / radius);
			glVertex3f(x, y, length);
		}

	}

	glEnd();
	nocull;
	glPopMatrix();

	//the left side
	glPushMatrix();
	cull;
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);

	glTexCoord2d(0, 0);
	glVertex3d(-width / 2, 0, 0);

	glTexCoord2d(1, 0);
	glVertex3d(-width / 2, 0, length);

	glTexCoord2d(1, 1);
	glVertex3d(-width / 2, height, length);

	glTexCoord2d(0, 1);
	glVertex3d(-width / 2, height, 0);

	glEnd();
	glPopMatrix();

	//the right side
	glPushMatrix();
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);

	glTexCoord2d(0, 0);
	glVertex3d(width / 2, 0, 0);

	glTexCoord2d(1, 0);
	glVertex3d(width / 2, height, 0);

	glTexCoord2d(1, 1);
	glVertex3d(width / 2, height, length);

	glTexCoord2d(0, 1);
	glVertex3d(width / 2, 0, length);

	glEnd();
	glPopMatrix();


	//the top
	glPushMatrix();
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);

	glTexCoord2d(0, 0);
	glVertex3d(-width / 2, height, 0);

	glTexCoord2d(1, 0);
	glVertex3d(-width / 2, height, length);

	glTexCoord2d(1, 1);
	glVertex3d(width / 2, height, length);

	glTexCoord2d(0, 1);
	glVertex3d(width / 2, height, 0);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	
	Cylinder cylinder = Cylinder(radius, radius, length, sectorCount * 2);
	cylinder.setIsHalf(true);
	cylinder.reverseNormals();
	cylinder.drawSide();
	
	nocull;
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void EnvDrawer::drawArchway(const float size, const float pillarHeight, const int count, const int textureIndex, const int pillarCylinderSector, const int pillarBaseSector, const int innerSectorCount) {
	int texture = stonesTexture[textureIndex];
	//glPushMatrix();
	//glTranslatef(-size * 1.5, -pillarHeight * 0.5 - 0.1, 0);
	//EnvDrawer::drawPillar(0.25f * size, pillarHeight, texture, 0.2 * size, pillarCylinderSector, pillarBaseSector);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-size * 2, 0, -size * 0.5);
	Box().drawOutside(Constraints(size * 0.5, size * 1.5, 1 * size), texture);
	glPopMatrix();



	for (int i = 0; i < count; i++) {
		glPushMatrix();
		glTranslatef(i * size * 3, 0, 0);
		EnvDrawer::drawHalfCylinderInRectangularPrism(size, Constraints(size * 3, (size) * 1.5, 1 * size), innerSectorCount, texture);
		glPushMatrix();
		glTranslatef(-size * 1.5, (-pillarHeight - 0.2 * size) * 0.50, 0);
		EnvDrawer::drawPillar(0.25f * size, pillarHeight, texture, 0.2 * size, pillarCylinderSector, pillarBaseSector);
		glPopMatrix();
		glPopMatrix();
	}

	cull;
	glPushMatrix();
	glTranslatef(size * 1.5 + (count - 1) * size * 3, (-pillarHeight - 0.2 * size) * 0.50, 0);
	EnvDrawer::drawPillar(0.25f * size, pillarHeight, texture, 0.2 * size, pillarCylinderSector, pillarBaseSector);
	glPopMatrix();
	nocull;

	glPushMatrix();
	glTranslatef(size * 1.5 + (count - 1) * size * 3, 0, -size * 0.5);
	Box().drawOutside(Constraints(size * 0.5, size * 1.5, 1 * size), texture);
	glPopMatrix();

}

void EnvDrawer::drawHallway(const float size, const float wallHeight, const int count, const float length, const int textureIndex,const int sectorCount) {
	int texture = stonesTexture[textureIndex];
	glPushMatrix();
	glTranslatef(-size * 1.75, -wallHeight, -length * 0.5);
	Box().drawOutside(Constraints(size * 0.5, wallHeight + (size) * 1.5, length), texture);
	glPopMatrix();

	for (int i = 0; i < count; i++) {
		glPushMatrix();
		glTranslatef(i * size * 2.5, 0, 0);

		glPushMatrix();
		glTranslatef(-size * 1.25, -wallHeight, -length * 0.5);
		Box().drawOutside(Constraints(size * 0.25, wallHeight, length), texture);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(size, -wallHeight, -length * 0.5);
		Box().drawOutside(Constraints(size * 0.25, wallHeight, length), texture);
		glPopMatrix();

		EnvDrawer::drawHalfCylinderInRectangularPrism(size, Constraints(size * 2.5, (size) * 1.5, length), sectorCount, texture);

		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(size * 1.25 + (count - 1) * size * 2.5, -wallHeight, -length * 0.5);
	Box().drawOutside(Constraints(size * 0.5, wallHeight + (size) * 1.5, length), texture);
	glPopMatrix();

}

void EnvDrawer::drawBuidling(const float size, const int buildingTextureIndex) {
	Box().drawOutside(Constraints(10*size, 20 * size, 10 * size), buildingTexture[buildingTextureIndex], stonesTexture[buildingTextureIndex]);
}

void EnvDrawer::controlLightSourcePosition(bool* keys) {
	if (keys[VK_NUMPAD4])
	{
		LightPos[0] -= 1;
	}
	if (keys[VK_NUMPAD6])
	{
		LightPos[0] += 1;
	}
	if (keys[VK_NUMPAD2])
	{
		LightPos[1] -= 1;
	}
	if (keys[VK_NUMPAD8])
	{
		LightPos[1] += 1;
	}
	if (keys[VK_NUMPAD9])
	{
		LightPos[2] -= 1;
	}
	if (keys[VK_NUMPAD7])
	{
		LightPos[2] += 1;
	}
	if (keys['L']) {
		glEnable(GL_LIGHT0);		// Turn On Light
	}
	if (keys['O']) {
		glDisable(GL_LIGHT0);	// Turn Off Light
	}
}

float sunAngle = 0;

void EnvDrawer::simulateSun(const float rotatioRadius, const float sunRadius, const float speed) {

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	sunAngle += (2 * PI / 60) * speed;
	if (sunAngle >= PI * 2) {
		sunAngle = 0.0;
	}
	if (sunAngle >= PI * 1.5 || sunAngle <= PI * 0.5) {
		glEnable(GL_LIGHT0);
		if (sunAngle <= PI * 1.75&& sunAngle >= PI * 1.5 || 
			sunAngle >= PI * 0.25&& sunAngle <= PI * 0.5) {
			currentSkyBoxIndex = 1;
		}
		else {
			currentSkyBoxIndex = 0;
		}
	}
	else {
		glDisable(GL_LIGHT0);
		currentSkyBoxIndex = 2;
	}
	//std::cout << sunAngle << std::endl;
	LightPos[0] = rotatioRadius * sinf(sunAngle);
	LightPos[1] = rotatioRadius * cosf(sunAngle);
	glTranslatef(LightPos[0], LightPos[1], LightPos[2]);
	Sphere sun = Sphere(sunRadius);
	glBindTexture(GL_TEXTURE_2D, sunTexture);
	sun.draw();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void EnvDrawer::drawLightingPillar(const Point& position, const int lightIndex, const float size, const float pillarHeight) {
	GLenum light = GL_LIGHT0 + lightIndex;

	glEnable(light);
	float lightpos[4] = { position.x, position.y + pillarHeight * 0.5, position.z,1 };
	glLightfv(light, GL_POSITION, lightpos);
	glLightfv(light, GL_AMBIENT, LightAmb);
	glLightfv(light, GL_DIFFUSE, LightDiff);
	glLightfv(light, GL_SPECULAR, LightSpec);

	glLightfv(light, GL_POSITION, lightpos);
	glLightfv(light, GL_SPOT_DIRECTION, LightDir);
	glLightf(light, GL_SPOT_CUTOFF, 120);


	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(position.x, position.y - pillarHeight / 2, position.z);
	Cylinder pillar = Cylinder(0.1 * size, 0.1 * size, pillarHeight);
	pillar.setUpAxis(2);
	glBindTexture(GL_TEXTURE_2D, wall);
	pillar.draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	Sphere bulp = Sphere(0.4 * size, 10, 3);
	bulp.reverseNormals();
	bulp.setUpAxis(2);
	const float linesColor[4] = { 0.0f,0.0f,0.0f,0.0f };
	glBindTexture(GL_TEXTURE_2D, lightTexture);
	bulp.drawWithLines(linesColor);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}
void EnvDrawer::decodeEnables(bool* keys) {
	if (keys[VK_CONTROL] && keys[VK_NUMPAD1])
	{
		drawFountains = !drawFountains;
	}
	if (keys[VK_CONTROL] && keys[VK_NUMPAD2])
	{
		drawCity = !drawCity;
		if (drawCity) {
			sounds[5].Play(true);
		}
		else {
			sounds[5].Stop();
		}
	}
	if (keys[VK_CONTROL] && keys[VK_NUMPAD3])
	{
		drawGardens = !drawGardens;
		if (drawGardens) {
			sounds[6].Play(true);
		}
		else {
			sounds[6].Stop();
		}
	}
	if (keys[VK_CONTROL] && keys[VK_NUMPAD4])
	{
		drawTanks = !drawTanks;
		if (drawTanks) {
			sounds[0].Play(true);
		}
		else {
			sounds[0].Stop();
		}
	}
	if (keys[VK_CONTROL] && keys[VK_NUMPAD5])
	{
		drawMinarts = !drawMinarts;
		if (drawMinarts) {
			sounds[1].Play(true);
			sounds[2].Play(true);
			sounds[3].Play(true);
			sounds[4].Play(true);
		}
		else {
			sounds[1].Stop();
			sounds[2].Stop();
			sounds[3].Stop();
			sounds[4].Stop();
		}
	}
	if (keys[VK_CONTROL] && keys[VK_NUMPAD6])
	{
		drawSun = !drawSun;
	}
	if (keys['M']) {
		enableSounds = !enableSounds;
	}
}

void EnvDrawer::handleSounds(const Point& cameraPosition) {
	if (enableSounds) {
		for (int i = 0; i < 13; i++) {
			float x = soundsData[i][0], y = soundsData[i][1], z = soundsData[i][2];
			float radius = soundsData[i][3];
			/*glPushMatrix();
			glTranslatef(x, y, z);
			GLubyte red = (i * 30) % 256;
			GLubyte green = (i * 70) % 256;
			GLubyte blue = (i * 110) % 256;
			glColor3ub(red, green, blue);
			Sphere(radius, 5, 5).draw();
			glColor3ub(255, 255, 255);
			glPopMatrix();*/
			float distance = sqrtf(
				powf(cameraPosition.x - x, 2.0f) +
				powf(cameraPosition.y - y, 2.0f) +
				powf(cameraPosition.z - z, 2.0f)
			);
			if (distance > radius) {
				sounds[i].Stop();
			}
			else {
				sounds[i].Play(true);
				sounds[i].SetVolume((radius - distance) * 1.2 / radius);
			}
		}
	}
	else {
		for (int i = 0; i < 13; i++) {
			sounds[i].Stop();
		}
	}
}