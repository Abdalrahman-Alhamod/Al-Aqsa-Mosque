#include "PrimitiveDrawer.h"
#include "Constants.h";
#include <GL/gl.h>
#include <GL/glu.h>
long double pi = Constants().pi;

void PrimitiveDrawer::drawPoint(const Point& point) {
	glColor3f(point.getColor().getRedFloat(), point.getColor().getGreenFloat(), point.getColor().getBlueFloat());
	glPointSize(point.getSize());
	glBegin(GL_POINTS);
	glVertex3f(point.getX(), point.getY(), point.getZ());
	glEnd();
}

void PrimitiveDrawer::drawLine(const Point& start, const Point& end) {
	glBegin(GL_LINES);
	glColor3f(start.getColor().getRedFloat(), start.getColor().getGreenFloat(), start.getColor().getBlueFloat());
	glVertex3f(start.getX(), start.getY(), start.getZ());
	glColor3f(end.getColor().getRedFloat(), end.getColor().getGreenFloat(), end.getColor().getBlueFloat());
	glVertex3f(end.getX(), end.getY(), end.getZ());
	glEnd();
}

void PrimitiveDrawer::drawTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Color& color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_TRIANGLES);
	glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
	glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
	glVertex3f(vertex3.getX(), vertex3.getY(), vertex3.getZ());
	glEnd();
}
void PrimitiveDrawer::drawEquilateralTriangle(const Point& vertex, const GLfloat sideLength, const Color& color) {
	Point vertex2(vertex.getX() + sideLength, vertex.getY(), vertex.getZ());
	Point vertex3(vertex2.getX() - sideLength * cos(60.0 * 3.141592653589793 / 180.0), vertex2.getY() + sideLength * cos(60.0 * 3.141592653589793 / 180.0), vertex.getZ());

	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());

	glBegin(GL_TRIANGLES);

	glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
	glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
	glVertex3f(vertex3.getX(), vertex3.getY(), vertex3.getZ());

	glEnd();
}
void PrimitiveDrawer::drawQuad(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Point& vertex4, const Color& color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_QUADS);
	glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
	glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
	glVertex3f(vertex3.getX(), vertex3.getY(), vertex3.getZ());
	glVertex3f(vertex4.getX(), vertex4.getY(), vertex4.getZ());
	glEnd();
}

void PrimitiveDrawer::drawRect(const Point vertex, const GLfloat width, const GLfloat length, const Color color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_QUADS);
	glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
	glVertex3f(vertex.getX() + width, vertex.getY(), vertex.getZ());
	glVertex3f(vertex.getX() + width, vertex.getY() - length, vertex.getZ());
	glVertex3f(vertex.getX(), vertex.getY() - length, vertex.getZ());
	glEnd();
}

