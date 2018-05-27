/**
 * @desc Programa que exibe uma pir�mide sob dois pontos de vista distintos.
 * @author Diego Cintra
 */
#include <iostream>
#include <GL/glut.h>
#include "point.h"

int width = 1000;
int height = 500;

Point eye = Point(3.0, 5.0, 5.0);
Point target = Point(0.0, 0.0, 0.0);

/**
 * @desc Desenha eixos de um sistema de coordenadas.
 * @param {float*} basePoint Ponto de origem de um sistema de coordenadas.
 * @param {float*} i Primeiro versor.
 * @param {float*} j Segundo versor.
 * @param {float*} k Terceiro versor.
 */
void drawAxes(float *basePoint, float *i, float *j, float *k)
{
  float currentColor[4];
  /** Armazena cor atual */
  glGetFloatv(GL_CURRENT_COLOR, currentColor);

  glColor3f(0,0,0);
  for(int i=-10; i<=10; i++){
    glBegin(GL_LINES);
      glVertex3f(-10, 0, i);
      glVertex3f(10, 0, i);
    glEnd();
  }

  for(int i=-10; i<=10; i++){
    glBegin(GL_LINES);
      glVertex3f(i, 0, -10);
      glVertex3f(i, 0, 10);
    glEnd();
  }
  /** Desenha versores */
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(i[0], i[1], i[2]);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(j[0], j[1], j[2]);
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
    glVertex3f(basePoint[0], basePoint[1], basePoint[2]);
    glVertex3f(k[0], k[1], k[2]);
  glEnd();

  /** Retorna para cor anterior */
  glColor3f(currentColor[0], currentColor[1], currentColor[2]);
}

/**
 * @desc Desenha as coordenadas globais.
 */
void drawWCAxes()
{
  float *basePoint, *i, *j, *k;
  basePoint = new float[3];
  basePoint[0] = basePoint[1] = basePoint[2] = 0.0;
  i = new float[3];
  i[0] = 5.0;
  i[1] = i[2] = 0.0;
  j = new float[3];
  j[0] = j[2] = 0.0;
  j[1] = 5.0;
  k = new float[3];
  k[0] = k[1] = 0.0;
  k[2] = 5.0;
  drawAxes(basePoint, i, j, k);
}

/**
 * @desc Fun��o de callback para desenho na tela.
 */
void displayCallback()
{
  /** Limpa a janela APENAS uma vez */
  glClear(GL_COLOR_BUFFER_BIT);

  Point p = Point(0,0,1);
  Point r = Point(1,0,0);
  Point o = Point(0,0,2);

  glColor3f(0.0f, 0.0f, 0.0f);
  /** Desenha a janela mais a esquerda */
  glViewport(0, 0, width, height);
  /*glLoadIdentity();
  gluLookAt(eye.getX(), eye.getY(), eye.getZ(), target.getX(), target.getY(), target.getZ(), 0.0, 1.0, 0.0);
  drawWCAxes();
  glBegin(GL_POINTS);
    glVertex3f(p.getX(), p.getY(), p.getZ());
  glEnd();
  GLUquadric *cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_LINE);
  gluCylinder(cylinder,  1,  1,  3,  30,  1);
*/
  /** Desenha a janela mais a direita */
  //glViewport(width/2, 0, width/2, height);
  glLoadIdentity();
  gluLookAt(eye.getX(), eye.getY(), eye.getZ(), target.getX(), target.getY(), target.getZ(), 0.0, 1.0, 0.0);
  drawWCAxes();
  p.rotate(o, 90, r);
  glBegin(GL_POINTS);
    glVertex3f(p.getX(), p.getY(), p.getZ());
  glEnd();
  glutWireSphere(0.1, 30, 30);
  GLUquadric *cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_LINE);
  gluCylinder(cylinder,  0.1,  0.1,  3,  30,  1);
  glTranslatef(0,0,3);
  glutWireSphere(0.1, 30, 30);
  glRotatef(45,1,0,0);
  gluCylinder(cylinder,  0.1,  0.1,  3,  30,  1);
  glTranslatef(0,0,3);
  glutWireSphere(0.1, 30, 30);


  /** Dispara os comandos APENAS uma vez */
  glFlush();
}

/**
 * @desc Fun��o de callback para reshape.
 * @param {int} w Nova largura da janela.
 * @param {int} h Nova altura da janela.
 */
void reshapeCallback(int w, int h)
{
  /** Atualiza os valores da janela */
  width = w;
  height = h;
  /** Define o volume de vista */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 0.0001, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

void keybord_keypress(GLubyte key, GLint x, GLint y){
    GLint m = glutGetModifiers();

    //FECHA A JANELA AO APERTAR CTRL+D
    if(m == GLUT_ACTIVE_CTRL && (GLint) key == 4)
        exit(EXIT_SUCCESS);


    if (key == 'w' || key == 'W'){
        target.setY(target.getY() + 0.1);
        glutPostRedisplay();
    }
    if (key == 's' || key == 'S'){
        target.setY(target.getY() - 0.1);
        glutPostRedisplay();
    }
    if (key == 'a' || key == 'A'){
        target.rotate(eye, 2.5, Point(0,1,0));
        glutPostRedisplay();
    }
    if (key == 'd' || key == 'D'){
        target.rotate(eye, -2.5, Point(0,1,0));
        glutPostRedisplay();
    }

    //Reset target
    if (key == ' '){
        target = Point(0,0,0);
        glutPostRedisplay();
    }

    //ESC = 27
    if (key == 27){
        glutReshapeWindow(width, height);
    }
}

void keybord_special_keypress(GLint key, GLint x, GLint y){
    if(key == GLUT_KEY_F11){
        glutFullScreen();
    }

    if (key == GLUT_KEY_RIGHT){
        eye.rotate(target, 5, Point(0,1,0));
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_LEFT){
        eye.rotate(target, -5, Point(0,1,0));
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_UP){
        eye.setY(eye.getY() + 0.1);
        target.setY(target.getY() + 0.1);
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_DOWN){
        eye.setY(eye.getY() - 0.1);
        target.setY(target.getY() - 0.1);
        glutPostRedisplay();
    }
}


int main(int argc, char **argv)
{
  /** Passo 1: Inicializa fun��es GLUT */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow("Duas viewports");
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  /** Passo 2: Registra callbacks da OpenGl */
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);

  glutKeyboardFunc(keybord_keypress);
  glutSpecialFunc(keybord_special_keypress);

  /** Passo 3: Executa o programa */
  glutMainLoop();
  return 0;
}
