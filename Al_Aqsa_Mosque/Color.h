#pragma once

// Including necessary header files for the Color class
#include <windows.h> // Header File For Windows
#include <gl\gl.h>   // Header File For the OpenGL32 Library
#include <gl\glu.h>  // Header File For the GLu32 Library
#include <gl\glaux.h> // Header File For the Glaux Library
#include <math.h>    // Header File For the Math Library

/**
 * @class Color
 * @brief Represents an RGB color with values in either GLubyte or GLfloat range.
 */
class Color
{
public:
    /**
     * @brief Default constructor for a Color.
     */
    Color();

    /**
     * @brief Create a Color with red, green, and blue values in the GLubyte range [0, 255].
     * @param red The red component.
     * @param green The green component.
     * @param blue The blue component.
     */
    Color(GLint red, GLint green, GLint blue);

    /**
     * @brief Create a Color with red, green, and blue values in the GLfloat range [0, 1].
     * @param red The red component.
     * @param green The green component.
     * @param blue The blue component.
     */
    Color(GLfloat red, GLfloat green, GLfloat blue);
    /**
    * @brief Get the red component of the color in the GLubyte range [0, 255].
    * @return The red component.
    */
    GLubyte getRedUbyte() const;

    /**
     * @brief Set the red component of the color in the GLubyte range [0, 255].
     * @param red The new red component.
     */
    void setRedUbyte(GLubyte red);

    /**
     * @brief Get the green component of the color in the GLubyte range [0, 255].
     * @return The green component.
     */
    GLubyte getGreenUbyte() const;

    /**
     * @brief Set the green component of the color in the GLubyte range [0, 255].
     * @param green The new green component.
     */
    void setGreenUbyte(GLubyte green);

    /**
     * @brief Get the blue component of the color in the GLubyte range [0, 255].
     * @return The blue component.
     */
    GLubyte getBlueUbyte() const;

    /**
     * @brief Set the blue component of the color in the GLubyte range [0, 255].
     * @param blue The new blue component.
     */
    void setBlueUbyte(GLubyte blue);

    /**
     * @brief Get the red component of the color in the GLfloat range [0, 1].
     * @return The red component.
     */
    GLfloat getRedFloat() const;

    /**
     * @brief Set the red component of the color in the GLfloat range [0, 1].
     * @param red The new red component.
     */
    void setRedFloat(GLfloat red);

    /**
     * @brief Get the green component of the color in the GLfloat range [0, 1].
     * @return The green component.
     */
    GLfloat getGreenFloat() const;

    /**
     * @brief Set the green component of the color in the GLfloat range [0, 1].
     * @param green The new green component.
     */
    void setGreenFloat(GLfloat green);

    /**
     * @brief Get the blue component of the color in the GLfloat range [0, 1].
     * @return The blue component.
     */
    GLfloat getBlueFloat() const;

    /**
     * @brief Set the blue component of the color in the GLfloat range [0, 1].
     * @param blue The new blue component.
     */
    void setBlueFloat(GLfloat blue);

    /**
     * @brief Red component in GLubyte range [0, 255].
     */
    GLubyte red;

    /**
     * @brief Green component in GLubyte range [0, 255].
     */
    GLubyte green;

    /**
     * @brief Blue component in GLubyte range [0, 255].
     */
    GLubyte blue;

    /**
     * @brief Red component in GLfloat range [0, 1].
     */
    GLfloat redf;

    /**
     * @brief Green component in GLfloat range [0, 1].
     */
    GLfloat greenf;

    /**
     * @brief Blue component in GLfloat range [0, 1].
     */
    GLfloat bluef;
};

