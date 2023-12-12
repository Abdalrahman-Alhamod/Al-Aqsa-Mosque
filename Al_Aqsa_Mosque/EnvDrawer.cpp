#include "EnvDrawer.h"
#include <GL/glut.h>  
#include "Point.h"
#include "Color.h"
#include "Constants.h"
#include "Texture.h"
#include "Model_3DS.h"

Model_3DS* EnvDrawer::tree1Model = new Model_3DS();
Model_3DS* EnvDrawer::tree2Model = new Model_3DS();
Model_3DS* EnvDrawer::tankModel = new Model_3DS();

EnvDrawer::EnvDrawer() {

	glEnable(GL_TEXTURE_2D);

	ground = LoadTexture((char*)"assets/materials/ground.bmp", 255);
	grass = LoadTexture((char*)"assets/materials/grass.bmp", 255);
	stone = LoadTexture((char*)"assets/materials/stone1.bmp", 255);

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
		,SKYBACK = 0
		,SKYLEFT = 0
		,SKYRIGHT = 0
		,SKYUP = 0
		,SKYDOWN = 0;

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

void EnvDrawer::drawLand(const Point points[4], const int count, const int textureID) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(points[0].x, points[0].y, points[0].z);
	glTexCoord2f(count, 0); glVertex3f(points[1].x, points[1].y, points[1].z);
	glTexCoord2f(count, count); glVertex3f(points[2].x, points[2].y, points[2].z);
	glTexCoord2f(0, count); glVertex3f(points[3].x, points[3].y, points[3].z);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();
}

void EnvDrawer::drawTiledLand(const Point points[4], const int count) {
	drawLand(points, count, ground);
}

void EnvDrawer::drawGrassLand(const Point points[4], const int count) {
	drawLand(points, count, grass);
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

	glDisable(GL_TEXTURE_2D);

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