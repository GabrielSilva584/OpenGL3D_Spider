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

#define EYE_SIZE1 0.025
#define EYE_SIZE2 0.040
#define EYE_ANGLEY1 10
#define EYE_ANGLEZ1 20
#define EYE_ANGLEY2 20
#define EYE_ANGLEZ2 20
#define EYE_ANGLEY3 15
#define EYE_ANGLEZ3 30
#define EYE_ANGLEY4 15
#define EYE_ANGLEZ4 40

#define LEG_SIZEA 2
#define LEG_SIZEB 2.82845
#define LEG_SIZEA1 2.5
#define LEG_SIZEB1 3.53556
#define LEG1_ANGLEA 60
#define LEG2_ANGLEA 30
#define LEG3_ANGLEA 0
#define LEG4_ANGLEA -30
#define LEG_ANGLEAX -30
#define LEG_ANGLEBX 75 

#define SPIDER_ANIMATION_TIME 1000
#define MOVEMENT_SPEED 0.008
#define ACCELERATION 0.0005
#define DEACCELERATION 0.0005
#define TURN_SPEED 0.1

class Spider : public DrawableObject{
    private:
        Point pos, direction;
        Leg leg_r1, leg_r2, leg_r3, leg_r4,
            leg_l1, leg_l2, leg_l3, leg_l4;
        GLfloat animationTime, speed;
        GLboolean isAnimated, wireframeMode;

        void drawEyes(GLfloat size, GLfloat angleZ, GLfloat angleY);
        
    public:
        Spider();
        Spider(Point pos);
        void update(GLfloat delta_temp);
        void draw();
        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
        void toggleRenderMode();

        //Movement
        void turnLeft(GLfloat delta_temp);
        void turnRight(GLfloat delta_temp);
        void walkForward(GLfloat delta_temp);
        void walkBackward(GLfloat delta_temp);

        void toggleAnimation();
};

#endif
