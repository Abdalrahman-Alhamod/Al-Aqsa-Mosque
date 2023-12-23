#pragma once
#include "math3d.h"
#include "Constraints.h"
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
	void drawOutside(const Constraints& c, int texture[]);
	/**
	* @brief draw the box from the outside
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param texture for the 6 faces of the box.
	*/
	void drawOutside(const Constraints& c,const int texture);
	/**
	* @brief draw the box from the outside
	* @param width the width of the box
	* @param length the length of the box
	* @param height the height of the box
	* @param texture for the 6 faces of the box.
	* texture[0] the sourrounding faces
	* texture[1] the bases faces
	*/
	void drawOutside(const Constraints& c, const int sourroundTexture,const int baseTexture);
	/**
	* @brief draw the box from the inside
	* @param constraints is an object of width height length
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
	void drawInside(const Constraints& c, int texture[]);
	/**
	* @brief draw the shadow of the box
	* @param constraints is an object of width height length
	* @param shadowMat takes the matrix of shadows
	*/
	void drawShadow(const Constraints& c, M3DMatrix44f shadowMat);
	/**
	* @brief draws the box from inside and outside
	* @param constraints is an object of width height length
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
	Box();
	Box( const Constraints& c, int texture1[], int texture2[], M3DMatrix44f shadowMat, bool shad = false);
};

