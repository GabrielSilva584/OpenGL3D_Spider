//=======================================================================
// Importações
//=======================================================================

#include <iostream>
#include <GL/glut.h>
#include <string.h>
#include <assert.h>
#include "point.h"
#include "spider.h"

//=======================================================================
// Declarações
//=======================================================================

//Tamanho da tela
int width = 1000;
int height = 500;

//Parâmetros do chão
const int gridSize = 50;
const int gridSpacing = 1;

//Modo de Câmera
GLboolean freeCameraMode = false;

//Movimento da Aranha
GLboolean spiderTurnRight = false, spiderTurnLeft = false, 
		spiderWalkFoward = false, spiderWalkBackward = false;

//Movimento da Câmera
GLboolean eyeTurnRight = false, eyeTurnLeft = false, 
		eyeTurnUp = false, eyeTurnDown = false,
		eyeMoveForward = false, eyeMoveBackward = false, 
		eyeMoveLeft = false, eyeMoveRight = false,
		lookAtSpider = false;

const GLfloat EYE_TURN_SPEED  = 0.1,
			EYE_MOVEMENT_SPEED = 0.2;

//Intervalo entre frames
const GLfloat FRAME_MS = 1000/60;

//Pontos da câmera
Point eye = Point(3.0, 5.0, 5.0),
	target = Point(0.0, 0.0, 0.0),
	eyeY = Point(-1.0, 15.0, 0.0),
	eyeX = Point(15.0, 1.0, 0.0),
	eyeZ = Point(0.0, 1.0, 15.0),
	eyeXYZ = Point(10.0, 10.0, 10.0),
	spiderPos = Point(0.0, 0.0, 0.0); 


//Textos da HUD
const GLchar *HUDHelp = "H = Exibir Comandos",
		*HUDMovAra = "Setas = Mover Aranha",
		*HUDMovCam = "WASD = Mover Camera",
		*HUDRotCam = "IJKL = Rotacionar Camera",
		*HUDLookAra = "Espaco = Olhar para Aranha",
		*HUDRendMode = "R = Modo de Renderizacao",
		*HUDCamMode = "M = Modo de Camera Livre",
		*HUDAAMode = "T = MultiSample Anti-Aliasing",
		*HUDFS = "F11 = Modo FullScreen",
		*HUDExitFS = "ESC = Sair do Modo FullScreen",
		*HUDClose = "Ctrl+D = Fechar";
const GLfloat HUDx = 10, HUDy = 30;

//Estado da HUD
GLboolean exibirHUD = false;

//Estado do Anti-Aliasing
GLboolean msaa = true;

//A aranha
Spider *spider;

//Funções
void keyPress(GLubyte key, GLint x, GLint y);
void keyRelease(GLubyte key, GLint x, GLint y);
void specialKeyPress(GLint key, GLint x, GLint y);
void specialKeyRelease(GLint key, GLint x, GLint y);
void renderText(GLfloat x, GLfloat y, const GLchar *string );
void drawGround();
void draw();
void reshape(GLint w, GLint h);
void update(GLint param);
int main(int argc, char **argv);

//=======================================================================
// Entrada de teclado
//=======================================================================

//Apertar teclas normais
void keyPress(GLubyte key, GLint x, GLint y){
	GLint m = glutGetModifiers();

	//fecha a janela com Ctrl+D
	if(m == GLUT_ACTIVE_CTRL && (GLint) key == 4)
		exit(EXIT_SUCCESS);

	if(freeCameraMode){
		switch(key){
			//Move a câmera com WASD
			case 'w': case 'W':
				eyeMoveForward = true;
				break;
			case 's': case 'S':
				eyeMoveBackward = true;
				break;
			case 'a': case 'A':
				eyeMoveLeft  = true;
				break;
			case 'd': case 'D':
				eyeMoveRight  = true;
				break;
			
			//Rotaciona a câmera com IJKL
			case 'i': case 'I':
				eyeTurnUp  = true;
				break;
			case 'k': case 'K':
				eyeTurnDown  = true;
				break;
			case 'j': case 'J':
				eyeTurnLeft  = true; 
				break;
			case 'l': case 'L':
				eyeTurnRight  = true;
				break;
		}
	}

	switch(key){
		//Altera modo de câmera
		case 'm': case 'M':
			freeCameraMode = !freeCameraMode;
			break;

		//Altera modo de renderização
		case 'r': case 'R':
			spider->toggleRenderMode();
			break;

		//Altera modo da HUD
		case 'h': case 'H':
			exibirHUD = !exibirHUD;
			break;

		//Altera modo do Anti-Aliasing
		case 't': case 'T':
			msaa = !msaa;
			if (msaa) 
				glEnable(GL_MULTISAMPLE_ARB);
			else 
				glDisable(GL_MULTISAMPLE_ARB);
			break;

		//Olha para a aranha
		case ' ':
			lookAtSpider = true;
			break;

		//Restaura tamanho da janela (ESC)
		case 27:
			glutReshapeWindow(width, height);
			break;
	}
}

