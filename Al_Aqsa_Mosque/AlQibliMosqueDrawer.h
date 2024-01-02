#ifndef AL_QIBLI_MOSQUE_DRAWER_H
#define AL_QIBLI_MOSQUE_DRAWER_H
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#define txt(s,t) glTexCoord2d(s,t)
#include "Point.h"
#include "Color.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Model_3DS.h"
#include "Box.h"
#include "Constraints.h"
#include "EnvDrawer.h";
class AlQibliMosqueDrawer
{
public :
	AlQibliMosqueDrawer();
	void drawAlQibliMosque();
	
private :
	int side[30],block[10],roof[10],carpet;
	float size = 1;
	void drawSideUnit(int type);
	void drawNormalWall(const Constraints& constraints, float textureCount=1);
	void drawLeftNormalWall(const Constraints& constraints, float textureCount);
	void drawRightWall();
	void drawRoof(const Constraints& constraints, float textureCount=1);
	void drawLineOfCylinders(int count, GLuint texture);
	void drawSmallColumnSideUnit(int count);
	void drawFront();
	void drawDoorFront();
	void drawFrontMainDoor();
	void drawSideShortWall();
	void drawMultiSmallWindowUnit(int count);
	void drawMultiBigWindowUnit(int count);
	void drawMultiHallway(int count);
	void drawMultiHalfCylinders(int count);
	void drawLeftMultiBigWindowUnit(int count);
	void drawTransparentWindow(int count);
	void drawRoof();
	void drawCarpet();
	bool drawInside = false;
	Box boxDrawer;
	EnvDrawer envDrawer;
};

#endif 