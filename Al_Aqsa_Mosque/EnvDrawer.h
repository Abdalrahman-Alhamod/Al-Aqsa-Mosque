#ifndef ENV_DRAWER_H
#define ENV_DRAWER_H

#include "Point.h"
#include "Constraints.h"
#include "Color.h"
#include "Model_3DS.h"  

/**
 * @class EnvDrawer
 * @brief A utility class for drawing environmental elements such as trees, tanks, land, and skyboxes.
 */
class EnvDrawer {
public:
	/**
	 * @brief Constructor for the EnvDrawer class.
	 */
	EnvDrawer();

	/**
	 * @brief Draw a small tree at the specified position with the given size.
	 * @param position The position where the tree will be drawn.
	 * @param size The size of the tree.
	 */
	void drawSmallTree(const Point& position, const float size);

	/**
	 * @brief Draw a big tree at the specified position with the given size.
	 * @param position The position where the tree will be drawn.
	 * @param size The size of the tree.
	 */
	void drawBigTree(const Point& position, const float size);

	/**
	 * @brief Draw a tank at the specified position with the given size.
	 * @param position The position where the tank will be drawn.
	 * @param size The size of the tank.
	 */
	void drawTank(const Point& position, const float size);

	/**
	 * @brief Draw a tiled land using the specified points and count.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 */
	void drawTiledLand(const Point points[4], const int count);

	/**
	 * @brief Draw a grassy land using the specified points and count.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 */
	void drawGrassLand(const Point points[4], const int count);

	/**
	 * @brief Draw a city skybox at the specified position and constraints.
	 * @param position The position where the skybox will be drawn.
	 * @param constraints The constraints defining the size of the skybox.
	 */
	void drawCitySkyBox(const Point& position, const Constraints& constraints);

	/**
	 * @brief Draw a clouds skybox at the specified position and constraints.
	 * @param position The position where the skybox will be drawn.
	 * @param constraints The constraints defining the size of the skybox.
	 */
	void drawCloudsSkyBox(const Point& position, const Constraints& constraints);

private:
	static Model_3DS* tree1Model;
	static Model_3DS* tree2Model;
	static Model_3DS* tankModel;
	int ground, grass, stone;
	int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;
	int CitySKYFRONT, CitySKYBACK, CitySKYLEFT, CitySKYRIGHT, CitySKYUP, CitySKYDOWN;
	int CloudsSKYFRONT, CloudsSKYBACK, CloudsSKYLEFT, CloudsSKYRIGHT, CloudsSKYUP, CloudsSKYDOWN;

	/**
	 * @brief Draw a model at the specified position with the given size and scale factor.
	 * @param model The 3D model to be drawn.
	 * @param position The position where the model will be drawn.
	 * @param size The size of the model.
	 * @param scaleFactor The scale factor applied to the model.
	 */
	void drawModel(Model_3DS* model, const Point& position, const float size, const float scaleFactor);

	/**
	 * @brief Draw a land using the specified points, count, and texture ID.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 * @param textureID The texture ID for the land.
	 */
	void drawLand(const Point points[4], const int count, const int textureID);

	/**
	 * @brief Draw a skybox at the specified position and constraints.
	 * @param position The position where the skybox will be drawn.
	 * @param constraints The constraints defining the size of the skybox.
	 */
	void drawSkyBox(const Point& position, const Constraints& constraints);
};

#endif // ENV_DRAWER_H
