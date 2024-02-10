//***************************************************************************
// Camera based on Vectors
//***************************************************************************
#ifndef CAMERA_H
#define CAMERA_H

#include "Constants.h"
#include "Sound.h"
#include "Point.h"
#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "Console.h"
#include <stdlib.h>   /* for exit */
#include <string>

/////////////////////////////////
// Note: All angles in degrees //
/////////////////////////////////

struct Vector3dStruct
{
    GLfloat x, y, z;
};
Vector3dStruct operator+ (Vector3dStruct, Vector3dStruct);
Vector3dStruct operator* (Vector3dStruct, float);
Vector3dStruct operator- (Vector3dStruct, Vector3dStruct);

/**
 * @brief Create a 3D vector with the given coordinates.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @param z Z-coordinate.
 * @return A 3D vector with the specified coordinates.
 */
Vector3dStruct Vector3dCreate(GLfloat x, GLfloat y, GLfloat z);

/**
 * @brief Calculate the length of a 3D vector.
 * @param v Pointer to the vector.
 * @return The length of the vector.
 */
GLfloat LengthVector3d(Vector3dStruct* v);

/**
 * @brief Normalize a 3D vector.
 * @param v The vector to be normalized.
 * @return The normalized vector.
 */
Vector3dStruct NormalizeVector3d(Vector3dStruct v);

/**
 * @brief Camera class for controlling view and position in a 3D scene.
 */
class Camera
{
private:
    static int cameraMode;
    static Camera* camera[3];
    /*
    * 0->free Camera
    * 1->first Person Camera
    * 2->third Person Camera
    */

    Vector3dStruct View;        ///< View direction vector.
    Vector3dStruct RightVector; ///< Right vector.
    Vector3dStruct Up;           ///< Up vector.
    Vector3dStruct Position;     ///< Camera position vector.

    GLfloat RotatedX, RotatedY, RotatedZ; ///< Rotation angles around X, Y, and Z axes.

    /**
     * @brief Default constructor. Initializes camera values.
     */
    Camera();
    static int nx(int);
    static int nz(int);
    static void posInit();

     DirectSoundBuffer soundBuffer;
     DirectSoundManager SoundManager;

public:
    static bool pos[701][1001];
    static void cameraInit(HWND hWnd);
    static Camera* getInstance();

    /**
     * @brief Render the camera view by setting up the OpenGL viewing matrix.
     * @note You should call glLoadIdentity before using Render.
     */
    void Render(void);
    void setY(float);

    /**
    * @brief
    */
    static void changeMode(void);

    /**
     * @brief Move the camera in the specified direction.
     * @param Direction The direction to move the camera.
     */
    void Move(Vector3dStruct Direction);

    /**
     * @brief Rotate the camera around the X-axis.
     * @param Angle The angle in degrees to rotate.
     */
    void RotateX(GLfloat Angle);

    /**
     * @brief Rotate the camera around the Y-axis.
     * @param Angle The angle in degrees to rotate.
     */
    void RotateY(GLfloat Angle);

    /**
     * @brief Rotate the camera around the Z-axis.
     * @param Angle The angle in degrees to rotate.
     */
    void RotateZ(GLfloat Angle);

    /**
     * @brief Move the camera forward along its view direction.
     * @param Distance The distance to move.
     */
    void MoveForward(GLfloat Distance);

    /**
     * @brief Move the camera right along its right vector.
     * @param Distance The distance to move.
     */
    void MoveRight(GLfloat Distance);

    /**
     * @brief Move the camera upward along its up vector.
     * @param Distance The distance to move.
     */
    void MoveUpward(GLfloat Distance);

    /**
     * @brief Set the rotation angle around the X-axis.
     * @param Angle The angle in degrees.
     */
    void SetRotateX(GLfloat Angle);

    /**
     * @brief Decode keyboard input to control the camera's movement and orientation.
     * @param keys An array representing the state of keys on the keyboard.
     * @param speed The speed at which the camera should move or rotate.
     */
    void decodeKeyboard(bool* keys, float speed);

    /**
    * @brief Decode mouse input to control the camera's movement.
    * @param mouseX The x-coordinate of the mouse.
    * @param mouseY The y-coordinate of the mouse.
    * @param isLeftClicked Indicates whether the left mouse button is clicked.
    * @param isRightClicked Indicates whether the right mouse button is clicked.
    */
    void decodeMouse(int mouseX, int mouseY, bool isLeftClicked, bool isRightClicked);

    Point getPosition();

    float getRotatedY();

    int getMode();
};

#endif 