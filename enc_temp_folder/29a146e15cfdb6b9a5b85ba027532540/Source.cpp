#define ZOOM_INCREASE true
#define ZOOM_DECREASE false
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()


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
#include "Constraints.h"
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


int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);

	// Initialize Camera
	Camera::cameraInit();
	Camera::changeMode();

	// Initialize Console
	//console.init();
	// Print testing message
	//console.print("Hello, Console!");

	// Initialize Texture Images
	initTextures();

	// Initialize Shadows
	//initShadows();

	// Initialize Objects
	mosqueDrawer = MosqueDrawer();
	envDrawer = EnvDrawer();

	personDrawer = PersonDrawer();

	return TRUE;										// Initialization Went OK
}

float angle = 90;
GLfloat zoomFactor = 1.0f; // Adjust this value based on your zoom requirements

void square(void) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood);
	glTranslatef(0, 2.5, 0);
	glScalef(2, 2, 2);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void bench(void) {
	glPushMatrix();
	glColor4f(1, 1, 1, 0.4);
	glTranslatef(0, -2.5, 0);
	glScalef(4, 2, 4);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -0.5);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, 1);
	glEnd();
	glPopMatrix();
}
void testReflection() {
	// Disable the color mask and depth mask
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);

	// Enable stencil testing
	glEnable(GL_STENCIL_TEST);

	// Set the stencil buffer to replace the next lot of data
	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	// Set the data plane to be replaced (assuming `bench` is a function to set the data plane)
	bench();

	// Enable the color mask and depth mask
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);

	// Set the stencil buffer to keep the next lot of data
	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// Disable depth testing of the reflection
	glDisable(GL_DEPTH_TEST);

	// Apply transformations to draw the reflection
	glPushMatrix();
	glScalef(1.0f, -1.0f, 1.0f);  // Flip the reflection vertically
	glTranslatef(0, 2, 0);        // Translate the reflection onto the drawing plane
	glRotatef(angle, 0, 1, 0);     // Rotate the reflection
	square();                      // Draw the square as our reflection
	glPopMatrix();

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Disable stencil testing
	glDisable(GL_STENCIL_TEST);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the bench with alpha blending
	bench();

	// Disable alpha blending
	glDisable(GL_BLEND);

	// Rotate the square and draw it
	glRotatef(angle, 0, 1, 0);
	square();

}

