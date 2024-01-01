#ifndef AL_QIBLI_MOSQUE_DRAWER_H
#define AL_QIBLI_MOSQUE_DRAWER_H
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
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
	void drawSideUnit(int type);
private :
	int side[10],block[10],roof[10];
	double size = 1;
	void drawNormalWall(const Constraints& constraints);
	void drawRightWall();
	void drawRoof(const Constraints& constraints, int textureCount = 1);
	void drawLineOfCylinders(int count, GLuint texture);
	void drawFront();
	EnvDrawer envDrawer;
};

#endif 