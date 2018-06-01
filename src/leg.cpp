//=======================================================================
// Copyright (c) 2018 
// Amador Marcelino de Souza Neto
// Gabriel Martins da Silva
// Matheus Araujo Jorge
// 
// Este código-fonte está sobre efeito da licensa GNU GPL v3.0 
// (veja LICENSE para mais informações)
//=======================================================================

#include "leg.h"
#include<cmath>
#include<math.h>
#include<iostream>

//Construtores
Leg::Leg(){}

Leg::Leg(Point a, GLfloat angleA, GLfloat angleAx, GLfloat angleBx,
	GLfloat sizeA, GLfloat sizeB, GLboolean leftLeg, GLboolean invertAnim) :
		a(a), angleA0(angleA), angleAx0(angleAx), angleBx0(angleBx), 
		sizeA(sizeA), sizeB(sizeB), leftLeg(leftLeg), invertAnim(invertAnim)
{	
	if(leftLeg == true){
		this->angleA0 = - angleA;
	}

	this->angleA = angleA0;
	this->angleAx = angleAx0;
	this->angleBx = angleBx0;

	rangeAngleA = 10;
	rangeAngleAx = 5;
	rangeAngleBx = 30;

	animationTime = 0;
	normalAnimation = false;
}

//Atualizar a animação
void Leg::update(GLfloat delta_ms){

	GLfloat initSpeed = 2;

	if(this->leftLeg){
		//Definição pernas E2 e E4, PI/6 adicionado nos cossenos puramente para quebrar simetria
		if(this->invertAnim){
			if(this->normalAnimation){
				angleA = angleA0 + rangeAngleA*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
				angleAx = angleAx0 + halfBridgeRectifier(rangeAngleAx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0);
				angleBx = angleBx0 + halfBridgeRectifier(rangeAngleBx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0);
			}else{ //Animação realizada para transição suave entre estado parado e estado de movimento
				if(angleA == (angleA0 + rangeAngleA))
					this->normalAnimation = true;
				else if((angleA0 + rangeAngleA - angleA) >= initSpeed)
					angleA += initSpeed;
				else
					angleA = angleA0 + rangeAngleA;
			}
		}
		//Definição pernas E1 e E3
		else{
			if(this->normalAnimation){
				angleA = angleA0 - rangeAngleA*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
				angleAx = angleAx0 + halfBridgeRectifier(-rangeAngleAx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0.0);
				angleBx = angleBx0 + halfBridgeRectifier(-rangeAngleBx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0);
			}else{ //Animação realizada para transição suave entre estado parado e estado de movimento
				if(angleA == (angleA0 - rangeAngleA))
					this->normalAnimation = true;
				else if((angleA0 - rangeAngleA - angleA) <= initSpeed)
					angleA -= initSpeed;
				else
					angleA = angleA0 - rangeAngleA;
			}
		}
	}
	else{
		//Definição pernas D1 e D3, PI/6 adicionado nos cossenos puramente para quebrar simetria
		if(this->invertAnim){
			if(this->normalAnimation){
				angleA = angleA0 - rangeAngleA*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
				angleAx = angleAx0 - halfBridgeRectifier(rangeAngleAx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0.0);
				angleBx = angleBx0 - halfBridgeRectifier(rangeAngleBx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0);
			}else{ //Animação realizada para transição suave entre estado parado e estado de movimento
				if(angleA == (angleA0 - rangeAngleA))
					this->normalAnimation = true;
				else if((angleA0 - rangeAngleA - angleA) <= initSpeed)
					angleA -= initSpeed;
				else
					angleA = angleA0 - rangeAngleA;
			}
		}
		//Definição pernas D2 e D4
		else{
			if(this->normalAnimation){
				angleA = angleA0 + rangeAngleA*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
				angleAx = angleAx0 - halfBridgeRectifier(-rangeAngleAx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0.0);
				angleBx = angleBx0 - halfBridgeRectifier(-rangeAngleBx*sin(2*PI*animationTime/ANIMATION_LOOP_TIME), 0);
			}else{ //Animação realizada para transição suave entre estado parado e estado de movimento
				if(angleA == (angleA0 + rangeAngleA))
					this->normalAnimation = true;
				else if((angleA0 + rangeAngleA - angleA) >= initSpeed)
					angleA += initSpeed;
				else
					angleA = angleA0 + rangeAngleA;
			}
		}
	}

	if(normalAnimation)
		animationTime+=delta_ms;
}

//Parar suavemente a animação
void Leg::rest(){
	animationTime = 0;
	normalAnimation = false;

	int restSpeed = 2;

	GLfloat deltaAngleA = angleA - angleA0;
	GLfloat deltaAngleAx = angleAx - angleAx0;
	GLfloat deltaAngleBx = angleBx - angleBx0;

	if(deltaAngleA != 0){
		if(deltaAngleA >= restSpeed)
			angleA -= restSpeed;
		else if(deltaAngleA <= -restSpeed)
			angleA += restSpeed;
		else 
			angleA = angleA0;
	}

	if(deltaAngleAx != 0){
		if(deltaAngleAx >= restSpeed)
			angleAx -= restSpeed;
		else if(deltaAngleAx <= -restSpeed)
			angleAx += restSpeed;
		else 
			angleAx = angleAx0;
	}

	if(deltaAngleBx != 0){
		if(deltaAngleBx >= restSpeed)
			angleBx -= restSpeed;
		else if(deltaAngleBx <= -restSpeed)
			angleBx += restSpeed;
		else 
			angleBx = angleBx0;
	}
};

//Desenhar a perna
void Leg::draw(GLboolean wireframeMode){
	glPushMatrix();

	GLUquadric *cylinder = gluNewQuadric();
	if(wireframeMode){
		gluQuadricDrawStyle(cylinder, GLU_LINE);
	}

	glTranslatef(a.getX(), a.getY(), a.getZ());
	glRotatef(angleA, 0.0, 1.0, 0.0);
	glRotatef(angleAx, 1.0, 0.0, 0.0);

	if(wireframeMode){
		glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);	
	}else {
		glutSolidSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);
	}

	gluCylinder(cylinder,  LEG_RADIUS,  LEG_RADIUS,  sizeA,  DETAIL_RATE,  1);

	glTranslatef(0.0, 0.0, sizeA);

	if(wireframeMode){
		glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);	
	}else {
		glutSolidSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);
	}

	glRotatef(angleBx, 1.0, 0.0, 0.0);

	gluCylinder(cylinder,  LEG_RADIUS,  LEG_RADIUS,  sizeB,  DETAIL_RATE,  1);

	glTranslatef(0,0,sizeB);

	if(wireframeMode){
		glutWireSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);	
	}else {
		glutSolidSphere(LEG_RADIUS, DETAIL_RATE, DETAIL_RATE);
	}

	glPopMatrix();
}

//Retorna o maior valor entre 'number' e 'inferiorLimit'
GLfloat Leg::halfBridgeRectifier(GLfloat number, GLfloat inferiorLimit){
	if(number>inferiorLimit)
		return number;
	
	return inferiorLimit;
};
