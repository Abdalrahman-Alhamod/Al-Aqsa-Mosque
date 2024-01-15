#include "PersonDrawer.h"
#include "Texture.h"

Model_3DS* PersonDrawer::personModel = new Model_3DS();

//TODO: convert Vector3dStruct into class

PersonDrawer::PersonDrawer()
{
	personModel->Load((char*)"assets/models/MAN .3DS");
	personModel->Materials[0].tex.LoadBMP((char*)"assets/materials/Body1.bmp");
	personModel->Materials[1].tex.LoadBMP((char*)"assets/materials/Head1.bmp");
	personModel->Materials[2].tex.LoadBMP((char*)"assets/materials/Ghutra1.bmp");
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
	drawModel(personModel, position, size,rotation, 0.002); //0.1
}