void PrimitiveDrawer::drawPolygon(const Point* vertices, int vertexCount, const Color& color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertexCount; i++) {
		glVertex3f(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
	}
	glEnd();
}
void PrimitiveDrawer::drawPalestineFlag() {
	PrimitiveDrawer drawer = PrimitiveDrawer();
	drawer.drawRect(Point(-8, 8, -10), 16, 16, Color(200, 200, 200));
	drawer.drawRect(Point(-3, 1.95, -6), 6, 1.3, Color(0, 120, 0));
	drawer.drawRect(Point(-3, 0.65, -6), 6, 1.3, Color(255, 255, 255));
	drawer.drawRect(Point(-3, -0.65, -6), 6, 1.3, Color(0, 0, 0));
	drawer.drawEquilateralTriangle(Point(-3, 1.95, -6), 3.9, Color(120, 0, 0));
}
void PrimitiveDrawer::drawCube(const Point& center, GLfloat size, const Color& color) {
	// Calculate half the size to determine vertex positions relative to the center.
	GLfloat halfSize = size * 0.5f;

	// Set the color for the cube.
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());

	glBegin(GL_QUADS);

	// Front face
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() + halfSize);

	// Back face
	glColor3f(120, 0, 0);
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() - halfSize);

	// Left face
	glColor3f(0, 120, 0);
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() - halfSize);

	// Right face
	glColor3f(0, 120, 120);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() - halfSize);

	// Top face
	glColor3f(0, 0, 120);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() + halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() + halfSize, center.getZ() + halfSize);

	// Bottom face
	glColor3f(120, 120, 0);
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() - halfSize);
	glVertex3f(center.getX() + halfSize, center.getY() - halfSize, center.getZ() + halfSize);
	glVertex3f(center.getX() - halfSize, center.getY() - halfSize, center.getZ() + halfSize);

	glEnd();
}
void PrimitiveDrawer::drawDomeOfRock() {
	glColor3f(1.0, 0.7, 0.0); // Orange color

	// Draw the base of the Dome
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, -10);       // Center of the base
	glVertex3f(3.0, 0.0, -10);       // Right-most point
	glVertex3f(2.0, 2.0, -10);       // Top-right point
	glVertex3f(-2.0, 2.0, -10);      // Top-left point
	glVertex3f(-3.0, 0.0, -10);      // Left-most point
	glEnd();


	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, -10);
	glVertex3f(0.0, 3.0, -10);
	glEnd();

	// Draw the dome
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float theta = i * pi / 180; // Convert degrees to radians
		float x = 1.5 * cos(theta); // Adjust radius as needed
		float y = 0.5 * sin(theta); // Adjust height as needed
		glVertex3f(x, y + 2.0, -10); // Offset by the height of the base
	}

	glEnd();

	glColor3f(0.2, 0.2, 0.2); // Dark Grey color
	// Draw the building
	glBegin(GL_POLYGON);
	glVertex3f(-4.0, 0.0, -10);       // Bottom-left corner
	glVertex3f(4.0, 0.0, -10);        // Bottom-right corner
	glVertex3f(4.0, -4.0, -10);        // Top-right corner
	glVertex3f(-4.0, -4.0, -10);       // Top-left corner
	glEnd();
}
void PrimitiveDrawer::drawSquare(const Point& vertex, const GLfloat sideLength, const Color& color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_QUADS);
	glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
	glVertex3f(vertex.getX() + sideLength, vertex.getY(), vertex.getZ());
	glVertex3f(vertex.getX() + sideLength, vertex.getY() - sideLength, vertex.getZ());
	glVertex3f(vertex.getX(), vertex.getY() - sideLength, vertex.getZ());
	glEnd();
}
void PrimitiveDrawer::draw2DEquilateralHouse(const Point& vertex, const GLfloat sideLength, const Color& color) {
	drawEquilateralTriangle(vertex, sideLength, color);
	drawSquare(vertex, sideLength, color);
}
void PrimitiveDrawer::draw2DHouse(const Point& top, const Point& upR, const Point& upL, const Point& downL, const Point& downR, const Color& color) {
	PrimitiveDrawer::drawTriangle(upL, upR, top, color);
	PrimitiveDrawer::drawQuad(upL, upR, downR, downL, color);
}
void PrimitiveDrawer::drawPyramid(const Point& top, const Point& baseTL, const Point& baseTR, const Point& baseDR, const Point& baseDL, const Color& color)
{
	PrimitiveDrawer::drawQuad(baseTL, baseTR, baseDR, baseDL, color);
	PrimitiveDrawer::drawTriangle(baseTR, baseTL, top, Color(0, 120, 0));
	PrimitiveDrawer::drawTriangle(baseTR, baseDR, top, Color(0, 0, 120));
	PrimitiveDrawer::drawTriangle(baseDR, baseDL, top, Color(0, 120, 120));
	PrimitiveDrawer::drawTriangle(baseDL, baseTL, top, Color(120, 0, 120));
}
void PrimitiveDrawer::drawCircle(const Point& center, const GLfloat rad, const Color& color) {
	float angle = 0, x = rad, y = 0, z = 0;
	for (angle = 0.0; angle <= 2 * pi + 0.1; angle += pi / 20) {
		Point first = Point(x, y, center.z);
		x = rad * cos(angle);
		y = rad * sin(angle);
		Point second = Point(x, y, center.z);
		PrimitiveDrawer::drawTriangle(center, first, second, color);
	}
}
void PrimitiveDrawer::drawConeBody(const Point& top, const GLfloat rad, const Color& color) {
	float angle = 0, x = rad, y = 0, z = 0;
	for (angle = 0.0; angle <= 2 * pi + 0.1; angle += pi / 20) {
		Point first = Point(x, y, top.z);
		x = rad * cos(angle);
		y = rad * sin(angle);
		Point second = Point(x, y, top.z);
		PrimitiveDrawer::drawTriangle(top, first, second, color);
	}
}
void PrimitiveDrawer::drawCone(const Point& base_center, const GLfloat base_rad, const GLfloat height, const Color& color) {
	PrimitiveDrawer::drawCircle(base_center, base_rad, color);
	Point top = Point(base_center.x, base_center.y, height);
	PrimitiveDrawer::drawConeBody(top, base_rad, Color(0, 0, 120));
}
void PrimitiveDrawer::drawCircleLine(const Point& center, const GLfloat rad, const Color& color) {
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	glBegin(GL_LINE_LOOP);
	for (GLfloat angle = 0.0f; angle <= (2.0f * pi) * 3.0f; angle += 0.01f) {
		GLfloat x = rad * cos(angle);
		GLfloat y = rad * sin(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}
void PrimitiveDrawer::drawRing(const Point& center, const float innerRad, const float outerRad, const Color& color)
{
	glColor3f(color.getRedFloat(), color.getGreenFloat(), color.getBlueFloat());
	const int numSegments = 100;  // Number of segments in the ring
	float angleOffset = 60.0f;  // Rotate the ring by 45 degrees (you can adjust this angle as needed)

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= numSegments; i++) {
		float angle = (2 * pi * i / numSegments) + (angleOffset * (pi / 180.0f));  // Apply the rotation angle
		float x = cos(angle);
		float y = sin(angle);

		glVertex3f(innerRad * x, innerRad * y, 0);
		glVertex3f(outerRad * x, outerRad * y, 0);
	}
	glEnd();
}