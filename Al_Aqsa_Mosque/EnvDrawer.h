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
	/**
	 * @brief Draw a garden with grass and trees.
	 * @param point Position, width, and length of the garden.
	 * @param grassTilesCount Number of grass tiles.
	 * @param treeSize Size of the trees.
	 * @param isSmall Draw small trees if true, big trees if false.
	 *
	 * Draws a garden with grass tiles covering the ground and randomly placed trees.
	 * The number of grass tiles and tree size are specified. Tree size is determined
	 * by the boolean flag "isSmall". Actual tree arrangement may vary due to randomness.
	 *
	 * Example usage: "envDrawer.drawGarden({0, 0, 0}, 100, 100, 500, 0.1, true);"
	 */
	void drawGarden(const Point& point, const int width, const int length,const int grassTilesCount,const int treeSize, bool isSmall);

	/**
	* @brief Draw a textured cylindrical column with decorative elements.
	* @param size Size factor determining the dimensions of the column.
	*
	* Draws a textured cylindrical column with decorative elements, including a top and
	* bottom base. The size parameter determines the overall dimensions of the column.
	*
	* Example: "envDrawer.drawColumn(3);"
	* Draws a larger column with a size factor of 3.
	*/
	void drawPillar(const int size);

	/**
	 * @brief Draw a tiled passage using the specified points and count.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 */
	void drawPassage(const Point points[4], const int count);

	/**
	 * @brief Draw a asphalted street using the specified points and count.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 */
	void drawStreet(const Point points[4], const int count);

private:
	static Model_3DS* tree1Model;
	static Model_3DS* tree2Model;
	static Model_3DS* tankModel;
	int ground, grass, stone,wall,passage,street;
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
