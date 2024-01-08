#define cull glEnable(GL_CULL_FACE)
#define nocull glDisable(GL_CULL_FACE)
#define Front glCullFace(GL_FRONT)
#define Back glCullFace(GL_BACK)
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#include "EnvDrawer.h"
#include <GL/glut.h>  
#include "Point.h"
#include "Color.h"
#include "Constants.h"
#include "Texture.h"
#include "Model_3DS.h"
#include "Cylinder.h"
#include "Sphere.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
Model_3DS* EnvDrawer::tree1Model = new Model_3DS();
Model_3DS* EnvDrawer::tree2Model = new Model_3DS();
Model_3DS* EnvDrawer::tankModel = new Model_3DS();
Model_3DS* EnvDrawer::fountainModel = new Model_3DS();
Model_3DS* EnvDrawer::birdModel = new Model_3DS();
Model_3DS* EnvDrawer::quraanModel = new Model_3DS();

bool pos[701][1001] = {};

void* font = GLUT_BITMAP_8_BY_13;
void drawString(const char* str, int x, int y, float color[4], void* font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

	// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}

void showInfo(string info)
{
	// backup current model-view matrix
	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

	// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);     // switch to projection matrix
	glPushMatrix();                  // save current projection matrix
	glLoadIdentity();                // reset projection matrix
	gluOrtho2D(0, 400, 0, 300);  // set to orthogonal projection

	float color[4] = { 1, 1, 1, 1 };

	stringstream ss;
	ss << std::fixed << std::setprecision(3);

	ss << info << ends;
	drawString(ss.str().c_str(), 2, 290, color, font);

	// unset floating format
	ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

	// restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();                   // restore to previous modelview matrix
}

EnvDrawer::EnvDrawer() {
	envBoxDrawer = Box();
}

EnvDrawer::EnvDrawer(HWND hWnd) {

	envBoxDrawer = Box();

	pos[0][0] = 0;

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
	stonesTexture[14] = LoadTexture((char*)"assets/materials/stones9.bmp", 255);

	buildingTexture[0] = LoadTexture((char*)"assets/materials/building1.bmp", 255);
	buildingTexture[1] = LoadTexture((char*)"assets/materials/building2.bmp", 255);
	buildingTexture[2] = LoadTexture((char*)"assets/materials/building3.bmp", 255);
	buildingTexture[3] = LoadTexture((char*)"assets/materials/building4.bmp", 255);
	buildingTexture[4] = LoadTexture((char*)"assets/materials/building5.bmp", 255);
	buildingTexture[5] = LoadTexture((char*)"assets/materials/building6.bmp", 255);

	skyBoxTextures[0][0] = LoadTexture((char*)"assets/skybox/SkyBox0Bottom.bmp", 255);
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

	birdModel->Load((char*)"assets/models/bird.3DS");
	birdModel->Materials[0].tex.LoadBMP((char*)"assets/materials/bird.bmp");

	quraanModel->Load((char*)"assets/models/quraan.3DS");
	quraanModel->Materials[0].tex.LoadBMP((char*)"assets/materials/quraanCover.bmp");
	quraanModel->Materials[1].tex.LoadBMP((char*)"assets/materials/quraanPage2.bmp");
	quraanModel->Materials[2].tex.LoadBMP((char*)"assets/materials/quraanPage1.bmp");
	quraanModel->Materials[3].tex.LoadBMP((char*)"assets/materials/quraanWood.bmp");
	/*quraanModel->Materials[0].tex.LoadBMP((char*)"assets/materials/bird.bmp");
	quraanModel->Materials[0].tex.LoadBMP((char*)"assets/materials/bird.bmp");
	quraanModel->Materials[0].tex.LoadBMP((char*)"assets/materials/bird.bmp");
	quraanModel->Materials[0].tex.LoadBMP((char*)"assets/materials/bird.bmp");*/

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
	soundsData[12][1] = -9;	// y
	soundsData[12][2] = 39;	// z
	soundsData[12][3] = 20;	// r

	// Pigons Sounds
	SoundManager.CreateSound((char*)"assets/sounds/pigeons.wav", sounds[13]);
	soundsData[13][0] = 20;	 // x
	soundsData[13][1] = -2;	// y
	soundsData[13][2] = 0;	// z
	soundsData[13][3] = 40;	// r

	lights[0] = true;
	for (int i = 1; i <= 7; i++) {
		lights[i] = false;
	}

	envDisplayList = glGenLists(1);
	glNewList(envDisplayList, GL_COMPILE);
	drawConst();
	glEndList();

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

void EnvDrawer::drawBird(const Point& position, const float size) {
	drawModel(birdModel, position, size, 1);
}

void EnvDrawer::drawQuraan(const Point& position, const float size) {
	drawModel(quraanModel, position, size, 0.01);
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
	EnvDrawer::drawPillar(0.7, hight, stonesTexture[10], 0.4, 9, 9);

	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[13]);
	Cylinder cyl = Cylinder(2.5, 2.5, 0.1, 9);
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
		envBoxDrawer.drawOutside(Constraints(0.10, 1.0, 0.05), texture);
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
	Sphere sphere = Sphere(0.75, 10, 18, true, 2, true, 2);
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
	envBoxDrawer.drawOutside(Constraints(4, 0.1, 4), stonesTexture[13]);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.5, 5.2, -1.42);
	envBoxDrawer.drawOutside(Constraints(3, 0.1, 3), stonesTexture[13]);
	glPopMatrix();



	for (int i = 0; i <= 3; ++i)
	{
		glRotatef(i * 360 / 4, 0, 1, 0);
		glPushMatrix();
		glTranslatef(0, height - 4, 1.4);
		drawHalfCylinderInRectangularPrism(0.35,
			Constraints(2.8, 0.6, 0.07), 6, stonesTexture[14]);
		glPopMatrix();
		glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glTranslatef(0, height - 4.8, 1.9);
		envBoxDrawer.drawOutside(Constraints(0.10, .8, 0.05), stonesTexture[14]);
		glPopMatrix();
	}

	glTranslated(0, height - 3.8, 0);

	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stonesTexture[12]);
	Cylinder cyl = Cylinder(0.7, 0.9, 2.5, 5, 1, true, 3, false, true);
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
		glTranslatef(0, 0.6 + yOffset, 0);
		Sphere((0.1 - (yOffset * 0.1) + 0.02), 3, 3).draw();
		glPopMatrix();
	}
	nocull;
	glColor4f(1, 1, 1, 1);

	glPopMatrix();
}

