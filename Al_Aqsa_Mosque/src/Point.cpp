#include "Point.h"

// Default Constructor
Point::Point() {
    // Initialize the coordinates and other attributes to their default values.
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    size = 1.0f;
    smooth = false;
    color = Color(1.0f, 1.0f, 1.0f);
}

// Constructor to create a 3D Point with provided coordinates
Point::Point(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
    // Initialize other attributes to their default values.
    size = 1.0f;
    smooth = false;
    color = Color(1.0f, 1.0f, 1.0f);
}

// Constructor to create a 3D Point with provided coordinates and size
Point::Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->size = size;
    // Initialize other attributes to their default values.
    smooth = false;
    color = Color(1.0f, 1.0f, 1.0f);
}

// Constructor to create a 3D Point with provided coordinates, size, and an option for smooth shading
Point::Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLboolean smooth) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->size = size;
    this->smooth = smooth;
    // Initialize other attributes to their default values.
    color = Color(1.0f, 1.0f, 1.0f);
}

// Constructor to create a 3D Point with provided coordinates and color
Point::Point(GLfloat x, GLfloat y, GLfloat z, Color color) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = color;
    // Initialize other attributes to their default values.
    size = 1.0f;
    smooth = false;
}

// Constructor to create a 3D Point with provided coordinates, size, an option for smooth shading, and color
Point::Point(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLboolean smooth, Color color) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->size = size;
    this->smooth = smooth;
    this->color = color;
}
/**
 * @brief Get the X-coordinate of the point.
 * @return The X-coordinate.
 */
GLfloat Point::getX() const {
    return x;
}
/**
 * @brief Get the Y-coordinate of the point.
 * @return The Y-coordinate.
 */
GLfloat Point::getY() const {
    return y;
}

/**
 * @brief Get the Z-coordinate of the point.
 * @return The Z-coordinate.
 */
GLfloat Point::getZ() const {
    return z;
}

/**
 * @brief Set the X-coordinate of the point.
 * @param x The new X-coordinate.
 */
void Point::setX(GLfloat x) {
    this->x = x;
}

/**
 * @brief Set the Y-coordinate of the point.
 * @param y The new Y-coordinate.
 */
void Point::setY(GLfloat y) {
    this->y = y;
}

/**
 * @brief Set the Z-coordinate of the point.
 * @param z The new Z-coordinate.
 */
void Point::setZ(GLfloat z) {
    this->z = z;
}

/**
 * @brief Get the size of the point.
 * @return The size of the point.
 */
GLfloat Point::getSize() const {
    return size;
}

/**
 * @brief Set the size of the point.
 * @param size The new size of the point.
 */
void Point::setSize(GLfloat size) {
    this->size = size;
}

/**
 * @brief Check if smooth shading is enabled for the point.
 * @return True if smooth shading is enabled, false if flat shading is used.
 */
GLboolean Point::isSmooth() const {
    return smooth;
}

/**
 * @brief Set the shading mode for the point.
 * @param smooth True for smooth shading, false for flat shading.
 */
void Point::setSmooth(GLboolean smooth) {
    this->smooth = smooth;
}

/**
 * @brief Get the color of the point.
 * @return The color of the point.
 */
Color Point::getColor() const {
    return color;
}

/**
 * @brief Set the color of the point.
 * @param color The new color of the point.
 */
void Point::setColor(const Color& color) {
    this->color = color;
}
