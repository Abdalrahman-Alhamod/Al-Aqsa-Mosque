#ifndef PERSON_DRAWER_H
#define PERSON_DRAWER_H

#include "Point.h"
#include "Constraints.h"
#include "Color.h"
#include "Model_3DS.h"
#include "Camera.h"
#include <GL/glut.h>  
#include "Constants.h"
#include "Model_3DS.h"

/**
 * @class PersonDrawer
 * @brief A utility class for drawing personModel
 */
class PersonDrawer {
private:
	static Model_3DS* personModel;
	Vector3dStruct View;        ///< View direction vector.
	Vector3dStruct RightVector; ///< Right vector.
	Vector3dStruct Up;           ///< Up vector.
	Vector3dStruct Position;     ///< person position vector.

	GLfloat RotatedX, RotatedY, RotatedZ; ///< Rotation angles around X, Y, and Z axes.

public:
	PersonDrawer();



	/**
	 * @brief Draw a model at the specified position with the given size and scale factor.
	 * @param model The 3D model to be drawn.
	 * @param position The position where the model will be drawn.
	 * @param size The size of the model.
	 * @param scaleFactor The scale factor applied to the model.
	 */
	void drawModel(Model_3DS* model, const  Point& position, const float size,const float rotation, const float scaleFactor);

	void drawPerson(const Point& position,const float rotation, const float size);
};


#endif // PERSON_DRAWER_H
