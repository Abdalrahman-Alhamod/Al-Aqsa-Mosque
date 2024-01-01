#define ZOOM_INCREASE true
#define ZOOM_DECREASE false
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
#define white glColor3f(1,1,1)
const db srt = 1.414213562373095;
const db pi = 3.141592653589793238462643383279502884197;

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


void arch(db sectorCount , db radius, db thickness = 0) {
	glEnable(GL_TEXTURE_2D);

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

void innerRoof() {
	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	db dist = dia / 2.0 * sin(45) - dia2 / 2.0 * sin(45) + 5.2;
	glColor3f(0.23, 1, 0.23);
	pshm;
	glNormal3f(0, 1, 0);
	glTranslated(0, 35.1, 0);

	pshm;
	beg(GL_QUADS);
	glVertex3d(p + 0.6, 0, 0);
	glVertex3d(p + a - 0.5, 0, 0);
	glVertex3d(p + a - 7.1, 0, -dist);
	glVertex3d(p + 7.1, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 0.6, 0, 0);
	glVertex3d(p + a - 1.5, 0, 0);
	glVertex3d(p + a - 7.2, 0, -dist);
	glVertex3d(p + 7.4, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 1.6, 0, 0);
	glVertex3d(p + a - 1.5, 0, 0);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.3, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 0.6, 0, -2);
	glVertex3d(p + a - 1.5, 0, -2);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p, 0, -2);
	glVertex3d(p + a - 0.1, 0, -2);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p, 0, -2);
	glVertex3d(p + a + 0.7, 0, -2);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + 2, 0, -1.5);
	glVertex3d(p + a + 1, 0, -1.5);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + 1, 0, 0);
	glVertex3d(p + a + 1, 0, 0);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	endf;
	ppm;

	ppm;

	//the second layer
	glColor3f(0.3, 0.5, 0.2);
	pshm;
	glNormal3f(0, 1, 0);
	glTranslated(0, 35.1, 0);

	pshm;
	beg(GL_QUADS);
	glVertex3d(p + a - 7.1, 0, -dist);
	glVertex3d(p + 7.1, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.2, 0, -dist);
	glVertex3d(p + 7.4, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.3, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + a - 7.3, 0, -dist);
	glVertex3d(p + 7.2, 0, -dist);
	glVertex3d(p + 16, 3.5, -dist - 22);
	glVertex3d(p + a - 16, 3.5, -dist - 22);
	endf;
	ppm;

	ppm;
}

void outerRoof() {


	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	db dist = dia / 2.0 * sin(45) - dia2 / 2.0 * sin(45) + 5.2;

	pshm;
	glNormal3f(0, 1, 0);
	glTranslated(0, 35.1, 0);
	glColor3f(0, 0.230, 0.23);
	pshm;
	beg(GL_QUADS);
	glVertex3d(p + 0.6, 0.5, 0);
	glVertex3d(p + a - 0.5, 0.5, 0);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(0, -0.1, 0);
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(45, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 0.6, 0.5, 0);
	glVertex3d(p + a - 1.5, 0.5, 0);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(90, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 1.6, 0.5, 0);
	glVertex3d(p + a - 1.5, 0.5, 0);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(135, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p - 0.6, 0, -2);
	glVertex3d(p + a - 1.5, 0, -2);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(180, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p, 0, -2);
	glVertex3d(p + a - 0.1, 0, -2);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(225, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p, 0, -2);
	glVertex3d(p + a + 0.7, 0, -2);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(270, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + 2, 0, -1.5);
	glVertex3d(p + a + 1, 0, -1.5);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(315, 0, 1, 0);
	glTranslated(-p - a / 2.0, 0, p + a / 2.0);
	beg(GL_QUADS);
	glVertex3d(p + 1, 0, 0);
	glVertex3d(p + a + 1, 0, 0);
	glVertex3d(p + a - 15, 5, -dist - 22);
	glVertex3d(p + 15, 5, -dist - 22);
	endf;
	ppm;

	ppm;
}

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

