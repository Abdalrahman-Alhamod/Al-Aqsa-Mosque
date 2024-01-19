#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#define beg(word) glBegin(word)
#define endf glEnd()
#define cull glEnable(GL_CULL_FACE)
#define nocull glDisable(GL_CULL_FACE)
#define frontf glCullFace(GL_FRONT)
#define backf glCullFace(GL_BACK)
#define txt(s,t) glTexCoord2d(s,t)
#define entxt 	glEnable(GL_TEXTURE_2D)
#define distxt glDisable(GL_TEXTURE_2D)
#define white glColor3f(1,1,1)
const db srt = 1.414213562373095;
const db pi = 3.141592653589793238462643383279502884197;


#include "DomeOfTheRock.h"
#include "Texture.h"

DomeOfTheRock::DomeOfTheRock() {
	/*
	ROOF1 = LoadTexture((char*)"assets/domeOfTheRock/roof1.bmp");
	ROOF2 = LoadTexture((char*)"assets/domeOfTheRock/roof2.bmp");
	ROOF3 = LoadTexture((char*)"assets/domeOfTheRock/roof03.bmp");
	ROOF4 = LoadTexture((char*)"assets/domeOfTheRock/roof4.bmp");

	BRIDGE1 = LoadTexture((char*)"assets/domeOfTheRock/bridge1.bmp");
	BRIDGE2 = LoadTexture((char*)"assets/domeOfTheRock/bridge2.bmp");

	ROCK1 = LoadTexture((char*)"assets/domeOfTheRock/rock3.bmp");
	ROCK2 = LoadTexture((char*)"assets/domeOfTheRock/rock4.bmp");

	FENCE = LoadTexture((char*)"assets/domeOfTheRock/fence.bmp");
	FENCE1 = LoadTexture((char*)"assets/domeOfTheRock/fence1.bmp");
	MARBLE_FENCE = LoadTexture((char*)"assets/domeOfTheRock/marbleFence.bmp");

	FOOT1 = LoadTexture((char*)"assets/domeOfTheRock/footprint1.bmp");
	FOOT2 = LoadTexture((char*)"assets/domeOfTheRock/footprint2.bmp");
	FOOT3 = LoadTexture((char*)"assets/domeOfTheRock/footprint3.bmp");
	FOOT4 = LoadTexture((char*)"assets/domeOfTheRock/footprint4.bmp");
	FOOT5 = LoadTexture((char*)"assets/domeOfTheRock/footprint5.bmp");
	FOOT6 = LoadTexture((char*)"assets/domeOfTheRock/footprint6.bmp");

	ARCH1 = LoadTexture((char*)"assets/domeOfTheRock/arch01.bmp");
	ARCH2 = LoadTexture((char*)"assets/domeOfTheRock/arch2.bmp");
	ARCH3 = LoadTexture((char*)"assets/domeOfTheRock/arch3.bmp");
	ARCH4 = LoadTexture((char*)"assets/domeOfTheRock/arch4.bmp");
	ARCH5 = LoadTexture((char*)"assets/domeOfTheRock/arch5.bmp");
	ARCH6 = LoadTexture((char*)"assets/domeOfTheRock/arch6.bmp");
	ARCH7 = LoadTexture((char*)"assets/domeOfTheRock/arch7.bmp");
	ARCH8 = LoadTexture((char*)"assets/domeOfTheRock/arch8.bmp");
	LEAD = LoadTexture((char*)"assets/domeOfTheRock/arch9.bmp");
	ARCH10 = LoadTexture((char*)"assets/domeOfTheRock/arch10.bmp");

	DRUM1 = LoadTexture((char*)"assets/domeOfTheRock/drum1.bmp");
	DRUM2 = LoadTexture((char*)"assets/domeOfTheRock/drum002.bmp");
	DRUM3 = LoadTexture((char*)"assets/domeOfTheRock/drum3.bmp");
	DRUM4 = LoadTexture((char*)"assets/domeOfTheRock/drum4.bmp");
	DRUM5 = LoadTexture((char*)"assets/domeOfTheRock/drum5.bmp");

	DOME1 = LoadTexture((char*)"assets/domeOfTheRock/dome01.bmp");
	DOME2 = LoadTexture((char*)"assets/domeOfTheRock/dome02.bmp");
	//DOME2 = LoadTexture((char*)"assets/domeOfTheRock/dome2.bmp");
	DOME3 = LoadTexture((char*)"assets/domeOfTheRock/dome3.bmp");

	PILLAR1 = LoadTexture((char*)"assets/domeOfTheRock/pillar1.bmp");
	PILLAR2 = LoadTexture((char*)"assets/domeOfTheRock/pillar2.bmp");

	MARBLE1 = LoadTexture((char*)"assets/domeOfTheRock/marble1.bmp");
	MARBLE2 = LoadTexture((char*)"assets/domeOfTheRock/marble2.bmp");
	MARBLE3 = LoadTexture((char*)"assets/domeOfTheRock/marble3.bmp");
	MARBLE4 = LoadTexture((char*)"assets/domeOfTheRock/marble4.bmp");
	MARBLE5 = LoadTexture((char*)"assets/domeOfTheRock/marble5.bmp");
	MARBLE6 = LoadTexture((char*)"assets/domeOfTheRock/marble6.bmp");
	MARBLE7 = LoadTexture((char*)"assets/domeOfTheRock/marble7.bmp");
	MARBLE8 = LoadTexture((char*)"assets/domeOfTheRock/marble8.bmp");

	LIME_STONE1 = LoadTexture((char*)"assets/domeOfTheRock/limestone1.bmp");
	LIME_STONE2 = LoadTexture((char*)"assets/domeOfTheRock/limestone2.bmp");
	LIME_STONE3 = LoadTexture((char*)"assets/domeOfTheRock/limestone3.bmp");

	WHITE_STONE = LoadTexture((char*)"assets/domeOfTheRock/whiteStone.bmp");

	WOOD = LoadTexture((char*)"assets/domeOfTheRock/wood.bmp");

	TIER1 = LoadTexture((char*)"assets/domeOfTheRock/tier01.bmp");
	TIER2 = LoadTexture((char*)"assets/domeOfTheRock/tier02.bmp");
	TIER3 = LoadTexture((char*)"assets/domeOfTheRock/tier3.bmp");
	TIER4 = LoadTexture((char*)"assets/domeOfTheRock/tier4.bmp");

	WALL1 = LoadTexture((char*)"assets/domeOfTheRock/wall1.bmp");
	WALL2 = LoadTexture((char*)"assets/domeOfTheRock/wall2.bmp");
	WALL3 = LoadTexture((char*)"assets/domeOfTheRock/wall3.bmp");
	WALL4 = LoadTexture((char*)"assets/domeOfTheRock/wall4.bmp");
	WALL5 = LoadTexture((char*)"assets/domeOfTheRock/wall5.bmp");
	WALL6 = LoadTexture((char*)"assets/domeOfTheRock/wall6.bmp");

	DOOR1 = LoadTexture((char*)"assets/domeOfTheRock/door1.bmp");
	DOOR2 = LoadTexture((char*)"assets/domeOfTheRock/door2.bmp");
	DOOR3 = LoadTexture((char*)"assets/domeOfTheRock/door3.bmp");

	CARPET = LoadTexture((char*)"assets/domeOfTheRock/carpet.bmp");

	KHALILI1 = LoadTexture((char*)"assets/domeOfTheRock/khalili1.bmp");
	KHALILI2 = LoadTexture((char*)"assets/domeOfTheRock/khalili2.bmp");
	KHALILI3 = LoadTexture((char*)"assets/domeOfTheRock/khalili3.bmp");
	KHALILI4 = LoadTexture((char*)"assets/domeOfTheRock/khalili4.bmp");

	*/

	mosqueDrawer = MosqueDrawer();

	domeOfTheRockDisplayList = glGenLists(1);
	glNewList(domeOfTheRockDisplayList, GL_COMPILE);
	draw(90);
	glEndList();

	dome1DisplayList = glGenLists(1);
	glNewList(dome1DisplayList, GL_COMPILE);
	drawDomeOfSouls();
	glEndList();

	dome2DisplayList = glGenLists(1);
	glNewList(dome2DisplayList, GL_COMPILE);
	drawDomeOfAscention();
	glEndList();

	dome3DisplayList = glGenLists(1);
	glNewList(dome3DisplayList, GL_COMPILE);
	drawDomeOfKhalili();
	glEndList();

	dome4DisplayList = glGenLists(1);
	glNewList(dome4DisplayList, GL_COMPILE);
	drawDomeOfTheProphet();
	glEndList();


}

void DomeOfTheRock::arch(db sectorCount, db radius, db thickness) {

	db length = 0;
	pshm;
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_TRIANGLE_STRIP);

	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (static_cast<float>(i) / sectorCount) * PI;
		GLfloat x = radius * cos(angle);
		GLfloat y = radius * sin(angle);

		if (angle <= PI / 2) {
			glTexCoord2d(1, 1);
			glVertex3d(radius, radius + thickness, length);
			glTexCoord2d(x / radius, y / radius);
			glVertex3f(x, y, length);
		}
		else {
			glTexCoord2d(1, 1);
			glVertex3d(-radius, radius + thickness, length);
			glTexCoord2d(fabs(x) / radius, fabs(y) / radius);
			glVertex3f(x, y, length);
		}

	}
	endf;
	ppm;
}

