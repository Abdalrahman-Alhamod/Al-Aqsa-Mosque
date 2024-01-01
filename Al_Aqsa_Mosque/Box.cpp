#include "Box.h"
#include "Point.h"
#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glaux.h>		// Header File For The Glaux Library
#include <gl/glut.h>		// Header File For The Glut Library
#include <cmath>
#include "math3d.h"
#include "texture.h"
#include "Constraints.h"
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#define shadow glColor3f(0.0,0.0,0.0);glMultMatrixf((gf*)shadowMat)
#define txt(s,t) glTexCoord2d(s,t)

void Box::drawOutside(const Constraints& c, int texture[]) {
	db width = c.width;
	db height = c.height;
	db length = c.length;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	pshm;

	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(width, 0, 0);
	txt(1, 1);
	glVertex3d(width, 0, length);
	txt(0, 1);
	glVertex3d(0, 0, length);
	glEnd();
	ppm;

	//the top
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	txt(0, 0);
	glVertex3d(0, height, 0);
	txt(1, 0);
	glVertex3d(0, height, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(width, height, 0);
	glEnd();
	ppm;
	
	//the back face
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	txt(0, 0);
	glVertex3d(width, 0, 0);
	txt(1, 0);
	glVertex3d(0, 0, 0);
	txt(1, 1);
	glVertex3d(0, height, 0);
	txt(0, 1);
	glVertex3d(width, height, 0);
	glEnd();
	ppm;
	
	//the front face
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, length);
	txt(1, 0);
	glVertex3d(width, 0, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(0, height, length);
	glEnd();
	ppm;
	
	//the right side
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(0, 0, length);
	txt(1, 1);
	glVertex3d(0, height, length);
	txt(0, 1);
	glVertex3d(0, height, 0);
	glEnd();
	ppm;
	
	//the left side
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(width, 0, length);
	txt(1, 0);
	glVertex3d(width, 0, 0);
	txt(1, 1);
	glVertex3d(width, height, 0);
	txt(0, 1);
	glVertex3d(width, height, length);
	glEnd();
	ppm;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	ppm;


}

void Box::drawOutside(const Constraints& c,const int texture) {
	int textures[6] = { texture,texture, texture, texture, texture, texture };
	Box::drawOutside(c, textures);
}

void Box::drawOutside(const Constraints& c, const int sourroundTexture, const int baseTexture) {
	int textures[6] = { baseTexture,baseTexture, sourroundTexture, sourroundTexture,sourroundTexture,sourroundTexture };
	Box::drawOutside(c, textures);
}

void Box::drawOutside(const Constraints& c, int texture[], bool flag[]) {
	db width = c.width;
	db height = c.height;
	db length = c.length;
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	pshm;

	//the base
if(!flag[0])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(width, 0, 0);
	txt(1, 1);
	glVertex3d(width, 0, length);
	txt(0, 1);
	glVertex3d(0, 0, length);
	glEnd();
	ppm;
}

	//the top
if(!flag[1])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	txt(0, 0);
	glVertex3d(0, height, 0);
	txt(1, 0);
	glVertex3d(0, height, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(width, height, 0);
	glEnd();
	ppm;
}

	//the back face
if(!flag[2])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	txt(0, 0);
	glVertex3d(width, 0, 0);
	txt(1, 0);
	glVertex3d(0, 0, 0);
	txt(1, 1);
	glVertex3d(0, height, 0);
	txt(0, 1);
	glVertex3d(width, height, 0);
	glEnd();
	ppm;
}

	//the front face
if(!flag[3])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, length);
	txt(1, 0);
	glVertex3d(width, 0, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(0, height, length);
	glEnd();
	ppm;

}
	//the right side
if(!flag[4])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(0, 0, length);
	txt(1, 1);
	glVertex3d(0, height, length);
	txt(0, 1);
	glVertex3d(0, height, 0);
	glEnd();
	ppm;
}

	//the left side
if(!flag[5])
{
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(width, 0, length);
	txt(1, 0);
	glVertex3d(width, 0, 0);
	txt(1, 1);
	glVertex3d(width, height, 0);
	txt(0, 1);
	glVertex3d(width, height, length);
	glEnd();
	ppm;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	ppm;
}
}

void Box::drawInside(const Constraints& c, int texture[]) {

	db width = c.width;
	db height = c.height;
	db length = c.length;
	
	glEnable(GL_TEXTURE_2D);
	pshm;
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	//base
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(width, 0, 0);
	txt(1, 1);
	glVertex3d(width, 0, length);
	txt(0, 1);
	glVertex3d(0, 0, length);
	glEnd();
	ppm;

	//the top
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	//glNormal3f(0, -1, 0);
	txt(0, 0);
	glVertex3d(0, height, 0);
	txt(1, 0);
	glVertex3d(0, height, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(width, height, 0);
	glEnd();

	ppm;

	//the back face
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(0, height, 0);
	txt(1, 1);
	glVertex3d(width, height, 0);
	txt(0, 1);
	glVertex3d(width, 0, 0);
	glEnd();
	ppm;

	//the front face
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, -1);
	txt(0, 0);
	glVertex3d(0, 0, length);
	txt(1, 0);
	glVertex3d(width, 0, length);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(0, height, length);
	glEnd();
	ppm;

	//the right side
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	//glNormal3f(1, 0, 0);
	txt(0, 0);
	glVertex3d(0, 0, 0);
	txt(1, 0);
	glVertex3d(0, 0, length);
	txt(1, 1);
	glVertex3d(0, height, length);
	txt(0, 1);
	glVertex3d(0, height, 0);
	glEnd();
	ppm;

	//the left side
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, -1);
	txt(0, 0);
	glVertex3d(width, 0, 0);
	txt(1, 0);
	glVertex3d(width, height, 0);
	txt(1, 1);
	glVertex3d(width, height, length);
	txt(0, 1);
	glVertex3d(width, 0, length);
	glEnd();
	ppm;

	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CW);

	ppm;

	glDisable(GL_TEXTURE_2D);
}

void Box::drawShadow(const Constraints& c, M3DMatrix44f shadowMat) {
	
	db width = c.width;
	db height = c.height;
	db length = c.length;

	ppm;
	//the top
	pshm;
	shadow;
	glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);
	glVertex3d(0, height, 0);
	glVertex3d(0, height, length);
	glVertex3d(width, height, length);
	glVertex3d(width, height, 0);
	glEnd();
	ppm;

	//back face
	pshm;
	shadow;
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, -1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, height, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, 0, 0);
	glEnd();
	ppm;

	//the front face
	pshm;
	shadow;
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	glVertex3d(0, 0, length);
	glVertex3d(width, 0, length);
	glVertex3d(width, height, length);
	glVertex3d(0, height, length);
	glEnd();
	ppm;

	//the right sie
	pshm;
	shadow;
	glBegin(GL_QUADS);
	//glNormal3f(-1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glVertex3d(0, height, length);
	glVertex3d(0, height, 0);
	glEnd();
	ppm;

	//the left side
	pshm;
	shadow;
	glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	glVertex3d(width, 0, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, height, length);
	glVertex3d(width, 0, length);
	glEnd();
	ppm;

	ppm;
}

Box::Box(const Constraints& c, int texture1[], int texture2[], M3DMatrix44f shadowMat, bool shad) {
	glEnable(GL_CULL_FACE);
	drawOutside(c, texture1);
	drawInside(c, texture2);
	if (shad) {
		pshm;
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		drawShadow(c, shadowMat);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		ppm;
	}
	glDisable(GL_CULL_FACE);
}
Box::Box() {
}