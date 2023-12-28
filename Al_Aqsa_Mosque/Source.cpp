#define ZOOM_INCREASE true
#define ZOOM_DECREASE false
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#define beg(word) glBegin(word)
#define endf glEnd()
#define txt(s,t) glTexCoord2d(s,t)
#define white glColor3f(1,1,1)
const db srt = 1.414213562373095;



#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <gl\glut.h>		// Header File For The Glut Library
#include <iostream>
#include <math.h>
#include "Point.h"
#include "Color.h"
#include "Constants.h"
#include "PrimitiveDrawer.h"
#include "Texture.h"
#include "Camera.h"
#include "Console.h"
#include "Model_3DS.h"
#include "3DTexture.h"
#include "Constraints.h"
#include "math3d.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "MosqueDrawer.h"
#include "EnvDrawer.h"
#include "PersonDrawer.h"
#include "Box.h"


using namespace std;

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
int mouseX = 0;	// Current mouse X-coordinate
int mouseY = 0;	// Current mouse Y-coordinate
bool isClicked = false;	// Flag indicating whether the left mouse button is clicked
bool isRClicked = false;	// Flag indicating whether the right mouse button is clicked

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

void ToggleFullscreen();	// Function to toggle between full-screen and windowed mode
void SwitchToWindowedMode();	// Function to switch to windowed mode
bool SwitchToFullScreen();	// Function to switch to full-screen mode
void initTextures();
void initShadows();
void updatePerspective();
void updateZoomFactor(bool zoom);

GLsizei screenWidth, screenHeight;

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	screenWidth = width;
	screenHeight = height;

	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
void arch() {
	glEnable(GL_TEXTURE_2D);

	db length = 10; db sectorCount = 20; db radius = 5;
	glPushMatrix();
	glTranslatef(0, 0, -length / 2);
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);

	for (int i = 0; i <= sectorCount; ++i) {
		GLfloat angle = (static_cast<float>(i) / sectorCount) * PI;
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
}

// Camera Object
Camera* camera;

// Console Object
Console console;

// More Texture Images Variables
int wood, ground;

// Shadows Variables
M3DMatrix44f shadowMat;
M3DVector4f vPlaneEquation;

// Mosque Drawer Object
MosqueDrawer mosqueDrawer;

// Environment Drawer Object
EnvDrawer envDrawer;

PersonDrawer personDrawer;

int art;
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
	art = LoadTexture((char*)"assets/materials/art9.bmp");

	// Initialize Camera
	Camera::cameraInit();
	Camera::changeMode();

	initTextures();

	mosqueDrawer = MosqueDrawer();
	envDrawer = EnvDrawer();

	personDrawer = PersonDrawer();

	return TRUE;										// Initialization Went OK
}

float angle = 90;
GLfloat zoomFactor = 1.0f; // Adjust this value based on your zoom requirements

db openTheDoor = 0;


void drawRing(db innerR, db outerR,db height, int sectorCnt, int texture1, int texture2, bool isHalf) {

	glEnable(GL_TEXTURE_2D);
	pshm;
	db x1, x2, x3, x4, y1, y2, y3, y4, angle; int div = 1;
	if (isHalf) div =2;
	for (float i = 0; i <sectorCnt/div ; i++) {
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
		glVertex3d(x1, y1,height/ 2.0);
		txt(0, 1);
		glVertex3d(x2, y2, height/ 2.0);
		txt(1, 1);
		glVertex3d(x4, y4, height/ 2.0);
		txt(1, 0);
		glVertex3d(x3, y3, height/ 2.0);
		glEnd();

		angle = 2 * (++i / sectorCnt) * PI;
		x1 = innerR * cos(angle);
		y1 = innerR * sin(angle);
		x2 = outerR * cos(angle);
		y2 = outerR * sin(angle);

		glBindTexture(GL_TEXTURE_2D, texture2);
		glBegin(GL_QUADS);
		txt(0, 0);
		glVertex3d(x3, y3, height/ 2);
		txt(0, 1);
		glVertex3d(x4, y4, height/ 2);
		txt(1, 1);
		glVertex3d(x2, y2, height/ 2);
		txt(1, 0);
		glVertex3d(x1, y1, height/ 2);
		glEnd();
		i--;
	}
	ppm;
	glDisable(GL_TEXTURE_2D);
}

