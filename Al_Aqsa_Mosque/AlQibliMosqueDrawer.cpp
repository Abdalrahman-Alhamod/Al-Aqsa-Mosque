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
	side[20] = LoadTexture((char*)"assets/materials/AlQibli/side20.bmp", 255);
	side[21] = LoadTexture((char*)"assets/materials/AlQibli/side21.bmp", 255);
	side[22] = LoadTexture((char*)"assets/materials/AlQibli/side22.bmp", 255);
	side[23] = LoadTexture((char*)"assets/materials/AlQibli/side23.bmp", 255);
	side[24] = LoadTexture((char*)"assets/materials/AlQibli/side24.bmp", 255);
	side[25] = LoadTexture((char*)"assets/materials/AlQibli/side25.bmp", 255);
	side[26] = LoadTexture((char*)"assets/materials/AlQibli/side26.bmp", 255);

	block[0] = LoadTexture((char*)"assets/materials/AlQibli/block0.bmp", 255);
	block[1] = LoadTexture((char*)"assets/materials/AlQibli/block1.bmp", 255);
	block[2] = LoadTexture((char*)"assets/materials/AlQibli/block2.bmp", 255);
	block[3] = LoadTexture((char*)"assets/materials/AlQibli/block3.bmp", 255);

	roof[0] = LoadTexture((char*)"assets/materials/AlQibli/roof0.bmp", 255);

	carpet = LoadTexture((char*)"assets/materials/AlQibli/carpet.bmp", 255);

	HWND		hWnd = NULL;		// Holds Our Window Handle
	envDrawer = EnvDrawer(hWnd);
	boxDrawer = Box();


	alQibliDisplayList = glGenLists(1);
	glNewList(alQibliDisplayList, GL_COMPILE);

	drawFront();

	drawRightWall();

	drawCarpet();

	drawLeft();

	drawRoof();

	drawBack();

	drawDome();

	drawAdditionalSide();

	drawInner();

	drawMihrab();

	drawTransparentWindow(5);

	glEndList();

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
		constraints = Constraints(2, 3, 0.5);
		break;
	}
	case 1: {

		// right wall side unit , with door
		for (int i : { block[0], block[0], side[3], side[2], block[0], block[0] }) {
			*texturesPtr++ = i;
		}
		constraints = Constraints(2, 3, 0.5);
		break;
	}
	default: {
		for (int i : { block[0], block[0], side[4], side[1], block[0], block[0] }) {
			*texturesPtr++ = i;
		}
		constraints = Constraints(2, 3.76, 0.5);
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
		tr(0, 0, -2.74 * i);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float height = 1.2, width = 0.8;

		glBindTexture(GL_TEXTURE_2D, side[14]);

		glColor4ub(255, 255, 255, 200);  // Set alpha value for transparency


		glPushMatrix();

		tr(11, 0.2, 4.75);
		rt(90, 0, 1, 0);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
		glTexCoord2f(1, 0); glVertex3f(width, 0, 0);
		glTexCoord2f(1, 1); glVertex3f(width, height, 0);
		glTexCoord2f(0, 1); glVertex3f(0, height, 0);
		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		tr(0.80, -0.3, -0.05);
		drawLeftNormalWall(Constraints(1, 1.7, 0.05), 1);

		tr(-1.8, 0, 0);
		drawLeftNormalWall(Constraints(1, 1.7, 0.05), 1);

		tr(1, 1.5, 0);
		drawLeftNormalWall(Constraints(0.8, 0.2, 0.05), 1);

		tr(0, -1.5, 0);
		drawLeftNormalWall(Constraints(0.8, 0.4, 0.05), 1);

		glPopMatrix();

		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiHalfCylinders(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(24.8, 2.2, (3.99 - i * 2));
		envDrawer.drawHalfCylinderInRectangularPrism(0.65, Constraints(0, 0.8, 0.3), 5, block[0]);
		ppm;

		pshm;
		tr(23.15, 2.2, (3.99 - i * 2));
		envDrawer.drawHalfCylinderInRectangularPrism(0.65, Constraints(0, 0.8, 0.3), 5, block[0]);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiHallway(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		rt(90, 0, 1, 0);
		tr(24.8 + 2 * i, 2.2, (3.99));
		envDrawer.drawHallway(0.66,
			2.2, 1, 0.4, 10, 5);
		ppm;

	}
}

void AlQibliMosqueDrawer::drawRightWall() {
	pshm;
	tr(0.48, -0.05, 0);

	// start wall
	pshm;
	tr(25, 0, 8.99);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(3, 3.76, 0.5));
	ppm;

	// up windows wall
	pshm;
	tr(25, 3, 6);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(14, 0.76, 0.5), 3);
	ppm;

	pshm;
	tr(25, 0, 6);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25, 0, 4);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25, 0, 2);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25, 0, 0);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25, 0, -2);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;

	pshm;
	tr(25, 0, -4);
	rt(90, 0, 1, 0);
	drawSideUnit(1);
	ppm;

	pshm;
	tr(25, 0, -6);
	rt(90, 0, 1, 0);
	drawSideUnit(0);
	ppm;


	// ending wall
	pshm;
	tr(25, 0, -8);
	rt(90, 0, 1, 0);
	drawNormalWall(Constraints(12.25, 3.76, 0.5));
	ppm;

	ppm;

	// roof
	pshm;
	tr(22.5, 3, -20.25);
	drawRoof(Constraints(3, 0.7, 26.05), 9);
	ppm;


	drawMultiHalfCylinders(7);

	pshm;
	tr(20, -0.2, 29.79);
	drawMultiHallway(7);
	ppm;

	pshm;
	tr(18.33, -0.2, 29.79);
	drawMultiHallway(7);
	ppm;




}

