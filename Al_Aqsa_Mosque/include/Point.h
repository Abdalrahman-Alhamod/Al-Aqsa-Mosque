#pragma once

// Including necessary header files for the Point class
#include <windows.h>      // Header File For Windows
#include <gl\gl.h>        // Header File For the OpenGL32 Library
#include <gl\glu.h>       // Header File For the GLu32 Library
#include <gl\glaux.h>      // Header File For the Glaux Library
#include <math.h>         // Header File For the Math Library
#include "Color.h"        // Header File For the Color Library

/**
 * @class Point
 * @brief Represents a 2D or 3D point in space with various attributes.
 */
class Point
{
public:
    /**
     * @brief Default constructor for a Point.
     */
    Point();

    /**
     * @brief Constructor to create a 3D Point with provided coordinates.
     * @param x The X-axis coordinate.
     * @param y The Y-axis coordinate.
     * @param z The Z-axis coordinate.
     */
    Point(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Constructor to create a 3D Point with provided coordinates and size.
     * @param x The X-axis coordinate.
     * @param y The Y-axis coordinate.
     * @param z The Z-axis coordinate.
     * @param size The size of the point.
     */
    Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size);

    /**
     * @brief Constructor to create a 3D Point with provided coordinates, size, and an option for smooth shading.
     * @param x The X-axis coordinate.
     * @param y The Y-axis coordinate.
     * @param z The Z-axis coordinate.
     * @param size The size of the point.
     * @param smooth True for smooth shading, false for flat shading.
     */
    Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLboolean smooth);

    /**
     * @brief Constructor to create a 3D Point with provided coordinates and color.
     * @param x The X-axis coordinate.
     * @param y The Y-axis coordinate.
     * @param z The Z-axis coordinate.
     * @param color The color of the point.
     */
    Point(GLfloat x, GLfloat y, GLfloat z, Color color);

    /**
     * @brief Constructor to create a 3D Point with provided coordinates, size, an option for smooth shading, and color.
     * @param x The X-axis coordinate.
     * @param y The Y-axis coordinate.
     * @param z The Z-axis coordinate.
     * @param size The size of the point.
     * @param smooth True for smooth shading, false for flat shading.
     * @param color The color of the point.
     */
    Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLboolean smooth, Color color);

    // Member variables
    GLfloat x;        ///< X-axis coordinate
    GLfloat y;        ///< Y-axis coordinate
    GLfloat z;        ///< Z-axis coordinate
    GLfloat size = 1; ///< Point size
    GLboolean smooth = false; ///< True for smooth shading; False for flat shading
    Color color = Color(1.0f, 1.0f, 1.0f); ///< Point color

    /**
     * @brief Get the X-coordinate of the point.
     * @return The X-coordinate.
     */
    GLfloat getX() const;

    /**
     * @brief Get the Y-coordinate of the point.
     * @return The Y-coordinate.
     */
    GLfloat getY() const;

    /**
     * @brief Get the Z-coordinate of the point.
     * @return The Z-coordinate.
     */
    GLfloat getZ() const;

    /**
     * @brief Set the X-coordinate of the point.
     * @param x The new X-coordinate.
     */
    void setX(GLfloat x);

    /**
     * @brief Set the Y-coordinate of the point.
     * @param y The new Y-coordinate.
     */
    void setY(GLfloat y);

    /**
     * @brief Set the Z-coordinate of the point.
     * @param z The new Z-coordinate.
     */
    void setZ(GLfloat z);

    /**
     * @brief Get the size of the point.
     * @return The size of the point.
     */
    GLfloat getSize() const;

    /**
     * @brief Set the size of the point.
     * @param size The new size of the point.
     */
    void setSize(GLfloat size);

    /**
     * @brief Check if smooth shading is enabled for the point.
     * @return True if smooth shading is enabled, false if flat shading is used.
     */
    GLboolean isSmooth() const;

    /**
     * @brief Set the shading mode for the point.
     * @param smooth True for smooth shading, false for flat shading.
     */
    void setSmooth(GLboolean smooth);

    /**
     * @brief Get the color of the point.
     * @return The color of the point.
     */
    Color getColor() const;

    /**
     * @brief Set the color of the point.
     * @param color The new color of the point.
     */
    void setColor(const Color& color);
};