void testEnv() {
	// Testing Camera

	glPushMatrix();
	glTranslatef(-4, 2, +2);
	glColor3f(0, 0, 1);
	//PrimitiveDrawer().drawCube(Point(0, 0, -5), 2, Color(255, 255, 255));   // Nedd fixing for lighting
	auxSolidCube(2);
	glPopMatrix();

	// Testing Light & Shadows

	// Set light position in world coordinates ( fix moving with camera bug)
	glLightfv(GL_LIGHT0, GL_POSITION, envDrawer.LightPos);

	// Lighting Destination Test
	
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	// Shadow
	initShadows();
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glColor3b(0, 0, 0);
	glMultMatrixf((GLfloat*)shadowMat);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();
	glEnable(GL_LIGHTING);


	// Test Texture
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0, 2, -20);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);       glVertex3f(5, -5, 0);
	glTexCoord2f(-1, 0);       glVertex3f(5, 5, 0);
	glTexCoord2f(-1, -1);       glVertex3f(-5, 5, 0);
	glTexCoord2f(0, -1);       glVertex3f(-5, -5, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslated(30, 10, 10);
	testReflection();
	glPopMatrix();

	if (keys[VK_ADD]) {
		updateZoomFactor(ZOOM_INCREASE);
	}
	if (keys[VK_SUBTRACT]) {
		updateZoomFactor(ZOOM_DECREASE);
	}


	// Rotate and change rotate angle
	/*glRotatef(angle, 0.0f, 0.0f, 1.0f);
	angle++;

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3i(0, 1, -6);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3i(-1, -1, -6);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(1, -1, -6);

	glEnd();*/
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
	camera->decodeKeyboard(keys, 0.1);
	//camera->decodeMouse(mouseX, mouseY, isClicked, isRClicked);

	//testEnv();
	const Point points[4] = { Point(-30.0f, -2.0f, -20.0f),Point(-30.0f, -2.0f, 20.0f),Point(40.0f, -2.0f, 20.0f),Point(40.0f, -2.0f, -20.0f) };
	envDrawer.drawTiledLand(points, 10);
	//envDrawer.drawPillar(2, 10, 1);
	//envDrawer.drawHalfCylinderInRectangularPrism(1, Constraints(1,3,3), 2);
	glPushMatrix();
	glTranslated(0, 3.2, +7);
	envDrawer.drawCubedMinaret(1,1);
	glTranslated(0,0.51,0);
	envDrawer.drawCylindricMinaret(1,1);
	glPopMatrix();
	//envDrawer.drawGrassLand(points, 10);
	//mosqueDrawer.drawPrayerCarbet1(points, 10);
	//mosqueDrawer.drawPrayerCarbet2(points, 10);

	//envDrawer.drawCitySkyBox(Point(0, 0, 0), Constraints(1000, 1000, 1000));
	envDrawer.drawCloudsSkyBox(Point(0, 0, 0), Constraints(1000, 1000, 1000));

	//envDrawer.drawSmallTree(Point(5, -2, -5), 1);
	//envDrawer.drawBigTree(Point(15, -2, -5), 1);
	//envDrawer.drawTank(Point(-5, -2, -5), 1);

	if (camera->getMode() == THIRD_PERSON_CAMERA)
	{
		Point p = camera->getPosition();
		float angel = 180 + camera->getRotatedY(), r = 1.8;

		/* trying to fix weird movement while pressing movement letters
		p.x *= 0.95;
		p.z *= 0.95; */

		p.x += r * sin(angel * PIdiv180);
		p.z += r * cos(angel * PIdiv180);
		p.y = -0.9 * 0.02 * cos(4 * (abs(p.x) + abs(p.z)) );

		//console.print(int(sqrt(pow(p.x - c.x, 2) + pow(p.z - c.z, 2))));
		//console.print(personDrawer.v());
		personDrawer.drawPerson(p, angel, 10);
	}
		//personDrawer.drawPerson(Point(0,0,-5), 0, 10);
	//envDrawer.drawGarden(Point(0, -1, 20), 30, 10, 10,1,true);

	//const Point passagePoints[4] = { Point(-35.0f, -2.0f, -20.0f),Point(-35.0f, -2.0f, 20.0f),Point(-30.0f, -2.0f, 20.0f),Point(-30.0f, -2.0f, -20.0f) };
	//envDrawer.drawPassage(passagePoints, 10);

	//const Point streetPoints[4] = { Point(50.0f, -2.0f, -20.0f), Point(40.0f, -2.0f, -20.0f),Point(40.0f, -2.0f, 20.0f),Point(50.0f, -2.0f, 20.0f) };
	//envDrawer.drawStreet(streetPoints, 1);

	//// Test Column
	//glPushMatrix();
	//glTranslatef(-20, 10, 0);
	//envDrawer.drawPillar(1);
	//glPopMatrix();
	//

	////added by mohammad yassen
	//pshm;
	//glTranslated(-11, 0, 0);
	//int inside[6];
	//inside[0] = wood;
	//inside[1] = wood;
	//inside[2] = wood;
	//inside[3] = wood;
	//inside[4] = wood;
	//inside[5] = wood;

	//int outside[6];
	//outside[0] = ground;
	//outside[1] = ground;
	//outside[2] = ground;
	//outside[3] = ground;
	//outside[4] = ground;
	//outside[5] = ground;
	////shadow won't work because the flag is false in default
	//pshm;
	//glTranslated(-5, 0, 0);
	//Box b1 = Box();
	//b1.drawOutside(1, 1, 1, outside);
	//ppm;
	//ppm;
	//Box b(5, 5, 10, inside, outside, shadowMat,true);

	//ppm;

	//// Test Windows
	//int alpha =200;
	//glTranslatef(-10, 10, 0);
	//mosqueDrawer.drawWindow(1,alpha,0);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(-5, 10, 0);
	//mosqueDrawer.drawWindow(1, alpha, 1);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(0, 10, 0);
	//mosqueDrawer.drawWindow(1, alpha, 2);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(5, 10, 0);
	//mosqueDrawer.drawWindow(1, alpha, 3);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(10, 10, 0);
	//mosqueDrawer.drawWindow(1, alpha, 4);
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(15, 10, 0);
	//mosqueDrawer.drawWindow(1, alpha, 5);
	//glPopMatrix();

	//mosqueDrawer.drawDome(Point(5, -2, 0), 0.5, GOLDEN_DOME);
	//mosqueDrawer.drawDome(Point(5, -2, 7), 0.5, SILVER_DOME);

	/*glPushMatrix();
	glTranslatef(0, 10, 0);
	envDrawer.drawHallway(2, 8, 4, 10, 6);
	envDrawer.drawArchway(1, 3, 3, 6);
	glPopMatrix();*/

	// envDrawer.drawFountain(Point(0, 15, 0), 1);

	/*for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(20 * i, 20, 0);
		envDrawer.drawBuidling(1, i);
		glPopMatrix();
	}*/

	// envDrawer.drawLightingPillar(Point(0, 0, 0), 1);
	


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
