#pragma once
#include "math3d.h"
#include "Constraints.h"
#include "Point.h"
#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <gl/glaux.h>		// Header File For The Glaux Library
#include <gl/glut.h>		// Header File For The Glut Library
#include <cmath>
#include "math3d.h"

#define db double 

class Box {

public:

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

    void drawOutside(const Constraints& c, int textures[], int flag[]);

    void drawOutside(const Constraints& c, int textures[], db textureCntS[],db textureCntT[]);

    void drawOutside(const Constraints& c, const int texture, db textureCntS[], db textureCntT[]);

    void drawOutside(const Constraints& c, const int texture, int flag[]);

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

