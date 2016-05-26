#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "globalvariables.h"

#define PI 3.141592653589
const double omega = PI/4;
const double k = 2*PI / 0.5;

enum { wireFrame, tangent, normal, nBools } Bools;
int booleans[nBools] = { 0, 0, 0 };


typedef struct { float leftBorder, rightBorder, range, stepSize, amplitude;
	int segments;
	}SineWave;
SineWave sine;

void resetSegments(){
	sine.segments = globalSegments;
	sine.stepSize = sine.range / sine.segments;
}

void waterInit(){
	sine.leftBorder = -1.0;
	sine.rightBorder = 1.0;
	sine.range = abs(sine.leftBorder) + abs(sine.rightBorder);
	sine.amplitude = 0.1;
	resetSegments();
}

void toggleWireFrame(){
	booleans[wireFrame]++;
}

void toggleNormal(){
	booleans[normal]++;
}

void toggleTangent(){
	booleans[tangent]++;
}

float getSineY(float x){
	return sine.amplitude * sinf(k * x + omega * time.t);
}

float getSineDY(float x){
	return k * sine.amplitude * cosf(k * x + omega * time.t);
}

void drawNormalsAndTangents(){
	for(int i = 0; i <= sine.segments; i++){
        float x = sine.leftBorder + i * sine.stepSize;
        float y = getSineY(x);
        float dx = 1;
        float dy = getSineDY(x);

		float vLength = sqrt(pow(dx, 2) + pow(dy, 2));
		dx /= vLength * 8;
      	dy /= vLength * 8;

		if (booleans[tangent] % 2 == 1){
    		glColor3f(0, 1, 0);
    		for(int j = sine.segments; j >= 0; j--){
        		float z = sine.leftBorder + j * sine.stepSize;
				glBegin(GL_LINES);
 				glVertex3f(x, y, z);
				glVertex3f(x + dx, y + dy, z);
     			glEnd();
			}
	 		
		}

		if (booleans[normal] % 2 == 1){
	 		glColor3f(1, 0, 0);
	 		for(int j = sine.segments; j >= 0; j--){
        		float z = sine.leftBorder + j * sine.stepSize;
			
	 			glBegin(GL_LINES);
	 			glVertex3f(x, y, z);
				glVertex3f(x - dy, y + dx, z);
 				glEnd();
 			}
 		}
 	}
}

void lighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
    
    //this lighting combination keeps the requested cyan but makes it a bit darker and bluer
    GLfloat light_position[] = {1.0f, 0.8f, 0.0f, 0.7f};
	GLfloat light_ambient[] = {-0.1f, 0.1f, 0.1f, -0.5f};
	GLfloat light_diffuse[] = {0.5f, 0.5f, 1.0f, 0.1f}; // the green is dampened, making the water blue-er

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}



void drawWater(){
	if (booleans[wireFrame] % 2 == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
 	lighting();

	GLfloat cyan[] = {0.0f, 1.8f, 1.8f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cyan);
	

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 1, 1, 0.5);

    for(int i = 0; i <= sine.segments; i++){
	glBegin(GL_QUAD_STRIP);

   		float leftX = sine.leftBorder + i * sine.stepSize;
    	float leftSineY = getSineY(leftX);
    	float rightX = sine.leftBorder + (i+1) * sine.stepSize;
		float rightSineY = getSineY(rightX);

        for(int j = sine.segments; j >= 0; j--){
        	float z = sine.leftBorder + j * sine.stepSize;
        	glNormal3f(1.0, getSineDY(leftX), 0.0);
			glVertex3f(leftX, leftSineY, z);
        	glNormal3f(1.0, getSineDY(rightX), 0.0);
			glVertex3f(rightX, rightSineY, z);
		}
	glEnd();
	}
    
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
    drawNormalsAndTangents();
}