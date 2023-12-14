#include "Box.h"
#include "Point.h"
#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <glut.h>		// Header File For The Glut Library
#include <cmath>
#include "math3d.h"
#include <texture.h>
#define db double
#define gf GLfloat
#define pshm glPushMatrix()
#define ppm glPopMatrix()
#define shadow 	glMultMatrixf((gf*)shadowMat); glColor3f(0.5,0.5,0.5);
#define txt(s,t) glTexCoord2d(s,t)

void Box::drawOutside(db width, db length, db height, int texture[]) {
	//pshm;
	//
	//glEnable(GL_TEXTURE_2D);
	////base 
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glBegin(GL_QUADS);
	//glNormal3f(0, -1, 0);
	//txt(0, 0);
	//Point p1(0, 0, 0);
	//txt(1, 0);
	//Point p2(width, 0, 0);
	//txt(1, 1);
	//Point p3(width, 0, length);
	//txt(0, 1);
	//Point p4(0, 0, length);
	//glEnd();
	//
	////the top
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);
	//txt(0, 0);
	//Point p5(0, height, 0);
	//txt(1, 0);
	//Point p6(0, height, length);
	//txt(1, 1);
	//Point p7(width, height, length);
	//txt(0, 1);
	//Point p8(width, height, 0);
	//glEnd();
	//ppm;
	//
	////the back face
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, -1);
	//txt(0, 0);
	//Point p9(0, 0, 0);
	//txt(1, 0);
	//Point p10(0, height, 0);
	//txt(1, 1);
	//Point p11(width, height, 0);
	//txt(0, 1);
	//Point p12(width, 0, 0);
	//glEnd();
	//ppm;
	//
	////the front face
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[3]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	//txt(0, 0);
	//Point p13(0, 0, length);
	//txt(1, 0);
	//Point p14(width, 0, length);
	//txt(1, 1);
	//Point p15(width, height, length);
	//txt(0, 1);
	//Point p16(0, height, length);
	//glEnd();
	//ppm;
	//
	////the left side
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[4]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(-1, 0, 0);
	//txt(0, 0);
	//Point p17(0, 0, 0);
	//txt(1, 0);
	//Point p18(0, 0, length);
	//txt(1, 1);
	//Point p19(0, height, length);
	//txt(0, 1);
	//Point p20(0, height, 0);
	//glEnd();
	//ppm;
	//
	////the right side
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[5]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	//txt(0, 0);
	//Point p21(width, 0, 0);
	//txt(1, 0);
	//Point p22(width, height, 0);
	//txt(1, 1);
	//Point p23(width, height, length);
	//txt(0, 1);
	//Point p24(width, 0, length);
	//glEnd();
	//ppm;
	//
	//ppm;
	//base 
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
	//glColor3ub(12, 213, 122);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
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

}

void Box::drawInside(db width, db length, db height, int texture[]) {
	//pshm;
	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);

	//glEnable(GL_TEXTURE_2D);
	////base 
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glBegin(GL_QUADS);
	//glNormal3f(0, -1, 0);
	//txt(0, 0);
	//Point p1(0, 0, 0);
	//txt(1, 0);
	//Point p2(width, 0, 0);
	//txt(1, 1);
	//Point p3(width, 0, length);
	//txt(0, 1);
	//Point p4(0, 0, length);
	//glEnd();

	////the top
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 1, 0);
	//txt(0, 0);
	//Point p5(0, height, 0);
	//txt(1, 0);
	//Point p6(0, height, length);
	//txt(1, 1);
	//Point p7(width, height, length);
	//txt(0, 1);
	//Point p8(width, height, 0);
	//glEnd();
	//ppm;

	////the back face
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, -1);
	//txt(0, 0);
	//Point p9(0, 0, 0);
	//txt(1, 0);
	//Point p10(0, height, 0);
	//txt(1, 1);
	//Point p11(width, height, 0);
	//txt(0, 1);
	//Point p12(width, 0, 0);
	//glEnd();
	//ppm;


	////the front face
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[3]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	//txt(0, 0);
	//Point p13(0, 0, length);
	//txt(1, 0);
	//Point p14(width, 0, length);
	//txt(1, 1);
	//Point p15(width, height, length);
	//txt(0, 1);
	//Point p16(0, height, length);
	//glEnd();
	//ppm;

	////the left side
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[4]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(-1, 0, 0);
	//txt(0, 0);
	//Point p17(0, 0, 0);
	//txt(1, 0);
	//Point p18(0, 0, length);
	//txt(1, 1);
	//Point p19(0, height, length);
	//txt(0, 1);
	//Point p20(0, height, 0);
	//glEnd();
	//ppm;

	////the right side
	//pshm;
	//glBindTexture(GL_TEXTURE_2D, texture[5]);
	////glColor3ub(12, 213, 122);
	//glBegin(GL_QUADS);
	//glNormal3f(0, 0, 1);
	//txt(0, 0);
	//Point p21(width, 0, 0);
	//txt(1, 0);
	//Point p22(width, height, 0);
	//txt(1, 1);
	//Point p23(width, height, length);
	//txt(0, 1);
	//Point p24(width, 0, length);
	//glEnd();
	//ppm;
	//glFrontFace(GL_CW);
	//ppm;
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

	//the top
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glColor3ub(12, 213, 122);
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

	//the back face
	pshm;
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glColor3ub(12, 213, 122);
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
	pshm;

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
}

