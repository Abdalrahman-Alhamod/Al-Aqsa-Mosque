#define cull glEnable(GL_CULL_FACE)
#define nocull glDisable(GL_CULL_FACE)
#define Front glCullFace(GL_FRONT)
#define Back glCullFace(GL_BACK)

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
	side[9] = LoadTexture((char*)"assets/materials/AlQibli/side9.bmp", 255);
	side[10] = LoadTexture((char*)"assets/materials/AlQibli/side10.bmp", 255);
	side[11] = LoadTexture((char*)"assets/materials/AlQibli/side11.bmp", 255);
	side[12] = LoadTexture((char*)"assets/materials/AlQibli/side12.bmp", 255);
	side[13] = LoadTexture((char*)"assets/materials/AlQibli/side13.bmp", 255);
	side[14] = LoadTexture((char*)"assets/materials/AlQibli/side14.bmp", 255);
	side[15] = LoadTexture((char*)"assets/materials/AlQibli/side15.bmp", 255);
	side[16] = LoadTexture((char*)"assets/materials/AlQibli/side16.bmp", 255);
	side[17] = LoadTexture((char*)"assets/materials/AlQibli/side17.bmp", 255);
	side[18] = LoadTexture((char*)"assets/materials/AlQibli/side18.bmp", 255);
	side[19] = LoadTexture((char*)"assets/materials/AlQibli/side19.bmp", 255);

	block[0] = LoadTexture((char*)"assets/materials/AlQibli/block0.bmp", 255);
	block[1] = LoadTexture((char*)"assets/materials/AlQibli/block1.bmp", 255);
	block[2] = LoadTexture((char*)"assets/materials/AlQibli/block2.bmp", 255);
	block[3] = LoadTexture((char*)"assets/materials/AlQibli/block3.bmp", 255);

	roof[0] = LoadTexture((char*)"assets/materials/AlQibli/roof0.bmp", 255);

	carpet = LoadTexture((char*)"assets/materials/AlQibli/carpet.bmp", 255);

	envDrawer = EnvDrawer();
	boxDrawer = Box();

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
		constraints = Constraints(2 * size, 3.76 * size, 0.5 * size);
		break;
	}
	}

	// Use the original 'textures' pointer to pass to drawOutside
	boxDrawer.drawOutside(constraints, textures);

	// Don't forget to deallocate the memory when done
	delete[] textures;
}

void tr(GLfloat x, GLfloat y, GLfloat z) {
	glTranslatef(x, y, z);
}

void rt(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	glRotatef(angle, x, y, z);
}

void AlQibliMosqueDrawer::drawNormalWall(const Constraints& constraints, float textureCount) {
	int textures[6] = { block[0], block[0], block[1], block[0], block[0], block[0] };
	boxDrawer.drawOutside(constraints, textures, textureCount);
}

void AlQibliMosqueDrawer::drawLeftNormalWall(const Constraints& constraints, float textureCount) {
	int textures[6] = { block[3], block[3], block[3], block[1], block[3], block[3] };
	boxDrawer.drawOutside(constraints, textures, textureCount);
}

void AlQibliMosqueDrawer::drawRoof(const Constraints& constraints, float textureCount) {
	int textures[6] = { block[1], roof[0],
		block[1], block[1], block[1], block[1] };
	boxDrawer.drawOutside(constraints, textures, textureCount);
}

