#ifndef ENV_DRAWER_H
#define ENV_DRAWER_H

#include "Point.h"
#include "Constraints.h"
#include "Color.h"
#include "Camera.h"
#include "Model_3DS.h"
#include "MosqueDrawer.h"
#include "Sound.h"
#include "Box.h"
#include <chrono>
#include <thread>
#include <GL/glut.h>  
#include <random>
#include "Constants.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "PrimitiveDrawer.h"
#include "DomeOfTheRock.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#define MINUTE_PER_SECOND (1.f/24.f)*(1.f/60.f)
#define QUARTER_HOUR_PER_SECOND (1.f/24.f)/4
#define HALF_HOUR_PER_SECOND (1.f/24.f)/2
#define HOUR_PER_SECOND (1.f/24.f)
#define TWO_HOURS_PER_SECOND (1.f/24.f)*2
#define THREE_HOURS_PER_SECOND (1.f/24.f)*3

/**
 * @class EnvDrawer
 * @brief A utility class for drawing environmental elements such as trees, tanks, land, and skyboxes.
 */

class EnvDrawer {
public:
	EnvDrawer();
	/**
	 * @brief Constructor for the EnvDrawer class.
	 */
	EnvDrawer(HWND hWnd);

	/**
	 * @brief Draw a small tree at the specified position with the given size.
	 * @param position The position where the tree will be drawn.
	 * @param size The size of the tree.
	 */
	void drawSmallTree(const Point& position, const float size,float rotateY = 0);

	/**
	 * @brief Draw a big tree at the specified position with the given size.
	 * @param position The position where the tree will be drawn.
	 * @param size The size of the tree.
	 */
	void drawBigTree(const Point& position, const float size,float rotateY = 0);

	/**
	 * @brief Draw a tank at the specified position with the given size.
	 * @param position The position where the tank will be drawn.
	 * @param size The size of the tank.
	 */
	void drawTank(const Point& position,float size);

	/**
	 * @brief Draw a fountain at the specified position with the given size.
	 * @param position The position where the fountain will be drawn.
	 * @param size The size of the fountain.
	 */
	void drawFountain(const Point& position, const float size);

	/**
	 * @brief Draw a bird at the specified position with the given size.
	 * @param position The position where the bird will be drawn.
	 * @param size The size of the bird.
	 */
	void drawBird(const Point& position, const float size);

	/**
	 * @brief Draw a Quraan at the specified position with the given size.
	 * @param position The position where the Quraan will be drawn.
	 * @param size The size of the Quraan.
	 */
	void drawQuraan(const Point& position, const float size);

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
	 * @brief Draw a skybox at the specified position and constraints.
	 * @param constraints The constraints defining the size of the skybox.
	 */
	void drawSkyBox(const Constraints& constraints);

	/**
	* @brief Change the texture of the skybox.
	*/
	void changeSkyBoxTexture();

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
	void drawGarden(const Point& point, const float width, const float length, const int grassTilesCount, const float treeSize, bool isSmall);

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
	void drawPillar(const float radius, const float height, const int texture, const float baseHeight = 0.2, const int cylinderSector = 18, const int baseSector = 18);

	/**
	 * @brief Draw a tiled passage using the specified points and count.
	 * @param points An array of points representing the land.
	 * @param count The number of points in the array.
	 */
	void drawPassage(const Point points[4], const int sCount, const int tCount);

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
	void drawHalfCylinderInRectangularPrism(const float radius, const Constraints& constraints, const int sectors, const  int texture);

	/**
	* @brief Draw an archway composed of pillars and a curved structure.
	* @param size The overall size of the archway.
	* @param pillarHeight The height of the pillars supporting the archway.
	* @param count The number of archway segments.
	* @param textureIndex The index of the texture to be applied, between 0 and 9.
	* @param pillarCylinderSector The number of sectors in the pillar cylinders.
	* @param pillarBaseSector The number of sectors in the pillar bases.
	*/
	void drawArchway(const float size, const float pillarHeight, const int count, const int textureIndex, const int pillarCylinderSector = 18, const int pillarBaseSector = 18, const int innerSectorCount = 18);

