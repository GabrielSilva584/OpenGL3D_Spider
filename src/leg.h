#ifndef LEG
#define LEG

#include <GL/glut.h>
#include "point.h"

#define ANIMATION_LOOP_TIME 1000
#define LEG_RADIUS 0.1
#define DETAIL_RATE 30

class Leg{
    private:
        Point a;
        GLfloat angleA, angleA0, angleB, angleB0,
                angleAx, angleAx0, angleBx, angleBx0,
                sizeA, sizeB, animationTime;
        GLboolean leftLeg, invertAnim;

    public:
        Leg();
        Leg(Point a, GLfloat angleA, GLfloat angleAx,
            GLfloat angleB, GLfloat angleBx, GLfloat sizeA,
            GLfloat sizeB, GLboolean leftLeg, GLboolean invertAnim);
        void update(GLfloat delta_ms);
        void draw();
};

#endif