void AlQibliMosqueDrawer::drawLineOfCylinders(int count, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int i = 0; i < count; ++i) {
		pshm;
		tr(0.2 * i, 0, 0); // Adjust the spacing as needed
		Cylinder(0.1, 0.001, 0.5, 4, 1, true, 2).drawSide();
		ppm;
	}

	glDisable(GL_TEXTURE_2D);
}

void AlQibliMosqueDrawer::drawSideShortWall() {
	int texture[6] = { block[1],
		block[0], block[0], block[0], block[1], block[0] };
	boxDrawer.drawOutside(Constraints(0.5,
		2, 26.05)
		, texture, 3.0f);
}

void AlQibliMosqueDrawer::drawMultiSmallWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(1 * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[10], side[5], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(1, 1.3, 0.05)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawMultiBigWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(1.34 * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[10], side[6], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(1.34, 2.6, 0.05)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawLeftMultiBigWindowUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(2.74 * i, 0, 0);
		int texture[6] = { block[1],
			block[0], side[13], side[11], block[0], block[0] };
		boxDrawer.drawOutside(Constraints(2.74, 2.1, 0.05)
			, texture);
		ppm;
	}
}

void AlQibliMosqueDrawer::drawSmallColumnSideUnit(int count) {
	for (int i = 0; i < count; i++) {
		pshm;
		tr(0, 0, -2.06 * i);
		boxDrawer.drawOutside(Constraints(0.25, 0.7, 0.25), block[0]);
		tr(0.125, 0.85, 0.125);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, block[0]);
		Cylinder(0.12, 0.001, 0.3, 5, 1, true, 2).drawSide();
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
	glVertex3d(1.5, 0, 0);
	txt(1, 1);
	glVertex3d(1.5, 3.35, 0);
	txt(0, 1);
	glVertex3d(0, 3.35, 0);
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
	glVertex3d(0.556, 0, 0);
	txt(0.1855, 0.3711);
	glVertex3d(0.556, 2.1976, 0);
	txt(0, 0.3711);
	glVertex3d(0, 2.1976, 0);
	glEnd();

	glTranslatef(2.44, 0, 0);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(0.1855, 0);
	glVertex3d(0.556, 0, 0);
	txt(0.1855, 0.3711);
	glVertex3d(0.556, 2.1976, 0);
	txt(0, 0.3711);
	glVertex3d(0, 2.1976, 0);
	glEnd();

	glTranslatef(-2.44, 2.1976, 0);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0.6386);
	glVertex3d(0, 0, 0);
	txt(1, 0.6386);
	glVertex3d(3, 0, 0);
	txt(1, 1);
	glVertex3d(3, 1.0839, 0);
	txt(0, 1);
	glVertex3d(0, 1.0839, 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
}