void DomeOfTheRock::drawArch(db innerR, db outerR, db height,int textures[], int sectorCnt) {
	white;
	entxt;
	pshm;
	glNormal3f(0, 0, 1);
	glTranslated(0, 0, height / 2.0 - 0.01);
	cull;
	frontf;
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	arch(sectorCnt / 2.0, outerR);
	backf;
	nocull;
	ppm;

	pshm;
	glNormal3f(0, 0, -1);
	glTranslated(0, 0, -height / 2.0 + 0.01);
	cull;
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	arch(sectorCnt / 2.0, outerR);
	nocull;
	ppm;

	//glColor3f(0, 0.123, 0.21);
	drawPipe(innerR, outerR, height, sectorCnt, textures, true, true);

	distxt;
}

void DomeOfTheRock::drawInnerRoof() {
	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	db dist = dia / 2.0 * sin(45) - dia2 / 2.0 * sin(45) + 5.2;

#pragma region octRoof

	pshm;

	cull;
	entxt;
	frontf;
	glNormal3f(0, 0.2, 0);
	glTranslated(0, 35.1, 0);

	pshm;
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 0.6, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 0.5, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.1, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.1, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 0.6 + 7.1, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 0.5 - 7.1, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.1, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.1, 0, -dist);
	endf;
	ppm;


	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 0.6, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 1.5, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.2, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.4, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 0.6 + 7.4, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 1.5 - 7.2, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.2, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.4, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 1.6, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 1.5, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.3, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 1.6 + 7.3, 0, 0);
	txt(1, 0);
	glVertex3d(p + a - 1.5 - 7.3, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.3, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 0.6, 0, -2);
	txt(1, 0);
	glVertex3d(p + a - 1.5, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p - 0.6 + 7.2, 0, -2);
	txt(1, 0);
	glVertex3d(p + a - 1.5 - 7.3, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p, 0, -2);
	txt(1, 0);
	glVertex3d(p + a - 0.1, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 7.2, 0, -2);
	txt(1, 0);
	glVertex3d(p + a - 0.1 - 7.3, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p, 0, -2);
	txt(1, 0);
	glVertex3d(p + a + 0.7, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 7.2, 0, -2);
	txt(1, 0);
	glVertex3d(p + a + 0.7 - 7.3, 0, -2);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 2, 0, -1.5);
	txt(1, 0);
	glVertex3d(p + a + 1, 0, -1.5);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 2 + 7.2, 0, -1.5);
	txt(1, 0);
	glVertex3d(p + a + 1 - 7.3, 0, -1.5);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	glBindTexture(GL_TEXTURE_2D, ROOF4);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 1, 0, 0);
	txt(1, 0);
	glVertex3d(p + a + 1, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	white;
	glTranslated(0, -0.1, 0);
	glBindTexture(GL_TEXTURE_2D, ROOF1);
	beg(GL_QUADS);
	txt(0, 0);
	glVertex3d(p + 1 + 7.2, 0, 0);
	txt(1, 0);
	glVertex3d(p + a + 1 - 7.3, 0, 0);
	txt(1, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(0, 1);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;


	backf;
	nocull;
	ppm;
#pragma endregion

#pragma region trapizoidRoof

	cull;
	//the second layer
	glColor3f(0.3, 0.5, 0.2);
	pshm;
	glNormal3f(0, 0.2, 0);
	glTranslated(0, 35.1, 0);

	white;
	entxt;
	glBindTexture(GL_TEXTURE_2D, ROOF2);
	pshm;
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.1, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.1, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.1, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.1, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.2, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.4, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.4, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.2, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.3, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.3, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.2, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.2, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.2, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.2, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.2, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.2, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.2, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.2, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0, 1);
	glVertex3d(p + a - 7.3, 0, -dist);
	txt(1, 1);
	glVertex3d(p + 7.2, 0, -dist);
	txt(1, 0);
	glVertex3d(p + 16 - 7.2, 3.5, -dist - 22);
	txt(0, 0);
	glVertex3d(p + a - 16 + 7.3, 3.5, -dist - 22);
	endf;
	ppm;

#pragma endregion

	ppm;
	nocull;
}

void DomeOfTheRock::drawLeadRoof() {


	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	db dist = dia / 2.0 * sin(45) - dia2 / 2.0 * sin(45) + 5.2;

	cull;

	pshm;
	glNormal3f(0, 1, 0);
	glTranslated(0, 35.1, 0);
	entxt;
	glBindTexture(GL_TEXTURE_2D, ROOF3);

	pshm;
	glTranslated(0, 0.1, 0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p + 0.6, 0.5, 0);
	txt(0.8, 0);
	glVertex3d(p + a - 0.5, 0.5, 0);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p - 0.6, 0.5, 0);
	txt(0.8, 0);
	glVertex3d(p + a - 1.5, 0.5, 0);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0.2, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p - 1.6, -0.2, 0);
	txt(0.8, 0);
	glVertex3d(p + a - 1.5, -0.2, 0);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p - 0.6, 0, -2);
	txt(0.8, 0);
	glVertex3d(p + a - 1.5, 0, -2);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0.1, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p, 0, -2);
	txt(0.8, 0);
	glVertex3d(p + a - 0.1, 0, -2);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0.2, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p, 0, -2);
	txt(0.8, 0);
	glVertex3d(p + a + 0.7, 0, -2);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p + 2, 0, -1.5);
	txt(0.8, 0);
	glVertex3d(p + a + 1, 0, -1.5);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0.2, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	txt(0.2, 0);
	glVertex3d(p + 1, 0, 0);
	txt(0.8, 0);
	glVertex3d(p + a + 1, 0, 0);
	txt(0.6, 1);
	glVertex3d(p + a - 15, 5, -dist - 22);
	txt(0.3, 1);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	ppm;

	nocull;
}

void DomeOfTheRock::drawRing(db innerR, db outerR, db height, int sectorCnt, int texture1, int texture2, bool isHalf) {

	glEnable(GL_TEXTURE_2D);
	pshm;
	db x1, x2, x3, x4, y1, y2, y3, y4, angle; int div = 1;
	if (isHalf) div = 2;
	for (float i = 0; i < sectorCnt / div; i++) {
		angle = 2 * (i / sectorCnt) * PI;
		x1 = innerR * cos(angle);
		y1 = innerR * sin(angle);
		x2 = outerR * cos(angle);
		y2 = outerR * sin(angle);
		angle = 2 * (++i / sectorCnt) * PI;
		x3 = innerR * cos(angle);
		y3 = innerR * sin(angle);
		x4 = outerR * cos(angle);
		y4 = outerR * sin(angle);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBegin(GL_QUADS);
		txt(0, 0);
		glVertex3d(x1, y1, height / 2.0);
		txt(0, 1);
		glVertex3d(x2, y2, height / 2.0);
		txt(1, 1);
		glVertex3d(x4, y4, height / 2.0);
		txt(1, 0);
		glVertex3d(x3, y3, height / 2.0);
		glEnd();

		angle = 2 * (++i / sectorCnt) * PI;
		x1 = innerR * cos(angle);
		y1 = innerR * sin(angle);
		x2 = outerR * cos(angle);
		y2 = outerR * sin(angle);

		glBindTexture(GL_TEXTURE_2D, texture2);
		glBegin(GL_QUADS);
		txt(0, 0);
		glVertex3d(x3, y3, height / 2);
		txt(0, 1);
		glVertex3d(x4, y4, height / 2);
		txt(1, 1);
		glVertex3d(x2, y2, height / 2);
		txt(1, 0);
		glVertex3d(x1, y1, height / 2);
		glEnd();
		i--;
	}
	ppm;
	glDisable(GL_TEXTURE_2D);
}

void DomeOfTheRock::drawPipe(db innerR, db outerR, db height, int sectorCnt, int textures[], bool isHalf, bool isArch = false) {
	//texture 2 and 3 for front ring, 4 and 5 for back ring, 6 for outer cylinder and 7 for the inner one

#pragma region front ring
	entxt; white;

	pshm;
	glNormal3f(0, 0, -1);
	cull;
	frontf;
	drawRing(innerR, outerR, -height, sectorCnt, textures[2], textures[3], isHalf);
	backf;
	nocull;
	ppm;
#pragma endregion
	entxt;
#pragma region outer cylinder
	if (!isArch) {
		pshm;
		Cylinder outerC = Cylinder(outerR, outerR, height, sectorCnt);
		outerC.setIsHalf(isHalf);
		cull;
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		outerC.drawSide();
		nocull;
		ppm;
	}
#pragma endregion

#pragma region inner cylinder
	pshm;
	Cylinder innerC = Cylinder(innerR, innerR, height, sectorCnt);
	innerC.setIsHalf(isHalf);
	innerC.reverseNormals();
	cull;
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	innerC.drawSide();
	nocull;
	ppm;
#pragma endregion

#pragma region back ring 
	pshm;
	glNormal3f(0, 0, 1);
	cull;
	drawRing(innerR, outerR, height, sectorCnt, textures[4], textures[5], isHalf);
	nocull;
	ppm;
#pragma endregion

	distxt;
	if (isHalf) {
		white;
		glNormal3f(0, -1, 0);
		cull;
		beg(GL_QUADS);
		glVertex3d(outerR, 0, height / 2.0);
		glVertex3d(innerR, 0, height / 2.0);
		glVertex3d(innerR, 0, -height / 2.0);
		glVertex3d(outerR, 0, -height / 2.0);
		endf;
		frontf;
		beg(GL_QUADS);
		glVertex3d(-outerR, 0, height / 2.0);
		glVertex3d(-innerR, 0, height / 2.0);
		glVertex3d(-innerR, 0, -height / 2.0);
		glVertex3d(-outerR, 0, -height / 2.0);
		endf;
		backf;
		nocull;
	}
}