void drawPipe(db innerR, db outerR, db height, int sectorCnt,int textures[4], bool isHalf) {

#pragma region front ring
	pshm;
	glNormal3f(0, 0, -1);
	drawRing(innerR, outerR, -height, sectorCnt, textures[0], textures[1], isHalf);
	ppm;
#pragma endregion

#pragma region outer cylinder
	glEnable(GL_TEXTURE_2D);
	pshm;
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	Cylinder outerC = Cylinder(outerR, outerR,height, sectorCnt);
	outerC.setIsHalf(isHalf);
	outerC.drawSide();
	ppm;
#pragma endregion

#pragma region inner cylinder
	pshm;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	Cylinder innerC = Cylinder(innerR, innerR, height, sectorCnt);
	innerC.setIsHalf(isHalf);
	innerC.drawSide();
	ppm;
	glDisable(GL_TEXTURE_2D);
#pragma endregion

#pragma region back ring 
	pshm;
	glNormal3f(0, 0, 1);
	drawRing(innerR, outerR, height, sectorCnt, textures[0], textures[1], isHalf);
	ppm;
#pragma endregion
	
	if (isHalf) {
		glNormal3f(0, -1, 0);
		beg(GL_QUADS);
		glVertex3d(outerR,0,height/2.0);
		glVertex3d(innerR, 0, height / 2.0);
		glVertex3d(innerR, 0, -height / 2.0);
		glVertex3d(outerR, 0, -height / 2.0);
		endf;

		beg(GL_QUADS);
		glVertex3d(-outerR, 0, height / 2.0);
		glVertex3d(-innerR, 0, height / 2.0);
		glVertex3d(-innerR, 0, -height / 2.0);
		glVertex3d(-outerR, 0, -height / 2.0);
		endf;
	}
}


void drawOuterPillar(db pillarRadius, db pillarHeight, db basesWidth, int textures[]) {


	pshm;
	glTranslated(5, pillarHeight/2.0 + 1.401, 0);
#pragma region main body
	pshm;
	glColor3f(1, 0.5, 0.5);
	Cylinder c = Cylinder(pillarRadius, pillarRadius, pillarHeight, 20);
	c.setUpAxis(2);
	c.drawSide();
	ppm;
#pragma endregion

#pragma region bracelets
	pshm;
	glTranslated(0, -pillarHeight / 2.0 + pillarRadius / 2.0, 0);
	glColor3f(1, 1, 1);
	Cylinder bracelet = Cylinder(pillarRadius + 0.01, pillarRadius + 0.01, 0.5, 20);
	bracelet.setUpAxis(2);
	bracelet.drawSide();
	ppm;

	pshm;
	glTranslated(0, pillarHeight / 2.0 - pillarRadius / 2.0, 0);
	glColor3f(1, 1, 1);
	bracelet.setUpAxis(2);
	bracelet.drawSide();
	ppm;
#pragma endregion

#pragma region base
	pshm;

	Box base;

	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 0.2, -3 * pillarRadius / 2.0);
	pshm;
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), textures);
	ppm;

	pshm;
	glTranslated(0.1, -1, 0.1);
	base.drawOutside(Constraints(basesWidth - 0.2, 1, basesWidth - 0.2), textures);
	ppm;

	pshm;
	glTranslated(0, -1.2, 0);
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), textures);
	ppm;

	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0, 0);
	glRotated(45, 0, 1, 0);
	Cylinder top = Cylinder(pillarRadius - 0.1, basesWidth - 0.5, 1.4, 4);
	top.setUpAxis(2);
	top.drawSide();
	ppm;
#pragma endregion
	ppm;
}