void Box::drawShadow(db width, db length, db height, M3DMatrix44f shadowMat) {
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p1(0, 0, 0);
	txt(1, 0);
	Point p2(width, 0, 0);
	txt(1, 1);
	Point p3(width, 0, length);
	txt(0, 1);
	Point p4(0, 0, length);
	glEnd();

	//the top
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p5(0, height, 0);
	txt(1, 0);
	Point p6(0, height, length);
	txt(1, 1);
	Point p7(width, height, length);
	txt(0, 1);
	Point p8(width, height, 0);
	glEnd();
	ppm;

	//the back face
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p9(0, 0, 0);
	txt(1, 0);
	Point p10(0, height, 0);
	txt(1, 1);
	Point p11(width, height, 0);
	txt(0, 1);
	Point p12(width, 0, 0);
	glEnd();
	ppm;


	//the front face
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p13(0, 0, length);
	txt(1, 0);
	Point p14(width, 0, length);
	txt(1, 1);
	Point p15(width, height, length);
	txt(0, 1);
	Point p16(0, height, length);
	glEnd();
	ppm;

	//the left side
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p17(0, 0, 0);
	txt(1, 0);
	Point p18(0, 0, length);
	txt(1, 1);
	Point p19(0, height, length);
	txt(0, 1);
	Point p20(0, height, 0);
	glEnd();
	ppm;

	//the right side
	pshm;
	shadow;
	glBegin(GL_QUADS);
	txt(0, 0);
	Point p21(width, 0, 0);
	txt(1, 0);
	Point p22(width, height, 0);
	txt(1, 1);
	Point p23(width, height, length);
	txt(0, 1);
	Point p24(width, 0, length);
	glEnd();
	ppm;

	ppm;
	//the top
	pshm;
	glDisable(GL_TEXTURE_2D);
	shadow;
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3d(0, height, 0);
	glVertex3d(0, height, length);
	glVertex3d(width, height, length);
	glVertex3d(width, height, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	ppm;

	//back face
	pshm;
	glDisable(GL_TEXTURE_2D);
	shadow;
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, height, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, 0, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	ppm;

	//the front face
	pshm;
	glDisable(GL_TEXTURE_2D);
	shadow;
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3d(0, 0, length);
	glVertex3d(width, 0, length);
	glVertex3d(width, height, length);
	glVertex3d(0, height, length);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	ppm;

	//the right sie
	pshm;
	glDisable(GL_TEXTURE_2D);
	shadow;
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glVertex3d(0, height, length);
	glVertex3d(0, height, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	ppm;

	//the left side
	pshm;
	glDisable(GL_TEXTURE_2D);
	shadow;
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3d(width, 0, 0);
	glVertex3d(width, height, 0);
	glVertex3d(width, height, length);
	glVertex3d(width, 0, length);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	ppm;

}

Box::Box(db width, db length, db height, int texture1[], int texture2[], M3DMatrix44f shadowMat, bool shad) {
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	drawOutside(width, length, height, texture1);
	drawInside(width, length, height, texture2);
	if (shad) {
		drawShadow(width, length, height, shadowMat);
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
}