void EnvDrawer::drawWallWithDoor(const float length, const float wallHeight, const int texture)
{
	glPushMatrix();

	int i = 0;
	for (; 2 * (i + 1) < length; ++i)
	{
		glPushMatrix();
		glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
		envBoxDrawer.drawOutside(Constraints(1.3, 1, 1), texture);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
	envBoxDrawer.drawOutside(Constraints(length - (2 * i), 1, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, wallHeight - 5, 0);
	glPushMatrix();
	glTranslatef(-(length - 2.5) / 2, -wallHeight + 1, -0.5);
	envBoxDrawer.drawOutside(Constraints((length - 2.5) / 2, wallHeight, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -wallHeight + 1, 0);

	glPushMatrix();
	glTranslatef(0, 0, -1 * 0.5);
	envBoxDrawer.drawOutside(Constraints(0.25, wallHeight - 2, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.25, 0, -0.5);
	envBoxDrawer.drawOutside(Constraints(0.25, wallHeight - 2, 1), texture);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.25, -1, 0);
	EnvDrawer::drawHalfCylinderInRectangularPrism(1, Constraints(2.5, 2, 1), 5, texture);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(2.5, -wallHeight + 1, -0.5);
	envBoxDrawer.drawOutside(Constraints((length - 2.5) / 2, wallHeight, 1), texture);
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
		envBoxDrawer.drawOutside(Constraints(1.3, 1, 1), texture);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslated(2 * i - (length - 2.5) / 2, wallHeight - 4, -0.5);
	envBoxDrawer.drawOutside(Constraints(length - (2 * i), 1, 1), texture);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-(length - 2.5) / 2, -wallHeight, -0.5);
	int t[] = { texture,texture,texture, texture, texture, texture, };
	envBoxDrawer.drawOutside(Constraints(length, wallHeight, 1), t, length / 10,1,1);
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
	height = max(constraints.height, radius);

	int sectorCount = sectors; // for dividing cylinder and circle ( increase for more quality )

	// Start drawing cylinder
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

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

	//top
	glPushMatrix();
	glTranslatef(-width / 2, radius, -length / 2);
	envBoxDrawer.drawOutside(Constraints(width, height - radius, length), texture);
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(radius, 0, -length / 2);
	envBoxDrawer.drawOutside(Constraints(width / 2 - radius, radius, length), texture);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslatef(-width / 2, 0, -length / 2);
	envBoxDrawer.drawOutside(Constraints(width / 2 - radius, radius, length), texture);
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

	glPushMatrix();
	glTranslatef(-size * 2, 0, -size * 0.5);
	envBoxDrawer.drawOutside(Constraints(size * 0.5, size * 1.5, 1 * size), texture);
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
	envBoxDrawer.drawOutside(Constraints(size * 0.5, size * 1.5, 1 * size), texture);
	glPopMatrix();

}

void EnvDrawer::drawHallway(const float size, const float wallHeight, const int count, const float length, const int textureIndex, const int sectorCount) {
	int texture = stonesTexture[textureIndex];
	glPushMatrix();
	glTranslatef(-size * 1.75, -wallHeight, -length * 0.5);
	envBoxDrawer.drawOutside(Constraints(size * 0.5, wallHeight + (size) * 1.5, length), texture);
	glPopMatrix();

	for (int i = 0; i < count; i++) {
		glPushMatrix();
		glTranslatef(i * size * 2.5, 0, 0);

		glPushMatrix();
		glTranslatef(-size * 1.25, -wallHeight, -length * 0.5);
		envBoxDrawer.drawOutside(Constraints(size * 0.25, wallHeight, length), texture);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(size, -wallHeight, -length * 0.5);
		envBoxDrawer.drawOutside(Constraints(size * 0.25, wallHeight, length), texture);
		glPopMatrix();

		EnvDrawer::drawHalfCylinderInRectangularPrism(size, Constraints(size * 2.5, (size) * 1.5, length), sectorCount, texture);

		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(size * 1.25 + (count - 1) * size * 2.5, -wallHeight, -length * 0.5);
	envBoxDrawer.drawOutside(Constraints(size * 0.5, wallHeight + (size) * 1.5, length), texture);
	glPopMatrix();

}

void EnvDrawer::drawBuidling(const float size, const int buildingTextureIndex) {
	envBoxDrawer.drawOutside(Constraints(10 * size, 20 * size, 10 * size), buildingTexture[buildingTextureIndex], stonesTexture[buildingTextureIndex]);
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
}

float sunAngle = 0;

// Function to convert sun angle to simulated time
std::string getSimulatedTime(float sunAngle) {
	float totalSunAngles = 2 * PI;
	float offsetAngle = PI; // Offset angle to adjust for midmorning

	float adjustedSunAngle = sunAngle + offsetAngle;
	if (adjustedSunAngle > totalSunAngles) {
		adjustedSunAngle -= totalSunAngles;
	}

	float percentOfDay = adjustedSunAngle / totalSunAngles;

	int totalSecondsInDay = 24 * 60 * 60; // 24 hours * 60 minutes * 60 seconds
	int simulatedTimeInSeconds = static_cast<int>(percentOfDay * totalSecondsInDay);

	int hours = simulatedTimeInSeconds / 3600;
	int minutes = (simulatedTimeInSeconds % 3600) / 60;

	char buffer[10];
	std::sprintf(buffer, "%02d:%02d", hours, minutes);

	return std::string(buffer);
}

void EnvDrawer::simulateSun(const float rotatioRadius, const float sunRadius, const float speed) {
	string simulatedTime = getSimulatedTime(sunAngle);
	showInfo("Time : " + simulatedTime);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	sunAngle += (2 * PI / 60) * speed;
	if (sunAngle >= PI * 2) {
		sunAngle = 0.0;
	}
	if (sunAngle >= PI * 1.5 || sunAngle <= PI * 0.5) {
		glEnable(GL_LIGHT0);
		for (int i = 1; i <= 7; i++) {
			glDisable(GL_LIGHT0 + i);
		}
		if (sunAngle <= PI * 1.75 && sunAngle >= PI * 1.5 ||
			sunAngle >= PI * 0.25 && sunAngle <= PI * 0.5) {
			currentSkyBoxIndex = 1;
		}
		else {
			currentSkyBoxIndex = 0;
		}
	}
	else {
		glDisable(GL_LIGHT0);
		for (int i = 1; i <= 7; i++) {
			glEnable(GL_LIGHT0 + i);
		}
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

	// Light properties
	float lightpos[4] = { position.x, position.y + pillarHeight * 0.5, position.z, 1.0 };
	glLightfv(light, GL_POSITION, lightpos);

	float lightAmbient[] = { 0.002, 0.002, 0.002, 1.0 };
	float lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // Adjust for color
	float lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // Adjust for shininess

	glLightfv(light, GL_AMBIENT, lightAmbient);
	glLightfv(light, GL_DIFFUSE, lightDiffuse);
	glLightfv(light, GL_SPECULAR, lightSpecular);

	// Set up the attenuation
	float constantAttenuation = 1;
	float linearAttenuation = 0.05; // Adjust as needed
	float quadraticAttenuation = 0.001; // Adjust as needed
	glLightf(light, GL_CONSTANT_ATTENUATION, constantAttenuation);
	glLightf(light, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(light, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);


	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(position.x, position.y - pillarHeight / 2, position.z);
	Cylinder pillar = Cylinder(0.1 * size, 0.1 * size, pillarHeight, 5);
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
	bulp.draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}



void EnvDrawer::setLightAmb(GLfloat ambx, GLfloat amby, GLfloat ambz) {
	this->LightAmb[0] = ambx;
	this->LightAmb[1] = amby;
	this->LightAmb[2] = ambz;
	glLightfv(GL_LIGHT0, GL_AMBIENT, this->LightAmb);

	return;
}

void EnvDrawer::setLightDiff(GLfloat diffx, GLfloat diffy, GLfloat diffz) {
	this->LightDiff[0] = diffx;
	this->LightDiff[1] = diffy;
	this->LightDiff[2] = diffz;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, this->LightDiff);
	return;
}

void EnvDrawer::setLightSpec(GLfloat specx, GLfloat specy, GLfloat specz) {
	this->LightSpec[0] = specx;
	this->LightSpec[1] = specy;
	this->LightSpec[2] = specz;
	glLightfv(GL_LIGHT0, GL_SPECULAR, this->LightSpec);
	return;
}

void EnvDrawer::decodeEnables(bool* keys) {
	if (keys[VK_CONTROL] && keys[VK_NUMPAD0])
	{
		drawSun = !drawSun;
	}
	if (keys['M']) {
		enableSounds = !enableSounds;
	}
	for (int i = '0'; i <= '7'; i++) {
		if (keys[i]) {
			int index = i - '0';
			lights[index] = !lights[index];
			if (lights[index]) {
				glEnable(GL_LIGHT0 + index);
			}
			else {
				glDisable(GL_LIGHT0 + index);
			}
		}
	}
}


void EnvDrawer::handleSounds(const Point& cameraPosition) {
	if (enableSounds) {
		for (int i = 0; i < 14; i++) {
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

float birdAngle = 0;

void EnvDrawer::drawPigeons() {

	pshm;

	glRotatef(birdAngle -= 1, 0, 1, 0);
	glTranslatef(20, 0, 0);


	soundsData[13][0] = 20 * cosf(birdAngle * PIdiv180);	 // x
	soundsData[13][2] = 20 * sinf(-birdAngle * PIdiv180);	// z
	const int numRows = 3;
	const GLfloat triangleLength = 2.0 * sqrt(3.0) / 2.0;
	const GLfloat xOffset = 2.0;
	const GLfloat zOffset = triangleLength;

	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < (i + 1) * 2; ++j) {
			GLfloat x = 1 * (j - i) + xOffset * 2;
			GLfloat z = -i * zOffset;
			GLfloat y = 0.0;
			GLfloat scale = 1.0;

			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(45, 0, 0, 1);
			drawBird(Point(x, y, z), 1);
			glPopMatrix();
		}
	}

	glPushMatrix();
	glTranslatef(4.5, 0, 2);
	glRotatef(45, 0, 0, 1);
	drawBird(Point(4.5, 0, 2), 0.8);
	glPopMatrix();

	ppm;

}

void EnvDrawer::drawAllGardens() {
	float treeSize = 0.9;
	bool isTreeSmall = true;

	pshm;
	drawGarden(Point(-16, -9.98, 0), 10, 20,
		10, treeSize, isTreeSmall);
	ppm;

	pshm;
	drawGarden(Point(26, -9.98, 0), 10, 20,
		10, treeSize, isTreeSmall);
	ppm;

	pshm;
	drawGarden(Point(-16, -9.98, -35), 10, 20,
		10, treeSize, isTreeSmall);
	ppm;

	pshm;
	drawGarden(Point(26, -9.98, -35), 10, 20,
		10, treeSize, isTreeSmall);
	ppm;

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  grassLandPoints1[4] = { Point(-14 + i * 10, -9.98, -35) ,
			Point(-6 + i * 10, -9.98, -35) ,
			Point(-6 + i * 10, -9.98, -27) ,
			Point(-14 + i * 10, -9.98, -27) };
		drawGrassLand(grassLandPoints1, 10);
		ppm;
	}

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  grassLandPoints1[4] = { Point(-14 + i * 10, -9.98, -25) ,
			Point(-6 + i * 10, -9.98, -25) ,
			Point(-6 + i * 10, -9.98, -17) ,
			Point(-14 + i * 10, -9.98, -17) };
		drawGrassLand(grassLandPoints1, 10);
		ppm;
	}

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  grassLandPoints1[4] = { Point(-14 + i * 10, -9.98, 2) ,
			Point(-6 + i * 10, -9.98, 2) ,
			Point(-6 + i * 10, -9.98, 10) ,
			Point(-14 + i * 10, -9.98, 10) };
		drawGrassLand(grassLandPoints1, 10);
		ppm;
	}

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  grassLandPoints1[4] = { Point(-14 + i * 10, -9.98, 12) ,
			Point(-6 + i * 10, -9.98, 12) ,
			Point(-6 + i * 10, -9.98, 20) ,
			Point(-14 + i * 10, -9.98, 20) };
		drawGrassLand(grassLandPoints1, 10);
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		Point  passagePoints1[4] = { Point(-16 + i * 10 , -9.98,2) ,
				Point(-14 + i * 10 , -9.98, 2) ,
				Point(-14 + i * 10 , -9.98, 20) ,
				Point(-16 + i * 10, -9.98, 20) };
		drawPassage(passagePoints1, 5);
		ppm;
	}


	for (int i = 0; i < 4; i++) {
		pshm;
		Point  passagePoints1[4] = { Point(-16 + i * 10 , -9.98, -35) ,
				Point(-14 + i * 10 , -9.98, -35) ,
				Point(-14 + i * 10 , -9.98, -17) ,
				Point(-16 + i * 10, -9.98, -17) };
		drawPassage(passagePoints1, 5);
		ppm;
	}

	pshm;
	Point  passagePoints1[4] = { Point(-16  , -9.98, 0) ,
			Point(16  , -9.98, 0) ,
			Point(16  , -9.98, 2) ,
			Point(-16 , -9.98, 2) };
	drawPassage(passagePoints1, 4);
	ppm;

	pshm;
	Point  passagePoints2[4] = { Point(-16  , -9.98, -17) ,
			Point(16  , -9.98, -17) ,
			Point(16  , -9.98, -15) ,
			Point(-16 , -9.98, -15) };
	drawPassage(passagePoints2, 4);
	ppm;

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  passagePoints1[4] = { Point(-14 + i * 10  , -9.98, 10) ,
				Point(-6 + i * 10  , -9.98,10) ,
				Point(-6 + i * 10  , -9.98, 12) ,
				Point(-14 + i * 10 , -9.98, 12) };
		drawPassage(passagePoints1, 3);
		ppm;
	}

	for (int i = 0; i < 3; i++) {
		pshm;
		Point  passagePoints1[4] = { Point(-14 + i * 10  , -9.98, -27) ,
				Point(-6 + i * 10  , -9.98,-27) ,
				Point(-6 + i * 10  , -9.98, -25) ,
				Point(-14 + i * 10 , -9.98, -25) };
		drawPassage(passagePoints1, 3);
		ppm;
	}

}

