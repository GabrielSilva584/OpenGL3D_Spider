#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <list>

#include "point.h"
#include "spider.h"

GLint   WINDOW_WIDTH  = 1120,
        WINDOW_HEIGHT = 630;

GLfloat FRAME_MS = 1000/60;

GLint   screen_width,
        screen_height;

Spider *spider;

void init();
void draw();

void mouse_click(GLint button, GLint action, GLint x, GLint y);
void mouse_move(GLint x, GLint y);
void mouse_drag(GLint x, GLint y);

void keybord_keypress(GLubyte key, GLint x, GLint y);
void keybord_special_keypress(GLint key, GLint x, GLint y);

void update(GLint delta_ms);

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    screen_width  = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_HEIGHT) / 2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OGLSpider");

    init();
    glutDisplayFunc(draw);

    glutMouseFunc(mouse_click);

    glutKeyboardFunc(keybord_keypress);
    glutSpecialFunc(keybord_special_keypress);

    //Start spider
    Point p = Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    spider = new Spider(p);

    glutTimerFunc(FRAME_MS, update, 0);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0, 1.0, 1.0, 1.0);

    if(spider != NULL) spider->draw();

    glFlush();
}

void mouse_click(GLint button, GLint action, GLint x, GLint y){
    if(button == GLUT_LEFT_BUTTON ){
	if(action == GLUT_DOWN){
		//Do the spider dance (set destiny)
		spider->walkTo(Point(x,y));
	}
    }
}

void keybord_keypress(GLubyte key, GLint x, GLint y){
    GLint m = glutGetModifiers();

    //FECHA A JANELA AO APERTAR CTRL+D
    if(m == GLUT_ACTIVE_CTRL && (GLint) key == 4)
        exit(EXIT_SUCCESS);

    //ESC = 27
    if (key == 27){
        glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

void keybord_special_keypress(GLint key, GLint x, GLint y){
    if(key == GLUT_KEY_F11){
        glutFullScreen();
    }
}

void update(GLint param){
    //update spider here (move/animate)
    spider->update(FRAME_MS);

    glutTimerFunc(FRAME_MS, update, 0);
    glutPostRedisplay();
}
