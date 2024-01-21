#include "MosqueDrawer.h"
#include "Texture.h"

Model_3DS* MosqueDrawer::crescentModel = new Model_3DS();  // Initialize crescentModel

MosqueDrawer::MosqueDrawer() {
	glEnable(GL_TEXTURE_2D);

	carbet1 = LoadTexture((char*)"assets/materials/carbet1.bmp", 255);
	carbet2 = LoadTexture((char*)"assets/materials/carbet2.bmp", 255);
	window[0] = LoadTexture((char*)"assets/materials/window1.bmp", 255);
	window[1] = LoadTexture((char*)"assets/materials/window2.bmp", 255);
	window[2] = LoadTexture((char*)"assets/materials/window3.bmp", 255);
	window[3] = LoadTexture((char*)"assets/materials/window6.bmp", 255);
	window[4] = LoadTexture((char*)"assets/materials/window4.bmp", 255);
	window[5] = LoadTexture((char*)"assets/materials/window5.bmp", 255);

	glDisable(GL_TEXTURE_2D);

}

void MosqueDrawer::drawDome(const Point& position, const float size, const Color& color, int sectorCnt, bool inside, bool lines , bool smooth,bool crescent) {
	// Dome
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	Sphere sphere = Sphere(5 * size, sectorCnt,18,smooth, 2, true);
	glColor3f(color.redf, color.greenf, color.bluef);
	const float lineColor[4] = { 0,0,0,0 };
	if (inside) sphere.reverseNormals();
	if(lines) sphere.drawWithLines(lineColor);
	if (!lines) sphere.draw();
	//sphere.draw();
	glPopMatrix();
	
	if(crescent && !inside)
	{
		glPushMatrix();
		//Top Cone
		glPushMatrix();
		glTranslatef(position.x, position.y + 5.7 * size, position.z);
		glDisable(GL_TEXTURE_2D);
		Cylinder domeTop = Cylinder( 0.15 * size, 0.025 * size, 1.5 * size, 5);
		domeTop.setUpAxis(2);
		if (!color.equal(DOME_SHADOW)) {
			glColor3f(162.0f / 255.0f, 162.0f / 255.0f, 162.0f / 255.0f);
		}
		else {
			glColor3f(color.redf, color.greenf, color.bluef);
		}
		domeTop.draw();
		glPopMatrix();

		//Top Spheres
		for (float yOffset = 0.3; yOffset <= 0.92; yOffset += 0.3) {
			glPushMatrix();
			glTranslatef(position.x, position.y + (5 + yOffset) * size, position.z);
			Sphere topSphere = Sphere((0.2 - (yOffset * 0.1) + 0.02) * size,20, 20); // Adjust size based on yOffset
			topSphere.draw();
			glPopMatrix();
		}
		glColor4f(1, 1, 1, 1);
		 //Drawing crescentModel
		/*crescentModel->pos.x = position.x;
		crescentModel->pos.y = position.y + 5.8 * size;
		crescentModel->pos.z = position.z;
		crescentModel->scale = 0.01 * size;
		crescentModel->Draw();*/
		glPopMatrix();
	}
}


void MosqueDrawer::drawCarbet(const Point points[4], const int count, const int textureID) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(points[0].x, points[0].y, points[0].z);
	glTexCoord2f(count * 1.5, 0); glVertex3f(points[1].x, points[1].y, points[1].z);
	glTexCoord2f(count * 1.5, count); glVertex3f(points[2].x, points[2].y, points[2].z);
	glTexCoord2f(0, count); glVertex3f(points[3].x, points[3].y, points[3].z);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();
}

void MosqueDrawer::drawPrayerCarbet1(const Point points[4], const int count) {
	drawCarbet(points, count, carbet1);
}

void MosqueDrawer::drawPrayerCarbet2(const Point points[4], const int count) {
	drawCarbet(points, count, carbet2);
}

void MosqueDrawer::drawRectWithAlpha(const Point points[4], const int alpha, const int textureID) {
	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glColor4ub(255, 255, 255, alpha);  // Set alpha value for transparency

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(points[0].x, points[0].y, points[0].z);
	glTexCoord2f( 1, 0); glVertex3f(points[1].x, points[1].y, points[1].z);
	glTexCoord2f( 1, 1); glVertex3f(points[2].x, points[2].y, points[2].z);
	glTexCoord2f(0, 1); glVertex3f(points[3].x, points[3].y, points[3].z);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
}

void MosqueDrawer::drawWindow(const int size,const int alpha, const int windowNum) {
	const Point points[4] = { Point(size, -size*2, 0),Point(0, -0-size * 2, 0),Point(0, 0, 0),Point(size, 0, 0) };
	drawRectWithAlpha(points,alpha,  window[windowNum]);
}