void EnvDrawer::drawBench() {
	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-2 + i * 0.2, -10, 2);
		envBoxDrawer.drawOutside(Constraints(0.05, 0.15, 0.05), stonesTexture[0]);
		ppm;
	}
	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-2 + i * 0.2, -10, 2.2);
		envBoxDrawer.drawOutside(Constraints(0.05, 0.15, 0.05), stonesTexture[0]);
		ppm;
	}
	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-2 + i * 0.2, -9.85, 2);
		glRotatef(90, 1, 0, 0);
		envBoxDrawer.drawOutside(Constraints(0.05, 0.25, 0.05), stonesTexture[0]);
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-2 + i * 0.2, -9.92, 2.2);
		glRotatef(10, 1, 0, 0);
		envBoxDrawer.drawOutside(Constraints(0.05, 0.25, 0.05), stonesTexture[0]);
		ppm;
	}
	for (int i = 0; i < 3; i++) {
		pshm;
		glTranslatef(-2, -9.85, 2 + i * 0.07);
		envBoxDrawer.drawOutside(Constraints(0.65, 0.01, 0.05), stonesTexture[9]);
		ppm;
	}
	pshm;
	glTranslatef(-2, -9.85, 2.22);
	glRotatef(-80, 1, 0, 0);
	for (int i = 0; i < 3; i++) {
		pshm;
		glTranslatef(0, 0, 0 + i * 0.07);
		envBoxDrawer.drawOutside(Constraints(0.65, 0.01, 0.05), stonesTexture[9]);
		ppm;
	}
	ppm;
}

