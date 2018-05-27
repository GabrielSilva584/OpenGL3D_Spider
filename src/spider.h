#ifndef SPIDER
#define SPIDER

#include <GL/glut.h>
#include <cmath>
#include "drawable_object.h"
#include "point.h"
#include "leg.h"

#define PI 3.14159265359

//Parâmetros do corpo e das pernas da aranha
#define BODY_SIZE1 0.5
#define BODY_SIZE2 0.75
#define BODY_INTERSECTION 0.7 
#define LEG_SIZEA 2
#define LEG_SIZEB 5.6569/2
#define LEG1_ANGLEA 60
#define LEG2_ANGLEA 30
#define LEG3_ANGLEA 0
#define LEG4_ANGLEA -30
#define LEG_ANGLEAX -30
#define LEG_ANGLEBX 75 

#define SPIDER_ANIMATION_TIME 1000
#define MOVEMENT_SPEED 0.3
#define TURN_SPEED 3

class Spider : public DrawableObject{
    private:
        Point pos, destiny, direction;
        Leg leg_r1, leg_r2, leg_r3, leg_r4,
            leg_l1, leg_l2, leg_l3, leg_l4;
        GLfloat animationTime;
        GLboolean isAnimated;

    public:
        Spider();
        Spider(Point pos);
        void walkTo(Point destiny);
        void update(GLfloat delta_temp);
        void draw();
};

#endif
