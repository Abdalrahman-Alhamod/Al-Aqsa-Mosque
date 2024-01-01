#include "AlQibliMosqueDrawer.h"
#include "Point.h"
#include "Color.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Model_3DS.h"
#include "Texture.h"
#include "Box.h"
#include "Constraints.h"
AlQibliMosqueDrawer::AlQibliMosqueDrawer() {
	side[0] = LoadTexture((char*)"assets/materials/AlQibli/side0.bmp", 255);
	side[1] = LoadTexture((char*)"assets/materials/AlQibli/side1.bmp", 255);
	side[2] = LoadTexture((char*)"assets/materials/AlQibli/side2.bmp", 255);
	side[3] = LoadTexture((char*)"assets/materials/AlQibli/side3.bmp", 255);
	side[4] = LoadTexture((char*)"assets/materials/AlQibli/side4.bmp", 255);
	side[5] = LoadTexture((char*)"assets/materials/AlQibli/side5.bmp", 255);
	side[6] = LoadTexture((char*)"assets/materials/AlQibli/side6.bmp", 255);
	side[7] = LoadTexture((char*)"assets/materials/AlQibli/side7.bmp", 255);
	side[8] = LoadTexture((char*)"assets/materials/AlQibli/side8.bmp", 255);

	block[0] = LoadTexture((char*)"assets/materials/AlQibli/block0.bmp", 255);
	block[1] = LoadTexture((char*)"assets/materials/AlQibli/block1.bmp", 255);
	block[2] = LoadTexture((char*)"assets/materials/AlQibli/block2.bmp", 255);

	roof[0] = LoadTexture((char*)"assets/materials/AlQibli/roof0.bmp", 255);

	envDrawer = EnvDrawer();

}
void AlQibliMosqueDrawer::drawSideUnit(int type) {
	int* textures = new int[6];
	Constraints constraints;
	int* texturesPtr = textures;  // Create a separate pointer to iterate through the array

	switch (type) {
	case 0: {

		// right wall side unit , no door
		for (int i : { block[0], block[0], side[4], side[1], block[0], block[0] }) {
			*texturesPtr++ = i;
		}
		constraints = Constraints(2 * size, 3 * size, 0.5 * size);
		break;
	}
	case 1: {

		// right wall side unit , with door
		for (int i : { block[0], block[0], side[3], side[2], block[0], block[0] }) {
			*texturesPtr++ = i;
		}
		constraints = Constraints(2 * size, 3 * size, 0.5 * size);
		break;
	}
	default: {
		for (int i : { block[0], block[0], side[4], side[1], block[0], block[0] }) {
			*texturesPtr++ = i;
		}
		constraints = Constraints(2 * size, 3 * size, 0.5 * size);
		break;
	}
	}

	// Use the original 'textures' pointer to pass to drawOutside
	Box box = Box();
	box.drawOutside(constraints, textures);

	// Don't forget to deallocate the memory when done
	delete[] textures;
}
void tr(GLfloat x, GLfloat y, GLfloat z) {
	glTranslatef(x, y, z);
}
void rt(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	glRotatef(angle, x, y, z);
}
void AlQibliMosqueDrawer::drawNormalWall(const Constraints& constraints) {
	int textures[6] = { block[0], block[0], block[1], block[0], block[0], block[0] };
	Box().drawOutside(constraints, textures,2);
}
void AlQibliMosqueDrawer::drawRoof(const Constraints& constraints, int textureCount) {
	int textures[6] = { block[2], roof[0], block[0], block[0], block[0], block[0] };
	Box().drawOutside(constraints, textures, textureCount);
}
void AlQibliMosqueDrawer::drawRightWall() {
	pshm;
	tr(25 * size, 0,  8* size);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(2 * size, 3 * size, 0.5 * size));
	ppm;

	pshm;
	tr(25 * size, 0, 6 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25 * size, 0, 4 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25 * size, 0, 2 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25 * size, 0, 0);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25 * size, 0, -2 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25 * size, 0, -4 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25 * size, 0, -6 * size);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;


	pshm;
	tr(25 * size, 0, -8 * size);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(8 * size, 3 * size, 0.5 * size));
	ppm;
}
void AlQibliMosqueDrawer::drawLineOfCylinders(int count, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int i = 0; i < count; ++i) {
		pshm;
		tr(0.2*i*size, 0, 0); // Adjust the spacing as needed
		Cylinder(0.1 * size, 0.001 * size, 0.5 * size, 4, 1, true, 2).drawSide();
		ppm;
	}

	glDisable(GL_TEXTURE_2D);
}

void AlQibliMosqueDrawer::drawFront() {
	pshm;
	tr(19.5 * size, 2.71 * size, 8 * size);
	drawNormalWall(Constraints(6 * size, 1 * size, 1 * size));
	ppm;

	pshm;
	tr(10.9 * size, 3.2 * size, 5.8 * size);
	drawRoof(Constraints(14.6 * size, 0.5 * size, 2.2 * size));
	ppm;

	pshm;
	tr(10.9 * size, 2.71 * size, 8 * size);
	drawNormalWall(Constraints(6 * size, 1 * size, 1 * size));
	ppm;

	pshm;
	tr(25 * size, 2.2 * size, 5.8 * size);
	drawNormalWall(Constraints(0.5 * size, 1 * size, 2.2 * size));
	ppm;


	pshm;
	tr(21.1 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(0.65 * size, 2.05 * size, 3, 1 * size, 10);
	ppm;

	pshm;
	tr(12.04 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(0.65 * size, 2.05 * size, 3, 1 * size, 10);
	ppm;

	pshm;
	tr(18.2 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(1.2 * size, 2.05 * size, 1, 1 * size, 10);
	ppm;

	pshm;
	tr(20.4 * size, 3.9 * size, 8.8 * size);
	drawLineOfCylinders(26, block[0]);
	ppm;

	pshm;
	tr(11 * size, 3.9 * size, 8.8 * size);
	drawLineOfCylinders(26, block[0]);
	ppm;

	pshm;
	tr(16.2 * size, 4 * size, 8.8 * size);
	drawLineOfCylinders(21, block[0]);
	ppm;
}
void AlQibliMosqueDrawer::drawAlQibliMosque() {

	drawFront();

	drawRightWall();

	pshm;
	tr(22.5 * size, 3 * size, -16 * size);
	drawRoof(Constraints(3 * size, 0.7 * size, 21.8 * size), 8);
	ppm;
;}

