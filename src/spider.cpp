//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#include "spider.h"
#include <stdio.h>

//Construtores
Spider::Spider(){}

Spider::Spider(Point pos){
    Point tmp, tmp2, o;

    o = Point(0.0, 0.0, 0.0);

    this->pos = pos;

    tmp = Point(0, 0, BODY_SIZE1);
    
    //Definição das oito pernas
    tmp2 = tmp;
    tmp2.rotate(o, 180-LEG1_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_l1 = Leg(tmp2, LEG1_ANGLEA, 180-LEG_ANGLEAX, -LEG_ANGLEBX, LEG_SIZEA1, LEG_SIZEB1, true, false);

    tmp2 = tmp;
    tmp2.rotate(o, LEG1_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_r1 = Leg(tmp2, LEG1_ANGLEA, LEG_ANGLEAX, LEG_ANGLEBX, LEG_SIZEA1, LEG_SIZEB1, false, true);

    tmp2 = tmp;
    tmp2.rotate(o, 180-LEG2_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_l2 = Leg(tmp2, LEG2_ANGLEA, 180-LEG_ANGLEAX, -LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, true, true);

    tmp2 = tmp;
    tmp2.rotate(o, LEG2_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_r2 = Leg(tmp2, LEG2_ANGLEA, LEG_ANGLEAX, LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, false, false);

    tmp2 = tmp;
    tmp2.rotate(o, 180-LEG3_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_l3 = Leg(tmp2, LEG3_ANGLEA, 180-LEG_ANGLEAX, -LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, true, false);

    tmp2 = tmp;
    tmp2.rotate(o, LEG3_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_r3 = Leg(tmp2, LEG3_ANGLEA, LEG_ANGLEAX, LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, false, true);

    tmp2 = tmp;
    tmp2.rotate(o, 180-LEG4_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_l4 = Leg(tmp2, LEG4_ANGLEA, 180-LEG_ANGLEAX, -LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, true, true);

    tmp2 = tmp;
    tmp2.rotate(o, LEG4_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_r4 = Leg(tmp2, LEG4_ANGLEA, LEG_ANGLEAX, LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, false, false);

    //Variáveis de controle
    animationTime = 0;
    speed = 0;
    isAnimated = false;
    wireframeMode = false;

    directionRightAnimation = 1;
    directionLeftAnimation = 1;
}

//Atualizar animação e movimento da aranha
void Spider::update(GLfloat delta_temp){
    //Mover aranha
    if(speed!=0){
        Point p = Point(1.0, 0.0, 0.0);
        Point o = Point(0.0, 0.0, 0.0);
        Point d = Point(0.0, 1.0, 0.0);
        p.rotate(o, rot_y, d);

        GLfloat movX, movZ;
        movX = p.getX()*speed*delta_temp;
        movZ = p.getZ()*speed*delta_temp;

        translate(movX, 0.0, movZ);
    }

    //Animar pernas
    if(isAnimated){
        //Invert Animation if walking backwards
        if(speed < 0) delta_temp *= -1;

        leg_l1.update(directionLeftAnimation * delta_temp);
        leg_l2.update(directionLeftAnimation * delta_temp);
        leg_l3.update(directionLeftAnimation * delta_temp);
        leg_l4.update(directionLeftAnimation * delta_temp);
        leg_r1.update(directionRightAnimation * delta_temp);
        leg_r2.update(directionRightAnimation * delta_temp);
        leg_r3.update(directionRightAnimation * delta_temp);
        leg_r4.update(directionRightAnimation * delta_temp);
        animationTime += delta_temp;
    } else {
        leg_l1.rest();
        leg_l2.rest();
        leg_l3.rest();
        leg_l4.rest();
        leg_r1.rest();
        leg_r2.rest();
        leg_r3.rest();
        leg_r4.rest();
    }

    //Desacelerar aranha
    if(speed > DEACCELERATION){
        speed -= DEACCELERATION;
    }else if(speed < -DEACCELERATION){
        speed += DEACCELERATION;
    }else{
        speed = 0;
        isAnimated = false;
    }
}

//Desenhar aranha
void Spider::draw(){
    glPushMatrix();

    //Posicionamento inicial
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(pos.getX() + tx, pos.getY() + ty, pos.getZ() + tz);
    glRotatef(rot_y, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    //Desenhar pernas
    leg_r1.draw(wireframeMode);
    leg_l1.draw(wireframeMode);
    leg_r2.draw(wireframeMode);
    leg_l2.draw(wireframeMode);
    leg_r3.draw(wireframeMode);
    leg_l3.draw(wireframeMode);
    leg_r4.draw(wireframeMode);
    leg_l4.draw(wireframeMode);

    //Desenhar corpo
    if(wireframeMode){
        glutWireSphere(BODY_SIZE1, DETAIL_RATE*2, DETAIL_RATE*2);
    }else {
        glutSolidSphere(BODY_SIZE1, DETAIL_RATE*2, DETAIL_RATE*2);
    }

    glTranslatef(-BODY_INTERSECTION*(BODY_SIZE1+BODY_SIZE2), 0.0, 0.0);

    if(wireframeMode){
        glutWireSphere(BODY_SIZE2, DETAIL_RATE*2, DETAIL_RATE*2);
    }else {
        glutSolidSphere(BODY_SIZE2, DETAIL_RATE*2, DETAIL_RATE*2);
    }

    glPopMatrix();

    //Desenhar olhos
    drawEyes(EYE_SIZE1, EYE_ANGLEZ1, EYE_ANGLEY1);
    drawEyes(EYE_SIZE1, EYE_ANGLEZ2, EYE_ANGLEY2);
    drawEyes(EYE_SIZE2, EYE_ANGLEZ3, EYE_ANGLEY3);
    drawEyes(EYE_SIZE2, EYE_ANGLEZ4, EYE_ANGLEY4);
}

//Desenhar par de olhos
void Spider::drawEyes(GLfloat size, GLfloat angleZ, GLfloat angleY){
    glPushMatrix();

    glColor3f(0.7, 0.1, 0.1);
    glTranslatef(pos.getX() + tx, pos.getY() + ty, pos.getZ() + tz);
    glRotatef(rot_y, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(BODY_SIZE1 - size/2, 0.0, 0.0);

    if(wireframeMode){
        glutWireSphere(size, DETAIL_RATE, DETAIL_RATE);
    }else {
        glutSolidSphere(size, DETAIL_RATE, DETAIL_RATE);
    }

    glTranslatef(-(BODY_SIZE1 - size/2), 0.0, 0.0);
    glRotatef(-angleZ, 0.0, 0.0, 1.0);
    glRotatef(-2*angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(BODY_SIZE1 - size/2, 0.0, 0.0);

    if(wireframeMode){
        glutWireSphere(size, DETAIL_RATE, DETAIL_RATE);
    }else {
        glutSolidSphere(size, DETAIL_RATE, DETAIL_RATE);
    }

    glPopMatrix();
}

//Retornar a coordenada X
GLfloat Spider::getX(){
    return pos.getX() + tx;
}

//Retornar a coordenada Y
GLfloat Spider::getY(){
    return pos.getY() + ty;
}

//Retornar a coordenada Z
GLfloat Spider::getZ(){
    return pos.getZ() + tz;
}

//Alterar modo de renderização
void Spider::toggleRenderMode(){
    wireframeMode = !wireframeMode;
}

//Virar para a esquerda
void Spider::turnLeft(GLfloat delta_temp){
    rotate(TURN_SPEED*delta_temp);
    isAnimated = true;
    if(speed == 0){
        directionLeftAnimation = -1;
        directionRightAnimation = 1.5;
    }
}

//Virar para a direita
void Spider::turnRight(GLfloat delta_temp){
    rotate(-TURN_SPEED*delta_temp);
    isAnimated = true;
    if(speed == 0){
        directionRightAnimation = -1;
        directionLeftAnimation = 1.5;
    }
}

//Acelerar para frente
void Spider::walkForward(GLfloat delta_temp){
    isAnimated = true;
    speed += ACCELERATION*delta_temp;
    if(speed > MOVEMENT_SPEED){
        speed = MOVEMENT_SPEED;
        directionRightAnimation = 1;
        directionLeftAnimation = 1;
    }
}

//Acelerar para trás
void Spider::walkBackward(GLfloat delta_temp){
    isAnimated = true;
    speed -= ACCELERATION*delta_temp;
    if(speed < -MOVEMENT_SPEED){
        speed = -MOVEMENT_SPEED;
        directionRightAnimation = 1;
        directionLeftAnimation = 1;
    }
}

//Alterar estado da animação
void Spider::toggleAnimation(){
    isAnimated = !isAnimated;
}
