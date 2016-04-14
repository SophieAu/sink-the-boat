#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.141592653589
const double omega = PI/4;
const double k = 2*PI / 0.5;

enum { wireFrame, tangent, normal, nBools } Bools;
int booleans[nBools] = { 0, 0, 0};

float time = 0.0;

typedef struct { float leftBorder, rightBorder, range, stepSize, amplitude;
	int segments;
	}SineWave;
SineWave sine;

void resetSegments(int globalSegments){
	sine.segments = globalSegments;
	sine.stepSize = sine.range / sine.segments;
}

void waterInit(int globalSegments){
	sine.leftBorder = -1.0;
	sine.rightBorder = 1.0;
	sine.range = abs(sine.leftBorder) + abs(sine.rightBorder);
	sine.amplitude = 0.4;
	resetSegments(globalSegments);
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
	return sine.amplitude * sinf(k * x + omega * time);
}

float getSineDY(float x){
	return k * sine.amplitude * cosf(k * x + omega * time);
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
	 		glBegin(GL_LINES);
 			glVertex3f(x, y, 0);
			glVertex3f(x + dx, y + dy, 0);
     		glEnd();
		}

		if (booleans[normal] % 2 == 1){
	 		glColor3f(1, 0, 0);
	 		glBegin(GL_LINES);
	 		glVertex3f(x, y, 0);
			glVertex3f(x - dy, y + dx, 0);
 			glEnd();
 		}
 	}
}

void drawWater(float globalTime){
	time = globalTime;
	if (booleans[wireFrame] % 2 == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUAD_STRIP);
    glColor4f(0, 1, 1, 0.5);

    //Fence post problem. Hence the 0th node outside the for loop
    glVertex3f(sine.leftBorder, getSineY(sine.leftBorder), 0);
    glVertex3f(sine.leftBorder, -1.0, 0);

	for(int i = 1; i <= sine.segments; i++){
        float x = sine.leftBorder + i * sine.stepSize;
		glVertex3f(x, getSineY(x), 0);
		glVertex3f(x, -1.0, 0);
    }
    glEnd();

    drawNormalsAndTangents();
}