void AlQibliMosqueDrawer::drawTransparentWindow(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(0, 0, -2.74 * i * size);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float height = 1.2 * size, width = 0.8 * size;

		glBindTexture(GL_TEXTURE_2D, side[14]);

		glColor4ub(255, 255, 255, 200);  // Set alpha value for transparency


		glPushMatrix();

		tr(11 * size, 0.2 * size, 4.75 * size);
		rt(90, 0, 1, 0);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0); glVertex3f(width, 0, 0);
		glTexCoord2f(1, 1); glVertex3f(width, height, 0);
		glTexCoord2f(0, 1); glVertex3f(0, height, 0);
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		tr(0.80 * size, -0.3 * size, -0.05 * size);
		drawLeftNormalWall(Constraints(1 * size, 1.7 * size, 0.05 * size), 1);

		tr(-1.8 * size, 0, 0);
		drawLeftNormalWall(Constraints(1 * size, 1.7 * size, 0.05 * size), 1);

		tr(1 * size, 1.5 * size, 0);
		drawLeftNormalWall(Constraints(0.8 * size, 0.2 * size, 0.05 * size), 1);

		tr(0, -1.5 * size, 0);
		drawLeftNormalWall(Constraints(0.8 * size, 0.4 * size, 0.05 * size), 1);

		glPopMatrix();

		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiHalfCylinders(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(24.8 * size, 2.2 * size, (3.99 - i * 2) * size);
		envDrawer.drawHalfCylinderInRectangularPrism(0.65 * size, Constraints(0, 0.8 * size, 0.3 * size), 5, block[0]);
		ppm;

		pshm;
		tr(23.15 * size, 2.2 * size, (3.99 - i * 2) * size);
		envDrawer.drawHalfCylinderInRectangularPrism(0.65 * size, Constraints(0, 0.8 * size, 0.3 * size), 5, block[0]);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiHallway(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		rt(90, 0, 1, 0);
		tr(24.8 * size + 2 * size * i, 2.2 * size, (3.99) * size);
		envDrawer.drawHallway(0.66 * size,
			2.2 * size, 1, 0.4 * size, 10, 5);
		ppm;

	}
}

void AlQibliMosqueDrawer::drawRightWall() {
	pshm;
	tr(0.48 * size, -0.05 * size, 0);

	// start wall
	pshm;
	tr(25 * size, 0, 8.99 * size);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(3 * size, 3.76 * size, 0.5 * size));
	ppm;

	// up windows wall
	pshm;
	tr(25 * size, 3 * size, 6 * size);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(14 * size, 0.76 * size, 0.5 * size), 3);
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


	// ending wall
	pshm;
	tr(25 * size, 0, -8 * size);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(12 * size, 3.76 * size, 0.5 * size));
	ppm;

	ppm;

	// roof
	pshm;
	tr(22.5 * size, 3 * size, -20 * size);
	drawRoof(Constraints(3 * size, 0.7 * size, 25.8 * size), 9);
	ppm;

	if (drawInside)
	{
		drawMultiHalfCylinders(7);

		pshm;
		tr(20 * size, -0.2 * size, 29.79 * size);
		drawMultiHallway(7);
		ppm;

		pshm;
		tr(18.33 * size, -0.2 * size, 29.79 * size);
		drawMultiHallway(7);
		ppm;

	}


}

void AlQibliMosqueDrawer::drawLineOfCylinders(int count, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int i = 0; i < count; ++i) {
		pshm;
		tr(0.2 * i * size, 0, 0); // Adjust the spacing as needed
		Cylinder(0.1 * size, 0.001 * size, 0.5 * size, 4, 1, true, 2).drawSide();
		ppm;
	}

	glDisable(GL_TEXTURE_2D);
}

void AlQibliMosqueDrawer::drawSideShortWall() {
	int texture[6] = { block[1],
		block[0], block[0], block[0], block[1], block[0] };
	boxDrawer.drawOutside(Constraints(0.5 * size, 2 * size, 25.8 * size)
		, texture, 3.0f);
}

