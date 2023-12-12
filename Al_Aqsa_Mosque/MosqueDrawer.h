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

class MosqueDrawer {
public:
    MosqueDrawer();
    /**
     * Draws a customizable dome using OpenGL.
     *
     * @param position Center position of the dome.
     * @param size Scaling factor for size.
     * @param color RGB color of the dome.
     */
    void drawDome(const Point& position, const float size, const Color& color);
    void drawPrayerCarbet1(const Point points[4], const int count);
    void drawPrayerCarbet2(const Point points[4], const int count);

private:
     static Model_3DS* crescentModel;  
     int carbet1, carbet2;
     void drawCarbet(const Point points[4], const int count, const int textureID);
};

#endif // MOSQUE_DRAWER_H
