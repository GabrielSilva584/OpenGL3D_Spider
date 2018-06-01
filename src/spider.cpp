#include "spider.h"
#include <stdio.h>

Spider::Spider(){}

Spider::Spider(Point pos){
    Point tmp, tmp2, o;

    o = Point(0.0, 0.0, 0.0);

    this->pos = pos;

    tmp = Point(0, 0, BODY_SIZE1);

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

    animationTime = 0;
    wireframeMode = false;
}

void Spider::update(GLfloat delta_temp){
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

    //Animate legs
    if(isAnimated){
        //Invert Animation if walking backwards
        if(speed < 0) delta_temp *= -1;

        leg_l1.update(delta_temp);
        leg_l2.update(delta_temp);
        leg_l3.update(delta_temp);
        leg_l4.update(delta_temp);
        leg_r1.update(delta_temp);
        leg_r2.update(delta_temp);
        leg_r3.update(delta_temp);
        leg_r4.update(delta_temp);
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

    //Deaccelerate
    if(speed > DEACCELERATION){
        speed -= DEACCELERATION;
    }else if(speed < -DEACCELERATION){
        speed += DEACCELERATION;
    }else{
        speed = 0;
        isAnimated = false;
    }
}

void Spider::draw(){
    glPushMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(pos.getX() + tx, pos.getY() + ty, pos.getZ() + tz);
    glRotatef(rot_y, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    leg_r1.draw(wireframeMode);
    leg_l1.draw(wireframeMode);
    leg_r2.draw(wireframeMode);
    leg_l2.draw(wireframeMode);
    leg_r3.draw(wireframeMode);
    leg_l3.draw(wireframeMode);
    leg_r4.draw(wireframeMode);
    leg_l4.draw(wireframeMode);

    if(wireframeMode){
        glutWireSphere(BODY_SIZE1, DETAIL_RATE, DETAIL_RATE);
    }else {
        glutSolidSphere(BODY_SIZE1, DETAIL_RATE, DETAIL_RATE);
    }

    glTranslatef(-BODY_INTERSECTION*(BODY_SIZE1+BODY_SIZE2), 0.0, 0.0);

    if(wireframeMode){
        glutWireSphere(BODY_SIZE2, DETAIL_RATE, DETAIL_RATE);
    }else {
        glutSolidSphere(BODY_SIZE2, DETAIL_RATE, DETAIL_RATE);
    }

    glPopMatrix();

    drawEyes(EYE_SIZE1, EYE_ANGLEZ1, EYE_ANGLEY1);
    drawEyes(EYE_SIZE1, EYE_ANGLEZ2, EYE_ANGLEY2);
    drawEyes(EYE_SIZE2, EYE_ANGLEZ3, EYE_ANGLEY3);
    drawEyes(EYE_SIZE2, EYE_ANGLEZ4, EYE_ANGLEY4);
}

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
        glutWireSphere(size, DETAIL_RATE/2, DETAIL_RATE/2);
    }else {
        glutSolidSphere(size, DETAIL_RATE/2, DETAIL_RATE/2);
    }

    glTranslatef(-(BODY_SIZE1 - size/2), 0.0, 0.0);
    glRotatef(-angleZ, 0.0, 0.0, 1.0);
    glRotatef(-2*angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    glTranslatef(BODY_SIZE1 - size/2, 0.0, 0.0);

    if(wireframeMode){
        glutWireSphere(size, DETAIL_RATE/2, DETAIL_RATE/2);
    }else {
        glutSolidSphere(size, DETAIL_RATE/2, DETAIL_RATE/2);
    }

    glPopMatrix();
}

GLfloat Spider::getX(){
    return pos.getX() + tx;
}

GLfloat Spider::getY(){
    return pos.getY() + ty;
}

GLfloat Spider::getZ(){
    return pos.getZ() + tz;
}

void Spider::toggleRenderMode(){
    wireframeMode = !wireframeMode;
}

void Spider::turnLeft(GLfloat delta_temp){
    rotate(TURN_SPEED*delta_temp);
}

void Spider::turnRight(GLfloat delta_temp){
    rotate(-TURN_SPEED*delta_temp);
}

void Spider::walkForward(GLfloat delta_temp){
    isAnimated = true;
    speed += ACCELERATION*delta_temp;
    if(speed > MOVEMENT_SPEED)
        speed = MOVEMENT_SPEED;
}

void Spider::walkBackward(GLfloat delta_temp){
    isAnimated = true;
    speed -= ACCELERATION*delta_temp;
    if(speed < -MOVEMENT_SPEED)
        speed = -MOVEMENT_SPEED;
}

void Spider::toggleAnimation(){
    isAnimated = !isAnimated;
}