#include "leg.h"
#include<cmath>
#include<math.h>

Leg::Leg(){}

Leg::Leg(Point a, GLfloat angleA, GLfloat angleB, GLfloat sizeA,
	GLfloat sizeB, GLboolean leftLeg, GLboolean invertAnim) :
		a(a), angleA0(angleA), angleB0(angleB),sizeA(sizeA), sizeB(sizeB),
		leftLeg(leftLeg), invertAnim(invertAnim)
{	

	
	if(leftLeg == true){
		this->angleA0 = 180 - angleA;
		this->angleB0 = - angleB;
	}

	this->angleA = angleA0;
	this->angleB = angleB0;

	b = c = a;
	b.setX(b.getX() + sizeA);
	c.setX(c.getX() + sizeA + sizeB);

	animationTime = 0;
	initialSizeArmOne = b.getX();
	initialSizeArmTwo = c.getX();
}

void Leg::update(GLfloat delta_ms){

	if(this->leftLeg){
		//Definição pernas E2 e E4, PI/6 adicionado nos senos e cossenos puramente para quebrar simetria
		if(this->invertAnim){
			//Variação no angulo A
			angleA = angleA0 + 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			//Variação no angulo B
			angleB = angleB0 + 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			//Variação no tamanho da coxa
			b.setX(initialSizeArmOne + (this->sizeA/10)*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6));
			//Variação no tamanho da perna
			c.setX(initialSizeArmTwo + (this->sizeB/7)*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6));
		}
		//Definição pernas E1 e E3
		else{
			angleA = angleA0 - 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
			angleB = angleB0 - 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME);
			b.setX(initialSizeArmOne - (this->sizeA/10)*cos(2*PI*animationTime/ANIMATION_LOOP_TIME));
			c.setX(initialSizeArmTwo - (this->sizeB/7)*sin(2*PI*animationTime/ANIMATION_LOOP_TIME));
		}
	}
	else{
		//Definição pernas D1 e D3, PI/6 adicionado nos senos e cossenos puramente para quebrar simetria
		if(this->invertAnim){
			angleA = angleA0 - 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			angleB = angleB0 - 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6);
			b.setX(initialSizeArmOne + (this->sizeA/10)*cos(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6));
			c.setX(initialSizeArmTwo + (this->sizeB/7)*sin(2*PI*animationTime/ANIMATION_LOOP_TIME+PI/6));
		}
		//Definição pernas D2 e D4
		else{
			angleA = angleA0 + 15*cos(2*PI*animationTime/ANIMATION_LOOP_TIME);
			angleB = angleB0 + 15*sin(2*PI*animationTime/ANIMATION_LOOP_TIME);
			b.setX(initialSizeArmOne - (this->sizeA/10)*cos(2*PI*animationTime/ANIMATION_LOOP_TIME));
			c.setX(initialSizeArmTwo - (this->sizeB/7)*sin(2*PI*animationTime/ANIMATION_LOOP_TIME));
		}
	}


	animationTime+=delta_ms;

}

void Leg::draw(){
	glPushMatrix();

	//Prepara para desenhar a primeira divisão da perna
	glTranslated(a.getX(), a.getY(), 0);
	glRotated(angleA, 0.0, 0.0, -1.0);
	glTranslated(-a.getX(), -a.getY(), 0);

	//Desenha a primeira divisão da perna
	glBegin(GL_LINES);
		glVertex2i(a.getX(), a.getY());
		glVertex2i(b.getX(), b.getY());
	glEnd();

	//Prepara para desenhar a segunda divisão da perna
	glTranslated(b.getX(), b.getY(), 0);
	glRotated(angleB, 0.0, 0.0, -1.0);
	glTranslated(-b.getX(), -b.getY(), 0);

	//Desenha a segunda divisão da perna
	glBegin(GL_LINES);
		glVertex2i(b.getX(), b.getY());
		glVertex2i(c.getX(), c.getY());
	glEnd();

	glPopMatrix();
}
