#ifndef DRAWABLE
#define DRAWABLE

#include <GL/glut.h>
#include "point.h"

class DrawableObject{
    public:
        GLfloat rot_y = 0, sx = 1, sy = 1, sz = 1,
                tx = 0, ty = 0, tz = 0;

        virtual void draw();

        //Transformações
        void translate(GLfloat delX, GLfloat delY, GLfloat delZ);
        void rotate(GLfloat rad);
        void scale(GLfloat multX, GLfloat multY, GLfloat multZ);
};

#endif
