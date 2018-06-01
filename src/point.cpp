//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "point.h"

//Construtores
Point::Point() : X(0), Y(0), Z(0){}

Point::Point(GLfloat x, GLfloat y, GLfloat z) : X(x), Y(y), Z(z){}

//Translada o ponto no espaço
void Point::translate(GLfloat delX, GLfloat delY, GLfloat delZ){
    X += delX;
    Y += delY;
    Z += delZ;
}

//Rotaciona o ponto 'deg' grau ao redor do ponto 'O' na direção 'dir'
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

    if(angle1 != 0){
        //rotacao em Y para zerar Xref
        Z = Zold*cos(angle1) + Xold*sin(angle1);
        X = - Zold*sin(angle1) + Xold*cos(angle1);

        Zold = Z;
        Xold = X;
    }

    if(angle2 != 0){
        //rotacao em X para zerar Yref
        Y = Yold*cos(angle2) - Zold*sin(angle2);
        Z = Yold*sin(angle2) + Zold*cos(angle2);

        Yold = Y;
        Zold = Z;
    }

    //rotacao requisitada
    X = Xold*cos(PI*deg/180) - Yold*sin(PI*deg/180);
    Y = Xold*sin(PI*deg/180) + Yold*cos(PI*deg/180);

    Xold = X;
    Yold = Y;

    if(angle2 != 0){
        //desfaz rotacao em X
        Y = Yold*cos(-angle2) - Zold*sin(-angle2);
        Z = Yold*sin(-angle2) + Zold*cos(-angle2);

        Yold = Y;
        Zold = Z;
    }

    if(angle1 != 0){
        //desfaz rotacao em Y
        Z = Zold*cos(-angle1) + Xold*sin(-angle1);
        X = - Zold*sin(-angle1) + Xold*cos(-angle1);
    }

    if(abs(X) < 0.00001) X = 0;
    if(abs(Y) < 0.00001) Y = 0;
    if(abs(Z) < 0.00001) Z = 0;
   
    this->translate(O.getX(),O.getY(), O.getZ());

}

//Retornar a coordenada X
GLfloat Point::getX(){
    return X;
}

//Retornar a coordenada Y
GLfloat Point::getY(){
    return Y;
}

//Retornar a coordenada Z
GLfloat Point::getZ(){
    return Z;
}

//Normaliza a distância do ponto à origem 
//para ser utilizado como vetor
void Point::normalize(){
    GLfloat s = sqrt( pow(X,2) + pow(Y,2) + pow(Z,2) );
    if(s == 0) return;
    X /= s;
    Y /= s;
    Z /= s;
}