void DomeOfTheRock::drawColumn(db pillarRadius, db pillarHeight, int texture, int sectorCnt, bool bracelets) {
	cull;
	entxt;
#pragma region main body
	pshm;
	Cylinder c = Cylinder(pillarRadius, pillarRadius, pillarHeight, sectorCnt);
	c.setUpAxis(2);
	glBindTexture(GL_TEXTURE_2D, texture);
	c.drawSide();
	ppm;

#pragma endregion

#pragma region bracelets
	if (bracelets)
	{
		pshm;
		glTranslated(0, -pillarHeight / 2.0 + 0.25, 0);
		white;
		Cylinder bracelet = Cylinder(pillarRadius + 0.01, pillarRadius + 0.01, 0.5, sectorCnt);
		bracelet.setUpAxis(2);
		glBindTexture(GL_TEXTURE_2D, PILLAR2);
		bracelet.drawSide();
		ppm;

		pshm;
		glTranslated(0, pillarHeight / 2.0 - 0.25, 0);
		bracelet.setUpAxis(2);
		glBindTexture(GL_TEXTURE_2D, PILLAR1);
		bracelet.drawSide();
		ppm;
		distxt;
	}
#pragma endregion
	nocull;
}

void DomeOfTheRock::drawEntrancePillar(db pillarRadius, db pillarHeight, db basesWidth, int texture) {
	pshm;
	glTranslated(5, pillarHeight / 2.0 + 1.401, 0);
#pragma region column
	drawColumn(pillarRadius, pillarHeight, texture);
#pragma endregion

#pragma region base
	pshm;
	int flag[6] = { 0,1,1,1,1,1};
	Box base;

	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 0.2, -3 * pillarRadius / 2.0);
	pshm;
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), PILLAR2, flag);
	ppm;

	pshm;
	glTranslated(0.1, -1, 0.1);
	base.drawOutside(Constraints(basesWidth - 0.2, 1, basesWidth - 0.2), ARCH5, flag);
	ppm;

	pshm;
	glTranslated(0, -1.2, 0);
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), PILLAR2, flag);
	ppm;

	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0, 0);
	glRotated(45, 0, 1, 0);
	entxt;
	Cylinder top = Cylinder(pillarRadius - 0.1, basesWidth - 0.5, 1.4, 4);
	top.setUpAxis(2);
	cull;
	glBindTexture(GL_TEXTURE_2D, PILLAR1);
	top.drawSide();
	nocull;

	distxt;
	ppm;

#pragma endregion
	ppm;
}

void DomeOfTheRock::drawArcadePillar(db pillarRadius, db pillarHeight, db basesWidth, int texture) {

	pshm;
	glTranslated(0, pillarHeight / 2.0 + 1.5 + 0.1, 0);
#pragma region body
	pshm;
	drawColumn(1.2, pillarHeight, texture);
	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.2, 0);
	int flag[6] = { 0,0,1,1,1,1 };
	pshm;
	glTranslated(-1.5, 0.7, -1.5);
	Box base;
	base.drawOutside(Constraints(3, 1.5, 3), ARCH5);
	ppm;
	glRotated(45, 0, 1, 0);
	entxt;
	Cylinder top = Cylinder(pillarRadius + 0.2, basesWidth - 1, 1.4, 4);
	top.setUpAxis(2);
	cull;
	glBindTexture(GL_TEXTURE_2D, PILLAR1);
	top.drawSide();
	nocull;
	distxt;
	ppm;

#pragma endregion

#pragma region base
	pshm;
	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 2, -3 * pillarRadius / 2.0);
	flag[1] = 1;
	base.drawOutside(Constraints(basesWidth, 2, basesWidth), PILLAR2, flag);
	ppm;
#pragma endregion

	ppm;
}

void DomeOfTheRock::drawDrumPillar(db pillarRadius, db pillarHeight, db basesWidth, int texture) {
	pshm;
	glTranslated(0, pillarHeight / 2.0 + basesWidth + 0.1, 0);
#pragma region body
	pshm;
	drawColumn(1.2, pillarHeight, texture);
	ppm;
#pragma endregion

	int flag[6] = { 0,1,1,1,1,1 };
#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.2, 0);

	pshm;
	glTranslated(-1.5, 0.7, -1.5);
	Box base;
	base.drawOutside(Constraints(3, 1.5, 3), ARCH5);
	ppm;
	glRotated(45, 0, 1, 0);
	entxt;
	Cylinder top = Cylinder(pillarRadius + 0.2, basesWidth - 1, 1.4, 4);
	top.setUpAxis(2);
	cull;
	glBindTexture(GL_TEXTURE_2D, PILLAR1);
	top.drawSide();
	nocull;
	distxt;
	ppm;

#pragma endregion

#pragma region base
	pshm;
	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 0.5, -3 * pillarRadius / 2.0);
	base.drawOutside(Constraints(basesWidth, 0.5, basesWidth), PILLAR2, flag);
	glTranslated(-0.25, -1.5, -0.25);
	base.drawOutside(Constraints(basesWidth + 0.5, 1.5, basesWidth + 0.5), PILLAR2, flag);

	ppm;
#pragma endregion

	ppm;
}

void DomeOfTheRock::drawEntrance(db doorWidth, db doorHeight) {


	/*db thirdPeiceOfPillarBase = 0.2, sideLengthOfPillarBase = 1.6;
	db overflownEdgesForTheBaseOfArch = 0.6;*/

	db archbaseHeight = 1; db outerR = 5, innerR = 4, archLength = 8.5;
	Constraints c(0, 0, 1.5);
	Box marbleGround, arch;
	int flag[6] = { 0,1,1,1,1,1 };
	int textures[] = { 0,0,0,0,0,0,0,0 };

	pshm;
#pragma region marble ground
	pshm;
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(22.5, 0.01, 0);
	textures[1] = MARBLE7; textures[2] = textures[3] = textures[4] = textures[5] = WHITE_STONE;
	marbleGround.drawOutside(Constraints(15, 0.2, archLength + 2), textures, flag);
	ppm;
#pragma endregion


#pragma region pillars
	white;
	pshm;
	glTranslated(20 - 0.5, 0.2, archLength + 0.5);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE1);
	ppm;

	pshm;
	glTranslated(20 - 0.5 + doorWidth + 1, 0.2, archLength + 0.5);
	drawEntrancePillar(0.5, 15.4, 1.7, MARBLE1);
	ppm;
#pragma endregion

	white;

	glTranslated(0, archbaseHeight, 0);
	flag[0] = 1; flag[2] = 0;

#pragma region bases of the arch 
	pshm;
	glTranslated(24 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), WHITE_STONE, flag);
	ppm;

	pshm;
	glTranslated(35 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), WHITE_STONE, flag);
	ppm;
#pragma endregion

#pragma region the arch
	pshm;
	//moving the arch to it's position
	glTranslated(30, 17.7, archLength / 2.0 + c.length + 0.1);
	textures[6] = LEAD; textures[7] = ARCH8;
	textures[2] = textures[3] = textures[4] = textures[5] = ARCH10;
	drawPipe(innerR + 1, outerR + 1, archLength, 24, textures, true);
	ppm;
#pragma endregion




	ppm;

}