void AlQibliMosqueDrawer::drawFront() {
	pshm;
	tr(19.5, 2.71, 8);
	drawNormalWall(Constraints(6, 1, 1));
	ppm;

	pshm;
	tr(10.9, 3.2, 5.8);
	drawRoof(Constraints(14.6, 0.5, 2.2));
	ppm;

	pshm;
	tr(10.9, 2.71, 8);
	drawNormalWall(Constraints(6, 1, 1));
	ppm;

	int sectorCount = 5;

	// front right inter
	pshm;
	tr(21.1, 2, 8.5);
	envDrawer.drawHallway(0.65, 2.05, 3, 1, 10, sectorCount);
	ppm;

	// back right inter
	pshm;
	tr(21.1, 2.25, 6);
	envDrawer.drawHallway(0.65, 2.35, 3, 0.5, 11, sectorCount);
	ppm;


	// draw font right doors
	pshm;
	tr(20.35, -0.1, 6);
	drawDoorFront();
	ppm;

	pshm;
	tr(21.97, -0.1, 6);
	drawDoorFront();
	ppm;

	pshm;
	tr(23.6, -0.1, 6);
	drawDoorFront();
	ppm;

	// front left inter
	pshm;
	tr(12.04, 2, 8.5);
	envDrawer.drawHallway(0.65, 2.05, 3, 1, 10, sectorCount);
	ppm;

	// front left back
	pshm;
	tr(12.04, 2.25, 6);
	envDrawer.drawHallway(0.65
		, 2.35, 3,
		0.5, 11, sectorCount);
	ppm;

	// draw font left doors
	pshm;
	tr(11.28, -0.1, 6);
	drawDoorFront();
	ppm;

	pshm;
	tr(12.9, -0.1, 6);
	drawDoorFront();
	ppm;

	pshm;
	tr(14.53, -0.1, 6);
	drawDoorFront();
	ppm;

	// fron middle inter
	pshm;
	tr(18.2, 2, 8.5);
	envDrawer.drawHallway(1.2, 2.05, 1, 1, 10, sectorCount);
	ppm;

	// back middle inter
	pshm;
	tr(18.2, 1.88, 6);
	envDrawer.drawHallway(1.2, 1.98, 1, 0.5, 11, sectorCount);
	ppm;

	// draw fron main door
	pshm;
	tr(16.7, -0.1, 6);
	drawFrontMainDoor();
	ppm;

	// draw left wall
	pshm;
	tr(10.98, -0.042, 5.7);
	rt(-90, 0, 1, 0);
	drawNormalWall(Constraints(3.3, 3.75, 0.5));
	ppm;



	pshm;
	tr(20.4, 3.9, 8.8);
	drawLineOfCylinders(26, block[0]);
	ppm;

	pshm;
	tr(11, 3.9, 8.8);
	drawLineOfCylinders(26, block[0]);
	ppm;

	pshm;
	tr(16.2, 4, 8.8);
	drawLineOfCylinders(21, block[0]);
	ppm;
}