void EnvDrawer::drawStairs(const Constraints& unitConstraints, const int count, const int texture) {
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < i + 1; j++) {
			pshm;
			glTranslatef(0, -i-unitConstraints.height, j * unitConstraints.length);
			envBoxDrawer.drawOutside(unitConstraints, texture);
			ppm;
		}
	}
}

void EnvDrawer::drawStairs(const Constraints& unitConstraints, const int count) {
	drawStairs(unitConstraints, count, stonesTexture[7]);
}

void EnvDrawer::drawBenchesGroub() {
	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-1.2 + i * 2, 0, 0);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-11.2 + i * 2, 0, 0);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(8.8 + i * 2, 0, 0);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-1.2 + i * 2, 0, 10);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-11.2 + i * 2, 0, 10);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(8.8 + i * 2, 0, 10);
		drawBench();
		ppm;
	}
	pshm;

	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-1.2 + i * 2, 0, -12);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-11.2 + i * 2, 0, -12);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(8.8 + i * 2, 0, -12);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-1.2 + i * 2, 0, -22);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(-11.2 + i * 2, 0, -22);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glTranslatef(8.8 + i * 2, 0, -22);
		drawBench();
		ppm;
	}

	ppm;

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-7.3 + i * 2, 0, 4);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-17.3 + i * 2, 0, 4);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-7.3 + i * 2, 0, 14);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-17.3 + i * 2, 0, 14);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-7.3 + i * 2, 0, -6);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-17.3 + i * 2, 0, -6);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-7.3 + i * 2, 0, -16);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(-17.3 + i * 2, 0, -16);
		drawBench();
		ppm;
	}
	pshm;
	glRotatef(180, 0, 1, 0);
	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(4.8 + i * 2, 0, 4);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(14.8 + i * 2, 0, 4);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(4.8 + i * 2, 0, 14);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(14.8 + i * 2, 0, 14);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(4.8 + i * 2, 0, -6);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(14.8 + i * 2, 0, -6);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(4.8 + i * 2, 0, -16);
		drawBench();
		ppm;
	}

	for (int i = 0; i < 4; i++) {
		pshm;
		glRotatef(90, 0, 1, 0);
		glTranslatef(14.8 + i * 2, 0, -16);
		drawBench();
		ppm;
	}
	ppm;
}

