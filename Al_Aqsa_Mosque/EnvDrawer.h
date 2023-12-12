#ifndef ENV_DRAWER_H
#define ENV_DRAWER_H

#include "Point.h"
#include "Constraints.h"
#include "Color.h"
#include "Model_3DS.h"  

class EnvDrawer {
public:
    EnvDrawer();
    void drawSmallTree(const Point& position, const float size);
    void drawBigTree(const Point& position, const float size);
    void drawTank(const Point& position, const float size);
    void drawTiledLand(const Point points[4],const int count);
    void drawGrassLand(const Point points[4], const int count);
    void drawCitySkyBox(const Point& position, const Constraints& constraints);
    void drawCloudsSkyBox(const Point& position, const Constraints& constraints);
private:
     static Model_3DS* tree1Model;  
     static Model_3DS* tree2Model;
     static Model_3DS* tankModel;
     int ground, grass, stone;
     int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN;
     int CitySKYFRONT, CitySKYBACK, CitySKYLEFT, CitySKYRIGHT, CitySKYUP, CitySKYDOWN;
     int CloudsSKYFRONT, CloudsSKYBACK, CloudsSKYLEFT, CloudsSKYRIGHT, CloudsSKYUP, CloudsSKYDOWN;
     void drawLand(const Point points[4], const int count, const int textureID);
     void drawModel( Model_3DS* model,const Point& position, const float size, const float scaleFactor);
     void drawSkyBox(const Point& position,const Constraints& constraints);
};

#endif // ENV_DRAWER_H
