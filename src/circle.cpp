#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "circle.h"

Circle::Circle(){}

Circle::Circle(Point c, GLfloat r){
    this->define(c, r, r);
}

Circle::Circle(Point c, GLfloat rx, GLfloat ry){
    this->define(c, rx, ry);
}

void Circle::define(Point c, GLfloat rx, GLfloat ry){
    this->center = c;
    this->rx = rx;
    this->ry = ry;

    pontos.push_back(c);

    GLfloat angle = PI/40; // pi/40

    pontos.clear();

    Point a;

    GLfloat i = 0;
    while(i <= 2*PI){
        a = c;
        a.translate(rx*cos(i), ry*sin(i));
        pontos.push_back(a);

        i += angle;
    }

    a = c;
    a.translate(rx, 0);
    pontos.push_back(a);
}

void Circle::draw(){
    glPushMatrix();

    glTranslated(center.getX(), center.getY(), 0);
    glRotated(rot, 0.0, 0.0, -1.0);
    glScaled(sx, sy, 1);
    glTranslated(-center.getX() + tx, -center.getY() + ty, 0);

    glBegin(GL_TRIANGLE_FAN);
        for(Point &p : pontos){
            glVertex2i(p.getX(), p.getY());
        }
    glEnd();

    glPopMatrix();
}