float skyBoxLength = 113, skyboxWidth = 85, skyboxHeight = 100;

void EnvDrawer::drawConst() {

	float tiledLandLength = 83, tiledLandWidth = 55;
	Point tiledLandPoints[4] = { Point(-tiledLandWidth / 2,-skyboxHeight / 10,-tiledLandLength / 2),
		Point(tiledLandWidth / 2,-skyboxHeight / 10,-tiledLandLength / 2),
		Point(tiledLandWidth / 2,-skyboxHeight / 10,tiledLandLength / 2),
		Point(-tiledLandWidth / 2,-skyboxHeight / 10,tiledLandLength / 2), };

	drawTiledLand(tiledLandPoints, 100);


	float road1Length = 83, road1Width = 8;

	Point road1Points[4] = { Point(-road1Width / 2,-skyboxHeight / 10,-road1Length / 2),
		Point(road1Width / 2,-skyboxHeight / 10,-road1Length / 2),
		Point(road1Width / 2,-skyboxHeight / 10,road1Length / 2),
		Point(-road1Width / 2,-skyboxHeight / 10,road1Length / 2), };

	pshm;
	glTranslatef(31.5, 0, 0);
	drawStreet(road1Points, 50);
	ppm;

	pshm;
	glTranslatef(-31.5, 0, 0);
	drawStreet(road1Points, 50);
	ppm;

	float road2Length = 70, road2Width = 8;

	Point road2Points[4] = { Point(-road2Width / 2,-skyboxHeight / 10,-road2Length / 2),
		Point(road2Width / 2,-skyboxHeight / 10,-road2Length / 2),
		Point(road2Width / 2,-skyboxHeight / 10,road2Length / 2),
		Point(-road2Width / 2,-skyboxHeight / 10,road2Length / 2), };

	pshm;
	glRotatef(90, 0, 1, 0);
	glTranslatef(-45.5, 0, 0);
	drawStreet(road2Points, 40);
	ppm;

	pshm;
	glRotatef(90, 0, 1, 0);
	glTranslatef(45.5, 0, 0);
	drawStreet(road2Points, 40);
	ppm;



	// Bab Almgharebah Minart
	pshm;
	glTranslatef(-26.5, -7, 40);
	drawCubedMinaret(0.6);
	ppm;

	// Bab Alsilselah Minart
	pshm;
	glTranslatef(-26.9, -7, 10);
	drawCubedMinaret(0.6);
	ppm;

	// Bab Ghuanimah Minart
	pshm;
	glTranslatef(-26.9, -7, -41);
	drawCubedMinaret(0.6);
	ppm;
	// Bab Alasbat Minart
	pshm;
	glTranslatef(15, -8, -41.2);
	glScalef(1, 1.2, 1);
	drawCylindricMinaret(0.4, stonesTexture[14]);
	ppm;


	pshm;
	glTranslatef(-26.9, -8, 25.2);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWallWithDoor(5, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(-26.9, -8, 9);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWall(60, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(-26.9, -8, -7);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWallWithDoor(5, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(-26.9, -8, -24);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWall(65, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(-1, -8, -41.2);
	glScalef(1, 0.5, 0.5);
	drawWall(54, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(26.9, -8, -7);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWallWithDoor(5, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(26.9, -8, -24);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWall(65, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(26.9, -8, 18);
	glScalef(1, 0.5, 0.5);
	glRotatef(90, 0, 1, 0);
	drawWall(96, 4, stonesTexture[14]);
	ppm;

	pshm;
	glTranslatef(13.2, -8, 41.2);
	glScalef(1, 0.5, 0.5);
	drawWall(25, 4, stonesTexture[14]);
	ppm;



	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(i == 1 && j == 1)) {
				pshm;
				drawFountain(Point(-21 + j * 3, -9.4, 27 + i * 5), 0.3);
				ppm;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			pshm;
			drawFountain(Point(2 + j * 3, -9.4, 27 + i * 5), 0.3);
			ppm;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			pshm;
			drawFountain(Point(16 + j * 3, -9.4, 27 + i * 5), 0.3);
			ppm;
		}
	}



	pshm;
	drawTank(Point(12, -10, 32), 0.5);
	ppm;




	for (int i = 0; i < 14; i++) {
		pshm;
		glTranslatef(-40, -10, 44 - i * 7);
		drawBuidling(0.5, i % 6);
		ppm;


		pshm;
		Point  passagePoints3[4] = { Point(-40   , -9.98, 42 - i * 7) ,
				Point(-35   , -9.98,42 - i * 7) ,
				Point(-35   , -9.98, 44 - i * 7) ,
				Point(-40 , -9.98, 44 - i * 7) };
		drawPassage(passagePoints3, 3);
		ppm;
	}

	pshm;
	glTranslatef(75, 0, 0);
	for (int i = 0; i < 14; i++) {
		pshm;
		glTranslatef(-40, -10, 44 - i * 7);
		drawBuidling(0.5, i % 6);
		ppm;


		pshm;
		Point  passagePoints3[4] = { Point(-40   , -9.98, 42 - i * 7) ,
				Point(-35   , -9.98,42 - i * 7) ,
				Point(-35   , -9.98, 44 - i * 7) ,
				Point(-40 , -9.98, 44 - i * 7) };
		drawPassage(passagePoints3, 3);
		ppm;
	}
	ppm;

	pshm;
	glRotatef(90, 0, 1, 0);
	for (int i = 0; i < 10; i++) {
		pshm;
		glTranslatef(-54, -10, 29 - i * 7);
		drawBuidling(0.5, i % 6);
		ppm;


		pshm;
		Point  passagePoints3[4] = { Point(-54   , -9.98, 27 - i * 7) ,
				Point(-49  , -9.98,27 - i * 7) ,
				Point(-49   , -9.98, 29 - i * 7) ,
				Point(-54, -9.98, 29 - i * 7) };
		drawPassage(passagePoints3, 3);
		ppm;
	}
	ppm;

	pshm;
	glRotatef(90, 0, 1, 0);
	glTranslatef(103, 0, 0);
	for (int i = 0; i < 10; i++) {
		pshm;
		glTranslatef(-54, -10, 29 - i * 7);
		drawBuidling(0.5, i % 6);
		ppm;


		pshm;
		Point  passagePoints3[4] = { Point(-54   , -9.98, 27 - i * 7) ,
				Point(-49  , -9.98,27 - i * 7) ,
				Point(-49   , -9.98, 29 - i * 7) ,
				Point(-54, -9.98, 29 - i * 7) };
		drawPassage(passagePoints3, 3);
		ppm;
	}
	ppm;

	//drawBenchesGroub();
	pshm;
	glTranslatef(0, 0, -37);
	//drawBenchesGroub();
	ppm;

}

void EnvDrawer::drawDynamic(bool* keys) {
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

	if (drawSun) {
		simulateSun(100, 10, THREE_HOURS_PER_SECOND);
	}
	else {
		controlLightSourcePosition(keys);
		pshm;
		glTranslatef(LightPos[0], LightPos[1], LightPos[2]);
		Sphere(1, 5, 5).draw();
		ppm;
	}


	drawSkyBox(Constraints(skyboxWidth, skyboxHeight, skyBoxLength));

	pshm;
	drawLightingPillar(Point(17, -6, 11), 1, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(-17, -6, 11), 2, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(17, -6, -25), 3, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(-17, -6, -25), 4, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(12, -6, 38), 5, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(0, -6, -7), 6, 1, 4);
	ppm;

	pshm;
	drawLightingPillar(Point(-18, -6, 32), 7, 1, 4);
	ppm;

	drawPigeons();

}

void EnvDrawer::draw(bool* keys) {
	glCallList(envDisplayList);
	//drawAllGardens();
	drawDynamic(keys);
	//drawStairs(Constraints(3, 1, 1), 7);
}