void drawPipe(db innerR, db outerR, db height, int sectorCnt,int textures[4], bool isHalf, bool isArch = false) {

#pragma region front ring
	
	pshm;
	glNormal3f(0, 0, -1);
	cull;
	frontf;
	drawRing(innerR, outerR, -height, sectorCnt, textures[0], textures[1], isHalf);
	backf;
	nocull;
	ppm;
#pragma endregion

		if (!isArch) {
#pragma region outer cylinder
		pshm;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		Cylinder outerC = Cylinder(outerR, outerR, height, sectorCnt);
		outerC.setIsHalf(isHalf);
		cull;
		outerC.drawSide();
		nocull;
		ppm;
#pragma endregion
		}

#pragma region inner cylinder
	pshm;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	Cylinder innerC = Cylinder(innerR, innerR, height, sectorCnt);
	innerC.setIsHalf(isHalf);
	innerC.reverseNormals();
	cull;
	innerC.drawSide();
	nocull;
	glDisable(GL_TEXTURE_2D);
	ppm;
#pragma endregion

#pragma region back ring 
	pshm;
	glNormal3f(0, 0, 1);
	cull;
	drawRing(innerR, outerR, height, sectorCnt, textures[0], textures[1], isHalf);
	nocull;
	ppm;
#pragma endregion
	if (isHalf) {
		glNormal3f(0, -1, 0);
		cull;
		beg(GL_QUADS);
		glVertex3d(outerR,0,height/2.0);
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

void drawColumn(db pillarRadius, db pillarHeight) {
	cull;
#pragma region main body
	pshm;
	glColor3f(1, 0.5, 0.5);
	Cylinder c = Cylinder(pillarRadius, pillarRadius, pillarHeight, 6);
	c.setUpAxis(2);
	c.drawSide();
	ppm;
#pragma endregion

#pragma region bracelets
	pshm;
	glTranslated(0, -pillarHeight / 2.0 + 0.25, 0);
	white;
	Cylinder bracelet = Cylinder(pillarRadius + 0.01, pillarRadius + 0.01, 0.5, 6);
	bracelet.setUpAxis(2);
	bracelet.drawSide();
	ppm;

	pshm;
	glTranslated(0, pillarHeight / 2.0 - 0.25, 0);
	white;
	bracelet.setUpAxis(2);
	bracelet.drawSide();
	ppm;
#pragma endregion
	nocull;
}

void drawOuterPillar(db pillarRadius, db pillarHeight, db basesWidth, int textures[]) {


	pshm;
	glTranslated(5, pillarHeight/2.0 + 1.401, 0);
#pragma region column
	drawColumn(pillarRadius, pillarHeight);
#pragma endregion

#pragma region base
	pshm;
	bool flag[6] = { 1,0,0,0,0,0 };
	Box base;

	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 0.2, -3 * pillarRadius / 2.0);
	pshm;
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), textures,flag);
	ppm;

	pshm;
	glTranslated(0.1, -1, 0.1);
	base.drawOutside(Constraints(basesWidth - 0.2, 1, basesWidth - 0.2), textures,flag);
	ppm;

	pshm;
	glTranslated(0, -1.2, 0);
	base.drawOutside(Constraints(basesWidth, 0.2, basesWidth), textures,flag);
	ppm;

	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0, 0);
	glRotated(45, 0, 1, 0);
	Cylinder top = Cylinder(pillarRadius - 0.1, basesWidth - 0.5, 1.4, 4);
	top.setUpAxis(2);
	cull;
	top.drawSide();
	nocull;
	ppm;
#pragma endregion
	ppm;
}

