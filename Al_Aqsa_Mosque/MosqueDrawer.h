#ifndef MOSQUE_DRAWER_H
#define MOSQUE_DRAWER_H

#include "Point.h"
#include "Color.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Model_3DS.h"
#define GOLDEN_DOME Color(1.0f, 0.84f, 0.0f)
#define SILVER_DOME Color(0.5f, 0.5f, 0.5f)
#define DOME_SHADOW Color(0.0f, 0.0f, 0.0f)
/**
 * @class MosqueDrawer
 * @brief A utility class for drawing mosque-related structures, such as domes and prayer carpets, using OpenGL.
 */
class MosqueDrawer {
public:
    /**
     * @brief Default constructor for the MosqueDrawer class.
     */
    MosqueDrawer();

    /**
     * @brief Draws a customizable dome using OpenGL.
     *
     * This method draws a dome at the specified position with a customizable size and color.
     *
     * @param position Center position of the dome.
     * @param size Scaling factor for size.
     * @param color RGB color of the dome.
     */
    void drawDome(const Point& position, const float size, const Color& color);

    /**
     * @brief Draws the first type of prayer carpet.
     *
     * This method draws a prayer carpet with a specific texture at the provided vertices.
     *
     * @param points An array of points representing the vertices of the carpet.
     * @param count The number of vertices in the array.
     */
    void drawPrayerCarbet1(const Point points[4], const int count);

    /**
     * @brief Draws the second type of prayer carpet.
     *
     * This method draws a prayer carpet with a specific texture at the provided vertices.
     *
     * @param points An array of points representing the vertices of the carpet.
     * @param count The number of vertices in the array.
     */
    void drawPrayerCarbet2(const Point points[4], const int count);

private:
    /**
     * @brief Static model for the crescent used in the mosque.
     */
    static Model_3DS* crescentModel;

    /**
     * @brief Texture ID for the first type of prayer carpet.
     */
    int carbet1;

    /**
     * @brief Texture ID for the second type of prayer carpet.
     */
    int carbet2;

    /**
     * @brief Draws a prayer carpet with a specific texture at the provided vertices.
     *
     * @param points An array of points representing the vertices of the carpet.
     * @param count The number of vertices in the array.
     * @param textureID The texture ID for the carpet.
     */
    void drawCarbet(const Point points[4], const int count, const int textureID);
};

#endif // MOSQUE_DRAWER_H
