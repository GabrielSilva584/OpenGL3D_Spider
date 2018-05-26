#include "spider.h"
#include <stdio.h>

Spider::Spider(){}

Spider::Spider(Point pos){
    Point tmp, tmp2;

    this->pos = pos;
    this->destiny = pos;

    tmp = Point(pos.getX(), pos.getY() + BODY_SIZE1 + BODY_SIZE2);
    body1 = Circle(pos, BODY_SIZE1);
    body2 = Circle(tmp, BODY_SIZE2);

    glColor3f(0.0f, 0.0f, 0.0f);
    tmp = Point(pos.getX() - 2*BODY_SIZE1/10, pos.getY() - 2*BODY_SIZE1/3);
    l_eye = Circle(tmp, BODY_SIZE1/4);
    tmp = Point(pos.getX() + 2*BODY_SIZE1/10, pos.getY() - 2*BODY_SIZE1/3);
    r_eye = Circle(tmp, BODY_SIZE1/4);
    glColor3f(1.0f, 1.0f, 1.0f);

    tmp = Point(pos.getX() + BODY_SIZE1, pos.getY());

    tmp2 = tmp;
    tmp2.rotate(pos, 180-EXT_LEG_ANGLE);
    ext_leg_l = Leg(tmp2, EXT_LEG_ANGLE, EXT_KNEE_ANGLE, EXT_LEG_SIZE1, EXT_LEG_SIZE2, true, false);

    tmp2 = tmp;
    tmp2.rotate(pos, EXT_LEG_ANGLE);
    ext_leg_r = Leg(tmp2, EXT_LEG_ANGLE, EXT_KNEE_ANGLE, EXT_LEG_SIZE1, EXT_LEG_SIZE2, false, true);

    tmp2 = tmp;
    tmp2.rotate(pos, 180-INT_LEG_ANGLE1);
    int_leg_l1 = Leg(tmp2, INT_LEG_ANGLE1, INT_KNEE_ANGLE, INT_LEG1_SIZE1, INT_LEG1_SIZE2, true, true);

    tmp2 = tmp;
    tmp2.rotate(pos, INT_LEG_ANGLE1);
    int_leg_r1 = Leg(tmp2, INT_LEG_ANGLE1, INT_KNEE_ANGLE, INT_LEG1_SIZE1, INT_LEG1_SIZE2, false, false);

    tmp2 = tmp;
    tmp2.rotate(pos, 180-INT_LEG_ANGLE2);
    int_leg_l2 = Leg(tmp2, INT_LEG_ANGLE2, INT_KNEE_ANGLE, INT_LEG2_SIZE1, INT_LEG2_SIZE2, true, false);

    tmp2 = tmp;
    tmp2.rotate(pos, INT_LEG_ANGLE2);
    int_leg_r2 = Leg(tmp2, INT_LEG_ANGLE2, INT_KNEE_ANGLE, INT_LEG2_SIZE1, INT_LEG2_SIZE2, false, true);

    tmp2 = tmp;
    tmp2.rotate(pos, 180-INT_LEG_ANGLE3);
    int_leg_l3 = Leg(tmp2, INT_LEG_ANGLE3, INT_KNEE_ANGLE, INT_LEG3_SIZE1, INT_LEG3_SIZE2, true, true);

    tmp2 = tmp;
    tmp2.rotate(pos, INT_LEG_ANGLE3);
    int_leg_r3 = Leg(tmp2, INT_LEG_ANGLE3, INT_KNEE_ANGLE, INT_LEG3_SIZE1, INT_LEG3_SIZE2, false, false);

    animationTime = 0;
    isAnimated = true;
}

void Spider::walkTo(Point destiny){
    this->destiny = destiny;
}

void Spider::update(GLfloat delta_temp){
    if(GLint(pos.getX() + tx) != destiny.getX() || GLint(pos.getY() + ty) != destiny.getY()){
        
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
            
        //atualizar pernas
        if(isAnimated){
        ext_leg_r.update(delta_temp);
        int_leg_l1.update(delta_temp);
        int_leg_r2.update(delta_temp);
        int_leg_l3.update(delta_temp);
        ext_leg_l.update(delta_temp);
        int_leg_r1.update(delta_temp);
        int_leg_l2.update(delta_temp);
        int_leg_r3.update(delta_temp);
        animationTime += delta_temp;
	    }
    }

}

void Spider::draw(){
    glPushMatrix();

    glTranslated(pos.getX() + tx, pos.getY() + ty, 0);
    glRotated(rot, 0.0, 0.0, -1.0);
    glScaled(sx, sy, 1);
    glTranslated(-pos.getX(), -pos.getY(), 0);

    body1.draw();
    body2.draw();
    glColor4f(0.0, 0.0, 0.0, 1.0);
    l_eye.draw();
    r_eye.draw();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    ext_leg_r.draw();
    ext_leg_l.draw();
    int_leg_r1.draw();
    int_leg_l1.draw();
    int_leg_r2.draw();
    int_leg_l2.draw();
    int_leg_r3.draw();
    int_leg_l3.draw();

    glPopMatrix();
}
