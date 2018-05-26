#ifndef SPIDER
#define SPIDER

#include <GL/glut.h>
#include <cmath>
#include "point.h"
#include "circle.h"
#include "leg.h"

#define PI 3.14159265359

//Parâmetros do corpo e das pernas da aranha
#define BODY_SIZE1 10
#define BODY_SIZE2 15
#define EXT_LEG_SIZE1 75
#define EXT_LEG_SIZE2 50
#define INT_LEG1_SIZE1 40
#define INT_LEG1_SIZE2 55
#define INT_LEG2_SIZE1 40
#define INT_LEG2_SIZE2 55
#define INT_LEG3_SIZE1 50
#define INT_LEG3_SIZE2 60
#define EXT_LEG_ANGLE 70
#define INT_LEG_ANGLE1 40
#define INT_LEG_ANGLE2 0
#define INT_LEG_ANGLE3 -40
#define INT_KNEE_ANGLE -45
#define EXT_KNEE_ANGLE -40

#define SPIDER_ANIMATION_TIME 1000
#define MOVEMENT_SPEED 3
#define TURN_SPEED 3

class Spider : public DrawableObject{
    private:
        Point pos, destiny, direction;
        Circle body1, body2;
	Circle l_eye, r_eye;
        Leg ext_leg_r, ext_leg_l;
        Leg int_leg_r1, int_leg_l1;
        Leg int_leg_r2, int_leg_l2;
        Leg int_leg_r3, int_leg_l3;
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
