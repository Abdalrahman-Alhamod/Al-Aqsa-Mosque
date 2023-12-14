#pragma once
#include "math3d.h"
#define db double 
class Box
{

public:

	/**
	* @brief draw the box from the outside
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param texture array for the 6 faces of the box. 
	* 
	* the six of faces of the textures go as follow
	* texture[0] the base face
	* texture[1] the top face
	* texture[2] the back face
	* texture[3] the front face
	* texture[4] the left face
	* texture[5] the right face
	*/
	void drawOutside(db width, db length, db height, int texture[]);
	/**
	* @brief draw the box from the inside
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param texture array for the 6 faces of the box. 
	*
	* the six of faces of the textures go as follow
	* texture[0] the base face
	* texture[1] the top face
	* texture[2] the back face
	* texture[3] the front face
	* texture[4] the left face
	* texture[5] the right face
	*/
	void drawInside(db width, db length, db height, int texture[]);
	/**
	* @brief draw the shadow of the box
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param shadowMat takes the matrix of shadows
	*/
	void drawShadow(db width, db length, db height, M3DMatrix44f shadowMat);
	/**
	* @brief draws the box from inside and outside
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param texture1 array for the 6 faces of the box from outside
	* @param texture2 array for the 6 faces of the box from inside.            
	* 
	* 
	* the six of faces of the textures go as follow
	* texture[0] the base face
	* texture[1] the top face
	* texture[2] the back face
	* texture[3] the front face
	* texture[4] the left face
	* texture[5] the right face
	*/
	Box(db width, db length, db height, int texture1[], int texture2[], M3DMatrix44f shadowMat, bool shad = false);
};

