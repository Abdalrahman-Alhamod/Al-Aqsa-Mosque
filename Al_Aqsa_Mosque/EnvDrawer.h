#ifndef ENV_DRAWER_H
#define ENV_DRAWER_H

#include "Point.h"
#include "Constraints.h"
#include "Color.h"
#include "Model_3DS.h"
#define HOUR_PER_SECOND (1.f/24.f)
#define THREE_HOURS_PER_SECOND (3.f/24.f)
#define MINUTE_PER_SECOND (1.f/24.f)*(1.f/60.f)
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
	 * @brief Draw a fountain at the specified position with the given size.
	 * @param position The position where the fountain will be drawn.
	 * @param size The size of the fountain.
	 */
	void drawFountain(const Point& position, const float size);

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
	void drawPillar(const float radius,const float height, const int texture,const float baseHeight=0.2, const int cylinderSector=18,const int baseSector=18);

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

	/**
	 * @brief Draw a half-cylinder inside a rectangular prism with specified parameters.
	 * @param radius The radius of the half-cylinder.
	 * @param constraints The constraints defining the size of the rectangular prism.
	 * @param texture The texture ID to be applied to the surfaces.
	 */
	void drawHalfCylinderInRectangularPrism(const float radius, const Constraints& constraints,const  int texture);

	/**
	* @brief Draw an archway composed of pillars and a curved structure.
	* @param size The overall size of the archway.
	* @param pillarHeight The height of the pillars supporting the archway.
	* @param count The number of archway segments.
	* @param textureIndex The index of the texture to be applied, between 0 and 9.
	* @param pillarCylinderSector The number of sectors in the pillar cylinders.
	* @param pillarBaseSector The number of sectors in the pillar bases.
	*/
	void drawArchway(const int size,const int pillarHeight,const int count,const int textureIndex, const int pillarCylinderSector = 18, const int pillarBaseSector = 18);
	
	/**
	* @brief Draw a hallway with alternating rectangular and curved sections.
	* @param size The size of each section in the hallway.
	* @param wallHeight The height of the walls in the hallway.
	* @param count The number of sections in the hallway.
	* @param length The overall length of the hallway.
	* @param textureIndex The index of the texture to be applied, between 0 and 9.
	*/
	void drawHallway(const int size, const int wallHeight, const int count,const int length, const int textureIndex);

	/**
	* @brief Draw a building with the specified size and building texture.
	* @param size The size factor determining the dimensions of the building.
	* @param buildingTextureIndex The index of the building texture to be applied.
	*/
	void drawBuidling(const int size, const int buildingTextureIndex);

	/**
	* @brief Control the position of the light source based on user input.
	* @param keys An array indicating the state of keys, where true means a key is pressed.
	*/
	void controlLightSourcePosition(bool* keys);

	/**
	* @brief Simulate the movement of the sun in the sky.
	* @param rotationRadius The radius of the circular path along which the sun moves.
	* @param sunRadius The radius of the sun.
	* @param speed The speed at which the sun moves, in units per second.
	*/
	void simulateSun(const float rotatioRadius=40,const float sunRadius=10,const float speed=THREE_HOURS_PER_SECOND);

	/**
	* @brief Draw a lighting pillar at the specified position with optional parameters.
	* @param position The position where the lighting pillar will be drawn.
	* @param lightIndex The index of the light source to be associated with the pillar.
	* @param size The size factor determining the dimensions of the pillar.
	* @param pillarHeight The height of the lighting pillar.
	*/
	void drawLightingPillar(const Point& position,const int lightIndex,const float size=1,const float pillarHeight=4);

	GLfloat LightDir[4] = { 1.0f, 1.0f, -5.0f, 1.0f };  // Directional light from the top-left corner
	GLfloat LightPos[4] = { 1.0f, 1.0f, -5.0f, 1.0f };    // Positional light at (1, 1, -5)

private:
	static Model_3DS* tree1Model;
	static Model_3DS* tree2Model;
	static Model_3DS* tankModel;
	static Model_3DS* fountainModel;
	int ground, grass, stone,wall,passage,street,sunTexture,lightTexture;
	int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;
	int CitySKYFRONT, CitySKYBACK, CitySKYLEFT, CitySKYRIGHT, CitySKYUP, CitySKYDOWN;
	int CloudsSKYFRONT, CloudsSKYBACK, CloudsSKYLEFT, CloudsSKYRIGHT, CloudsSKYUP, CloudsSKYDOWN;
	int stonesTexture[10];
	int buildingTexture[6];

	// Lighting Variables
	float ch = 0;

	GLfloat LightAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };    // Low ambient lighting
	GLfloat LightDiff[4] = { 0.8f, 0.8f, 0.8f, 1.0f };    // High diffuse lighting
	GLfloat LightSpec[4] = { 1.0f, 1.0f, 1.0f, 1.0f };    // High specular lighting

	GLfloat MatAmb[4] = { 0.8f, 0.2f, 0.2f, 1.0f };      // Red ambient material
	GLfloat MatDif[4] = { 0.8f, 0.8f, 0.8f, 1.0f };      // High diffuse material
	GLfloat MatSpec[4] = { 0.5f, 0.5f, 0.5f, 1.0f };     // Moderate specular material

	GLfloat MatShn[1] = { 32.0f };                        // Moderate shininess

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