	/**
	* @brief Draw a hallway with alternating rectangular and curved sections.
	* @param size The size of each section in the hallway.
	* @param wallHeight The height of the walls in the hallway.
	* @param count The number of sections in the hallway.
	* @param length The overall length of the hallway.
	* @param textureIndex The index of the texture to be applied, between 0 and 9.
	*/
	void drawHallway(const float size, const float wallHeight, const int count, const float length, const int textureIndex, const int sectorCount = 18);

	/**
	* @brief Draw a building with the specified size and building texture.
	* @param size The size factor determining the dimensions of the building.
	* @param buildingTextureIndex The index of the building texture to be applied.
	*/
	void drawBuidling(const float size, const int buildingTextureIndex);
	void drawBuidling(const float size,const float hight, const int buildingTextureIndex);

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
	void simulateSun(const float rotatioRadius = 40, const float sunRadius = 10, const float speed = THREE_HOURS_PER_SECOND);

	/**
	* @brief Draw a lighting pillar at the specified position with optional parameters.
	* @param position The position where the lighting pillar will be drawn.
	* @param lightIndex The index of the light source to be associated with the pillar.
	* @param size The size factor determining the dimensions of the pillar.
	* @param pillarHeight The height of the lighting pillar.
	*/
	void drawLightingPillar(const Point& position, const int lightIndex, const float size = 1, const float pillarHeight = 4);

	/**
	 * @brief Decode key inputs to control various features.
	 * @param keys An array indicating the state of keys, where true means a key is pressed.
	 */
	void decodeKeyboard(bool* keys);
	void drawPassageWay();

	/**
	* @brief Draws a cylindric minaret with the specified size and texture.
	* @param size The size of the minaret.
	* @param texture The texture ID to be used.
	*/
	void drawCylindricMinaret(const float size, const int texture);

	/**
	* @brief Draws a cubed minaret with the specified size.
	* @param size The size of the minaret.
	*/
	void drawCubedMinaret(const float size);

	/**
	* @brief Draws a wall with a door using the specified length, wall height, and texture.
	* @param length The length of the wall.
	* @param wallHeight The height of the wall.
	* @param texture The texture ID to be used.
	*/
	void drawWallWithDoor(const float length, const float wallHeight, const int texture);

	/**
	 * @brief Draws a wall with the specified length, wall height, and texture.
	 * @param length The length of the wall.
	 * @param wallHeight The height of the wall.
	 * @param texture The texture ID to be used.
	 */
	void drawWall(const float length, const float wallHeight, const int texture);

	/**
	* @brief Handles sounds based on the camera position.
	* @param camerPosition The position of the camera.
	*/
	void handleSounds(const Point& camerPosition);

	/**
	* @brief Draws a flock of pigeons in a 3D environment.
	*
	* The function utilizes OpenGL for rendering and includes the creation and placement
	* of pigeon-like shapes in a geometric pattern. The pigeons are oriented and positioned
	* based on a combination of rotations and translations.
	*/
	void drawPigeons();

	void setLightAmb(GLfloat ambx, GLfloat amby, GLfloat ambz);
	void setLightDiff(GLfloat diffx, GLfloat diffy, GLfloat diffz);
	void setLightSpec(GLfloat specx, GLfloat specy, GLfloat specz);

	/**
	* @brief Draws a single bench in the 3D environment.
	*
	* The function draws a bench by arranging multiple rectangular blocks in a specific
	* configuration, creating a bench-like structure. The position, rotation, and dimensions
	* of each block are adjusted to form the overall appearance of a bench.
	*/
	void drawBench();

	/**
	 * @brief Draw a staircase in the 3D environment with a specified number of steps.
	 * @param unitConstraints The constraints for each step (width, height, length).
	 * @param count The number of steps in the staircase.
	 */
	void drawStairs(const Constraints& unitConstraints, const int count);

