#pragma once
#include "math3d.h"
#include "Constraints.h"
#define db double 

class Box {

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
	* @param sourroundTexture the sourrounding faces
	* @param baseTexture the bases faces
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

	void drawOutside(const Constraints& c, int textures[], bool flag[]);

	void drawOutside(const Constraints& c, const int texture, bool flag[]);



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

    /**
     * @brief Draws the box from the outside with multiple textures.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Array for the 6 faces of the box.
     * @param textureCount Count of textures to apply (optional, defaults to 1).
     */
    void drawOutside(const Constraints& c, int texture[], float textureCount = 1);

    /**
     * @brief Draws the box from the outside with multiple textures and texture counts.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Array for the 6 faces of the box.
     * @param textureWidthCount Width count for texture mapping.
     * @param textureHeightCount Height count for texture mapping.
     * @param textureLengthCount Length count for texture mapping.
     */
    void drawOutside(const Constraints& c, int texture[], float textureWidthCount, float textureHeightCount, float textureLengthCount);

    /**
     * @brief Draws the box from the outside with a single texture.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Texture for the 6 faces of the box.
     * @param textureCount Count of textures to apply (optional, defaults to 1).
     */
    void drawOutside(const Constraints& c, const int texture, float textureCount = 1);

    /**
     * @brief Draws a triangular prism from the outside with multiple textures.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Array for the 6 faces of the box.
     * @param textureCount Count of textures to apply (optional, defaults to 1).
     */
    void drawTriangleOutside(const Constraints& c, int texture[], float textureCount = 1);

    /**
     * @brief Draws a triangular prism from the outside with a single texture.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Texture for the 6 faces of the box.
     * @param textureCount Count of textures to apply (optional, defaults to 1).
     */
    void drawTrangleOutside(const Constraints& c, const int texture, float textureCount = 1);

    /**
     * @brief Draws the box from the outside with separate textures for surrounding and base faces.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param sourroundTexture Texture for surrounding faces.
     * @param baseTexture Texture for base faces.
     */
    void drawOutside(const Constraints& c, const int sourroundTexture, const int baseTexture);

    /**
     * @brief Draws the box from the inside with multiple textures.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture Array for the 6 faces of the box.
     */
    void drawInside(const Constraints& c, int texture[]);

    /**
     * @brief Draws the shadow of the box.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param shadowMat Matrix for shadow projection.
     */
    void drawShadow(const Constraints& c, M3DMatrix44f shadowMat);

    /**
     * @brief Draws the box from inside and outside with dual textures.
     * @param c Constraints object specifying width, height, and length of the box.
     * @param texture1 Array for the 6 faces of the box from outside.
     * @param texture2 Array for the 6 faces of the box from inside.
     * @param shadowMat Matrix for shadow projection.
     * @param shad Flag indicating whether to draw shadows (optional, defaults to false).
     */
    Box(const Constraints& c, int texture1[], int texture2[], M3DMatrix44f shadowMat, bool shad = false);

    Box();
};

