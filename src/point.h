//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#ifndef POINT
#define POINT

#define PI 3.14159265359

class Point{
    private:
        //Coordenadas
        GLfloat X, Y, Z;

    public:
        //Construtores
        Point();
        Point(GLfloat x, GLfloat y, GLfloat z);

        //Transformações úteis
        void translate(GLfloat delX, GLfloat delY, GLfloat delZ);
        void rotate(Point O, GLfloat rad, Point dir);

        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
        void normalize();
};

#endif