void AlQibliMosqueDrawer::drawRoof() {
	pshm;
	tr(22, 3, -20.25);
	drawSideShortWall();
	ppm;


	// right
	pshm;
	tr(20, 4.8, -20.25);
	drawRoof(Constraints(2, 0.2, 26.05), 9);
	ppm;

	// left
	pshm;
	tr(11, 4.8, -20.25);
	drawRoof(Constraints(5, 0.2, 26.05), 9);
	ppm;

	// front right 
	pshm;
	tr(20, 3.7, 5.751);
	drawMultiSmallWindowUnit(2);
	ppm;

	// front left
	pshm;
	tr(11, 3.7, 5.751);
	drawMultiSmallWindowUnit(5);
	ppm;

	// right 
	pshm;
	tr(19.95, 5, 5.75);
	rt(90, 0, 1, 0);
	drawMultiSmallWindowUnit(20);
	ppm;

	// left down
	pshm;
	tr(11, 3.7, -20.2);
	rt(-90, 0, 1, 0);
	drawMultiSmallWindowUnit(26);
	ppm;

	// left up
	pshm;
	tr(16.05, 5, -14.2);
	rt(-90, 0, 1, 0);
	drawMultiSmallWindowUnit(20);
	ppm;

	// front big windows
	pshm;
	tr(16, 3.7, 5.75);
	drawMultiBigWindowUnit(3);
	ppm;


	// front triangle
	pshm;
	tr(15.72, 6.21, 5.85);
	rt(-15, 1, 0, 0);
	boxDrawer.drawTrangleOutside(Constraints(4.6, 0.6, 0.05)
		, roof[0], 4.0f);
	ppm;

	// left triangle side
	pshm;
	tr(15.8, 6.2, -14.2);
	rt(15, 0, 0, 1);
	boxDrawer.drawOutside(Constraints(2.3,
		0.05, 20.1), roof[0], 9.0f);
	ppm;

	// right triangle side
	pshm;
	tr(18, 6.8, -14.2);
	rt(-15, 0, 0, 1);
	boxDrawer.drawOutside(Constraints(2.3,
		0.05, 20.1), roof[0], 9.0f);
	ppm;

	// back wall
	pshm;
	tr(16.05, 5, -14.25);
	int textures[6] = { block[0],block[0] ,block[0] ,block[1],block[0] ,block[0] };
	boxDrawer.drawOutside(Constraints(3.9, 1.3, 0.05), textures);
	ppm;

	// back triangle
	pshm;
	tr(15.72, 6.23, -14.28);
	rt(15, 1, 0, 0);
	boxDrawer.drawTrangleOutside(Constraints(4.6, 0.6, 0.05)
		, roof[0], 4.0f);
	ppm;
}

