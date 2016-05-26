#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//Own Libs
#include "water.h"
#include "boat.h"
#include "globalvariables.h"

float staticTime = 0.0;
float waitTime = 0.0;
int animationBool = 0;


void animationSpeed(){
	time.t = glutGet(GLUT_ELAPSED_TIME) - waitTime;
	time.t /= 1000.0; //convert from ms to s
	time.deltat = time.t - time.previoust;
	time.previoust = time.t;
}

void idle(){
	if (animationBool % 2 == 0)
		animationSpeed();
	else
		waitTime = glutGet(GLUT_ELAPSED_TIME) - (staticTime*1000);
	
	glutPostRedisplay();
}



void keyboard(unsigned char key, int x, int y){//x and y are the position of the mouse when key was pressed
	switch(key){
		//in- and decrease segment number
		case '+':
		globalSegments *= 2;
		resetSegments();
		glutSwapBuffers();
		break;
		case '-':
		globalSegments /= 2;
		if(globalSegments < 4) // using 4 as anything smaller doesn't make much sense
			globalSegments = 4;
		resetSegments();
		glutSwapBuffers();
		break;

		case '\'':
		animationBool++;
		staticTime = time.t;
		break;

		case 'p':
		toggleWireFrame();
		glutSwapBuffers();
		break;
		case 'n':
		toggleNormal();
		glutSwapBuffers();
		break;
		case 't':
		toggleTangent();
		glutSwapBuffers();
		break;

		case 'w':
		turnLeftCannonLeft();
		glutSwapBuffers();
		break;
		case 'a':
		moveLeftBoatLeft();
		glutSwapBuffers();
		break;
		case 's':
		turnLeftCannonRight();
		glutSwapBuffers();
		break;
		case 'd':
		moveLeftBoatRight();
		glutSwapBuffers();
		break;

		case 32:
		shootLeftBoat();
		break;
		case 13:
		shootRightBoat();
		break;

		case'q':
		exit(0);
		break;
		case 27:
		exit(0);
		break;

		default:
		break;
	}
}

void arrowKeys(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
		moveRightBoatLeft();
		glutSwapBuffers();
		break;
		case GLUT_KEY_UP:
		turnRightCannonRight();
		glutSwapBuffers();
		break;
		case GLUT_KEY_RIGHT: 
		moveRightBoatRight();
		glutSwapBuffers();
		break;
		case GLUT_KEY_DOWN:
		turnRightCannonLeft();
		glutSwapBuffers();
		break;

		default:
		break;
	}
}