void drawInnerPillar(db pillarRadius, db pillarHeight, db basesWidth, int textures[]) {

	pshm;
	glTranslated(0, pillarHeight / 2.0 + 1.5 + 0.1, 0);
#pragma region body
	pshm;
	drawColumn(1.2, pillarHeight);
	ppm;
#pragma endregion

#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.2, 0);
	bool flag[6] = { 1,1,0,0,0,0 };
	pshm;
	glTranslated(-1.5, 0.7, -1.5);
	Box base;
	base.drawOutside(Constraints(3, 1.5, 3), textures,flag);
	ppm;
	glRotated(45, 0, 1, 0);
	Cylinder top = Cylinder(pillarRadius + 0.2, basesWidth - 1, 1.4, 4);
	top.setUpAxis(2);
	cull;
	top.drawSide();
	nocull;
	ppm;

#pragma endregion

#pragma region base
	pshm;
	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 2, -3 * pillarRadius / 2.0);
	flag[1] = 0;
	base.drawOutside(Constraints(basesWidth, 2, basesWidth), textures,flag);
	ppm;
#pragma endregion

	ppm;
}

void drawDrumPillar(db pillarRadius, db pillarHeight, db basesWidth, int textures[]) {
	pshm;
	glTranslated(0, pillarHeight / 2.0 + basesWidth + 0.1, 0);
#pragma region body
	pshm;
	drawColumn(1.2, pillarHeight);
	ppm;
#pragma endregion

	bool flag[6] = { 1,0,0,0,0,0 };
#pragma region top
	pshm;
	glTranslated(0, pillarHeight / 2.0 + 0.2, 0);

	pshm;
	glTranslated(-1.5, 0.7, -1.5);
	Box base;
	base.drawOutside(Constraints(3, 1.5, 3), textures,flag);
	ppm;
	glRotated(45, 0, 1, 0);
	Cylinder top = Cylinder(pillarRadius + 0.2, basesWidth - 1, 1.4, 4);
	top.setUpAxis(2);
	cull;
	top.drawSide();
	nocull;
	ppm;

#pragma endregion

#pragma region base
	pshm;
	glTranslated(-3 * pillarRadius / 2.0, -pillarHeight / 2.0 - 0.5, -3 * pillarRadius / 2.0);
	base.drawOutside(Constraints(basesWidth, 0.5,basesWidth), textures,flag);
	glTranslated(-0.25,-1.5,-0.25);
	base.drawOutside(Constraints(basesWidth + 0.5, 1.5, basesWidth + 0.5), textures,flag);

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
	bool flag[6] = {1,0,0,0,0,0};

	pshm;
#pragma region marble ground
	pshm;
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(22.5, 0.01, 0);
	marbleGround.drawOutside(Constraints(15, 0.2, archLength + 2), textures,flag);
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
	flag[0] = 0; flag[2] = 1;
#pragma region bases of the arch 
	pshm;
	glColor3f(1, 1, 0);
	glTranslated(24 - 0.6 / 2, doorHeight - archbaseHeight, c.length);

	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), textures,flag);
	ppm;

	pshm;
	glColor3f(1, 1, 0);
	glTranslated(35 - 0.6 / 2, doorHeight - archbaseHeight, c.length);
	arch.drawOutside(Constraints(outerR - innerR + 0.6, archbaseHeight, archLength + 0.5), textures,flag);
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