void DomeOfTheRock::drawWalls(db openTheDoor) {

	//the main param is the length of the side: a, then every thing is drawn in the reverse order of the base ocatgon
	//the second param maybe the angle of door openeing

	Constraints c = Constraints(60, 37, 1.5);
	int textures[] = { 0,0,0,0,0,0 ,0,0 };
	Box wall, door, arch, marbleGround;
	db a = 60;
	db p = a / srt;

	//if (keys[VK_F1]) {
	//	if (openTheDoor < 90) openTheDoor += 2;
	//}
	//if (keys[VK_F2]) {
	//	if (openTheDoor > 0) openTheDoor -= 2;
	//}

#pragma region front side

#pragma region walls
	white;
	pshm;
	glTranslated(p, 0, 0);
	pshm;
	glTranslated(0, 17.7, 0);
	textures[2] = WALL2;
	textures[3] = WALL6;
	textures[1] = LEAD;
	wall.drawOutside(Constraints(60, 19.3, 1.5), textures);
	ppm;

	textures[2] = WALL1;
	textures[3] = WALL5;
	pshm;
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;
	textures[2] = -1;
	textures[3] = -1;
#pragma endregion

#pragma region entrance


	db doorWidth = 10; db doorHeight = 17.7;
	db archbaseHeight = 1; db outerR = 5, innerR = 4, archLength = 15;

	/*db thirdPeiceOfPillarBase = 0.2, sideLengthOfPillarBase = 1.6;
	db overflownEdgesForTheBaseOfArch = 0.6;*/

	//db umberellaWidth = 20;


	pshm;

#pragma region marble ground
	pshm;
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(0, 0.01, 0);
	textures[1] = MARBLE6; textures[2] = textures[3] = textures[4] = textures[5] = WHITE_STONE;
	marbleGround.drawOutside(Constraints(60, 0.2, archLength + 1), textures);
	ppm;
#pragma endregion

#pragma region pillars

	pshm;
	glTranslated(20 - 0.5, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE5);
	ppm;

	pshm;
	glTranslated(20 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE5);
	ppm;

	pshm;
	glTranslated(25 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;

	pshm;
	glTranslated(33.7 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;

	pshm;
	glTranslated(38.7 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;

	pshm;
	glTranslated(15 - 0.5, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;

	pshm;
	glTranslated(6.3 - 0.5, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;

	pshm;
	glTranslated(1.3 - 0.5, 0.2, archLength);
	drawEntrancePillar(0.5, 15.4, 1.6, MARBLE2);
	ppm;


#pragma endregion


	glTranslated(0, archbaseHeight, 0);

#pragma region bases of the arch 
	pshm;
	glTranslated(24 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), WHITE_STONE);
	ppm;

	pshm;
	glTranslated(35 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), WHITE_STONE);
	ppm;
#pragma endregion

#pragma region umbrellas
	textures[0] = textures[2] = textures[3] = textures[4] = textures[5] = textures[6] = WOOD; textures[1] = LEAD;
	pshm;
	glTranslated(5, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(20 - outerR + innerR - 0.6 / 2, archbaseHeight / 2.0, archLength), textures);
	ppm;

	pshm;
	glTranslated(60 - 5 - (20 - outerR + innerR - 0.6 / 2), doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(20 - outerR + innerR - 0.6 / 2, archbaseHeight / 2.0, archLength), textures);
	ppm;
#pragma endregion

#pragma region the arch
	textures[7] = ARCH8; textures[6] = LEAD; textures[2] = textures[3] = textures[4] = textures[5] = ARCH10;

	//moving the arch to it's position
	glTranslated(30, 17.7, 7.5 + c.length + 0.1);

	drawPipe(innerR + 1, outerR + 1, archLength, 24, textures, true);
#pragma endregion


	textures[7] = textures[6] = LEAD; textures[2] = textures[3] = textures[4] = textures[5] = -1;


	ppm;

#pragma endregion


#pragma region doors

	//the left door
	pshm;
	textures[0] = textures[1] = textures[4] = textures[5] = DOOR3;
	glTranslated(25, 0, 0);
	textures[2] = DOOR1; textures[3] = DOOR2;
	glRotated(openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glTranslated(35, 0, 0);
	glRotated(-openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	textures[3] = DOOR1; textures[2] = DOOR2;
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;
	textures[0] = textures[1] = textures[4] = textures[5] = textures[2] = textures[3] = -1;


#pragma endregion


	ppm;
#pragma endregion

#pragma region left wing of the front side
	pshm;
	glTranslated(p, 0.01, c.length);
	glRotated(135, 0, 1, 0);
	white;
	textures[3] = WALL3;
	textures[2] = WALL4;
	textures[1] = LEAD;
	wall.drawOutside(c, textures);
	textures[3] = -1;
	textures[2] = -1;
	ppm;
#pragma endregion

#pragma region left side

	pshm;
	glTranslated(0, 0, -p + c.length);
	glRotated(90, 0, 1, 0);
	glColor3f(1, 1, 1);

#pragma region walls
	pshm;
	glTranslated(0, 17.7, 0);
	textures[3] = WALL2;
	textures[2] = WALL6;
	textures[1] = LEAD;
	wall.drawOutside(Constraints(60, 19.3, 1.5), textures);
	ppm;

	pshm;
	textures[3] = WALL1;
	textures[2] = WALL5;
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;
	textures[3] = -1;
	textures[2] = -1;

#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 17.7);
	ppm;
#pragma endregion

#pragma region doors

	textures[0] = textures[1] = textures[4] = textures[5] = DOOR3;

	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glTranslated(25, 0, 0);
	textures[2] = DOOR1; textures[3] = DOOR2;
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	textures[3] = DOOR1; textures[2] = DOOR2;
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;
	textures[0] = textures[1] = textures[4] = textures[5] = textures[2] = textures[3] = -1;
	ppm;
#pragma endregion

	ppm;
#pragma endregion

#pragma region left wing of the back side
	pshm;
	glTranslated(0, 0, -p - a + c.length);
	glRotated(45, 0, 1, 0);
	white;
	textures[3] = WALL3;
	textures[2] = WALL4;
	textures[1] = LEAD;
	wall.drawOutside(c, textures);
	textures[3] = -1;
	textures[2] = -1;
	ppm;
#pragma endregion

#pragma region back side

	pshm;
	glTranslated(p, 0, -2 * p - a + c.length);
	glColor3f(1, 1, 1);
#pragma region walls
	pshm;
	glTranslated(0, 17.7, 0);
	textures[3] = WALL2;
	textures[2] = WALL6;
	textures[1] = LEAD;
	wall.drawOutside(Constraints(60, 19.3, 1.5), textures);
	ppm;

	pshm;
	textures[3] = WALL1;
	textures[2] = WALL5;
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;
	textures[3] = -1;
	textures[2] = -1;
#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 17.7);
	ppm;
#pragma endregion

#pragma region doors

	textures[0] = textures[1] = textures[4] = textures[5] = DOOR3;

	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glTranslated(25, 0, 0);
	textures[2] = DOOR1; textures[3] = DOOR2;
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	textures[3] = DOOR1; textures[2] = DOOR2;
	glTranslated(-5, 0, 0);
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;
	ppm;
	textures[0] = textures[1] = textures[4] = textures[5] = textures[2] = textures[3] = -1;
#pragma endregion

	ppm;
#pragma endregion

#pragma region right wing of the back side
	pshm;
	glTranslated(p + a, 0, -2 * p - a + c.length);
	glRotated(-45, 0, 1, 0);
	white;
	textures[3] = WALL3;
	textures[2] = WALL4;
	textures[1] = LEAD;
	wall.drawOutside(c, textures);
	textures[3] = -1;
	textures[2] = -1;
	ppm;
#pragma endregion

#pragma region right side
	pshm;
	glTranslated(2 * p + a, 0, -p - a + c.length);
	glRotated(-90, 0, 1, 0);
	glColor3f(1, 1, 1);

#pragma region walls
	pshm;
	glTranslated(0, 17.7, 0);
	textures[3] = WALL2;
	textures[2] = WALL6;
	textures[1] = LEAD;
	wall.drawOutside(Constraints(60, 19.3, 1.5), textures);
	ppm;

	pshm;
	textures[3] = WALL1;
	textures[2] = WALL5;
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 17.7, 1.5), textures);
	ppm;
	textures[3] = -1;
	textures[2] = -1;
#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 17.7);
	ppm;
#pragma endregion

#pragma region doors
	textures[0] = textures[1] = textures[4] = textures[5] = DOOR3;

	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glTranslated(25, 0, 0);
	textures[2] = DOOR1; textures[3] = DOOR2;
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	textures[3] = DOOR1; textures[2] = DOOR2;
	door.drawOutside(Constraints(5, 17.7, 0.5), textures);
	ppm;

	ppm;
	textures[0] = textures[1] = textures[4] = textures[5] = textures[2] = textures[3] = -1;
#pragma endregion

	ppm;

#pragma endregion

#pragma region right wing of the front side
	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);
	glRotated(-135, 0, 1, 0);
	white;
	textures[3] = WALL3;
	textures[2] = WALL4;
	textures[1] = LEAD;
	wall.drawOutside(c, textures);
	textures[3] = -1;
	textures[2] = -1;
	ppm;
#pragma endregion

#pragma region carpet

	db numOfUnits = 30;
	db side = numOfUnits * (srt / (1 + srt));
	db point = side / srt;
	db num = 0.5;
	entxt;
	glBindTexture(GL_TEXTURE_2D, CARPET);
	glNormal3f(0, 7, 0);
	glBegin(GL_POLYGON);
	txt(point, 0);
	glVertex3d(p, 0.1, 0);
	txt(point + side, 0);
	glVertex3d(p + a, 0.1, 0);
	txt(2 * point + side, num * point);
	glVertex3d(2 * p + a, 0.1, -p);
	txt(2 * point + side, (point + side) * num);
	glVertex3d(2 * p + a, 0.1, -p - a + c.length);
	txt(point + side, (2 * point + side) * num);
	glVertex3d(p + a, 0.1, -2 * p - a + c.length);
	txt(point, (2 * point + side) * num);
	glVertex3d(p, 0.1, -2 * p - a + c.length);
	txt(0, (point + side) * num);
	glVertex3d(0, 0.1, -p - a + c.length);
	txt(0, num * point);
	glVertex3d(0, 0.1, -p);
	glEnd();
	distxt;
#pragma endregion


}

void DomeOfTheRock::drawArcadeSide() {

	int textures[8] = { 0,0,0,0,0,0,0,0 }; db h = 20;
	db pillarH = h + 3 + 2.5;

#pragma region bridge
	Box bridge;
	pshm;
	glTranslated(0, pillarH, 0);
	int flag[6] = { 1,1,1,1,0,0 };
	textures[0] = textures[1] = BRIDGE2;
	textures[2] = textures[3] = BRIDGE1;
	white;
	bridge.drawOutside(Constraints(48, 1.5, 3), textures, flag);
	ppm;
#pragma endregion

#pragma region archs
	entxt;

	textures[0] = textures[1] = ARCH1;
	textures[2] = textures[3] = textures[4] = textures[5] = ARCH2;
	textures[6] = textures[7] = ARCH3;

	db sectorCnt = sectorCntForArchs;
	pshm;
	glTranslated(24, 1.5 + pillarH, 1.5);
	drawArch(6.5, 8, 3,textures,sectorCnt);
	ppm;
	/////////////////////////////////////////////////
	pshm;
	glTranslated(8, 1.5 + pillarH, 1.5);
	drawArch(6.5, 8, 3,textures, sectorCnt);
	ppm;
	/////////////////////////////////////////////
	pshm;
	glTranslated(40, 1.5 + pillarH, 1.5);
	drawArch(6.5, 8, 3,textures, sectorCnt);
	ppm;
#pragma endregion

#pragma region pillars
	h += 1;
	pshm;
	glTranslated(16, 0.5, 1.5);
	drawArcadePillar(1, h, 3, MARBLE3);
	ppm;

	pshm;
	glTranslated(32, 0.5, 1.5);
	drawArcadePillar(1, h, 3, MARBLE4);
	ppm;
#pragma endregion

}

void DomeOfTheRock::drawArcade() {

	int textures = TIER4;
	Constraints c = Constraints(48, 1.5, 3);
	db a = c.width;
	db p = a / srt;
	Box tier;
	int flag[6] = { 0,0,1,1,1,1 };

	white;

	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);
	glRotated(-135, 0, 1, 0);

	pshm;
	glTranslated(a, 0, 0);
	glRotated(-22.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	ppm;

	///the front face
	pshm;
	glTranslated(p, 0.1, 0);
	drawArcadeSide();
	ppm;

	///the left wing of the front 
	pshm;
	glTranslated(p, 0, c.length);

	pshm;
	glRotated(157.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(135, 0, 1, 0);
	drawArcadeSide();
	ppm;

	///the left side

	pshm;

	glTranslated(0, 0.1, -p + c.length);

	pshm;
	glRotated(112.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(90, 0, 1, 0);
	drawArcadeSide();

	ppm;

	///the left wing of the  back
	pshm;

	glTranslated(0, 0, -p - a + c.length);

	pshm;
	glRotated(67.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(45, 0, 1, 0);
	drawArcadeSide();

	ppm;

	///the back face
	pshm;
	glTranslated(p, 0.1, -2 * p - a + c.length);

	pshm;
	glRotated(22.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	drawArcadeSide();

	ppm;

	///the right wing of the back
	pshm;
	glTranslated(p + a, 0, -2 * p - a + c.length);

	pshm;
	glRotated(-22.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(-45, 0, 1, 0);
	drawArcadeSide();
	ppm;

	///the right side
	pshm;
	glTranslated(2 * p + a, 0.1, -p - a + c.length);

	pshm;
	glRotated(-67.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(-90, 0, 1, 0);
	drawArcadeSide();

	ppm;

	///the right wing of the front 
	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);

	pshm;
	glRotated(-112.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures, flag);
	ppm;

	glRotated(-135, 0, 1, 0);
	drawArcadeSide();
	ppm;
}

void DomeOfTheRock::drawDrum() {

	db innerR = 33, outerR = 36, Outerheight = 3;
	int textures[8] = { 0,0, 0,0,0,0,0,0 };
	int flag[6] = { 0,1,1,1,1,1 };
	glTranslated(0, 28, 0);


	white;
	pshm;
	cull;
	glTranslated(0, Outerheight / 2.0 + 5.65, 0);
	pshm;
	entxt;
	glTranslated(0, 8.6 * 47 / 20.0, 0);
	glBindTexture(GL_TEXTURE_2D, DRUM2);
	Cylinder drum = Cylinder(33, 33, 38, 20, 1);
	drum.setUpAxis(2);
	drum.reverseNormals();
	drum.drawSide();
	ppm;
	pshm;
	drum.reverseNormals();
	glTranslated(0, 2.4, 0);
	drum.set(36, 36, 2.5, 20, 1, true, 2);
	glBindTexture(GL_TEXTURE_2D, DRUM1);
	drum.drawSide();
	ppm;
	pshm;
	glTranslated(0, 13, 0);
	drum.set(36, 36, 17, 28, 1, true, 2);
	glBindTexture(GL_TEXTURE_2D, DRUM3);
	drum.drawSide();
	ppm;
	nocull;
	ppm;

	distxt;


	Box tier;
	int i = 0;
	for (db angle = 9; angle <= 360; angle += 18) {
		i++;
		if (i % 5) {
			pshm;
			glRotated(angle, 0, 1, 0);
			glTranslated(0, 2.8, -innerR * sin(11.25) + 2.13);
			textures[0] = ARCH1;
			textures[1] = ARCH4;
			textures[7] = ARCH7;
			textures[2] = textures[5] = ARCH5;
			textures[3] = textures[4] = ARCH6;
			drawArch(4.65, 5.65, 3, textures, 28);
			ppm;
		}
		else {
			pshm;
			glRotated(angle, 0, 1, 0);
			textures[2] = TIER3; textures[3] = TIER1;
			textures[4] = textures[5] = TIER2;

			glTranslated(-7, -28, -innerR * sin(11.25) - 0.3);
			tier.drawOutside(Constraints(15, 36.7, 6), textures, flag);
			textures[3] = DRUM4;
			textures[4] = textures[5] = DRUM5;
			glTranslated(2, 40, 3.5);
			tier.drawOutside(Constraints(10, 16.5, 3), textures);
			ppm;
		}
	}


	i = 0; int texture; white;
	for (db angle = 18; angle <= 360; angle += 18) {
		i++;
		if (i % 5 != 0 && i % 5 != 4)
		{
			if (i % 5 == 1) texture = MARBLE1;
			else if (i % 5 == 2) texture = MARBLE5;
			else texture = MARBLE2;
			pshm;
			glRotated(angle, 0, 1, 0);
			glTranslated(outerR - 1.5, -29, 0);
			drawDrumPillar(1, 26.3, 3, texture);
			ppm;
		}
	}
}

void DomeOfTheRock::drawFence(db heightOfWall) {

#pragma region Rock
	white;
	glNormal3f(0, 1, 0);
	entxt;
	glBindTexture(GL_TEXTURE_2D, ROCK2);
	//first topological tier
	db h1 = 0, h2 = 2;
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(-5, h1, 27);
	txt(0, 1);
	glVertex3d(-2, h2, 23);
	txt(2, 1);
	glVertex3d(0, h1, 27);
	txt(2, 0);
	glVertex3d(1, h2, 23);
	txt(0, 0);
	glVertex3d(7, h1, 25.5);
	txt(0, 1);
	glVertex3d(5, h2, 22);
	txt(2, 1);
	glVertex3d(14, h1, 20);
	txt(2, 0);
	glVertex3d(12, h2, 18);
	txt(0, 0);
	glVertex3d(20, h1, 12);
	txt(0, 1);
	glVertex3d(18, h2, 10);
	txt(2, 1);
	glVertex3d(22, h1, 7);
	txt(2, 0);
	glVertex3d(20, h2, 4);
	txt(0, 0);
	glVertex3d(18, h1, -10);
	txt(0, 1);
	glVertex3d(11, h2, -10);
	txt(2, 1);
	glVertex3d(7, h1, -22);
	txt(2, 0);
	glVertex3d(4, h2, -18);
	txt(0, 0);
	glVertex3d(-14, h1, -24);
	txt(0, 2);
	glVertex3d(-10, h2, -15);
	txt(3, 2);
	glVertex3d(-17, h1, 20);
	txt(3, 0);
	glVertex3d(-14, h2, 16);
	txt(0, 0);
	glVertex3d(-5, h1, 20);
	txt(0, 1);
	glVertex3d(-2, h2, 17);
	txt(2, 1);
	glVertex3d(-5, h1, 27);
	txt(2, 0);
	glVertex3d(-2, h2, 23);
	endf;

	h1 = 2; h2 = 3.2;
	glBindTexture(GL_TEXTURE_2D, ROCK1);
	glNormal3f(0, 1, 0);
	//second topological tier
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(-2, h1, 23);
	txt(0, 1);
	glVertex3d(1, h2, 20);
	txt(2, 1);
	glVertex3d(1, h1, 23);
	txt(2, 0);
	glVertex3d(3, h2, 20);
	txt(0, 0);
	glVertex3d(5, h1, 22);
	txt(0, 1);
	glVertex3d(5, h2, 18);
	txt(2, 1);
	glVertex3d(12, h1, 18);
	txt(2, 0);
	glVertex3d(8, h2, 15);
	txt(0, 0);
	glVertex3d(18, h1, 10);
	txt(0, 1);
	glVertex3d(12, h2, 10);
	txt(2, 1);
	glVertex3d(20, h1, 4);
	txt(2, 0);
	glVertex3d(12, h2, 4);
	txt(0, 0);
	glVertex3d(11, h1, -10);
	txt(0, 1);
	glVertex3d(8, h2, -3);
	txt(2, 1);
	glVertex3d(4, h1, -18);
	txt(2, 0);
	glVertex3d(4, h2, -13);
	txt(0, 0);
	glVertex3d(-10, h1, -15);
	txt(0, 1);
	glVertex3d(-7, h2, -10);
	txt(2, 1);
	glVertex3d(-14, h1, 16);
	txt(2, 0);
	glVertex3d(-12, h2, 12);
	txt(0, 0);
	glVertex3d(-2, h1, 17);
	txt(0, 1);
	glVertex3d(0, h2, 14);
	txt(2, 1);
	glVertex3d(-2, h1, 23);
	txt(2, 0);
	glVertex3d(1, h2, 20);
	endf;


	//distxt;

	h1 = 3.2; h2 = 4;
	glNormal3f(0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ROCK2);

	//third topological tier
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(1, h1, 20);
	txt(0, 1);
	glVertex3d(2, h2, 15);
	txt(2, 1);
	glVertex3d(3, h1, 20);
	txt(2, 0);
	glVertex3d(3, h2, 16);
	txt(0, 0);
	glVertex3d(5, h1, 18);
	txt(0, 1);
	glVertex3d(5, h2, 14);
	txt(2, 1);
	glVertex3d(8, h1, 15);
	txt(2, 0);
	glVertex3d(8, h2, 10);
	txt(0, 0);
	glVertex3d(12, h1, 10);
	txt(0, 1);
	glVertex3d(10, h2, 7);
	txt(2, 1);
	glVertex3d(12, h1, 4);
	txt(2, 0);
	glVertex3d(10, h2, 3);
	txt(0, 0);
	glVertex3d(8, h1, -3);
	txt(0, 1);
	glVertex3d(6, h2, 0);
	txt(2, 1);
	glVertex3d(4, h1, -13);
	txt(2, 0);
	glVertex3d(4, h2, -7);
	txt(0, 0);
	glVertex3d(-7, h1, -10);
	txt(0, 1);
	glVertex3d(-4, h2, -2);
	txt(2, 1);
	glVertex3d(-12, h1, 12);
	txt(2, 0);
	glVertex3d(-6, h2, 9);
	txt(0, 0);
	glVertex3d(0, h1, 14);
	txt(0, 1);
	glVertex3d(1, h2, 12);
	txt(2, 1);
	glVertex3d(1, h1, 20);
	txt(2, 0);
	glVertex3d(2, h2, 15);
	endf;

	//4th topological layers
	h1 = 4; h2 = 4.5;
	glNormal3f(0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ROCK1);
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(5, h1, 14);
	txt(0, 1);
	glVertex3d(5, h2, 11);
	txt(1, 1);
	glVertex3d(8, h1, 10);
	txt(1, 0);
	glVertex3d(5, h2, 10);
	txt(0, 0);
	glVertex3d(10, h1, 7);
	txt(0, 1);
	glVertex3d(6, h2, 7);
	txt(1, 1);
	glVertex3d(10, h1, 3);
	txt(1, 0);
	glVertex3d(7, h2, 3);
	txt(0, 0);
	glVertex3d(6, h1, 0);
	txt(0, 1);
	glVertex3d(6, h2, 2);
	txt(1, 1);
	glVertex3d(4, h1, -7);
	txt(1, 0);
	glVertex3d(4, h2, 0);
	txt(0, 0);
	glVertex3d(-4, h1, -2);
	txt(0, 1);
	glVertex3d(1, h2, 2);
	txt(1, 1);
	glVertex3d(-4, h1, -2);
	txt(1, 0);
	glVertex3d(-2, h2, 3);
	txt(0, 0);
	glVertex3d(-6, h1, 9);
	txt(0, 1);
	glVertex3d(1, h2, 8);
	txt(1, 1);
	glVertex3d(1, h1, 12);
	txt(1, 0);
	glVertex3d(2, h2, 10);
	txt(0, 0);
	glVertex3d(2, h1, 15);
	txt(0, 1);
	glVertex3d(3, h2, 11);
	txt(1, 1);
	glVertex3d(3, h1, 16);
	txt(1, 0);
	glVertex3d(5, h2, 11);
	txt(0, 0);
	glVertex3d(5, h1, 14);
	endf;

	h1 = 4.5; h2 = 4.7;
	//fifth topological tier
	glNormal3f(0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, ROCK2);
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(-2, h1, 3);
	txt(0, 1);
	glVertex3d(2, h2, 5);
	txt(1, 1);
	glVertex3d(1, h1, 8);
	txt(1, 0);
	glVertex3d(2, h2, 7);
	txt(0, 0);
	glVertex3d(2, h1, 10);
	txt(0, 1);
	glVertex3d(3, h2, 10.5);
	txt(1, 1);
	glVertex3d(3, h1, 11);
	txt(1, 0);
	glVertex3d(3.5, h2, 10);
	txt(0, 0);
	glVertex3d(3, h1, 11);
	txt(0, 1);
	glVertex3d(4, h2, 10.5);
	txt(1, 1);
	glVertex3d(5, h1, 11);
	txt(1, 0);
	glVertex3d(4, h2, 10.5);
	txt(0, 0);
	glVertex3d(5, h1, 10);
	txt(0, 1);
	glVertex3d(5, h2, 8);
	txt(1, 1);
	glVertex3d(6, h1, 7);
	txt(1, 0);
	glVertex3d(5, h2, 7);
	txt(0, 0);
	glVertex3d(7, h1, 3);
	txt(0, 1);
	glVertex3d(5, h2, 3);
	txt(1, 1);
	glVertex3d(6, h1, 2);
	txt(1, 0);
	glVertex3d(4, h2, 3);
	txt(0, 0);
	glVertex3d(4, h1, 0);
	txt(0, 1);
	glVertex3d(3, h2, 5);
	txt(1, 1);
	glVertex3d(1, h1, 2);
	txt(1, 0);
	glVertex3d(2, h2, 5);
	txt(0, 0);
	glVertex3d(-2, h1, 3);
	txt(0, 1);
	glVertex3d(2, h2, 7);
	endf;

	h1 = 4.7; h2 = 5;
	glBindTexture(GL_TEXTURE_2D, ROCK1);
	glNormal3f(0, 1, 0);
	//sixth topological tier
	beg(GL_TRIANGLE_STRIP);
	txt(0, 0);
	glVertex3d(4, h1, 3);
	txt(0, 1);
	glVertex3d(4, h2, 7);
	txt(1, 1);
	glVertex3d(3, h1, 5);
	txt(1, 0);
	glVertex3d(4, h2, 7);
	txt(0, 0);
	glVertex3d(2, h1, 5);
	txt(0, 1);
	glVertex3d(4, h2, 7);
	txt(1, 1);
	glVertex3d(2, h1, 7);
	txt(1, 0);
	glVertex3d(4, h2, 7);
	txt(0, 0);
	glVertex3d(3, h1, 10.5);
	txt(0, 1);
	glVertex3d(4, h2, 7);
	txt(1, 1);
	glVertex3d(3.5, h1, 10);
	txt(1, 0);
	glVertex3d(4, h2, 7);
	txt(0, 0);
	glVertex3d(4, h1, 10.5);
	txt(0, 1);
	glVertex3d(4, h2, 7);
	txt(1, 1);
	glVertex3d(5, h1, 8);
	txt(1, 0);
	glVertex3d(4, h2, 7);
	txt(0, 0);
	glVertex3d(5, h1, 7);
	txt(0, 1);
	glVertex3d(4, h2, 7);
	txt(1, 1);
	glVertex3d(5, h1, 3);
	txt(1, 0);
	glVertex3d(4, h2, 7);
	txt(0, 0);
	glVertex3d(4, h1, 3);
	endf;

	//glDisable(GL_LIGHTING);
#pragma endregion

#pragma region Fence

#pragma region feet place

	int textures[8] = { 0,FOOT3,FOOT2,FOOT1,FOOT2,FOOT2,0,0 };
	pshm;
	int flag[6] = { 0,1,1,1,1,1 };
	white;
	Box feet;
	glTranslated(-18.5, 0, 18.5);
	feet.drawOutside(Constraints(3, 10, 3), textures, flag);
	
	pshm;
	glTranslated(1.5, 10.1, 1.5);
	glRotated(45, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	textures[2] = textures[3] = textures[4] = textures[5] = DOME3;
	textures[6] = textures[7] = FOOT6;
	drawPipe(2, 2.3, 0.35, 4,textures,false);
	ppm;

	entxt;
	glBindTexture(GL_TEXTURE_2D, FOOT4);
	Cylinder top = Cylinder(1.1, 1.1, 1.5, 8, 1, false, 2, false, true);
	pshm;
	cull;
	glTranslated(1.5, 10.8, 1.5);
	glDisable(GL_LIGHTING);
	top.draw();
	glEnable(GL_LIGHTING);
	glTranslated(0, 0.96, 0);
	glBindTexture(GL_TEXTURE_2D, FOOT5);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.225, Color(255, 255, 255), 8, false, false, false);
	nocull;
	ppm;
	distxt;
	ppm;

#pragma endregion

#pragma region woodenFence

	textures[0] = 0;
	db texturesCntS[6]; db texturesCntT[6] = { 1,1,1,1,1,1 };
	texturesCntS[5] = texturesCntS[4] = texturesCntS[0] = texturesCntS[1] = 1;


	Box fence;

	///marble fence

	textures[1] = textures[4] = textures[5] = ARCH5;
	textures[3] = MARBLE_FENCE;
	textures[2] = ARCH5;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 3;
	glTranslated(-17, 0, 19.5);
	fence.drawOutside(Constraints(12, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;


	///wood

	textures[1] =textures[4] = textures[5] = FENCE1;
	textures[2] = textures[3] = FENCE;
	pshm;
	texturesCntS[2] = texturesCntS[3] =8;
	glTranslated(-14, 0, -24);
	glRotated(-93.9, 0, 1, 0);
	fence.drawOutside(Constraints(44, heightOfWall, 0.5),textures,texturesCntS,texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 2;
	glTranslated(-4.5, 0, 19.5);
	glRotated(-90, 0, 1, 0);
	fence.drawOutside(Constraints(7, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3]  = 1;
	glTranslated(-5, 0, 26.5);
	fence.drawOutside(Constraints(5, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 1.5;
	glTranslated(0, 0, 26.5);
	glRotated(12.1, 0, 1, 0);
	fence.drawOutside(Constraints(7.15891, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 2;
	glTranslated(20, 0, 12);
	glRotated(-126.9, 0, 1, 0);
	fence.drawOutside(Constraints(10, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;


	pshm;
	texturesCntS[2] = texturesCntS[3] = 1;
	glTranslated(22, 0, 7);
	glRotated(-111.8, 0, 1, 0);
	fence.drawOutside(Constraints(5.38516, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 4;
	glTranslated(18, 0, -10);
	glRotated(-76.8, 0, 1, 0);
	fence.drawOutside(Constraints(17.4642, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 3;
	glTranslated(7, 0, -22);
	glRotated(-47.5, 0, 1, 0);
	fence.drawOutside(Constraints(16.2788, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;

	pshm;
	texturesCntS[2] = texturesCntS[3] = 3;
	glTranslated(-14, 0, -24);
	glRotated(-5.4, 0, 1, 0);
	fence.drawOutside(Constraints(21.095, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;


	///glass
	pshm;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255, 255, 255, 60);
	pshm;
	texturesCntS[2] = texturesCntS[3] = 1;
	textures[0] = textures[1] = textures[2] = textures[3] = textures[4] = textures[5] = 0;
	glTranslated(14, 0, 20);
	glRotated(-141.8, 0, 1, 0);
	fence.drawOutside(Constraints(8.90225, heightOfWall, 0.5), textures, texturesCntS, texturesCntT);
	ppm;
	glDisable(GL_BLEND);
	ppm;
#pragma endregion


#pragma endregion

}

void DomeOfTheRock::drawDomes() {

	int textures[] = { 0,0,0,0,0,0,0,0 };
	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	entxt;
	glBindTexture(GL_TEXTURE_2D, DOME2);
	mosqueDrawer.drawDome(Point(p + a / 2.0, 67.3, -p - a / 2.0), 7.5, Color(255, 255, 255), 36, false, false);

	pshm;
	entxt;
	cull;
	glTranslated(0, -0.32, 0);
	glBindTexture(GL_TEXTURE_2D, DOME1);
	mosqueDrawer.drawDome(Point(p + a / 2.0, 68.3, -p - a / 2.0), 7.1, Color(255, 255, 255), 36, true, false,true,false);
	distxt;
	nocull;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 57, -p - a / 2.0);
	glRotated(90, 1, 0, 0);
	textures[2] = textures[3] = textures[4] = textures[4] = textures[5] = textures[6] = textures[7] = DOME3;
	drawPipe(35.5, 38, 1, 36, textures, false);
	ppm;
}

void DomeOfTheRock::drawOctagon(const Constraints& c, int textures[]) {
	//the main param is the length of the side: a, then every thing is drawn in the reverse order of the base ocatgon
	//the second param maybe the angle of door openeing

	Box wall, door;
	db a = c.width;
	db p = a / srt;

	///the front face
	pshm;
	glTranslated(p, 0.1, 0);
	wall.drawOutside(c, textures);
	ppm;

	///the left wing of the front 
	pshm;
	glTranslated(p, 0, c.length);
	glRotated(135, 0, 1, 0);
	glColor3f(0.5, 0.5, 0.5);
	wall.drawOutside(c, textures);
	ppm;

	///the left side

	pshm;

	glTranslated(0, 0.1, -p + c.length);
	glRotated(90, 0, 1, 0);
	glColor3f(1, 1, 1);
	wall.drawOutside(c, textures);

	ppm;

	///the left wing of the  back
	pshm;

	glTranslated(0, 0, -p - a + c.length);
	glRotated(45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	wall.drawOutside(c, textures);

	ppm;

	///the back face
	pshm;
	glTranslated(p, 0.1, -2 * p - a + c.length);
	glColor3f(1, 1, 1);
	wall.drawOutside(c, textures);

	ppm;

	///the right wing of the back
	pshm;
	glTranslated(p + a, 0, -2 * p - a + c.length);
	glRotated(-45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	wall.drawOutside(c, textures);
	ppm;

	///the right side
	pshm;
	glTranslated(2 * p + a, 0.1, -p - a + c.length);
	glRotated(-90, 0, 1, 0);
	glColor3f(1, 1, 1);
	wall.drawOutside(c, textures);

	ppm;

	///the right wing of the front 
	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);
	glRotated(-135, 0, 1, 0);
	glColor3f(0.1, 0.1, 0.1);
	wall.drawOutside(c, textures);
	ppm;
}

void DomeOfTheRock::draw(db openTheDoor) {


	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	int sectorCnt = 36; int radius = 4; int radius2 = 5;
	white;


	pshm;
	drawInnerRoof();
	drawLeadRoof();
	drawDomes();
	glTranslated(0, 0.1, 0);
	white;
	drawWalls(openTheDoor);
	ppm;



	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(55, 0, 1, 0);
	drawDrum();
	ppm;

	pshm;
	//moving the outer octagon to the base of the outer octagon 
	glTranslated(p - p2, 0, -inner.length);
	//move to the middle of the outer oct depending on the diameters of the oct
	glTranslated((a - b) / 2.0, 0, -(dia - dia2) / 2.0);
	drawArcade();
	ppm;

	pshm;
	glTranslated(p + a / 2.0 + 1, 0.2, -p - a / 2.0 - 2);
	db heightOfWall = 4;
	drawFence(heightOfWall);
	ppm;
}

void DomeOfTheRock::draw() {
	glCallList(domeOfTheRockDisplayList);
}


//other domes

void DomeOfTheRock::drawDomeOfSoulsPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture) {

	//db pillarHeight = 4, pillarRadius = 0.1; db basesWidth = 0.6;
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.1 + 0.3, 0);
#pragma region column
	drawColumn(pillarRadius, pillarHeight, texture, 10, false);
#pragma endregion

#pragma region base
	pshm;
	int flag[6] = { 0,1,1,1,1,1 };
	Box base;

	pshm;
	glTranslated(0, -pillarHeight / 2.0 - 0.1, 0);
	Cylinder coneBase = Cylinder(basesWidth / 2.0, pillarRadius, 0.3, 4, 1, true, 2);
	coneBase.drawSide();
	ppm;

	pshm;
	glRotated(45, 0, 1, 0);
	glTranslated(-(basesWidth - 0.15) / 2.0, -pillarHeight / 2.0 - 0.35, -(basesWidth - 0.15) / 2.0);
	base.drawOutside(Constraints(basesWidth - 0.15, 0.1, basesWidth - 0.15), texture, flag);
	ppm;
	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0, 0);
	Sphere topSphere = Sphere(0.18);
	entxt;
	glBindTexture(GL_TEXTURE_2D, texture);
	topSphere.draw();
	distxt;
	glRotated(45, 0, 1, 0);
	glTranslated(0, 0.1, 0);
	glTranslated(-(basesWidth - 0.3) / 2.0, 0.02, -(basesWidth - 0.3) / 2.0);
	base.drawOutside(Constraints(basesWidth - 0.3, 0.08, basesWidth - 0.3), texture);
	ppm;

#pragma endregion
	ppm;
}

void DomeOfTheRock::drawDomeOfAscentionPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture) {

	//db pillarHeight = 4, pillarRadius = 0.1; db basesWidth = 0.6;
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.1 + 0.3, 0);
#pragma region column
	drawColumn(pillarRadius, pillarHeight, texture, 10);
#pragma endregion

#pragma region base

	pshm;
	glTranslated(0, -pillarHeight / 2.0 - 0.1, 0);
	Cylinder coneBase = Cylinder((basesWidth - 0.1) / 2.0, (basesWidth - 0.1) / 2.0, 0.6, 6, 1, true, 2);
	coneBase.draw();
	ppm;
#pragma endregion

#pragma region top

	bool flag[6] = { 1,0,0,0,0,0 };
	Box base;

	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.1, 0);
	entxt;
	coneBase.set(pillarRadius + 0.01, basesWidth / 2.0 - 0.1, 0.3, 4, 1, true, 2);
	glBindTexture(GL_TEXTURE_2D, texture);
	coneBase.drawSide();
	distxt;
	glRotated(45, 0, 1, 0);
	glTranslated(0, 0.1, 0);
	glTranslated(-(basesWidth - 0.3) / 2.0, 0.02, -(basesWidth - 0.3) / 2.0);
	base.drawOutside(Constraints(basesWidth - 0.3, 0.08, basesWidth - 0.3), texture);
	ppm;

#pragma endregion
	ppm;
}

void DomeOfTheRock::drawDomeOfThePorphetPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture) {

	//db pillarHeight = 4, pillarRadius = 0.1; db basesWidth = 0.6;
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.1 + 0.3, 0);
#pragma region column
	drawColumn(pillarRadius, pillarHeight, texture, 10);
#pragma endregion

#pragma region base
	pshm;
	int flag[6] = { 0,1,1,1,1,1 };
	Box base;

	pshm;
	glTranslated(0, -pillarHeight / 2.0 - 0.1, 0);
	Cylinder coneBase = Cylinder(basesWidth / 2.0, pillarRadius, 0.3, 4, 1, true, 2);
	coneBase.drawSide();
	ppm;

	pshm;
	glRotated(45, 0, 1, 0);
	glTranslated(-(basesWidth - 0.15) / 2.0, -pillarHeight / 2.0 - 0.35, -(basesWidth - 0.15) / 2.0);
	base.drawOutside(Constraints(basesWidth - 0.15, 0.1, basesWidth - 0.15), texture, flag);
	ppm;
	ppm;
#pragma endregion

#pragma region top

	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.1, 0);
	entxt;
	coneBase.set(pillarRadius + 0.01, basesWidth / 2.0 - 0.1, 0.3, 4, 1, true, 2);
	glBindTexture(GL_TEXTURE_2D, LIME_STONE2);
	coneBase.drawSide();
	distxt;
	glRotated(45, 0, 1, 0);
	glTranslated(0, 0.1, 0);
	glTranslated(-(basesWidth - 0.3) / 2.0, 0.02, -(basesWidth - 0.3) / 2.0);
	base.drawOutside(Constraints(basesWidth - 0.3, 0.08, basesWidth - 0.3), texture);
	ppm;

#pragma endregion
	ppm;
}

void DomeOfTheRock::drawDomeOfSouls() {

	int textures[] = { 0,0,0,0,0,0,0,0 };
	db innerR = 1.5, outerR = 2; int PolygonRank = 8;
	db pillarHieght = 3;

#pragma region pillars
	for (db angle = 22.5; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR + 0.05);
		drawDomeOfSoulsPillar(3, 0.1, 0.6, LIME_STONE1);
		ppm;
	}
#pragma endregion

#pragma region archs

	Box top;
	pshm;
	glTranslated(0, pillarHieght + 0.6, 0);
	for (db angle = 0; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		pshm;
		glTranslated(-0.765, 0.765, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.1);
		textures[0] = textures[2] = textures[3] = textures[4] = textures[5] = textures[6] = LIME_STONE2;
		textures[1] = LEAD;
		top.drawOutside(Constraints(0.765 * 2, 0.2, 0.22), textures);
		ppm;
		textures[0] = LIME_STONE1;
		textures[1] = LIME_STONE2;
		textures[7] = LIME_STONE1;
		textures[2] = textures[3] = LIME_STONE2;
		textures[4] = textures[5] = LIME_STONE2;
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.1);
		drawArch(0.665, 0.765, 0.2, textures,28);
		ppm;
	}
	ppm;
#pragma endregion

#pragma region domes
	pshm;
	glRotated(22.5, 0, 1, 0);
	glTranslated(0, pillarHieght + 2, 0);
	cull;
	entxt;
	glBindTexture(GL_TEXTURE_2D, LEAD);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.38, Color(255, 255, 255), 16, false, false, false);
	entxt;
	glBindTexture(GL_TEXTURE_2D, LIME_STONE1);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.371, Color(255, 255, 255), 8, true, false, true);
	distxt;
	nocull;
	ppm;
#pragma endregion

#pragma region marble

	for (db angle = 0; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		glTranslated(-0.9, 0.1, -1.8 * cos(360.0 / (2 * PolygonRank)) + 0.5);
		top.drawOutside(Constraints(1.8, 0.1, 0.1), LIME_STONE2);
		ppm;
	}


	db side = 0.7 * (srt / (1 + srt));
	db point = side / srt;
	db a = 1.8;
	db p = a / srt;
	pshm;
	glTranslated(-(a / 2.0 + p), 0, (a / 2.0 + p));
	entxt;
	glBindTexture(GL_TEXTURE_2D, MARBLE8);
	glNormal3f(0, 7, 0);
	glBegin(GL_POLYGON);
	txt(point, 0);
	glVertex3d(p, 0.1, 0);
	txt(point + side, 0);
	glVertex3d(p + a, 0.1, 0);
	txt(2 * point + side, point);
	glVertex3d(2 * p + a, 0.1, -p);
	txt(2 * point + side, (point + side));
	glVertex3d(2 * p + a, 0.1, -p - a);
	txt(point + side, (2 * point + side));
	glVertex3d(p + a, 0.1, -2 * p - a);
	txt(point, (2 * point + side));
	glVertex3d(p, 0.1, -2 * p - a);
	txt(0, (point + side));
	glVertex3d(0, 0.1, -p - a);
	txt(0, point);
	glVertex3d(0, 0.1, -p);
	glEnd();
	distxt;

	ppm;
#pragma endregion

}

void DomeOfTheRock::drawDomeOfTheProphet() {

	int textures[] = { 0,0,0,0,0,0,0,0 };
	db innerR = 1.5, outerR = 2; int PolygonRank = 8;
	db pillarHieght = 3;

#pragma region pillars
	for (db angle = 22.5; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR + 0.05);
		drawDomeOfThePorphetPillar(3, 0.1, 0.6, LIME_STONE1);
		ppm;
	}
#pragma endregion

#pragma region archs

	Box top;
	pshm;
	glTranslated(0, pillarHieght + 0.6, 0);
	for (db angle = 0; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		pshm;
		glTranslated(-0.765, 0.765, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.1);
		textures[0] = textures[2] = textures[3] = textures[4] = textures[5] = textures[6] = LIME_STONE2;
		textures[1] = LEAD;
		top.drawOutside(Constraints(0.765 * 2, 0.2, 0.22), textures);
		ppm;
		textures[0] = LIME_STONE1;
		textures[1] = LIME_STONE2;
		textures[7] = LIME_STONE1;
		textures[2] = textures[3] = LIME_STONE2;
		textures[4] = textures[5] = LIME_STONE2;
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.1);
		drawArch(0.665, 0.765, 0.2, textures,28);
		ppm;
	}
	ppm;
#pragma endregion

#pragma region domes
	pshm;
	glRotated(22.5, 0, 1, 0);
	glTranslated(0, pillarHieght + 2, 0);
	cull;
	entxt;
	glBindTexture(GL_TEXTURE_2D, LEAD);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.38, Color(255, 255, 255), 16, false, false, false);
	entxt;
	glBindTexture(GL_TEXTURE_2D, LIME_STONE1);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.371, Color(255, 255, 255), 8, true, false, true);
	distxt;
	nocull;
	ppm;
#pragma endregion

}

void DomeOfTheRock::drawDomeOfAscention() {

	int textures[] = { 0,0,0,0,0,0,0,0 };
	db innerR = 2.5, outerR = 3; int PolygonRank = 8;
	db pillarHieght = 4;

#pragma region pillars
	for (db angle = 22.5; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		pshm;
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR + 0.15);
		drawDomeOfAscentionPillar(pillarHieght, 0.1, 0.6, LIME_STONE1);
		ppm;

		pshm;
		glTranslated(0, pillarHieght / 2.0 + 0.6, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.04);
		drawColumn(0.08, pillarHieght, LIME_STONE2, 12);
		ppm;
		ppm;
	}
#pragma endregion

#pragma region archs

	Box top;
	pshm;
	glTranslated(0, pillarHieght + 0.6, 0);
	for (db angle = 0; angle < 360; angle += 45) {
		pshm;
		glRotated(angle, 0, 1, 0);
		pshm;
		glTranslated(-1.5 * 0.765, 1.5 * 0.765, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.2);
		textures[0] = textures[2] = textures[3] = textures[4] = textures[5] = textures[6] = LIME_STONE2;
		textures[1] = LIME_STONE2;
		top.drawOutside(Constraints(0.765 * 3, 0.2, 0.26), textures);
		ppm;
		textures[0] = LIME_STONE3;
		textures[1] = LIME_STONE3;
		textures[7] = WHITE_STONE;
		textures[2] = textures[3] = WHITE_STONE;
		textures[4] = textures[5] = LIME_STONE3;
		pshm;
		glTranslated(0, 0, -innerR * cos(360.0 / (2 * PolygonRank)) + outerR - innerR - 0.1);
		drawArch(1.5 * 0.665, 1.5 * 0.765, 0.2, textures,28);
		ppm;

		pshm;
		textures[0] = LIME_STONE2;
		textures[1] = LIME_STONE2;
		textures[7] = LIME_STONE2;
		textures[2] = textures[3] = LIME_STONE2;
		textures[4] = textures[5] = LIME_STONE2;
		glTranslated(0, 0, -1.2 * cos(360.0 / (2 * PolygonRank)) + 2.7 - 1.2 - 0.1);
		drawArch(1.3 * 0.665, 1.3 * 0.765, 0.2, textures,28);
		ppm;

		ppm;
	}
	ppm;
#pragma endregion

#pragma region dome
	pshm;
	white;
	glRotated(22.5, 0, 1, 0);
	glTranslated(0, pillarHieght + 2, 0);
	cull;
	entxt;
	glBindTexture(GL_TEXTURE_2D, LIME_STONE2);
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.51, Color(255, 255, 255), 25, false, false, false,false);
	entxt;
	nocull;
	ppm;
#pragma endregion

#pragma region body
	pshm;
	glRotated(22.5, 0, 1, 0);
	glTranslated(0, pillarHieght / 2.0, 0);
	entxt;
	white;
	glBindTexture(GL_TEXTURE_2D, LIME_STONE3);
	Cylinder body = Cylinder(2.7, 2.7, pillarHieght + 3, 8, 1, false, 2, false, true);
	body.drawSide();
	distxt;
	ppm;
#pragma endregion



}

void DomeOfTheRock::drawDomeOfKhalili() {
	Box khalili;
	int textures[8] = { 0,0,0,0,0,0,0,0 };
	textures[0] = 0;
	textures[1] = KHALILI3;
	textures[2] = KHALILI1;
	textures[3] = KHALILI4;
	textures[4] = KHALILI4;
	textures[5] = KHALILI4;
	khalili.drawOutside(Constraints(9, 5, 9), textures);

	entxt;
	glBindTexture(GL_TEXTURE_2D, KHALILI2);
	mosqueDrawer.drawDome(Point(4.5, 4.9, 4.5), 0.7, Color(256, 256, 256), 20, false, false, true,false);
	distxt;
}


void DomeOfTheRock::drawDomeOfSouls1() {
	glCallList(dome1DisplayList);
}

void DomeOfTheRock::drawDomeOfAscention1() {
	glCallList(dome2DisplayList);
}

void DomeOfTheRock::drawDomeOfKhalili1() {
	glCallList(dome3DisplayList);

	
}

void DomeOfTheRock::drawDomeOfTheProphet1() {
	glCallList(dome4DisplayList);
}