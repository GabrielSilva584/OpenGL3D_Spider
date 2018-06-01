//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#ifndef LEG
#define LEG

#include <GL/glut.h>
#include "point.h"

#define ANIMATION_LOOP_TIME 500
#define LEG_RADIUS 0.05
#define DETAIL_RATE 10

class Leg{
    private:
        //Variáveis de Posicionamento e Tamanho
        Point a;
        GLfloat angleA, angleA0, angleAx, angleAx0, angleBx,
                angleBx0, sizeA, sizeB, animationTime,
                rangeAngleA, rangeAngleAx, rangeAngleBx;

        //Variáveis de direcionamento de animação
        GLboolean leftLeg, invertAnim, normalAnimation;

    public:
        Leg();
        Leg(Point a, GLfloat angleA, GLfloat angleAx,
            GLfloat angleBx, GLfloat sizeA, GLfloat sizeB, 
            GLboolean leftLeg, GLboolean invertAnim);
        void update(GLfloat delta_ms);
        void rest();
        void draw(GLboolean wireframeMode);
        GLfloat halfBridgeRectifier(GLfloat number, GLfloat inferiorLimit);
};

#endif
