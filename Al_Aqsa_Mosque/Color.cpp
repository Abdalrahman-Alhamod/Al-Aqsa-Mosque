#include "Color.h"

/**
 * @brief Default constructor for a Color.
 */
Color::Color() {
    // Initialize attributes...
}

/**
 * @brief Create a Color with red, green, and blue values in the GLubyte range [0, 255].
 * @param red The red component.
 * @param green The green component.
 * @param blue The blue component.
 */
Color::Color(GLint red, GLint green, GLint blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    // Initialize GLfloat attributes based on GLubyte values.
    redf = static_cast<GLfloat>(red) / 255.0f;
    greenf = static_cast<GLfloat>(green) / 255.0f;
    bluef = static_cast<GLfloat>(blue) / 255.0f;
}

/**
 * @brief Create a Color with red, green, and blue values in the GLfloat range [0, 1].
 * @param red The red component.
 * @param green The green component.
 * @param blue The blue component.
 */
Color::Color(GLfloat red, GLfloat green, GLfloat blue) {
    redf = red;
    greenf = green;
    bluef = blue;
    // Initialize GLubyte attributes based on GLfloat values.
    red = static_cast<GLubyte>(red * 255.0f);
    green = static_cast<GLubyte>(green * 255.0f);
    blue = static_cast<GLubyte>(blue * 255.0f);
}

/**
 * @brief Get the red component of the color in the GLubyte range [0, 255].
 * @return The red component.
 */
GLubyte Color::getRedUbyte() const {
    return red;
}

/**
 * @brief Set the red component of the color in the GLubyte range [0, 255].
 * @param red The new red component.
 */
void Color::setRedUbyte(GLubyte red) {
    this->red = red;
    // Update the corresponding GLfloat attribute.
    redf = static_cast<GLfloat>(red) / 255.0f;
}

/**
 * @brief Get the green component of the color in the GLubyte range [0, 255].
 * @return The green component.
 */
GLubyte Color::getGreenUbyte() const {
    return green;
}

/**
 * @brief Set the green component of the color in the GLubyte range [0, 255].
 * @param green The new green component.
 */
void Color::setGreenUbyte(GLubyte green) {
    this->green = green;
    // Update the corresponding GLfloat attribute.
    greenf = static_cast<GLfloat>(green) / 255.0f;
}

/**
 * @brief Get the blue component of the color in the GLubyte range [0, 255].
 * @return The blue component.
 */
GLubyte Color::getBlueUbyte() const {
    return blue;
}

/**
 * @brief Set the blue component of the color in the GLubyte range [0, 255].
 * @param blue The new blue component.
 */
void Color::setBlueUbyte(GLubyte blue) {
    this->blue = blue;
    // Update the corresponding GLfloat attribute.
    bluef = static_cast<GLfloat>(blue) / 255.0f;
}

/**
 * @brief Get the red component of the color in the GLfloat range [0, 1].
 * @return The red component.
 */
GLfloat Color::getRedFloat() const {
    return redf;
}

/**
 * @brief Set the red component of the color in the GLfloat range [0, 1].
 * @param red The new red component.
 */
void Color::setRedFloat(GLfloat red) {
    this->redf = red;
    // Update the corresponding GLubyte attribute.
    red = static_cast<GLubyte>(red * 255.0f);
}

/**
 * @brief Get the green component of the color in the GLfloat range [0, 1].
 * @return The green component.
 */
GLfloat Color::getGreenFloat() const {
    return greenf;
}

/**
 * @brief Set the green component of the color in the GLfloat range [0, 1].
 * @param green The new green component.
 */
void Color::setGreenFloat(GLfloat green) {
    this->greenf = green;
    // Update the corresponding GLubyte attribute.
    green = static_cast<GLubyte>(green * 255.0f);
}

/**
 * @brief Get the blue component of the color in the GLfloat range [0, 1].
 * @return The blue component.
 */
GLfloat Color::getBlueFloat() const {
    return bluef;
}

/**
 * @brief Set the blue component of the color in the GLfloat range [0, 1].
 * @param blue The new blue component.
 */
void Color::setBlueFloat(GLfloat blue) {
    this->bluef = blue;
    // Update the corresponding GLubyte attribute.
    blue = static_cast<GLubyte>(blue * 255.0f);
}
/**
 * @brief Check if two Color objects are equal.
 * @param other The Color object to compare with.
 * @return True if the two Color objects are equal, false otherwise.
 */
bool Color::equal(const Color& other)const {
    return ((red == other.red && green == other.green && blue == other.blue) ||
        (redf == other.redf && greenf == other.greenf && bluef == other.bluef));
}