void AlQibliMosqueDrawer::drawCarpet() {
	glPushMatrix();

	tr(25.9, 0, 5.8);
	rt(180, 0, 1, 0);


	float width = 14.9, length = 26.05;
	int textureCount = 40;

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

void AlQibliMosqueDrawer::drawLeft() {
	// up windows
	pshm;
	tr(11, 1.6, -8);
	rt(-90, 0, 1, 0);
	drawLeftMultiBigWindowUnit(5);
	ppm;

	//  side small wall
	pshm;
	tr(9.7, -0.1, 8.5);
	rt(180, 0, 1, 0);
	boxDrawer.drawOutside(Constraints(0.1,
		0.5, 16.4)
		, block[0], 3.0f);
	ppm;

	//  side small columns
	pshm;
	tr(9.525, -0.1, 8.5);
	drawSmallColumnSideUnit(9);
	ppm;

	// from small door
	pshm;
	tr(9.78, -0.1, 8.65);
	boxDrawer.drawOutside(Constraints(0.7, 1, 0.02), side[15]);
	ppm;

	// side door
	pshm;
	tr(10.95, -0.1, -11);
	int textures[6] = { block[3],block[3] ,block[3] ,block[3] ,side[16],side[17] };
	boxDrawer.drawOutside(Constraints(0.05, 3.8, 3), textures);
	ppm;

	// front side door small column
	pshm;
	tr(9.525, -0.1, -10.95);
	drawSmallColumnSideUnit(1);
	ppm;

	// side additional door unit
	pshm;
	int textures2[6] = { block[3],roof[0] ,
		block[3] ,side[19] ,side[18],block[1] };
	tr(9, -0.1, -13.95);
	boxDrawer.drawOutside(Constraints(2, 5.1, 3), textures2);
	ppm;

	// side small empty wall
	pshm;
	int textures3[6] = { block[3],roof[0] ,
		block[3] ,block[3] ,block[3],block[1] };
	tr(9, -0.1, -14.95);
	boxDrawer.drawOutside(Constraints(2, 3.8, 1), textures3);
	ppm;

	// side small empty wall with window
	pshm;
	int textures4[6] = { block[3],roof[0] ,
		block[3] ,block[3] ,side[20],block[1] };
	tr(9, -0.1, -16.5);
	boxDrawer.drawOutside(Constraints(2, 3.2,
		1.6), textures4);
	ppm;

	// side small empty wall
	pshm;
	tr(9, -0.1, -17.5);
	boxDrawer.drawOutside(Constraints(2, 3.8, 1), textures3);
	ppm;

	// above small wall
	pshm;
	int textures5[6] = { block[3],block[3] ,
		block[3] ,block[3] ,block[3],block[1] };
	tr(10.95, 3.1, -16.5);
	boxDrawer.drawOutside(Constraints(0.05, 0.6,
		1.6), textures5);
	ppm;

	// above tall wall
	pshm;
	tr(10.95, 2.3, -20.2);
	boxDrawer.drawOutside(Constraints(0.05, 1.5,
		2.7), textures5);
	ppm;

	// tall wall
	pshm;
	tr(5, -0.1, -20.2);
	boxDrawer.drawOutside(Constraints(6,
		2.4, 2.7), textures3);
	ppm;
}

void AlQibliMosqueDrawer::drawBack() {

	pshm;
	int textures[6] = { block[3],block[3],side[21] ,block[1],block[3],block[3] };
	tr(22.5, -0.1, -20.25);
	boxDrawer.drawOutside(Constraints(3.48,
		3.8, 0.05), textures);
	ppm;

	pshm;
	int textures2[6] = { block[3],block[3],side[22] ,block[1],block[3],block[3] };
	tr(11, -0.1, -20.25);
	boxDrawer.drawOutside(Constraints(11.5,
		5.1, 0.05), textures2);
	ppm;
}

void AlQibliMosqueDrawer::drawDome() {
	// outer surrounding cylinder
	pshm;
	tr(18, 5.5, -16.5);
	rt(180, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	cull;
	glBindTexture(GL_TEXTURE_2D, side[5]);
	Cylinder(2, 2, 1, 10, 1, true, 2, false, true).drawSide();
	nocull;
	glDisable(GL_TEXTURE_2D);
	ppm;

	// inner surrounding cylinder
	pshm;
	tr(18, 5.5, -16.5);
	rt(180, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	cull;
	glBindTexture(GL_TEXTURE_2D, side[10]);
	Cylinder cylinder = Cylinder(1.99, 1.99, 1, 10, 1, true, 2, false, true);
	cylinder.reverseNormals();
	cylinder.drawSide();
	nocull;
	glDisable(GL_TEXTURE_2D);
	ppm;

	// outer italic cylinder
	pshm;
	tr(18, 6, -16.5);
	rt(180, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	cull;
	glBindTexture(GL_TEXTURE_2D, roof[0]);
	Cylinder(2.04, 2.3, 0.29, 10, 1, true, 2, false, true).drawSide();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;

	// outer dome
	pshm;
	tr(18, 6.7, -16.5);
	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roof[0]);
	Sphere(2.12, 10, 18, true, 2, true, 8.0f).draw();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;

	// inner dome
	pshm;
	tr(18, 6.7, -16.5);
	cull;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[23]);
	Sphere insideDoom = Sphere(2.119, 10, 18, true, 2, true, 6);
	insideDoom.reverseNormals();
	insideDoom.draw();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;



	// Top Cone
	glPushMatrix();
	cull;
	glTranslatef(18, 9.17, -16.5);
	glColor3b(74, 74, 74);
	Cylinder(0.07, 0.01, 0.7, 5, 1, true, 2).drawSide();
	glPopMatrix();

	// Top Spheres
	for (float yOffset = 0.2; yOffset <= 0.62; yOffset += 0.2) {
		glPushMatrix();
		glTranslatef(18, 8.75 + yOffset, -16.5);
		Sphere((0.1 - (yOffset * 0.1) + 0.02), 5, 5).draw();
		glPopMatrix();
	}
	nocull;
	glColor4f(1, 1, 1, 1);


	// outer surrouding rectangular
	pshm;
	tr(18, 5, -16.5);
	rt(90, 1, 0, 0);


	float  radius = 1.99, sectorCount = 10;
	glNormal3f(0, -1, 0);
	cull;
	Front;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, roof[0]);

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (float(i) / sectorCount) * 2 * PI;
		GLfloat x = radius * cos(angle);
		GLfloat y = radius * sin(angle);

		glVertex3f(x, y, 0);
		glTexCoord2d(x / radius, y / radius);
		if (angle >= 0 && angle <= (PI / 2)) {
			glVertex3d(radius, radius, 0);
			glTexCoord2d(0, 1);

		}
		if (angle >= (PI / 2) && angle <= PI) {
			glVertex3d(-radius, radius, 0);
			glTexCoord2d(1, 1);


		}
		if (angle >= PI && angle <= 3 * (PI / 2)) {
			glVertex3d(-radius, -radius, 0);
			glTexCoord2d(1, 1);


		}
		if (angle >= 3 * (PI / 2) && angle <= 2 * PI) {
			glVertex3d(radius, -radius, 0);
			glTexCoord2d(0, 1);

		}

	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
	Back;
	nocull;
	ppm;


	// inner surrouding rectangular
	pshm;
	tr(18, 5, -16.5);
	rt(90, 1, 0, 0);
	cull;
	glNormal3f(0, -1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, block[1]);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (float(i) / sectorCount) * 2 * PI;
		GLfloat x = radius * cos(angle);
		GLfloat y = radius * sin(angle);

		glVertex3f(x, y, 0);
		glTexCoord2d(x / radius, y / radius);
		if (angle >= 0 && angle <= (PI / 2)) {
			glVertex3d(radius, radius, 0);
			glTexCoord2d(0, 1);

		}
		if (angle >= (PI / 2) && angle <= PI) {
			glVertex3d(-radius, radius, 0);
			glTexCoord2d(1, 1);


		}
		if (angle >= PI && angle <= 3 * (PI / 2)) {
			glVertex3d(-radius, -radius, 0);
			glTexCoord2d(1, 1);


		}
		if (angle >= 3 * (PI / 2) && angle <= 2 * PI) {
			glVertex3d(radius, -radius, 0);
			glTexCoord2d(0, 1);

		}

	}

	glEnd();
	glDisable(GL_TEXTURE_2D);

	nocull;
	ppm;

	// front small roof
	pshm;
	tr(16, 4.8, -20.2);
	drawRoof(Constraints(4, 0.2, 1.71));
	ppm;

	// back tall roof
	pshm;
	tr(16, 4.8, -14.51);
	drawRoof(Constraints(4, 0.2, 0.31));
	ppm;
}
void AlQibliMosqueDrawer::drawMihrab() {
	pshm;
	tr(16.4, -0.1, -20.19);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[24]);
	cull;
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(3, 0, 0);
	txt(1, 1);
	glVertex3d(3, 4, 0);
	txt(0, 1);
	glVertex3d(0, 4, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;


	pshm;
	tr(19.4, -0.1, -20.19);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[25]);
	cull;
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(5, 0, 0);
	txt(1, 2);
	glVertex3d(5, 2, 0);
	txt(0, 2);
	glVertex3d(0, 2, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;

	pshm;
	tr(11.4, -0.1, -20.19);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, side[25]);
	cull;
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(5, 0, 0);
	txt(1, 2);
	glVertex3d(5, 2, 0);
	txt(0, 2);
	glVertex3d(0, 2, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	nocull;
	ppm;
}
void AlQibliMosqueDrawer::drawInner() {
	pshm;
	tr(18, 3.3, -19);
	envDrawer.drawArchway(1, 3.2, 1, 10, 5, 5, 5);
	ppm;

	pshm;
	tr(20.5, 3.3, -16.5);
	rt(90, 0, 1, 0);
	envDrawer.drawArchway(1, 3.2, 1, 10, 5, 5, 5);
	ppm;

	pshm;
	tr(15.5, 3.3, -16.5);
	rt(90, 0, 1, 0);
	envDrawer.drawArchway(1, 3.2, 1, 10, 5, 5, 5);
	ppm;

	pshm;
	tr(18, 3.3, -14);
	envDrawer.drawArchway(1, 3.2, 1, 10, 5, 5, 5);
	ppm;

	pshm;
	tr(15, -0.1, -14.5);
	boxDrawer.drawOutside(Constraints(1, 4.9, 1), block[3], 3.0f);
	ppm;

	pshm;
	tr(20, -0.1, -14.5);
	boxDrawer.drawOutside(Constraints(1, 4.9, 1), block[3], 3.0f);
	ppm;

	pshm;
	tr(20, -0.1, -19.5);
	boxDrawer.drawOutside(Constraints(1, 4.9, 1), block[3], 3.0f);
	ppm;

	pshm;
	tr(15, -0.1, -19.5);
	boxDrawer.drawOutside(Constraints(1, 4.9, 1), block[3], 3.0f);
	ppm;

	pshm;
	tr(20.25, 4.35, 5);
	rt(90, 0, 1, 0);
	envDrawer.drawHallway(0.3, 0.4, 25, 0.5, 10, 5);
	tr(0, 0, -4.45);
	envDrawer.drawHallway(0.3, 0.4, 25, 0.5, 10, 5);
	ppm;

	pshm;
	tr(20.25, 3.02, 4.3);
	rt(90, 0, 1, 0);
	envDrawer.drawArchway(0.615, 2.9, 10, 10, 5, 5, 5);
	tr(0, 0, -4.45);
	envDrawer.drawArchway(0.615, 2.9, 10, 10, 5, 5, 5);
	ppm;

	drawQuraans();
}
void AlQibliMosqueDrawer::drawQuraans() {
	envDrawer.drawQuraan(Point(17.9, 0, -18.5), 1);
	for (int i = 0; i < 3; i++) {
		envDrawer.drawQuraan(Point(23, 0, -17 + 3 * i), 1);
	}
	for (int i = 0; i < 8; i++) {
		envDrawer.drawQuraan(Point(13, 0, -17 + 3 * i), 1);
	}
}
void AlQibliMosqueDrawer::drawAdditionalSide() {
	pshm;
	tr(26, 0, -20.2);
	int textures[6] = { block[0],roof[0],side[1],side[1],block[0],block[0] };
	boxDrawer.drawOutside(Constraints(28, 3.6, 3)
		, textures, 8, 1, 2);
	ppm;

	pshm;
	tr(54, 0, -17.2);
	rt(270, 0, 1, 0);
	int textures2[6] = { block[0],roof[0],block[0],side[1],block[0],block[0] };
	boxDrawer.drawOutside(Constraints(10, 3.6, 3)
		, textures2, 2, 1, 2);
	ppm;

	pshm;
	tr(54, 0, -7.2);
	rt(270, 0, 1, 0);
	int textures3[6] = { block[0],roof[0],block[0],side[26],block[0],block[0] };
	boxDrawer.drawOutside(Constraints(13, 3.6, 3)
		, textures3, 1, 1, 2);
	ppm;

}

void AlQibliMosqueDrawer::drawAlQibliMosque() {
	pshm;
	glScalef(size, size, size);

	glCallList(alQibliDisplayList);

	ppm;
}

