#include <GL/glut.h>
#include <iostream>
#include <math.h>

#include "triangle.h"

Triangle::Triangle(Point a, Point b, Point c){
    this->a = a;
    this->b = b;
    this->c = c;

    GLfloat medX = (a.getX() + b.getX() + c.getX())/3;
    GLfloat medY = (a.getY() + b.getY() + c.getY())/3;

    center = Point(medX, medY);
}

void Triangle::draw(){
    glPushMatrix();

    glTranslated(center.getX(), center.getY(), 0);
    glRotated(rot, 0.0, 0.0, -1.0);
    glScaled(sx, sy, 1);
    glTranslated(-center.getX() + tx, -center.getY() + ty, 0);

    glBegin(GL_TRIANGLES);
        glVertex2i(a.getX(), a.getY());
        glVertex2i(b.getX(), b.getY());
        glVertex2i(c.getX(), c.getY());
    glEnd();

    glPopMatrix();
}
