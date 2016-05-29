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

//Variables and functions concerning the rendering effects of the water
typedef enum { wireFrame, tangent, normal, transparency, lights, nBools } RenderBools;
int booleans[nBools] = { 0, 0, 0, 0, 0 };

float alpha = 1.0; //the transparency "intensity" of the water, no transparency by default

//Various rendering toggle functions
void toggleWireFrame(){
	booleans[wireFrame]++;
		if (booleans[wireFrame] % 2 == 1) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void toggleNormal(){
	booleans[normal]++;
}

void toggleTangent(){
	booleans[tangent]++;
}

void toggleTransparency(){
	booleans[transparency]++;
	if(booleans[transparency] % 2 == 0)
		alpha = 1.0;
	else
		alpha = 0.2;
}

void toggleLights(){
	booleans[lights]++;
}


void lighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
    
    //this lighting combination keeps the requested cyan but makes it a bit darker and bluer
    GLfloat light_position[] = {1.0f, 0.8f, 0.0f, 0.7f};
	GLfloat light_ambient[] = {-0.1f, 0.1f, 0.1f, -0.5f};
	GLfloat light_diffuse[] = {0.5f, 0.5f, 1.0f, 0.1f};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	//this is where the water is assigned its cyan colour
	GLfloat cyan[] = {0.0f, 1.8f, 1.8f, alpha};
	glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cyan);
}




//fuctions regarding the construction of the sine wave that represents the water
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

float getSineY(float x){
	return sine.amplitude * sinf(k * x + omega * time.t);
}

float getSineDY(float x){
	return k * sine.amplitude * cosf(k * x + omega * time.t);
}

void drawNormalsAndTangents(){
	//calculates the normal and tangent for each segment
	for(int i = 0; i <= sine.segments; i++){
        float x = sine.leftBorder + i * sine.stepSize;
        float y = getSineY(x);
        float dx = 1;
        float dy = getSineDY(x);

        //calculates the unit vector (vector of length 1)
		float vLength = sqrt(pow(dx, 2) + pow(dy, 2));
		dx /= vLength * 8;
      	dy /= vLength * 8;

      	//draws the tangents
		if (booleans[tangent] % 2 == 1){
    		glColor3f(0, 1, 0); // green
    		for(int j = 0; j <= sine.segments; j++){
        		float z = sine.leftBorder + j * sine.stepSize;
				glBegin(GL_LINES);
 				glVertex3f(x, y, z);
				glVertex3f(x + dx, y + dy, z);
     			glEnd();
			}
		}

		//draws the normals
		if (booleans[normal] % 2 == 1){
	 		glColor3f(1, 0, 0); // red
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


void drawWater(){
	glPushMatrix();
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (booleans[lights] % 2 == 0)
    	lighting();
    else
    	glColor4f(0, 1.0, 1.0, alpha);

    //the waves consist of #sine.segments stripes of quad strips
    for(int i = 0; i <= sine.segments-1; i++){
   		float leftX = sine.leftBorder + i * sine.stepSize;
    	float leftSineY = getSineY(leftX);
    	float rightX = sine.leftBorder + (i+1) * sine.stepSize;
		float rightSineY = getSineY(rightX);

    	glBegin(GL_QUAD_STRIP);
	    for(int j = sine.segments; j >= 0; j--){
        	float z = sine.leftBorder + j * sine.stepSize;
        	glNormal3f(1.0, getSineDY(leftX), 0.0);
			glVertex3f(leftX, leftSineY, z);
        	glNormal3f(1.0, getSineDY(rightX), 0.0);
			glVertex3f(rightX, rightSineY, z);
		}
		glEnd();
	}
    
    if (booleans[lights] % 2 == 0)
    	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
    drawNormalsAndTangents();
    glPopMatrix();
}