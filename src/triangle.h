#ifndef TRIANGLE
#define TRIANGLE

#include <list>

#include "drawable_object.h"
#include "point.h"

class Triangle : public DrawableObject{
    private:
        Point a, b, c, center;

    public:
        Triangle(Point a, Point b, Point c);
        void draw();
};

#endif