void AlQibliMosqueDrawer::drawMultiSmallWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(1 * size * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[10], side[5], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(1 * size, 1.3 * size, 0.05 * size)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiBigWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(1.34 * size * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[10], side[6], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(1.34 * size, 2.6 * size, 0.05 * size)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawLeftMultiBigWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(2.74 * size * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[13], side[11], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(2.74 * size, 2.1 * size, 0.05 * size)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawSmallColumnSideUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(0, 0, -2.06 * i * size);
		boxDrawer.drawOutside(Constraints(0.25 * size, 0.7 * size, 0.25 * size), block[0]);
		tr(0.125 * size, 0.85 * size, 0.125 * size);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, block[0]);
		Cylinder(0.12 * size, 0.001 * size, 0.3 * size, 5, 1, true, 2).drawSide();
		glDisable(GL_TEXTURE_2D);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawDoorFront() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[9]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(1.5 * size, 0, 0);
	txt(1, 1);
	glVertex3d(1.5 * size, 3.35 * size, 0);
	txt(0, 1);
	glVertex3d(0, 3.35 * size, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void AlQibliMosqueDrawer::drawFrontMainDoor() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[9]);


	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(0.1855, 0);
	glVertex3d(0.556 * size, 0, 0);
	txt(0.1855, 0.3711);
	glVertex3d(0.556 * size, 2.1976 * size, 0);
	txt(0, 0.3711);
	glVertex3d(0, 2.1976 * size, 0);
	glEnd();

	glTranslatef(2.44 * size, 0, 0);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(0.1855, 0);
	glVertex3d(0.556 * size, 0, 0);
	txt(0.1855, 0.3711);
	glVertex3d(0.556 * size, 2.1976 * size, 0);
	txt(0, 0.3711);
	glVertex3d(0, 2.1976 * size, 0);
	glEnd();

	glTranslatef(-2.44 * size, 2.1976 * size, 0);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0.6386);
	glVertex3d(0, 0, 0);
	txt(1, 0.6386);
	glVertex3d(3 * size, 0, 0);
	txt(1, 1);
	glVertex3d(3 * size, 1.0839 * size, 0);
	txt(0, 1);
	glVertex3d(0, 1.0839 * size, 0);
	glEnd();


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

	int sectorCount = 5;

	// front right inter
	pshm;
	tr(21.1 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(0.65 * size, 2.05 * size, 3, 1 * size, 10, sectorCount);
	ppm;

	// back right inter
	pshm;
	tr(21.1 * size, 2.25 * size, 6 * size);
	envDrawer.drawHallway(0.65 * size, 2.35 * size, 3, 0.5 * size, 11, sectorCount);
	ppm;


	// draw font right doors
	pshm;
	tr(20.35 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	pshm;
	tr(21.97 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	pshm;
	tr(23.6 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	// front left inter
	pshm;
	tr(12.04 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(0.65 * size, 2.05 * size, 3, 1 * size, 10, sectorCount);
	ppm;

	// front left back
	pshm;
	tr(12.04 * size, 2.25 * size, 6 * size);
	envDrawer.drawHallway(0.65 * size
		, 2.35 * size, 3,
		0.5 * size, 11, sectorCount);
	ppm;

	// draw font left doors
	pshm;
	tr(11.28 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	pshm;
	tr(12.9 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	pshm;
	tr(14.53 * size, -0.1, 6 * size);
	drawDoorFront();
	ppm;

	// fron middle inter
	pshm;
	tr(18.2 * size, 2 * size, 8.5 * size);
	envDrawer.drawHallway(1.2 * size, 2.05 * size, 1, 1 * size, 10, sectorCount);
	ppm;

	// back middle inter
	pshm;
	tr(18.2 * size, 1.88 * size, 6 * size);
	envDrawer.drawHallway(1.2 * size, 1.98 * size, 1, 0.5 * size, 11, sectorCount);
	ppm;

	// draw fron main door
	pshm;
	tr(16.7 * size, -0.1 * size, 6 * size);
	drawFrontMainDoor();
	ppm;

	// draw left wall
	pshm;
	tr(10.98 * size, -0.042 * size, 5.7 * size);
	rt(-90, 0, 1, 0);
	drawNormalWall(Constraints(3.3 * size, 3.75 * size, 0.5 * size));
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

void AlQibliMosqueDrawer::drawRoof() {
	pshm;
	tr(22 * size, 3 * size, -20 * size);
	drawSideShortWall();
	ppm;


	// right
	pshm;
	tr(20 * size, 4.8 * size, -20 * size);
	drawRoof(Constraints(2 * size, 0.2 * size, 25.8 * size), 9);
	ppm;

	// left
	pshm;
	tr(11 * size, 4.8 * size, -20 * size);
	drawRoof(Constraints(5 * size, 0.2 * size, 25.8 * size), 9);
	ppm;

	// front right 
	pshm;
	tr(20 * size, 3.7 * size, 5.751 * size);
	drawMultiSmallWindowUnit(2);
	ppm;

	// front left
	pshm;
	tr(11 * size, 3.7 * size, 5.751 * size);
	drawMultiSmallWindowUnit(5);
	ppm;

	// right 
	pshm;
	tr(19.95 * size, 5 * size, 5.75 * size);
	rt(90, 0, 1, 0);
	drawMultiSmallWindowUnit(20);
	ppm;

	// left down
	pshm;
	tr(11 * size, 3.7 * size, -20.2 * size);
	rt(-90, 0, 1, 0);
	drawMultiSmallWindowUnit(26);
	ppm;

	// left up
	pshm;
	tr(16.05 * size, 5 * size, -14.2 * size);
	rt(-90, 0, 1, 0);
	drawMultiSmallWindowUnit(20);
	ppm;

	// front big windows
	pshm;
	tr(16 * size, 3.7 * size, 5.75 * size);
	drawMultiBigWindowUnit(3);
	ppm;


	// front triangle
	pshm;
	tr(15.72 * size, 6.21 * size, 5.85 * size);
	rt(-15, 1, 0, 0);
	boxDrawer.drawTrangleOutside(Constraints(4.6 * size, 0.6 * size, 0.05 * size)
		, roof[0], 4.0f);
	ppm;

	// left triangle side
	pshm;
	tr(15.8 * size, 6.2 * size, -14.2 * size);
	rt(15, 0, 0, 1);
	boxDrawer.drawOutside(Constraints(2.3 * size,
		0.05 * size, 20.1 * size), roof[0], 9.0f);
	ppm;

	// right triangle side
	pshm;
	tr(18 * size, 6.8 * size, -14.2 * size);
	rt(-15, 0, 0, 1);
	boxDrawer.drawOutside(Constraints(2.3 * size,
		0.05 * size, 20.1 * size), roof[0], 9.0f);
	ppm;

	// back wall
	pshm;
	tr(16.05 * size, 5 * size, -14.25 * size);
	int textures[6] = { block[0],block[0] ,block[0] ,block[1],block[0] ,block[0] };
	boxDrawer.drawOutside(Constraints(3.9 * size, 1.3 * size, 0.05 * size), textures);
	ppm;

	// back triangle
	pshm;
	tr(15.72 * size, 6.23 * size, -14.28 * size);
	rt(15, 1, 0, 0);
	boxDrawer.drawTrangleOutside(Constraints(4.6 * size, 0.6 * size, 0.05 * size)
		, roof[0], 4.0f);
	ppm;
}

void AlQibliMosqueDrawer::drawCarpet() {
	glPushMatrix();

	tr(25.9 * size, -0.1 * size, 5.8 * size);
	rt(180, 0, 1, 0);


	float width = 14.9 * size, length = 26 * size;
	int textureCount = 20;

	glEnable(GL_TEXTURE_2D);
	cull;
	Front;
	glBindTexture(GL_TEXTURE_2D, carpet);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(textureCount, 0); glVertex3f(width, 0, 0);
	glTexCoord2f(textureCount, textureCount); glVertex3f(width, 0, length);
	glTexCoord2f(0, textureCount); glVertex3f(0, 0, length);
	glEnd();
	Back;
	nocull;
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

void AlQibliMosqueDrawer::drawAlQibliMosque() {

	drawFront();

	drawRightWall();

	drawCarpet();

	// up windows
	pshm;
	tr(11 * size, 1.6 * size, -8 * size);
	rt(-90, 0, 1, 0);
	drawLeftMultiBigWindowUnit(5);
	ppm;

	//  side small wall
	pshm;
	tr(9.7 * size, -0.1, 8.5 * size);
	rt(180, 0, 1, 0);
	boxDrawer.drawOutside(Constraints(0.1 * size,
		0.5 * size, 16.4 * size)
		, block[0], 3.0f);
	ppm;

	//  side small columns
	pshm;
	tr(9.525 * size, -0.1, 8.5 * size);
	drawSmallColumnSideUnit(9);
	ppm;

	// from small door
	pshm;
	tr(9.78 * size, -0.1, 8.65 * size);
	boxDrawer.drawOutside(Constraints(0.7 * size, 1 * size, 0.02 * size), side[15]);
	ppm;

	// side door
	pshm;
	tr(10.95 * size, -0.1 * size, -11 * size);
	int textures[6] = { block[3],block[3] ,block[3] ,block[3] ,side[16],side[17] };
	boxDrawer.drawOutside(Constraints(0.05 * size, 3.8 * size, 3 * size), textures);
	ppm;

	// front side door small column
	pshm;
	tr(9.525 * size, -0.1, -10.95 * size);
	drawSmallColumnSideUnit(1);
	ppm;

	// side additional door unit
	pshm;
	int textures2[6] = { block[3],roof[0] ,
		block[3] ,side[19] ,side[18],block[1] };
	tr(9 * size, -0.1, -13.95 * size);
	boxDrawer.drawOutside(Constraints(2 * size, 5.1 * size, 3 * size), textures2);
	ppm;

	drawRoof();

	drawTransparentWindow(5);
}

