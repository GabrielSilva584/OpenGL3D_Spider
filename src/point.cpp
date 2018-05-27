#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "point.h"


Point::Point() : X(0), Y(0), Z(0){}

Point::Point(GLfloat x, GLfloat y, GLfloat z) : X(x), Y(y), Z(z){}

void Point::translate(GLfloat delX, GLfloat delY, GLfloat delZ){
    X += delX;
    Y += delY;
    Z += delZ;
}

void Point::rotate(Point O, GLfloat deg, Point dir){
    this->translate(-O.getX(), -O.getY(), -O.getZ());
    GLfloat h1, h2, angle1, angle2;

    GLfloat Xold = X;
    GLfloat Yold = Y;
    GLfloat Zold = Z;

    GLfloat Xref = dir.getX();
    GLfloat Yref = dir.getY();
    GLfloat Zref = dir.getZ();

    if(Xref != 0){
        h1 = sqrt( pow(Zref,2) + pow(Xref,2) );
        angle1 = acos(Zref/h1);
        if(Xref < 0) angle1 = -angle1;
    }else{
        angle1 = 0;
        h1 = Zref;
    }

    if(Yref != 0){
        h2 = sqrt( pow(Zref,2) + pow(Yref,2) + pow(Xref,2) );
        angle2 = acos(h1/h2);
        if(Yref < 0) angle2 = -angle2;
    }else angle2 = 0;

    printf("%f %f\n", 180*angle1/PI, 180*angle2/PI);

    if(angle1 != 0){
        //rotacao em Y para zerar Xref
        Z = Zold*cos(angle1) + Xold*sin(angle1);
        X = - Zold*sin(angle1) + Xold*cos(angle1);

        Zold = Z;
        Xold = X;
    }

    print();

    if(angle2 != 0){
        //rotacao em X para zerar Yref
        Y = Yold*cos(angle2) - Zold*sin(angle2);
        Z = Yold*sin(angle2) + Zold*cos(angle2);

        Yold = Y;
        Zold = Z;
    }

    print();

    //rotacao requisitada
    X = Xold*cos(PI*deg/180) - Yold*sin(PI*deg/180);
    Y = Xold*sin(PI*deg/180) + Yold*cos(PI*deg/180);

    Xold = X;
    Yold = Y;

    print();

    if(angle2 != 0){
        //desfaz rotacao em X
        Y = Yold*cos(-angle2) - Zold*sin(-angle2);
        Z = Yold*sin(-angle2) + Zold*cos(-angle2);

        Yold = Y;
        Zold = Z;
    }

    print();
    if(angle1 != 0){
        //desfaz rotacao em Y
        Z = Zold*cos(-angle1) + Xold*sin(-angle1);
        X = - Zold*sin(-angle1) + Xold*cos(-angle1);
    }

    if(abs(X) < 0.00001) X = 0;
    if(abs(Y) < 0.00001) Y = 0;
    if(abs(Z) < 0.00001) Z = 0;
    print();

    this->translate(O.getX(),O.getY(), O.getZ());

    print();
}

void Point::setX(GLfloat x){
    X = x;
}

void Point::setY(GLfloat y){
    Y = y;
}

void Point::setZ(GLfloat z){
    Z = z;
}

GLfloat Point::getX(){
    return X;
}

GLfloat Point::getY(){
    return Y;
}

GLfloat Point::getZ(){
    return Z;
}

void Point::print(){
    std::cout << "P( " << X << ", " << Y << ", " << Z << ")\n";
}
