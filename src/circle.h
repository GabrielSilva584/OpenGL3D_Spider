#ifndef CIRCLE
#define CIRCLE

#include <list>

#include "drawable_object.h"
#include "point.h"
#include "triangle.h"

#define PI 3.14159265359


class Circle : public DrawableObject{
    private:
        Point center;
        GLfloat rx, ry;
        std::list<Point> pontos;

    public:
        Circle();
        Circle(Point c, GLfloat r);
        Circle(Point c, GLfloat rx, GLfloat ry);
        void define(Point c, GLfloat rx, GLfloat ry);
        void draw();
};

#endif