//Soltar teclas normais
void keyRelease(GLubyte key, GLint x, GLint y){

	switch(key){
		//Move a câmera com WASD
		case 'w': case 'W':
			eyeMoveForward = false;
			break;
		case 's': case 'S':
			eyeMoveBackward = false;
			break;
		case 'a': case 'A':
			eyeMoveLeft  = false;
			break;
		case 'd': case 'D':
			eyeMoveRight  = false;
			break;

		//Rotaciona a câmera com IJKL
		case 'i': case 'I':
			eyeTurnUp  = false;
			break;
		case 'k': case 'K':
			eyeTurnDown  = false;
			break;
		case 'j': case 'J':
			eyeTurnLeft  = false; 
			break;
		case 'l': case 'L':
			eyeTurnRight  = false;
			break;

		//Olha para a aranha
		case ' ':
			lookAtSpider = false;
			break;
	}
}

//Apertar teclas especiais
void specialKeyPress(GLint key, GLint x, GLint y){
	switch(key){
		//Entra no modo FullScreen
		case GLUT_KEY_F11:
			glutFullScreen();
			break;

		//Move a aranha com as setas
		case GLUT_KEY_RIGHT:
			spiderTurnRight = true;
			break;
		case GLUT_KEY_LEFT:
			spiderTurnLeft = true;
			break;
		case GLUT_KEY_UP:
			spiderWalkFoward = true;
			break;
		case GLUT_KEY_DOWN:
			spiderWalkBackward = true;
			break;
	}
	
}

//Soltar teclas especiais
void specialKeyRelease(GLint key, GLint x, GLint y){
	switch(key){
		//Move a aranha com as setas
		case GLUT_KEY_RIGHT:
			spiderTurnRight = false;
			break;
		case GLUT_KEY_LEFT:
			spiderTurnLeft = false;
			break;
		case GLUT_KEY_UP:
			spiderWalkFoward = false;
			break;
		case GLUT_KEY_DOWN:
			spiderWalkBackward = false;
			break;
	}
}

//=======================================================================
// Renderização
//=======================================================================

//Renderiza um texto na tela
void renderText(GLfloat x, GLfloat y, const GLchar *string ){
	int j = strlen( string );
 
	glColor3f(0.9, 0.4, 0.2);
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ ) {
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
	}
}

