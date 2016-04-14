#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//Own Libs
#include "water.h"
#include "boat.h"


int globalSegments = 0;

typedef struct { float t, deltat, previoust;
    } Time;
Time time;
float staticTime = 0.0;
float waitTime = 0.0;

int animationBool = 0;

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









//BASE FUNCTIONS HERE
void init(){
	globalSegments = 50;
	waterInit(globalSegments);
	boatInit(globalSegments);
}

void animationSpeed(){
	//get elapsed time since program was started
	time.t = glutGet(GLUT_ELAPSED_TIME) - waitTime;
	time.t /= 1000.0; //convert from ms to s

	//calculate time since last idle call
	time.deltat = time.t - time.previoust;

	//update previoust
	time.previoust = time.t;
}

void display(){
	int errorCode;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ALL THE STUFF TO BE DISPLAYED HERE
	glPushMatrix();
	drawAxis(0.5);
	drawWater(time.t);
	// printf("tempY: %f\n", getSineY(getBoatX()); //DEBUG
	// drawBoatLeft(getSineY(getBoatX());
	glPopMatrix();

	//Swap displaying and drawing buffers
	glutSwapBuffers();

	//Process error messages
	if ((errorCode = glGetError()) != GL_NO_ERROR) {
		printf("display: %i %s\n",errorCode, gluErrorString(errorCode));
	}
}

void idle(){
	if (animationBool % 2 == 0){
		animationSpeed();
	} else {
		waitTime = glutGet(GLUT_ELAPSED_TIME) - (staticTime*1000);
	}
	
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){//x and y are the position of the mouse when key was pressed
	switch(key){
		//in- and decrease segment number
		case '+':
		globalSegments += 5;
		// resetSegments(globalSegments);
		glutSwapBuffers();
		break;
		case '-':
		globalSegments -= 5;
		// resetSegments(globalSegments);
		glutSwapBuffers();
		break;
		
		//Toggle animation
		case '\'':
		animationBool++;
		staticTime = time.t;
		break;


		case 'w':
		// toggleWireFrame();
		glutSwapBuffers();
		break;
		case 'n':
		// toggleNormal();
		glutSwapBuffers();
		break;
		case 't':
		// toggleTangent();
		glutSwapBuffers();
		break;

		default:
		break;
	}
}

int main(int argc, char **argv){
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800); 
	glutCreateWindow("Sink the Boat"); //Window name
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	init();
	//Star the program/loop
	glutMainLoop();
}