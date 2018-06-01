//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#include "drawable_object.h"

void DrawableObject::draw(){
    //função abstrata (virtual)
}

//Transladar objeto no espaço
void DrawableObject::translate(GLfloat delX, GLfloat delY, GLfloat delZ){
    tx += delX;
    ty += delY;
    tz += delZ;
}

//Rotacionar objeto em relação ao eixo Y ao redor do próprio centro
void DrawableObject::rotate(GLfloat deg){
    rot_y += deg;
    if(rot_y >= 360) rot_y -= 360;
    if(rot_y < 0) rot_y += 360;
}

//Escalar objeto em relação ao próprio centro
void DrawableObject::scale(GLfloat multX, GLfloat multY, GLfloat multZ){
    sx *= multX;
    sy *= multY;
    sz *= multZ;
}