void drawEntrance(db doorWidth, db doorHeight, int textures[]) {


	/*db thirdPeiceOfPillarBase = 0.2, sideLengthOfPillarBase = 1.6;
	db overflownEdgesForTheBaseOfArch = 0.6;*/

	db archbaseHeight = 1; db outerR = 5, innerR = 4, archLength = 8.5;
	Constraints c(0, 0, 1.5);
	Box marbleGround, arch;


	pshm;
#pragma region marble ground
	pshm;
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(22.5, 0.01, 0);
	marbleGround.drawOutside(Constraints(15, 0.2, archLength + 2), textures);
	ppm;
#pragma endregion

#pragma region pillars
	white;
	pshm;
	glTranslated(20 - 0.5, 0.2, archLength + 0.5);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(20 - 0.5 + doorWidth + 1, 0.2, archLength + 0.5);
	drawOuterPillar(0.5, 12.7, 1.7, textures);
	ppm;
#pragma endregion


	glTranslated(0, archbaseHeight, 0);

#pragma region bases of the arch 
	pshm;
	glColor3f(1, 1, 0);
	glTranslated(24 - 0.6 / 2, doorHeight - archbaseHeight, c.length);

	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), textures);
	ppm;

	pshm;
	glColor3f(1, 1, 0);
	glTranslated(35 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), textures);
	ppm;
#pragma endregion

#pragma region the arch
	pshm;
	glColor3f(0, 1, 1);
	//moving the arch to it's position
	glTranslated(30, 15, archLength / 2.0 + c.length + 0.1);
	drawPipe(innerR + 1, outerR + 1, archLength, 24, textures, true);
	ppm;
#pragma endregion




	ppm;

}

