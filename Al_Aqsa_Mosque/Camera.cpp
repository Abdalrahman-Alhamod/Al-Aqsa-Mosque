#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "Console.h"
#include "Constants.h"

#include "Camera.h"

#include <stdlib.h>   /* for exit */
#include <string>

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3dCreate(0.0f,0.0f,0.0f)

int Camera::cameraMode = 2;
bool Camera::pos[701][1001] = {};

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

Vector3dStruct operator- (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res = v;
	int nx = min(max((v.x - u.x) * 10 + 350, 0), 701);
	int nz = min(max((v.z - u.z) * 10 + 500, 0), 1001);
	if (!Camera::pos[nx][nz])
	{
		res.x = v.x - u.x;
		res.z = v.z - u.z;
		res.y = v.y - u.y;
	}
	return res;
}

Vector3dStruct operator+ (Vector3dStruct v, Vector3dStruct u)
{
	Vector3dStruct res = v;
	{
		res.x = v.x + u.x;
		res.z = v.z + u.z;
		res.y = v.y + u.y;
	}
	return res;
}

Vector3dStruct operator* (Vector3dStruct v, float r)
{
	Vector3dStruct res = v;
	{
		res.x = v.x * r;
		res.z = v.z * r;
		res.y = v.y * r;
	}
	return res;
}

Vector3dStruct CrossProduct(Vector3dStruct* u, Vector3dStruct* v)
{
	Vector3dStruct resVector = *u;

	int nx = min(max((u->y * v->z - u->z * v->y) * 10 + 350, 0), 701);
	int nz = min(max((u->x * v->y - u->y * v->x) * 10 + 500, 0), 1001);
	if (!Camera::pos[nx][nz])
	{
		resVector.x = u->y * v->z - u->z * v->y;
		resVector.z = u->x * v->y - u->y * v->x;
		resVector.y = u->z * v->x - u->x * v->z;
	}

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

void Camera::posInit()
{
	// Left wall
	for (int i = -275; i <= -260; ++i)
		for (int j = -415; j <= 415; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	//Doors in it
	for (int i = -275; i <= -260; ++i)
		for (int j = -85; j <= -77; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -275; i <= -260; ++i)
		for (int j = 247; j <= 255; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	//Back wall
	for (int i = -275; i <= 276; ++i)
		for (int j = -415; j <= -406; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	// Right wall
	for (int i = 263; i <= 277; ++i)
		for (int j = -415; j <= 415; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = 263; i <= 277; ++i)
		for (int j = -87; j <= -77; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	// Front wall
	for (int i = -273; i <= 276; ++i)
		for (int j = 408; j <= 413; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	// start of al qibaly
	for (int i = -273; i <= 20; ++i)
		for (int j = 396; j <= 408; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -263; i <= -257; ++i)
		for (int j = 255; j <= 408; ++j)
			Camera::pos[i + 350][j + 500] = 1;

}

int Camera::nx(int v) {

	return max(min(v * 10 + 350,701),0);
}

int Camera::nz(int v) {
	return max(min(v * 10 + 500, 1001), 0);
}

Camera* Camera::getInstance()
{
	return Camera::camera[Camera::cameraMode];
}

void Camera::cameraInit()
{
	//Camera::posInit();

	for (int i = 0; i < 3; ++i)
	{
		camera[i] = new Camera();

		camera[i]->Position = Vector3dCreate(0.0, -9.5, 0.0);
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
	if (cameraMode == FREE_CAMERA)
	{
		Position = Position + (View * Distance);
		return;
	}

	int nx = Camera::nx(Position.x + (View * Distance).x);
	int nz = Camera::nz(Position.z + (View * Distance).z);
	if (Camera::pos[nx][nz])
		return;

	float x = View.x, z = View.z;
	Position = Position + (Vector3dCreate(x, 0, z) * Distance);
}

void Camera::MoveRight(GLfloat Distance)
{
	int nx = Camera::nx(Position.x + (RightVector * Distance).x);
	int nz = Camera::nz(Position.z + (RightVector * Distance).z);
	if (cameraMode != FREE_CAMERA && Camera::pos[nx][nz])
		return;
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
		Camera::RotateX(-1 * (speed + 5)); // Rotate camera around X-axis (look up)
	if (keys[VK_UP])
		Camera::RotateX(1 * (speed + 5)); // Rotate camera around X-axis (look down)
	if (keys[VK_LEFT])
		Camera::RotateY(1 * (speed + 5)); // Rotate camera around Y-axis (look left)
	if (keys[VK_RIGHT])
		Camera::RotateY(-1 * (speed + 5)); // Rotate camera around Y-axis (look right)
	if (keys['Z'])
		Camera::RotateZ(1 * (speed + 5));  // Rotate camera around Z-axis (roll clockwise)
	if (keys['X'])
		Camera::RotateZ(-1 * (speed + 5)); // Rotate camera around Z-axis (roll counterclockwise)
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