void arch(db innerR, db outerR, db height, int sectorCnt, int textures[]) {
	white;
	pshm;
	glNormal3f(0, 0, 1);
	glTranslated(0, 0, height/2.0 - 0.01);
	cull;
	frontf;
	arch(sectorCnt/2.0, outerR);
	backf;
	nocull;
	ppm;

	pshm;
	glNormal3f(0, 0, -1);
	glTranslated(0, 0, -height/2.0 + 0.01);
	cull;
	arch(sectorCnt/2.0, outerR);
	nocull;
	ppm;

	glColor3f(0, 0.123, 0.21);
	drawPipe(innerR, outerR, height, sectorCnt, textures, true, true);

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

void DORdrawArcadeSide() {

	int textures[6] = { 0,0,0,0,0,0 }; db h = 20;
	db pillarH = h + 3 + 2.5;

	pshm;
#pragma region bridge
	Box bridge;
	pshm;
	glTranslated(0, pillarH, 0);
	bool flag[6] = { 0,0,0,0,1,1 };
	bridge.drawOutside(Constraints(48, 1.5, 3), textures,flag);
	ppm;
#pragma endregion

#pragma region archs

	db sectorCnt = 16;
	pshm;
	glTranslated(24, 1.5, 1.5);
	arch(6.5, 8, 3, sectorCnt, textures);
	ppm;
	/////////////////////////////////////////////////
	pshm;
	glTranslated(8, 1.5 , 1.5);
	arch(6.5, 8, 3, sectorCnt, textures);
	ppm;
	/////////////////////////////////////////////
	pshm;
	glTranslated(40, 1.5 , 1.5);
	arch(6.5, 8, 3, sectorCnt, textures);
	ppm;
	ppm;
#pragma endregion

#pragma region pillars
	h += 1;
	pshm;
	glTranslated(16, 0.5, 1.5);
	drawInnerPillar(1, h, 3, textures);
	ppm;

	pshm;
	glTranslated(32, 0.5, 1.5);
	drawInnerPillar(1, h, 3, textures);
	ppm;
#pragma endregion

	ppm;
}

void DORdrawArcade() {

	int textures[6] = { 0,0,0,0,0,0 };
	Constraints c = Constraints(48, 1.5, 3);
	db a = c.width;
	db p = a / srt;
	Box tier;
	bool flag[6] = { 1,1,0,0,0,0 };

	pshm;
	glTranslated(2 * p + a  , 0, -p + c.length);
	glRotated(-135, 0, 1, 0);
	
	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glTranslated(a, 0, 0);
	glRotated(-22.5, 0, 1, 0);
	glTranslated(-2.5, 0,0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	ppm;

	///the front face
	pshm;
	glTranslated(p, 0.1, 0);
	DORdrawArcadeSide();
	ppm;

	///the left wing of the front 
	pshm;
	glTranslated(p, 0, c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(157.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(135, 0, 1, 0);
	glColor3f(0.5, 0.5, 0.5);
	DORdrawArcadeSide();
	ppm;

	///the left side

	pshm;

	glTranslated(0, 0.1, -p + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(112.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(90, 0, 1, 0);
	glColor3f(1, 1, 1);
	DORdrawArcadeSide();

	ppm;

	///the left wing of the  back
	pshm;

	glTranslated(0, 0, -p - a + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(67.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	DORdrawArcadeSide();

	ppm;

	///the back face
	pshm;
	glTranslated(p, 0.1, -2 * p - a + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(22.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glColor3f(1, 1, 1);
	DORdrawArcadeSide();

	ppm;

	///the right wing of the back
	pshm;
	glTranslated(p + a, 0, -2 * p - a + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(-22.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(-45, 0, 1, 0);
	glColor3f(0.3, 0.3, 0.3);
	DORdrawArcadeSide();
	ppm;

	///the right side
	pshm;
	glTranslated(2 * p + a, 0.1, -p - a + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(-67.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(-90, 0, 1, 0);
	glColor3f(1, 1, 1);
	DORdrawArcadeSide();

	ppm;

	///the right wing of the front 
	pshm;
	glTranslated(2 * p + a, 0, -p + c.length);

	pshm;
	glColor3f(0.3, 0.2, 0.7);
	glRotated(-112.5, 0, 1, 0);
	glTranslated(-2.5, 0, 0);
	tier.drawOutside(Constraints(5, 35.1, 5), textures,flag);
	ppm;

	glRotated(-135, 0, 1, 0);
	glColor3f(0.1, 0.1, 0.1);
	DORdrawArcadeSide();
	ppm;
}

void DORdrawDrum() {


	db innerR = 33, outerR = 36, Outerheight = 3;
	int textures[6] = { 0,0,0,0,0,0 };
	bool flag[6] = { 1,1,0,0,0,0 };
	glTranslated(0, 28, 0);
	glColor3f(1,1, 0.1);



	pshm;
	cull;
	glTranslated(0, Outerheight / 2.0 + 5.65, 0);
	pshm;
	glTranslated(0, 8.6 * 22 / 20.0, 0);
	Cylinder drum = Cylinder(33, 33, 22, 20, 1);
	drum.setUpAxis(2);
	drum.reverseNormals();
	drum.drawSide();
	ppm;
	pshm;
	drum.reverseNormals();
	glTranslated(0, 1, 0);
	drum.set(36, 36, 5, 20, 1, true, 2);
	drum.drawSide();
	ppm;
	pshm;
	glColor3ub(0, 119, 182);
	glTranslated(0, 13, 0);
	drum.set(36, 36, 17, 28, 1, true, 2);
	drum.drawSide();
	ppm;
	nocull;
	ppm;



	Box tier;
	int i = 0;
	for (db angle = 9; angle <= 360; angle += 18) {
		i++;
		if (i % 5) {
			pshm;
			glRotated(angle, 0, 1, 0);
			glTranslated(0, 0, -innerR * sin(11.25) + 2.13);
			arch(4.65, 5.65, 3, 16, textures);
			ppm;
		}
		else {
			pshm;
			glRotated(angle, 0, 1, 0);
			glTranslated(-6.5, -28, -innerR * sin(11.25) + 0.3);
			tier.drawOutside(Constraints(13, 35, 3.5), textures,flag);

			glColor3ub(0, 119, 182);
			glTranslated(0, 40,2);
			tier.drawOutside(Constraints(15, 16.5, 3), textures);
			ppm;
		}
	}


	i = 0;
	for (db angle = 18; angle <= 360; angle += 18) {
		i++;
		if (i % 5 != 0 && i % 5 != 4)
		{
			pshm;
			glRotated(angle, 0, 1, 0);
			glTranslated(outerR - 1.5, -29, 0);
			drawDrumPillar(1, 23.5, 3, textures);
			ppm;
		}
	}
}

void DORdrawFence(db heightOfWall) {
	int textures[6] = { 0,0,0,0,0,0 };
	bool flag[6] = { 1,0,0,0,0,0 };

	glColor3f(0.5, 0.5, 0.5);
	//first topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(-5, 0, 27);
	glVertex3d(-2, 2, 23);
	glVertex3d(0, 0, 27);
	glVertex3d(1, 2, 23);
	glVertex3d(7, 0, 25.5);
	glVertex3d(5, 2, 22);
	glVertex3d(14, 0, 20);
	glVertex3d(12, 2, 18);
	glVertex3d(20, 0, 12);
	glVertex3d(18, 2, 10);
	glVertex3d(22, 0, 7);
	glVertex3d(20, 2, 4);
	glVertex3d(18, 0, -10);
	glVertex3d(11, 2, -10);
	glVertex3d(7, 0, -22);
	glVertex3d(4, 2, -18);
	glVertex3d(-14, 0, -24);
	glVertex3d(-10, 2, -15);
	glVertex3d(-17, 0, 20);
	glVertex3d(-14, 2, 16);
	glVertex3d(-5, 0, 20);
	glVertex3d(-2, 2, 17);
	glVertex3d(-5, 0, 27);
	glVertex3d(-2, 2, 23);
	endf;

	glColor3f(0.4, 0.4, 0.4);
	//second topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(-2, 2, 23);
	glVertex3d(1, 2.5, 20);
	glVertex3d(1, 2, 23);
	glVertex3d(3, 2.5, 20);
	glVertex3d(5, 2, 22);
	glVertex3d(5, 2.5, 18);
	glVertex3d(12, 2, 18);
	glVertex3d(8, 2.5, 15);
	glVertex3d(18, 2, 10);
	glVertex3d(12, 2.5, 10);
	glVertex3d(20, 2, 4);
	glVertex3d(12, 2.5, 4);
	glVertex3d(11, 2, -10);
	glVertex3d(8, 2.5, -3);
	glVertex3d(4, 2, -18);
	glVertex3d(4, 2.5, -13);
	glVertex3d(-10, 2, -15);
	glVertex3d(-7, 2.5, -10);
	glVertex3d(-14, 2, 16);
	glVertex3d(-12, 2.5, 12);
	glVertex3d(-2, 2, 17);
	glVertex3d(0, 2.5, 14);
	glVertex3d(-2, 2, 23);
	glVertex3d(1, 2.5, 20);
	endf;

	glColor3f(0.3, 0.3, 0.3);
	//third topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(1, 2.5, 20);
	glVertex3d(2, 3, 15);
	glVertex3d(3, 2.5, 20);
	glVertex3d(3, 3, 16);
	glVertex3d(5, 2.5, 18);
	glVertex3d(5, 3, 14);
	glVertex3d(8, 2.5, 15);
	glVertex3d(8, 3, 10);
	glVertex3d(12, 2.5, 10);
	glVertex3d(10, 3, 7);
	glVertex3d(12, 2.5, 4);
	glVertex3d(10, 3, 3);
	glVertex3d(8, 2.5, -3);
	glVertex3d(6, 3, 0);
	glVertex3d(4, 2.5, -13);
	glVertex3d(4, 3, -7);
	glVertex3d(-7, 2.5, -10);
	glVertex3d(-4, 3, -2);
	glVertex3d(-12, 2.5, 12);
	glVertex3d(-6, 3, 9);
	glVertex3d(0, 2.5, 14);
	glVertex3d(1, 3, 12);
	glVertex3d(1, 2.5, 20);
	glVertex3d(2, 3, 15);
	endf;

	glColor3f(0.2, 0.2, 0.2);
	//fourth topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(5, 3, 14);
	glVertex3d(5, 3.5, 11);
	glVertex3d(8, 3, 10);
	glVertex3d(5, 3.5, 10);
	glVertex3d(10, 3, 7);
	glVertex3d(6, 3.5, 7);
	glVertex3d(10, 3, 3);
	glVertex3d(7, 3.5, 3);
	glVertex3d(6, 3, 0);
	glVertex3d(6, 3.5, 2);
	glVertex3d(4, 3, -7);
	glVertex3d(4, 3.5, 0);
	glVertex3d(-4, 3, -2);
	glVertex3d(1, 3.5, 2);
	glVertex3d(-4, 3, -2);
	glVertex3d(-2, 3.5, 3);
	glVertex3d(-6, 3, 9);
	glVertex3d(1, 3.5, 8);
	glVertex3d(1, 3, 12);
	glVertex3d(2, 3.5, 10);
	glVertex3d(2, 3, 15);
	glVertex3d(3, 3.5, 11);
	glVertex3d(3, 3, 16);
	glVertex3d(5, 3.5, 11);
	glVertex3d(5, 3, 14);
	endf;

	glColor3f(0.1, 0.1, 0.1);
	//fifth topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(-2, 3.5, 3);
	glVertex3d(2, 4, 5);
	glVertex3d(1, 3.5, 8);
	glVertex3d(2, 4, 7);
	glVertex3d(2, 3.5, 10);
	glVertex3d(3, 4, 10.5);
	glVertex3d(3, 3.5, 11);
	glVertex3d(3.5, 4, 10);
	glVertex3d(3, 3.5, 11);
	glVertex3d(4, 4, 10.5);
	glVertex3d(5, 3.5, 11);
	glVertex3d(4, 4, 10.5);
	glVertex3d(5, 3.5, 10);
	glVertex3d(5, 4, 8);
	glVertex3d(6, 3.5, 7);
	glVertex3d(5, 4, 7);
	glVertex3d(7, 3.5, 3);
	glVertex3d(5, 4, 3);
	glVertex3d(6, 3.5, 2);
	glVertex3d(4, 4, 3);
	glVertex3d(4, 3.5, 0);
	glVertex3d(3, 4, 5);
	glVertex3d(1, 3.5, 2);
	glVertex3d(2, 4, 5);
	glVertex3d(-2, 3.5, 3);
	glVertex3d(2, 4, 7);
	endf;

	glColor3f(0, 0, 0);
	//sixth topological tier
	beg(GL_TRIANGLE_STRIP);
	glVertex3d(4, 4, 3);
	glVertex3d(4, 4.3, 7);
	glVertex3d(3, 4, 5);
	glVertex3d(4, 4.3, 7);
	glVertex3d(2, 4, 5);
	glVertex3d(4, 4.3, 7);
	glVertex3d(2, 4, 7);
	glVertex3d(4, 4.3, 7);
	glVertex3d(3, 4, 10.5);
	glVertex3d(4, 4.3, 7);
	glVertex3d(3.5, 4, 10);
	glVertex3d(4, 4.3, 7);
	glVertex3d(4, 4, 10.5);
	glVertex3d(4, 4.3, 7);
	glVertex3d(5, 4, 8);
	glVertex3d(4, 4.3, 7);
	glVertex3d(5, 4, 7);
	glVertex3d(4, 4.3, 7);
	glVertex3d(5, 4, 3);
	glVertex3d(4, 4.3, 7);
	glVertex3d(4, 4, 3);
	endf;

	//////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////


	white;
	beg(GL_QUADS);
	glVertex3d(-14, 0, -24);
	glVertex3d(-17, 0, 20);
	glVertex3d(-17, heightOfWall, 20);
	glVertex3d(-14, heightOfWall, -24);
	endf;

	pshm;
	white;
	Box feet;
	glTranslated(-18.5, 0, 18.5);
	feet.drawOutside(Constraints(3, 10, 3), textures,flag);
	Cylinder top = Cylinder(1.2, 1.2, 1.5, 8, 1, false, 2);
	pshm;
	glTranslated(1.5, 10.5, 1.5);
	cull;
	top.drawSide();
	nocull;
	ppm;
	pshm;
	glTranslated(1.5, 11.46, 1.5);
	cull;
	mosqueDrawer.drawDome(Point(0, 0, 0), 0.24, Color(255, 34, 0),false,false);
	nocull;
	ppm;

	ppm;

	glColor3f(0.5, 0.2, 0.5);


	beg(GL_QUADS);
	glVertex3d(-17, 0, 20);
	glVertex3d(-5, 0, 20);
	glVertex3d(-5, heightOfWall, 20);
	glVertex3d(-17, heightOfWall, 20);
	endf;

	beg(GL_QUADS);
	glVertex3d(-5, 0, 20);
	glVertex3d(-5, 0, 27);
	glVertex3d(-5, heightOfWall, 27);
	glVertex3d(-5, heightOfWall, 20);
	endf;

	beg(GL_QUADS);
	glVertex3d(-5, 0, 27);
	glVertex3d(0, 0, 27);
	glVertex3d(0, heightOfWall, 27);
	glVertex3d(-5, heightOfWall, 27);
	endf;

	beg(GL_QUADS);
	glVertex3d(0, 0, 27);
	glVertex3d(7, 0, 25.5);
	glVertex3d(7, heightOfWall, 25.5);
	glVertex3d(0, heightOfWall, 27);
	endf;

	pshm;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255, 255, 255, 80);
	beg(GL_QUADS);
	glVertex3d(7, 0, 25.5);
	glVertex3d(14, 0, 20);
	glVertex3d(14, heightOfWall, 20);
	glVertex3d(7, heightOfWall, 25.5);
	endf;
	glDisable(GL_BLEND);
	ppm;

	glColor3f(0.5, 0.2, 0.5);

	beg(GL_QUADS);
	glVertex3d(14, 0, 20);
	glVertex3d(20, 0, 12);
	glVertex3d(20, heightOfWall, 12);
	glVertex3d(14, heightOfWall, 20);
	endf;

	beg(GL_QUADS);
	glVertex3d(20, 0, 12);
	glVertex3d(22, 0, 7);
	glVertex3d(22, heightOfWall, 7);
	glVertex3d(20, heightOfWall, 12);
	endf;

	beg(GL_QUADS);
	glVertex3d(22, 0, 7);
	glVertex3d(18, 0, -10);
	glVertex3d(18, heightOfWall, -10);
	glVertex3d(22, heightOfWall, 7);
	endf;

	beg(GL_QUADS);
	glVertex3d(18, 0, -10);
	glVertex3d(7, 0, -22);
	glVertex3d(7, heightOfWall, -22);
	glVertex3d(18, heightOfWall, -10);
	endf;


	beg(GL_QUADS);
	glVertex3d(7, 0, -22);
	glVertex3d(-14, 0, -24);
	glVertex3d(-14, heightOfWall, -24);
	glVertex3d(7, heightOfWall, -22);
	endf;

	

}

void DORdrawDomes() {
	int textures[] = { 0,0,0,0,0,0 };
	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;

	pshm;
	cull;
	mosqueDrawer.drawDome(Point(p + a / 2.0, 61.2, -p - a / 2.0), 7.2, Color(254, 203, 13));
	nocull;
	ppm;

	pshm;
	mosqueDrawer.drawDome(Point(p + a / 2.0, 61.4, -p - a / 2.0), 6.7, Color(254, 203, 13), true, false);
	ppm;

	pshm;
	glColor3ub(254, 203, 13);
	glTranslated(p + a / 2.0, 57, -p - a / 2.0);
	glRotated(90, 1, 0, 0);
	drawPipe(35.5, 38, 1, 40, textures, false);
	ppm;
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

void DomeOfTheRock() {


	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt;
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	int sectorCnt = 36; int radius = 4; int radius2 = 5;
	white;


	pshm;
	innerRoof();
	outerRoof();
	DORdrawDomes();
	glTranslated(0, 0.1, 0);
	white;
	DORdrawsides();
	ppm;

	pshm;
	glTranslated(p + a / 2.0 + 1, 0.2, -p - a / 2.0 - 2);
	db heightOfWall = 4;
	DORdrawFence(heightOfWall);
	ppm;

	pshm;
	glTranslated(p + a / 2.0, 0, -p - a / 2.0);
	glRotated(55, 0, 1, 0);
	DORdrawDrum();
	ppm;
	//moving the outer octagon to the base of the outer octagon 
	glTranslated(p - p2, 0, -inner.length);
	//move to the middle of the outer oct depending on the diameters of the oct
	glTranslated((a - b) / 2.0, 0, -(dia - dia2) / 2.0);
	DORdrawArcade();
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
	const Point points[4] = { Point(-200.0f, -2.0f, -200.0f),Point(-200.0f, -2.0f, 200.0f),Point(200.0f, -2.0f, 200.0f),Point(200.0f,-2.0f, -200.0f) };
	envDrawer.drawTiledLand(points, 10);
	

	if (camera->getMode() == THIRD_PERSON_CAMERA)
	{
		Point p = camera->getPosition();
		float angel = 180 + camera->getRotatedY(), r = 1.8;
		p.x += r * sin(angel * PIdiv180);
		p.z += r * cos(angel * PIdiv180);
		p.y = -0.9 * 0.04 * cos(4 * (abs(p.x) + abs(p.z)));


		personDrawer.drawPerson(p, angel, 10);
	}
	glTranslated(-50, -2, 20);

	//drawing the ocatgon shape 

	//the width of the dome of the rock is 18m and the height is 11m the width of the door is 2.75m and the height is 4.5m 
	//the virtual width and heights are 60 * 37 and the door is 15 * 10

	Box wall; int textures[] = { 0,0,0,0,0,0 };
	db texturess[] = { 0,0,0,0,0,0 };
	pshm;
	wall.drawOutside(Constraints(1,1,1), textures);
	ppm;


	Constraints outer = Constraints(60, 37, 1.5);
	Constraints inner = Constraints(48, 1.5, 3);
	db a = outer.width, b = inner.width;
	db p = a / srt, p2 = b / srt; 
	db dia = a + 2 * p, dia2 = b + 2 * p2;
	int sectorCnt = 36; int radius = 4; int radius2 = 5;
	white;

	

#pragma region design
	

	
	

#pragma endregion


	white;



#pragma region domeOfTheRock

	DomeOfTheRock();

#pragma endregion

	
	
	
	

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
