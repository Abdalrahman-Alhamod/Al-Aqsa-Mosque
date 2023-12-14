#include "PersonDrawer.h"
#include <GL/glut.h>  
#include "Point.h"
#include "Color.h"
#include "Constants.h"
#include "Texture.h"
#include "Model_3DS.h"

Model_3DS* PersonDrawer::personModel = new Model_3DS();

//TODO: convert Vector3dStruct into class

PersonDrawer::PersonDrawer()
{
	personModel->Load((char*)"assets/models/man.3ds");
}

void PersonDrawer::drawModel(Model_3DS* model, const Point& position, const float size,const float rotation, const float scaleFactor)
{
	glEnable(GL_TEXTURE_2D);
	model->pos.x = position.x;
	model->pos.y = position.y;
	model->pos.z = position.z;
	model->scale = scaleFactor * size;
	model->rot.y = rotation;
	model->Draw();
	glDisable(GL_TEXTURE_2D);
}

void PersonDrawer::drawPerson(const Point& position,const float rotation, const float size) 
{
	drawModel(personModel, position, size,rotation, 0.1);
}