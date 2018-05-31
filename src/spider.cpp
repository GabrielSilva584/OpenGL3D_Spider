#include "spider.h"
#include <stdio.h>

Spider::Spider(){}

Spider::Spider(Point pos){
    Point tmp, tmp2, o;

    o = Point(0.0, 0.0, 0.0);

    this->pos = pos;
    this->destiny = pos;

    tmp = Point(0, 0, BODY_SIZE1);

    tmp2 = tmp;
    tmp2.rotate(o, 180-LEG1_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_l1 = Leg(tmp2, LEG1_ANGLEA, 180-LEG_ANGLEAX, -LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, true, false);

    tmp2 = tmp;
    tmp2.rotate(o, LEG1_ANGLEA, Point(0.0, 1.0, 0.0));
    leg_r1 = Leg(tmp2, LEG1_ANGLEA, LEG_ANGLEAX, LEG_ANGLEBX, LEG_SIZEA, LEG_SIZEB, false, true);

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
    isAnimated = true;
}

void Spider::walkTo(Point destiny){
    this->destiny = destiny;
}

void Spider::update(GLfloat delta_temp){
    /*if(GLint(pos.getX() + tx) != destiny.getX() || GLint(pos.getY() + ty) != destiny.getY()){
        
        //calculando valor unitário de direção
        GLfloat dx = destiny.getX() - pos.getX() - tx;
        GLfloat dy = destiny.getY() - pos.getY() - ty;
        GLfloat h = sqrt( pow(dx,2) + pow(dy,2) );
        direction = Point(dx/h, dy/h);
        
        //ângulo entre posição atual e destino
        GLfloat angle = acos(dx/h)*180/PI;
        if(dy > 0) angle = 360 - angle;
        
        GLint turn_dir = GLint(angle)%360 - GLint(rot + 90)%360;
        
        if(turn_dir != 0){ //virar
            
            //manter turn_dir entre -180 e 180
            if(turn_dir > 180) turn_dir -= 360;
            else if(turn_dir < -180) turn_dir += 360;
            
            //decidindo direção para virar
            if(turn_dir >= TURN_SPEED) rotate(TURN_SPEED);
            else if(turn_dir <= -TURN_SPEED) rotate(-TURN_SPEED);
            else rotate(turn_dir);
        
        }else{ //andar
            if(h < MOVEMENT_SPEED)
                translate(h*direction.getX(), h*direction.getY());
            else
                translate(MOVEMENT_SPEED*direction.getX(), MOVEMENT_SPEED*direction.getY());
        }
    }*/      
        //atualizar pernas
    if(isAnimated){
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
    

}

void Spider::draw(){
    glPushMatrix();

    glTranslatef(pos.getX() + tx, pos.getY() + ty, pos.getZ() + tz);
    glRotatef(rot_y, 0.0, 1.0, 0.0);
    glScalef(sx, sy, sz);

    leg_r1.draw();
    leg_l1.draw();
    leg_r2.draw();
    leg_l2.draw();
    leg_r3.draw();
    leg_l3.draw();
    leg_r4.draw();
    leg_l4.draw();

    glutWireSphere(BODY_SIZE1, DETAIL_RATE, DETAIL_RATE);

    glTranslatef(-BODY_INTERSECTION*(BODY_SIZE1+BODY_SIZE2), 0.0, 0.0);

    glutWireSphere(BODY_SIZE2, DETAIL_RATE, DETAIL_RATE);

    glTranslatef(BODY_INTERSECTION*(BODY_SIZE1+BODY_SIZE2), 0.0, 0.0);

    glPopMatrix();
}

void Spider::toggleAnimation(){
    if(isAnimated) 
        isAnimated = false;
    else
        isAnimated = true;
}
