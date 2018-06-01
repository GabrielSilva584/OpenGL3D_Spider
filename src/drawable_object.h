//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#ifndef DRAWABLE
#define DRAWABLE

#include <GL/glut.h>
#include "point.h"

class DrawableObject{
    public:
        //Variáveis de controle de transformações
        GLfloat rot_y = 0, sx = 1, sy = 1, sz = 1,
                tx = 0, ty = 0, tz = 0;

        //função abstrata
        virtual void draw();

        //Transformações
        void translate(GLfloat delX, GLfloat delY, GLfloat delZ);
        void rotate(GLfloat rad);
        void scale(GLfloat multX, GLfloat multY, GLfloat multZ);
};

#endif
