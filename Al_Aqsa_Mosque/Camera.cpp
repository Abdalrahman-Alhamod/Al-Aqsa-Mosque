#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>

#include "Camera.h"

#include <stdlib.h>   /* for exit */

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3dCreate(0.0f,0.0f,0.0f)

int Camera::cameraMode = 2;

Camera* Camera::camera[] = {};

Vector3dStruct Vector3dCreate(GLfloat x, GLfloat y, GLfloat z)
{
	Vector3dStruct tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat LengthVector3d(Vector3dStruct* v)
{
	return (GLfloat)(sqrt(SQR(v->x) + SQR(v->y) + SQR(v->z)));
}

Vector3dStruct NormalizeVector3d(Vector3dStruct v)
{
	Vector3dStruct res;
	float L = LengthVector3d(&v);
	if (L == 0.0f) return NULL_VECTOR;
	res.x = v.x / L;
	res.y = v.y / L;
	res.z = v.z / L;
	return res;
}

Vector3dStruct operator+ (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x + u.x;
	res.y = v.y + u.y;
	res.z = v.z + u.z;
	return res;
}
Vector3dStruct operator- (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res;
	res.x = v.x - u.x;
	res.y = v.y - u.y;
	res.z = v.z - u.z;
	return res;
}


Vector3dStruct operator* (Vector3dStruct v, float r)
{
	Vector3dStruct res;
	res.x = v.x * r;
	res.y = v.y * r;
	res.z = v.z * r;
	return res;
}

Vector3dStruct CrossProduct(Vector3dStruct* u, Vector3dStruct* v)
{
	Vector3dStruct resVector;
	resVector.x = u->y * v->z - u->z * v->y;
	resVector.y = u->z * v->x - u->x * v->z;
	resVector.z = u->x * v->y - u->y * v->x;

	return resVector;
}
float operator* (Vector3dStruct v, Vector3dStruct u)	//dot product
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

/***************************************************************************************/

Camera::Camera()
{

}

Camera* Camera::getInstance()
{
	return Camera::camera[Camera::cameraMode];
}

void Camera::cameraInit()
{

	for (int i = 0; i < 3; ++i)
	{
		camera[i] = new Camera();
		camera[i]->Position.z = 0;
		camera[i]->Position.x = 0;
		camera[i]->Position.y = 0;

		camera[i]->Position = Vector3dCreate(0.0, 1.5, 0.0);
		camera[i]->View = Vector3dCreate(0.0, 0.0, -1.0);
		camera[i]->RightVector = Vector3dCreate(1.0, 0.0, 0.0);
		camera[i]->Up = Vector3dCreate(0.0, 1.0, 0.0);

		camera[i]->RotatedX = camera[i]->RotatedY = camera[i]->RotatedZ = 0.0;
	}
}

void Camera::Move(Vector3dStruct Direction)
{
	Position = Position + Direction;
}

void Camera::RotateX(GLfloat Angle)
{
	RotatedX += Angle;
	//Rotate viewdir around the right vector:
	View = NormalizeVector3d(View * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
	//now compute the new UpVector (by cross product)
	//Up = CrossProduct(&View, &RightVector) * -1;
}

void Camera::RotateY(GLfloat Angle)
{
	RotatedY += Angle;
	//Rotate viewdir around the up vector:
	View = NormalizeVector3d(View * cosf(Angle * PIdiv180) - RightVector * sinf(Angle * PIdiv180));
	//now compute the new RightVector (by cross product)
	RightVector = CrossProduct(&View, &Up);
}

void Camera::RotateZ(GLfloat Angle)
{
	RotatedZ += Angle;
	//Rotate viewdir around the right vector:
	RightVector = NormalizeVector3d(RightVector * cosf(Angle * PIdiv180) + Up * sinf(Angle * PIdiv180));
	//now compute the new UpVector (by cross product)
	//Up = CrossProduct(&View, &RightVector) * -1;
}

void Camera::Render(void)
{
	//calculate view point
	Vector3dStruct ViewPoint = Position + View;


	gluLookAt(Position.x, Position.y, Position.z,
		ViewPoint.x, ViewPoint.y, ViewPoint.z,
		Up.x, Up.y, Up.z);
}

void Camera::changeMode(void)
{
	Camera::cameraMode = (Camera::cameraMode + 1) % 3;
}

void Camera::MoveForward(GLfloat Distance)
{
	if (Camera::getMode() == FREE_CAMERA)
	{
		Position = Position + (View * Distance);
		return;
	}
	float x = View.x, z = View.z;
	Position = Position + (Vector3dCreate(x, 0, z) * Distance);
}

void Camera::MoveRight(GLfloat Distance)
{
	Position = Position + (RightVector * Distance);
}

void Camera::MoveUpward(GLfloat Distance)
{
	if (Camera::getMode() == FREE_CAMERA)
		Position = Position + (Up * Distance);
}

void Camera::SetRotateX(GLfloat Angle)
{

	View = Vector3dCreate(0.0, 0.0, -1.0);
	RightVector = Vector3dCreate(1.0, 0.0, 0.0);
	Up = Vector3dCreate(0.0, 1.0, 0.0);
	RotatedX = Angle;
}

void Camera::decodeKeyboard(bool* keys, float speed)
{

	// Translation controls
	if (keys['W'])
		Camera::MoveForward(1 * speed); // Move camera forward
	if (keys['S'])
		Camera::MoveForward(-1 * speed); // Move camera backward
	if (keys['D'])
		Camera::MoveRight(1 * speed); // Move camera to the right
	if (keys['A'])
		Camera::MoveRight(-1 * speed); // Move camera to the left
	if (keys['E'])
		Camera::MoveUpward(1 * speed); // Move camera upward
	if (keys['Q'])
		Camera::MoveUpward(-1 * speed); // Move camera downward

	// Camera orientation adjustment using arrow keys
	if (keys[VK_DOWN])
		Camera::RotateX(-1 * (speed + 1)); // Rotate camera around X-axis (look up)
	if (keys[VK_UP])
		Camera::RotateX(1 * (speed + 1)); // Rotate camera around X-axis (look down)
	if (keys[VK_LEFT])
		Camera::RotateY(1 * (speed + 1)); // Rotate camera around Y-axis (look left)
	if (keys[VK_RIGHT])
		Camera::RotateY(-1 * (speed + 1)); // Rotate camera around Y-axis (look right)
	if (keys['Z'])
		Camera::RotateZ(1 * (speed + 1));  // Rotate camera around Z-axis (roll clockwise)
	if (keys['X'])
		Camera::RotateZ(-1 * (speed + 1)); // Rotate camera around Z-axis (roll counterclockwise)
}


void Camera::decodeMouse(int mouseX, int mouseY, bool isLeftClicked, bool isRightClicked)
{
	static int prevMouseX = mouseX;
	static int prevMouseY = mouseY;

	// Calculate the mouse movement
	int deltaX = mouseX - prevMouseX;
	int deltaY = mouseY - prevMouseY;

	// Update the previous mouse position
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	// Adjust sensitivity for better control
	float sensitivity = 0.1f;

	// If the left mouse button is pressed, adjust camera orientation
	if (isLeftClicked)
	{
		// Rotate around Y-axis based on horizontal mouse movement
		Camera::RotateY(deltaX * sensitivity);

		// Rotate around X-axis based on vertical mouse movement
		Camera::RotateX(deltaY * sensitivity);
	}

	// If the right mouse button is pressed, reset camera orientation
	if (isRightClicked)
	{
		// Reset orientation to default
		Camera::SetRotateX(0.0f);

		// Optionally, you can also reset other camera properties like position
		Position = Vector3dCreate(0.0, 0.0, 0.0);
		View = Vector3dCreate(0.0, 0.0, -1.0);
		RightVector = Vector3dCreate(1.0, 0.0, 0.0);
		Up = Vector3dCreate(0.0, 1.0, 0.0);
		RotatedX = RotatedY = RotatedZ = 0.0;

	}
}

Point Camera::getPosition()
{
	return Point(Position.x, Position.y, Position.z);
}

float Camera::getRotatedY()
{
	return RotatedY;
}

int Camera::getMode()
{
	return cameraMode;
}