//Desenha o chão quadriculado
void drawGround(){
	//Armazena cor atual
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	//Armazena posição aproximada da aranha
	GLint cX = GLint(spider->getX() + 0.5);
	GLint cZ = GLint(spider->getZ() + 0.5);

	//Desenha chão quadriculado ao redor da aranha
	for(GLint i = (-gridSize + cX); i < (gridSize + cX); i += gridSpacing){
		for(GLint j = (-gridSize + cZ); j < (gridSize + cZ); j += gridSpacing){
			
			GLfloat a = i - gridSpacing/2 - cX;
			GLfloat b = j - gridSpacing/2 - cZ;
			GLfloat d = sqrt( pow(a,2) + pow(b,2) );

			if(d < gridSize){
				if((i+j)%2 == 0){
					glColor3f(0.9, 0.9, 0.9);
				}else{
					glColor3f(0.7, 0.7, 0.7);
				}	
				glBegin(GL_QUADS);
					glVertex3f(i, 0, j);
					glVertex3f(i+1, 0, j);
					glVertex3f(i+1, 0, j+1);
					glVertex3f(i, 0, j+1);
				glEnd();
			}
		}
	}

	//Retorna para cor anterior
	glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

//Função de callback para desenho na tela.
void draw(){
	//Limpa a janela
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Point p = Point(0,0,1);
	Point r = Point(1,0,0);
	Point o = Point(0,0,2);

	glColor3f(0.0f, 0.0f, 0.0f);
	
	if(!freeCameraMode){
		spiderPos = Point(spider->getX(), spider->getY(), spider->getZ());

		//Desenha a janela do canto inferior esquerdo
		glViewport(0, 0, width/2, height/2);
		glLoadIdentity();
		gluLookAt(eyeZ.getX(), eyeZ.getY(), eyeZ.getZ(), spiderPos.getX(), spiderPos.getY(), spiderPos.getZ(), 0.0, 1.0, 0.0);
		drawGround();
		spider->draw();

		//Desenha a janela do canto inferior direito
		glViewport(width/2, 0, width/2, height/2);
		glLoadIdentity();
		gluLookAt(eyeXYZ.getX(), eyeXYZ.getY(), eyeXYZ.getZ(), spiderPos.getX(), spiderPos.getY(), spiderPos.getZ(), 0.0, 1.0, 0.0);
		drawGround();
		spider->draw();

		//Desenha a janela do canto superior esquerdo
		glViewport(0, height/2, width/2, height/2);
		glLoadIdentity();
		gluLookAt(eyeX.getX(), eyeX.getY(), eyeX.getZ(), spiderPos.getX(), spiderPos.getY(), spiderPos.getZ(), 0.0, 1.0, 0.0);
		drawGround();
		spider->draw();

		//Desenha a janela do canto superior direito
		glViewport(width/2, height/2, width/2, height/2);
		glLoadIdentity();
		gluLookAt(eyeY.getX(), eyeY.getY(), eyeY.getZ(), spiderPos.getX(), spiderPos.getY(), spiderPos.getZ(), 0.0, 1.0, 0.0);
		drawGround();
		spider->draw();
	}else {
		//Desenha a janela completa
		glViewport(0, 0, width, height);
		glLoadIdentity();
		gluLookAt(eye.getX(), eye.getY(), eye.getZ(), target.getX(), target.getY(), target.getZ(), 0.0, 1.0, 0.0);
		drawGround();
		spider->draw();
	}

	//Desenhar HUD 2D
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glViewport(0, 0, width, height);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	renderText(HUDx, HUDy, HUDHelp);

	if(exibirHUD){
		renderText(HUDx, 2*HUDy, HUDMovAra);
		renderText(HUDx, 3*HUDy, HUDCamMode);
		renderText(HUDx, 4*HUDy, HUDRendMode);
		renderText(HUDx, 5*HUDy, HUDAAMode);
		renderText(HUDx, 6*HUDy, HUDFS);
		renderText(HUDx, 7*HUDy, HUDExitFS);
		renderText(HUDx, 8*HUDy, HUDClose);
		if(freeCameraMode){
			renderText(HUDx, 10*HUDy, HUDMovCam);
			renderText(HUDx, 11*HUDy, HUDRotCam);
			renderText(HUDx, 12*HUDy, HUDLookAra);
		}
	}

	//Retornar Matriz
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	//Troca de Buffer
	glutSwapBuffers();
}

//Função de callback para reshape.
void reshape(GLint w, GLint h){
	//Atualiza os valores da janela
	width = w;
	height = h;

	//Define o volume de vista
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(width)/height, 0.01, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

//=======================================================================
// Atualizar estados
//=======================================================================

void update(GLint param){
	//Pontos de referência
	Point o, d, p, f;
	
	o = Point(0.0, 0.0, 0.0);
	d = Point(0.0, 1.0, 0.0);
	p = Point(target.getX() - eye.getX(), 0.0, target.getZ() - eye.getZ());
	f = Point(target.getX() - eye.getX(),
			target.getY() - eye.getY(),
			target.getZ() - eye.getZ());
	p.rotate(o, 90, d);
	f.normalize();
	p.normalize();

	//Rotação do Olho
	if(eyeTurnUp){
		target.rotate(eye, -EYE_TURN_SPEED * FRAME_MS, p);
		if(abs(target.getX() - eye.getX()) < 0.1 )
			target.rotate(eye, -EYE_TURN_SPEED * FRAME_MS, p);
	}
	if(eyeTurnDown){
		target.rotate(eye, EYE_TURN_SPEED * FRAME_MS, p);
		if(abs(target.getX() - eye.getX()) < 0.1 )
			target.rotate(eye, EYE_TURN_SPEED * FRAME_MS, p);
	}
	if(eyeTurnLeft){
		target.rotate(eye, EYE_TURN_SPEED * FRAME_MS, d);
	}
	if(eyeTurnRight){
		target.rotate(eye, -EYE_TURN_SPEED * FRAME_MS, d);
	}

	//Movimento do Olho
	if(eyeMoveForward){
		eye.move(EYE_MOVEMENT_SPEED * f.getX(), 
				EYE_MOVEMENT_SPEED * f.getY(), 
				EYE_MOVEMENT_SPEED * f.getZ());
		target.move(EYE_MOVEMENT_SPEED * f.getX(), 
				EYE_MOVEMENT_SPEED * f.getY(), 
				EYE_MOVEMENT_SPEED * f.getZ());
	}
	if(eyeMoveBackward){
		eye.move(-EYE_MOVEMENT_SPEED * f.getX(), 
				-EYE_MOVEMENT_SPEED * f.getY(), 
				-EYE_MOVEMENT_SPEED * f.getZ());
		target.move(-EYE_MOVEMENT_SPEED * f.getX(), 
				-EYE_MOVEMENT_SPEED * f.getY(), 
				-EYE_MOVEMENT_SPEED * f.getZ());
	}
	if(eyeMoveLeft){
		eye.move(EYE_MOVEMENT_SPEED * p.getX(), 
				EYE_MOVEMENT_SPEED * p.getY(), 
				EYE_MOVEMENT_SPEED * p.getZ());
		target.move(EYE_MOVEMENT_SPEED * p.getX(), 
				EYE_MOVEMENT_SPEED * p.getY(), 
				EYE_MOVEMENT_SPEED * p.getZ());
	}
	if(eyeMoveRight){
		eye.move(-EYE_MOVEMENT_SPEED * p.getX(), 
				-EYE_MOVEMENT_SPEED * p.getY(), 
				-EYE_MOVEMENT_SPEED * p.getZ());
		target.move(-EYE_MOVEMENT_SPEED * p.getX(), 
				-EYE_MOVEMENT_SPEED * p.getY(), 
				-EYE_MOVEMENT_SPEED * p.getZ());
	}

	if(lookAtSpider)
		target = Point(spider->getX(), spider->getY(), spider->getZ());

	//Movimento da Aranha
	if(spiderWalkFoward)	
		spider->walkForward(FRAME_MS);
	if(spiderWalkBackward)	
		spider->walkBackward(FRAME_MS);
	if(spiderTurnLeft)	
		spider->turnLeft(FRAME_MS);
	if(spiderTurnRight)
		spider->turnRight(FRAME_MS);

	//Atualizar aranha
    spider->update(FRAME_MS);

	//Chamar próximo frame
    glutTimerFunc(FRAME_MS, update, 0);

	//Desenhar novo frame
    glutPostRedisplay();
}

//=======================================================================
// Main
//=======================================================================

int main(int argc, char **argv){
	//Inicializar funções GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Aranha 3D");

	//Configurar OpenGL
	glDepthMask(GL_TRUE);
	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Criar Aranha
	spider = new Spider(Point(0,1,0));

	//Registrar callbacks
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyRelease);
	glutSpecialFunc(specialKeyPress);
	glutSpecialUpFunc(specialKeyRelease);

	glutTimerFunc(FRAME_MS, update, 0);

	//Executar o programa
	glutMainLoop();
	return 0;
}