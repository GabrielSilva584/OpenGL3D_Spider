#include "leg.h"
#include<cmath>
#include<math.h>

Leg::Leg(){}

Leg::Leg(Point a, GLfloat angleA, GLfloat angleAx, GLfloat angleB, GLfloat angleBx,
	GLfloat sizeA, GLfloat sizeB, GLboolean leftLeg, GLboolean invertAnim) :
		a(a), angleA0(angleA), angleAx0(angleAx), angleB0(angleB), angleBx0(angleBx), 
		sizeA(sizeA), sizeB(sizeB), leftLeg(leftLeg), invertAnim(invertAnim)
{	
	if(leftLeg == true){
		this->angleA0 = 180 - angleA;
		this->angleB0 = - angleB;
	}

	this->angleA = angleA0;
	this->angleB = angleB0;
	this->angleAx = angleAx0;
	this->angleBx = angleBx0;

	animationTime = 0;
}

void Leg::update(GLfloat delta_ms){

	if(this->leftLeg){
		//Definição pernas E2 e E4, PI/6 adicionado nos senos e cossenos puramente para quebrar simetria
		if(this->invertAnim){
			//Variação no angulo A
			angleA = angleA0 + 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			//Variação no angulo B
			angleB = angleB0 + 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
		}
		//Definição pernas E1 e E3
		else{
			angleA = angleA0 - 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
			angleB = angleB0 - 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME);
		}
	}
	else{
		//Definição pernas D1 e D3, PI/6 adicionado nos senos e cossenos puramente para quebrar simetria
		if(this->invertAnim){
			angleA = angleA0 - 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			angleB = angleB0 - 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
		}
		//Definição pernas D2 e D4
		else{
			angleA = angleA0 + 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
			angleB = angleB0 + 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME);
		}
	}
	animationTime+=delta_ms;
}

void Leg::draw(){
	glPushMatrix();

	GLUquadric *cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);

	glTranslated(a.getX(), a.getY(), a.getZ());
	glRotatef(angleAx, 1.0, 0.0, 0.0);
	glRotatef(angleA, 0.0, 1.0, 0.0);

	glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);	
	gluCylinder(cylinder,  LEG_RADIUS,  LEG_RADIUS,  sizeA,  DETAIL_RATE,  1);

	glTranslatef(0,0,sizeA);

	glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);

	glRotatef(angleBx, 1.0, 0.0, 0.0);
	glRotatef(angleB, 0.0, 1.0, 0.0);

	gluCylinder(cylinder,  LEG_RADIUS,  LEG_RADIUS,  sizeB,  DETAIL_RATE,  1);

	glTranslatef(0,0,sizeB);

	glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);

	glPopMatrix();
}
