#pragma once

#include "Color.h"
#include "Point.h"
#include "Constants.h";
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * @class PrimitiveDrawer
 * @brief A utility class for drawing various geometric primitives using specified colors.
 */
class PrimitiveDrawer
{
public:
	/**
	 * @brief Draw a point at the specified position with the given color.
	 * @param point The point to be drawn.
	 * @param color The color of the point.
	 */
	void drawPoint(const Point& point);

	/**
	 * @brief Draw a line segment between two points with the given color.
	 * @param start The starting point of the line.
	 * @param end The ending point of the line.
	 * @param color The color of the line.
	 */
	void drawLine(const Point& start, const Point& end);

	/**
	 * @brief Draw a triangle with three specified vertices and the given color.
	 * @param vertex1 The first vertex of the triangle.
	 * @param vertex2 The second vertex of the triangle.
	 * @param vertex3 The third vertex of the triangle.
	 * @param color The color of the triangle.
	 */
	void drawTriangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Color& color);

	/**
	 * @brief Draw a quad with four specified vertices and the given color.
	 * @param vertex1 The first vertex of the quad.
	 * @param vertex2 The second vertex of the quad.
	 * @param vertex3 The third vertex of the quad.
	 * @param vertex4 The fourth vertex of the quad.
	 * @param color The color of the quad.
	 */
	void drawQuad(const Point& vertex1, const Point& vertex2, const Point& vertex3, const Point& vertex4, const Color& color);
	/**
	* @brief Draw an equilateral triangle pointing to the right from a given point.
	*
	* This method draws an equilateral triangle with one side parallel to the right, starting from the provided vertex,
	* with the specified side length and color.
	*
	* @param vertex The starting point of the triangle.
	* @param sideLength The length of each side of the equilateral triangle.
	* @param color The color of the triangle.
	*/
	void drawEquilateralTriangle(const Point& vertex, const GLfloat sideLength, const Color& color);
	/**
	* @brief Draw a rectangle with the specified vertex, width, length, and color.
	*
	* This method draws a rectangle starting from the provided vertex, with the given width, length, and color.
	*
	* @param vertex The bottom-left vertex of the rectangle.
	* @param width The width of the rectangle.
	* @param length The length of the rectangle.
	* @param color The color of the rectangle.
	*/
	void drawRect(const Point vertex, const GLfloat width, const GLfloat length, const Color color);

	/**
	 * @brief Draw a polygon with an array of vertices and the given color.
	 * @param vertices An array of points representing the polygon vertices.
	 * @param vertexCount The number of vertices in the polygon.
	 * @param color The color of the polygon.
	 */
	void drawPolygon(const Point* vertices, int vertexCount, const Color& color);
	/**
	* @brief Draw the flag of Palestine.
	*
	* This method draws the flag of Palestine, which consists of multiple colored rectangles and an equilateral triangle.
	*
	* - A pale gray rectangle at the top.
	* - A green rectangle below the gray one.
	* - A white rectangle below the green one.
	* - A black rectangle at the bottom.
	* - A red equilateral triangle on the green rectangle, pointing to the right.
	*/
	void drawPalestineFlag();
	/**
	* @brief Draw a colored cube.
	*
	* This method draws a cube centered at the specified point with the given size and color. The cube is filled with the provided color. The cube consists of six faces, each with a color defined by the input color.
	*
	* @param center The center point of the cube.
	* @param size The size of the cube.
	* @param color The color of the cube.
	*/
	void drawCube(const Point& center, GLfloat size, const Color& color);
	/**
	* @brief Draw a simplified representation of the Dome of the Rock with a building.
	*
	* This method visually represents the Dome of the Rock, including its base, dome, and a building structure underneath. The Dome is depicted in a vibrant orange color, and a dark grey rectangular building is drawn below it. A vertical line emphasizes the central axis of the Dome.
	*
	* @note This is a highly abstract representation and not to scale.
	*/
	void drawDomeOfRock();

	/**
	* @brief Draw a square with the specified vertex, side length, and color.
	*
	* This method draws a square starting from the provided vertex, with the given side length and color.
	*
	* @param vertex The bottom-left vertex of the square.
	* @param sideLength The length of each side of the square.
	* @param color The color of the square.
	*/
	void drawSquare(const Point& vertex, const GLfloat sideLength, const Color& color);

	/**
	 * @brief Draw a 2D equilateral house at the specified vertex, with a side length and color.
	 *
	 * This method combines the drawing of an equilateral triangle and a square to create a 2D representation of a house.
	 *
	 * @param vertex The vertex where the house is centered.
	 * @param sideLength The side length of the equilateral triangle and square.
	 * @param color The color of the house.
	 */
	void draw2DEquilateralHouse(const Point& vertex, const GLfloat sideLength, const Color& color);

	/**
	 * @brief Draw a 2D house using specified vertices and a color.
	 *
	 * This method creates a 2D house by drawing a triangle (roof) and a quadrilateral (base).
	 *
	 * @param top The top vertex of the house.
	 * @param upR The upper-right vertex of the base.
	 * @param upL The upper-left vertex of the base.
	 * @param downL The lower-left vertex of the base.
	 * @param downR The lower-right vertex of the base.
	 * @param color The color of the house.
	 */
	void draw2DHouse(const Point& top, const Point& upR, const Point& upL, const Point& downL, const Point& downR, const Color& color);

	/**
	 * @brief Draw a pyramid with a specified top vertex, base vertices, and color.
	 *
	 * This method creates a pyramid shape with the specified top vertex, base vertices, and color. The base is a quadrilateral, and each triangular face has a distinct color.
	 *
	 * @param top The top vertex of the pyramid.
	 * @param baseTL The top-left vertex of the base.
	 * @param baseTR The top-right vertex of the base.
	 * @param baseDR The bottom-right vertex of the base.
	 * @param baseDL The bottom-left vertex of the base.
	 * @param color The color of the pyramid.
	 */
	void drawPyramid(const Point& top, const Point& baseTL, const Point& baseTR, const Point& baseDR, const Point& baseDL, const Color& color);

	/**
	 * @brief Draw a circle centered at the specified point with the given radius and color.
	 *
	 * This method draws a circle in the XY plane centered at the specified point with the provided radius and color.
	 *
	 * @param center The center point of the circle.
	 * @param rad The radius of the circle.
	 * @param color The color of the circle.
	 */
	void drawCircle(const Point& center, const GLfloat rad, const Color& color);

	/**
	 * @brief Draw the body of a cone with the specified top vertex, base radius, and color.
	 *
	 * This method draws the body of a cone starting from the specified top vertex, with the given base radius and color.
	 *
	 * @param top The top vertex of the cone.
	 * @param rad The radius of the base.
	 * @param color The color of the cone body.
	 */
	void drawConeBody(const Point& top, const GLfloat rad, const Color& color);

	/**
	 * @brief Draw a cone with a base centered at the specified point, a base radius, height, and color.
	 *
	 * This method draws a cone with the specified base, base radius, height, and color.
	 *
	 * @param base_center The center point of the base of the cone.
	 * @param base_rad The radius of the base.
	 * @param height The height of the cone.
	 * @param color The color of the cone.
	 */
	void drawCone(const Point& base_center, const GLfloat base_rad, const GLfloat height, const Color& color);

	/**
	 * @brief Draw a circular line centered at the specified point with the given radius and color.
	 *
	 * This method draws a circular line in the XY plane centered at the specified point with the provided radius and color.
	 *
	 * @param center The center point of the circular line.
	 * @param rad The radius of the circular line.
	 * @param color The color of the circular line.
	 */
	void drawCircleLine(const Point& center, const GLfloat rad, const Color& color);

	/**
	 * @brief Draw a ring centered at the specified point with inner and outer radii and color.
	 *
	 * This method draws a ring centered at the specified point with inner and outer radii and color.
	 *
	 * @param center The center point of the ring.
	 * @param innerRad The inner radius of the ring.
	 * @param outerRad The outer radius of the ring.
	 * @param color The color of the ring.
	 */
	void drawRing(const Point& center, const float innerRad, const float outerRad, const Color& color);

private:
};