void DORdrawsides() {

	//the main param is the length of the side: a, then every thing is drawn in the reverse order of the base ocatgon
	//the second param maybe the angle of door openeing

	Constraints c = Constraints(60, 37, 1.5);
	int textures[] = { 0,0,0,0,0,0 };
	Box wall, door, arch, marbleGround;
	db a = 60;
	db p = a / srt;
	if (keys[VK_F1]) {
		if (openTheDoor < 90) openTheDoor += 1;
	}
	if (keys[VK_F2]) {
		if (openTheDoor > 0) openTheDoor -= 1;
	}

#pragma region front side

#pragma region walls
	pshm;
	glTranslated(p, 0, 0);

	pshm;
	glTranslated(0, 15, 0);
	wall.drawOutside(Constraints(60, 22, 1.5), textures);
	ppm;

	pshm;
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;
#pragma endregion

#pragma region entrance


	db doorWidth = 10; db doorHeight = 15;
	db archbaseHeight = 1; db outerR = 5, innerR = 4, archLength = 15;
	
	/*db thirdPeiceOfPillarBase = 0.2, sideLengthOfPillarBase = 1.6;
	db overflownEdgesForTheBaseOfArch = 0.6;*/

	//db umberellaWidth = 20;


	pshm;

#pragma region marble ground
	pshm;
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(0, 0.01, 0);
	marbleGround.drawOutside(Constraints(60, 0.2, archLength+1), textures);
	ppm;
#pragma endregion

#pragma region pillars

	pshm;
	glTranslated(20-0.5, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(20 - 0.5 + doorWidth + 1 , 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(25 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(33.7 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(38.7 - 0.5 + doorWidth + 1, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(15 - 0.5, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(6.3 - 0.5, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;

	pshm;
	glTranslated(1.3 - 0.5, 0.2, archLength);
	drawOuterPillar(0.5, 12.7, 1.6, textures);
	ppm;


#pragma endregion


	glTranslated(0, archbaseHeight, 0);

#pragma region bases of the arch 
	pshm;
	glColor3f(1, 1, 0);
	glTranslated(24-0.6/2, doorHeight- archbaseHeight, c.length);
	
	arch.drawOutside(Constraints(outerR - innerR + 0.6,archbaseHeight,archLength+0.5), textures);
	ppm;

	pshm;
	glColor3f(1, 1, 0);
	glTranslated(35 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), textures);
	ppm;
#pragma endregion

#pragma region umbrellas
	pshm;
	glColor3f(0, 0, 1);
	glTranslated(5, doorHeight-archbaseHeight, c.length);
	arch.drawOutside(Constraints(20 - outerR + innerR - 0.6/2, archbaseHeight / 2.0, archLength),textures);
	ppm;

	pshm;
	glColor3f(0, 0, 1);
	glTranslated(60 - 5 - (20 - outerR + innerR - 0.6 / 2), doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(20 - outerR + innerR - 0.6 / 2, archbaseHeight / 2.0, archLength), textures);
	ppm;
#pragma endregion

#pragma region the arch
	glColor3f(0, 1, 1);
	//moving the arch to it's position
	glTranslated(30,15, 7.5 + c.length + 0.1);
	drawPipe(innerR+1, outerR+1, archLength, 24, textures, true);
#pragma endregion



	
	ppm;

#pragma endregion


#pragma region doors

	//the left door
	pshm;
	glColor3ub(158, 69, 5);
	glTranslated(25, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glColor3ub(128, 45, 1);
	glTranslated(35, 0, 0);
	glRotated(-openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;
#pragma endregion


	ppm;
#pragma endregion

#pragma region left wing of the front side
	pshm;
	glTranslated(p, 0.01, c.length);
	glRotated(135, 0, 1, 0);
	glColor3f(0.5, 0.5, 0.5);
	wall.drawOutside(c, textures);
	ppm;
#pragma endregion

#pragma region left side

	pshm;
	glTranslated(0, 0, -p + c.length);
	glRotated(90, 0, 1, 0);
	glColor3f(1, 1, 1);

#pragma region walls

	pshm;
	glTranslated(0, 15, 0);
	wall.drawOutside(Constraints(60, 22, 1.5), textures);
	ppm;

	pshm;
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;
#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 15, textures);
	ppm;
#pragma endregion

#pragma region doors
	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glColor3ub(158, 69, 5);
	glTranslated(25, 0, 0);
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glColor3ub(128, 45, 1);
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	ppm;
#pragma endregion

	ppm;
#pragma endregion

#pragma region left wing of the back side
	pshm;
	glTranslated(0, 0, -p - a + c.length);
	glRotated(45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	wall.drawOutside(c, textures);
	ppm;
#pragma endregion

#pragma region back side

	pshm;
	glTranslated(p, 0, -2 * p - a + c.length);
	glColor3f(1, 1, 1);
#pragma region walls

	pshm;
	glTranslated(0, 15, 0);
	wall.drawOutside(Constraints(60, 22, 1.5), textures);
	ppm;

	pshm;
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;
#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 15, textures);
	ppm;
#pragma endregion

#pragma region doors
	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glColor3ub(158, 69, 5);
	glTranslated(25, 0, 0);
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glColor3ub(128, 45, 1);
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	ppm;
#pragma endregion

	ppm;
#pragma endregion

#pragma region right wing of the back side
	pshm;
	glTranslated(p + a, 0, -2 * p - a + c.length);
	glRotated(-45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	wall.drawOutside(c, textures);
	ppm;
#pragma endregion

#pragma region right side
	pshm;
	glTranslated(2 * p + a, 0, -p - a + c.length);
	glRotated(-90, 0, 1, 0);
	glColor3f(1, 1, 1);

#pragma region walls
	pshm;
	glTranslated(0, 15, 0);
	wall.drawOutside(Constraints(60, 22, 1.5), textures);
	ppm;

	pshm;
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;

	pshm;
	glTranslated(35, 0, 0);
	wall.drawOutside(Constraints(25, 15, 1.5), textures);
	ppm;
#pragma endregion

#pragma region entrance
	pshm;
	glRotated(180, 0, 1, 0);
	glTranslated(-60, 0, -2);
	drawEntrance(10, 15, textures);
	ppm;
#pragma endregion

#pragma region doors

	pshm;
	glTranslated(0, 0, c.length);
	//the left door
	pshm;
	glColor3ub(158, 69, 5);
	glTranslated(25, 0, 0);
	glRotated(-openTheDoor, 0, 1, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	//the right door
	pshm;
	glColor3ub(128, 45, 1);
	glTranslated(35, 0, 0);
	glRotated(openTheDoor, 0, 1, 0);
	glTranslated(-5, 0, 0);
	door.drawOutside(Constraints(5, 15, 0.5), textures);
	ppm;

	ppm;
#pragma endregion

	ppm;

#pragma endregion

#pragma region right wing of the front side
	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);
	glRotated(-135, 0, 1, 0);
	glColor3f(0.1, 0.1, 0.1);
	wall.drawOutside(c, textures);
	ppm;
#pragma endregion

#pragma region carpet
	glColor3ub(173, 3, 23);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3d(p, 0.1, 0);
	glVertex3d(p + a, 0.1, 0);
	glVertex3d(2 * p + a, 0.1, -p);
	glVertex3d(2 * p + a, 0.1, -p - a+c.length);
	glVertex3d(p + a, 0.1, -2 * p - a+c.length);
	glVertex3d(p, 0.1, -2 * p - a+c.length);
	glVertex3d(0, 0.1, -p - a + c.length);
	glVertex3d(0, 0.1, -p);
	glEnd();
#pragma endregion


}


void drawOctagon(Constraints c,int textures[]) {
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


void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	// Update Perspective Projection with new zooming value
	updatePerspective();

	// Set modelview matrix to the camera's view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera = Camera::getInstance();

	camera->Render();
	camera->decodeKeyboard(keys, 0.7);
	camera->decodeMouse(mouseX, mouseY, isClicked, isRClicked);


	//testEnv();
	const Point points[4] = { Point(-1000.0f, -2.0f, -1000.0f),Point(-1000.0f, -2.0f, 1000.0f),Point(1000.0f, -2.0f, 1000.0f),Point(1000.0f,-2.0f, -1000.0f) };
	envDrawer.drawTiledLand(points, 30);
	

	if (camera->getMode() == THIRD_PERSON_CAMERA)
	{
		Point p = camera->getPosition();
		float angel = 180 + camera->getRotatedY(), r = 1.8;
		p.x += r * sin(angel * PIdiv180);
		p.z += r * cos(angel * PIdiv180);
		p.y = -0.9 * 0.04 * cos(4 * (abs(p.x) + abs(p.z)));


		personDrawer.drawPerson(p, angel, 10);
	}
	glTranslated(-2, -2, -30);

	//drawing the ocatgon shape 

	//the width of the dome of the rock is 18m and the height is 11m the width of the door is 2.75m and the height is 4.5m 
	//the virtual width and heights are 60 * 37 and the door is 15 * 10

	Box wall; int textures[] = { 0,0,0,0,0,0 };
	pshm;
	wall.drawOutside(Constraints(1,1,1), textures);
	ppm;


	DORdrawsides();

	db a = 60;
	db p = a / srt;
	int sectorCnt = 36; int radius = 4; int radius2 = 5;
	white;
	
	

	//drawing pillar 
	//glTranslated(10, 8, 0);


	//drawOuterPillar(0.5, 12, 1.6, textures);

	glTranslated(8, 25, - 5);

	//x is outer length - inner
	//z is the outer radius - inner radius / 2
	glTranslated(5, 0,  - (30 +   60 /srt) + (25 + 50/srt ));
	drawOctagon(Constraints(50,2,5),textures);
	
	
	
	
	

	glFlush();											// Done Drawing The Quad

	//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}




void initTextures() {
	glEnable(GL_TEXTURE_2D);
	wood = LoadTexture((char*)"assets/materials/tree1.bmp", 255);
	ground = LoadTexture((char*)"assets/materials/ground.bmp", 255);
	// note if you load an image the opengl while on the GL_Texture_2D himself
	glDisable(GL_TEXTURE_2D);
}

void initShadows() {

	M3DVector3f points[3] = { { -30.0f, -1.9f, -20.0f },{ -30.0f, -1.9f, 20.0f },
		{ 40.0f, -1.9f, 20.0f } };

	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1],
		points[2]);
	// Calculate projection matrix to draw shadow on the ground
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation,
		envDrawer.LightPos);
}

void updatePerspective() {
	// Assuming you have a perspective projection set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Adjust the field of view based on zoom factor
	GLdouble aspectRatio = screenWidth / static_cast<GLdouble>(screenHeight);
	GLdouble nearPlane = 0.1;
	GLdouble farPlane = 10000.0;
	GLdouble fovY = 45.0 / zoomFactor; // Adjust the field of view

	gluPerspective(fovY, aspectRatio, nearPlane, farPlane);
}

void updateZoomFactor(bool zoom) {
	if (zoom == ZOOM_INCREASE) {
		if (zoomFactor < 7) {
			zoomFactor += 0.1;
		}
	}
	else {
		if (zoomFactor > 1) {
			zoomFactor -= 0.1;
		}
	}
}



/**
* @brief Toggles between full-screen and windowed mode.
*/
void ToggleFullscreen()
{
	if (fullscreen)
	{
		SwitchToWindowedMode();
	}
	else
	{
		if (SwitchToFullScreen())
		{
			fullscreen = true;
		}
		else
		{
			// Display an error message if switching to full-screen mode failed
			MessageBox(NULL, "Switching to full-screen mode failed. Running in windowed mode.", "Error", MB_OK | MB_ICONERROR);
		}
	}

	// Adjust OpenGL perspective based on the new window size
	ReSizeGLScene(1920, 1080);  // Set your desired width and height
}

/**
* @brief Switches to windowed mode.
*/
void SwitchToWindowedMode()
{
	ChangeDisplaySettings(NULL, 0);
	ShowCursor(TRUE);

	// Set window styles for windowed mode
	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	// Calculate window size based on client area size
	RECT windowRect = { 0, 0, 1920, 1080 }; // Set your desired window size
	AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	// Set the window size and position
	SetWindowPos(hWnd, HWND_TOP, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOMOVE | SWP_NOZORDER);

	// Show the window
	ShowWindow(hWnd, SW_SHOWNORMAL);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	// Update the fullscreen flag
	fullscreen = false;

	// Adjust OpenGL perspective based on the new window size
	ReSizeGLScene(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
}

/**
* @brief Switches to full-screen mode.
*/
bool SwitchToFullScreen()
{
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth = 1920;  // Set your desired width
	dmScreenSettings.dmPelsHeight = 1080; // Set your desired height
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Attempt to change the display settings to enable full-screen mode
	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
	{
		// Hide the cursor
		ShowCursor(FALSE);

		// Set window styles for full-screen mode
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
		SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW);

		// Show the window maximized
		ShowWindow(hWnd, SW_SHOWMAXIMIZED);

		return true;
	}

	return false;  // Unable to switch to full-screen mode
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop

	}

	case WM_MOUSEMOVE:
	{
		mouseX = (int)LOWORD(lParam);
		mouseY = (int)HIWORD(lParam);
		isClicked = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
		isRClicked = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
		break;
	}
	case WM_LBUTTONUP:
		isClicked = false; 	 break;
	case WM_RBUTTONUP:
		isRClicked = false;   break;
	case WM_LBUTTONDOWN:
		isClicked = true; 	break;
	case WM_RBUTTONDOWN:
		isRClicked = true;	break;
	case WM_MOUSEWHEEL:
		GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? updateZoomFactor(ZOOM_INCREASE) : updateZoomFactor(ZOOM_DECREASE);
		return 0;

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE

		// Check if the 'F' key is pressed to toggle full-screen mode
		if (keys['F'])
		{
			ToggleFullscreen();
		}

		if (keys['C'])
		{
			Camera::changeMode();
		}

		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	// if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = false;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Al Aqsa Mosque", 1920, 1080, 32, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 60 frame per second
	UINT timer = SetTimer(hWnd, 0, 1000 / 60, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
