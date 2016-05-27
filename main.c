#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//Own Libs
#include "callbacks.h"
#include "water.h"
#include "boat.h"
#include "globalvariables.h"


void drawAxis(float length){
	glBegin(GL_LINES);
    // X
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);
    //Y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
	// Z   
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);
    
    glEnd();
}




void display(){
	int errorCode;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glRotatef(-45, 1.0, 0, 0);
	glRotatef(-45, 0, 1.0, 0);	
	drawAxis(1);

	glPushMatrix();
	drawWater();
	glPopMatrix();

	drawBoatLeft(getSineY(getLeftBoatX()), getSineDY(getLeftBoatX()));
	drawBoatRight(getSineY(getRightBoatX()), getSineDY(getRightBoatX()));
	
	glPopMatrix();

	drawOSD();
	fps.frames++;

	glutSwapBuffers();
	if ((errorCode = glGetError()) != GL_NO_ERROR)
		printf("display: %i %s\n",errorCode, gluErrorString(errorCode));
}

void init(){
	globalSegments = 50;
	waterInit();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800); 
	glutCreateWindow("Sink the Boat");
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	init();

	glutMainLoop();
}