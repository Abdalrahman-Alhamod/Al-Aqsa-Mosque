

#include "Camera.h"
#include <Windows.h>
#include <string>
#include "Console.h"


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
	res.x = v.x - u.x;
	res.z = v.z - u.z;
	res.y = v.y - u.y;
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
	resVector.x = u->y * v->z - u->z * v->y;
	resVector.z = u->x * v->y - u->y * v->x;
	resVector.y = u->z * v->x - u->x * v->z;

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
		for (int j = -70; j <= -63; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -275; i <= -260; ++i)
		for (int j = 240; j <= 243; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	//Back wall
	for (int i = -275; i <= 276; ++i)
		for (int j = -415; j <= -405; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = 210; i <= 266; ++i)
		for (int j = -406; j <= -390; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -265; i <= -250; ++i)
		for (int j = -406; j <= -360; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	// Right wall
	for (int i = 260; i <= 277; ++i)
		for (int j = -415; j <= 415; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = 260; i <= 277; ++i)
		for (int j = -70; j <= -63; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	// Front wall
	for (int i = -273; i <= 276; ++i)
		for (int j = 408; j <= 413; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	// start of al qibaly
	for (int i = -273; i <= 20; ++i)
		for (int j = 390; j <= 408; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -263; i <= -250; ++i)
		for (int j = 253; j <= 408; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	// al qibaly
	for (int i = -100; i <= -2; ++i)
		for (int j = 230; j <= 408; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -55; i <= -50; ++i)
		for (int j = 230; j <= 272; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -90; i <= -20; ++i)
		for (int j = 270; j <= 395; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	// Dom square
	for (int i = -172; i <= 176; ++i)
		for (int j = -272; j <= 116; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	//side 1
	for (int i = -58; i <= -6; ++i)
		for (int j = 105; j <= 123; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	for (int i = 109; i <= 146; ++i)
		for (int j = 105; j <= 123; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	for (int i = -50; i <= -12; ++i)
		for (int j = 100; j <= 140; ++j)
			Camera::pos[i + 350][j + 500] = 0;
	for (int i = 119; i <= 140; ++i)
		for (int j = 100; j <= 140; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	//side 2
	for (int i = -87; i <= -50; ++i)
		for (int j = -287; j <= -274; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	for (int i = 52; i <= 90; ++i)
		for (int j = -287; j <= -274; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	for (int i = -43; i <= -5; ++i)
		for (int j = -300; j <= -260; ++j)
			Camera::pos[i + 350][j + 500] = 0;
	for (int i = 62; i <= 80; ++i)
		for (int j = -300; j <= -260; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	//side 3
	for (int i = -187; i <= -173; ++i)
	{
		for (int j = 56; j <= 91; ++j)
			Camera::pos[i + 350][j + 500] = 1;

		for (int j = -49; j <= -1; ++j)
			Camera::pos[i + 350][j + 500] = 1;

		for (int j = -264; j <= -216; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	}
	for (int i = -200; i <= -150; ++i)
	{
		for (int j = 65; j <= 85; ++j)
			Camera::pos[i + 350][j + 500] = 0;

		for (int j = -75; j <= 0; ++j)
			Camera::pos[i + 350][j + 500] = 0;

		for (int j = -254; j <= -226; ++j)
			Camera::pos[i + 350][j + 500] = 0;
	}
	//side 4
	for (int i = 175; i <= 187; ++i)
		for (int j = -62; j <= 0; ++j)
			Camera::pos[i + 350][j + 500] = 1;
	for (int i = 150; i <= 200; ++i)
		for (int j = -50; j <= -10; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -160; i <= 160; ++i)
		for (int j = -260; j <= 106; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	//Dom of rock
	/*
	for (int i = -90; i < -55; ++i)
		for (int j = -135 - i; j < 95 + i; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -20; i < 15; ++i)
		for (int j = -55 + i; j < 15 - i; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -55; i < -20; ++i)
		for (int j = -80; j < 40; ++j)
			Camera::pos[i + 350][j + 500] = 1;

	for (int i = -85; i < -55; ++i)
		for (int j = -130 - i; j < 90 + i; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -20; i < 10; ++i)
		for (int j = -50 + i; j < 10 - i; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -55; i < -20; ++i)
		for (int j = -75; j < 35; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -45; i < -30; ++i)
		for (int j = -90; j < 50; ++j)
			Camera::pos[i + 350][j + 500] = 0;

	for (int i = -100; i < 20; ++i)
		for (int j = -27; j < -12; ++j)
			Camera::pos[i + 350][j + 500] = 0;
	*/
}

int Camera::nx(int v) {

	return max(min(v * 10 + 350, 701), 0);
}

int Camera::nz(int v) {
	return max(min(v * 10 + 500, 1001), 0);
}

Camera* Camera::getInstance()
{
	return Camera::camera[Camera::cameraMode];
}

void Camera::cameraInit(HWND hWnd)
{
	Camera::posInit();

	for (int i = 0; i < 3; ++i)
	{
		camera[i] = new Camera();

		camera[i]->Position = Vector3dCreate(-4, -8.95, +9);
		camera[i]->View = Vector3dCreate(0.0, 0.0, -1.0);
		camera[i]->RightVector = Vector3dCreate(1.0, 0.0, 0.0);
		camera[i]->Up = Vector3dCreate(0.0, 1.0, 0.0);

		camera[i]->RotatedX = camera[i]->RotatedY = camera[i]->RotatedZ = 0.0;
		camera[i]->SoundManager.Initialize(hWnd);
		camera[i]->SoundManager.CreateSound((char*)"assets/sounds/footsteps.wav", Camera::camera[i]->soundBuffer);

		camera[i]->RotateX(20);
		camera[i]->RotateY(-6);
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

void Camera::setY(float value)
{
	this->Position.y = value;
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
	bool playSound = false;
	const float arrowMovementSpeed = speed + 3;
	// Translation controls
	if (keys['W']) {
		Camera::MoveForward(1 * speed); // Move camera forward
		if (Camera::getInstance()->getMode() != FREE_CAMERA) {
			playSound = true;
		}
	}
	if (keys['S']) {
		Camera::MoveForward(-1 * speed); // Move camera backward
		if (Camera::getInstance()->getMode() != FREE_CAMERA) {
			playSound = true;
		}
	}
	if (keys['D']) {
		Camera::MoveRight(1 * speed); // Move camera to the right
		if (Camera::getInstance()->getMode() != FREE_CAMERA) {
			playSound = true;
		}
	}
	if (keys['A']) {
		Camera::MoveRight(-1 * speed); // Move camera to the left
		if (Camera::getInstance()->getMode() != FREE_CAMERA) {
			playSound = true;
		}
	}
	if (keys['E'])
		Camera::MoveUpward(1 * speed); // Move camera upward
	if (keys['Q'])
		Camera::MoveUpward(-1 * speed); // Move camera downward

	if (playSound) {
		soundBuffer.Play(true);
	}
	else {
		soundBuffer.Stop();
	}

	// Camera orientation adjustment using arrow keys
	if (keys[VK_DOWN])
		Camera::RotateX(-1 * arrowMovementSpeed); // Rotate camera around X-axis (look up)
	if (keys[VK_UP])
		Camera::RotateX(1 * arrowMovementSpeed); // Rotate camera around X-axis (look down)
	if (keys[VK_LEFT])
		Camera::RotateY(1 * arrowMovementSpeed); // Rotate camera around Y-axis (look left)
	if (keys[VK_RIGHT])
		Camera::RotateY(-1 * arrowMovementSpeed); // Rotate camera around Y-axis (look right)
	if (keys['Z'])
		Camera::RotateZ(1 * arrowMovementSpeed);  // Rotate camera around Z-axis (roll clockwise)
	if (keys['X'])
		Camera::RotateZ(-1 * arrowMovementSpeed); // Rotate camera around Z-axis (roll counterclockwise)
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
	float sensitivity = 0.35f;

	/*
	if (abs(mouseX - 982) > 10 || abs(mouseY - 509) > 10)
	this values is normal window (not fullscreen) .. you can figure it out by use console and output mouse* values
	*/

	// If the mouse is not moving to its initial pos , adjust camera orientation
	if (abs(mouseX - 990) > 7 || abs(mouseY - 540) > 7)
	{
		// Rotate around Y-axis based on horizontal mouse movement
		Camera::RotateY(-deltaX * sensitivity);

		// Rotate around X-axis based on vertical mouse movement
		Camera::RotateX(-deltaY * sensitivity);
	}

	if(!deltaX && !deltaY) // if there is no change , return the cursor to the middle of the screen 
		SetCursorPos(990, 540); // the middle of 1920*1080 screen

	// If the right mouse button is pressed, reset camera orientation
	if (isRightClicked)
	{
		// Reset orientation to default
		Camera::SetRotateX(0.0f);

		// Optionally, you can also reset other camera properties like position
		Position = Vector3dCreate(-4, -8.95, +9);
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