	/**
	 * @brief Draw a textured staircase in the 3D environment with a specified number of steps.
	 * @param unitConstraints The constraints for each step (width, height, length).
	 * @param count The number of steps in the staircase.
	 * @param texture The texture index for the steps.
	 */
	void drawStairs(const Constraints& unitConstraints, const int count, const int texture);

	/**
	* @brief Draws a group of benches in the 3D environment.
	*
	* The function arranges multiple benches in a specific layout by translating and
	* rotating individual benches. The benches are drawn using the `drawBench` function,
	* and the layout forms a visually interesting pattern in the environment.
	*/
	void drawBenchesGroub();

	/**
	* @brief Draws all gardens in the 3D environment.
	*
	* The function checks if the flag `drawGardens` is set to true and proceeds to draw
	* gardens at specific locations. It includes the drawing of trees, grasslands, passages,
	* and various structures to create visually appealing garden areas.
	*/
	void drawAllGardens();

	void drawDomeOfTheRockSquare();
	void drawDomeOfRockSquareGround();

	/**
	* @brief Draws constant elements in the 3D environment.
	*
	* The function draws fixed elements in the environment such as tiled land, streets,
	* minarets, walls, fountains, tanks, buildings, and other structures that do not change
	* dynamically. It contributes to the overall static scenery of the environment.
	*/
	void drawConst();

	/**
	* @brief Draws dynamic elements and handles sun position in the 3D environment.
	*
	* The function adjusts the position of a light source based on user input or simulates
	* the movement of the sun if enabled. It also draws a representation of the sun or the
	* light source. Additionally, it may include other dynamic elements in the environment.
	*
	* @param keys A boolean array representing the state of keys, potentially used for
	* controlling elements in the environment.
	*/
	void drawDynamic(bool* keys);

	/**
	* @brief Draws various elements in the 3D environment.
	*
	* The function is the main drawing function for the environment. It typically calls a
	* display list (not shown in the provided code) and invokes other functions like
	* `drawAllGardens()` and `drawDynamic(keys)` to draw various elements in the environment.
	*
	* @param keys A boolean array representing the state of keys, potentially used for
	* controlling elements in the environment.
	*/
	void draw(bool* keys);

	int stonesTexture[20];

	bool drawSun = true, enableSounds = true;

private:
	static Model_3DS* tree1Model;
	static Model_3DS* tree2Model;
	static Model_3DS* tankModel;
	static Model_3DS* fountainModel;
	static Model_3DS* birdModel;
	static Model_3DS* quraanModel;
	int ground, grass, stone, wall, passage, street, sunTexture, lightTexture;
	int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;
	int CitySKYFRONT, CitySKYBACK, CitySKYLEFT, CitySKYRIGHT, CitySKYUP, CitySKYDOWN;
	int CloudsSKYFRONT, CloudsSKYBACK, CloudsSKYLEFT, CloudsSKYRIGHT, CloudsSKYUP, CloudsSKYDOWN;
	Box envBoxDrawer;
	MosqueDrawer dome;
	int buildingTexture[6];
	int minaret[6];
	int skyBoxTextures[3][6];
	int currentSkyBoxIndex = 0;

	GLfloat LightDir[3] = { 0.0f, -1.0f, 0.0f };
	GLfloat LightPos[4] = { 1.0f, 100.0f, 50.0f, 1.0f };

	bool lights[7];

	DirectSoundBuffer sounds[14];
	DirectSoundManager SoundManager;
	float soundsData[14][4]; // 14 sounds- each sound has its own : x, y, z, r value

	float sunTime = MINUTE_PER_SECOND;
	std::chrono::high_resolution_clock::time_point lastUpdateTime;

	bool drawBirds = true;

	int envDisplayList;

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
	void drawModel(Model_3DS* model, const Point& position, const float size, const float scaleFactor,const float rotateY = 0);

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

	int sectorsCount = 18;
};

#endif // ENV_DRAWER_H
