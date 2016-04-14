#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.141592653589

typedef enum { hullLeft, cannonLeft, hullRight, cannonRight, nJoints } Joint;
float increment[nJoints] = {0.1, 1.0, 0.1, 1.0};
float jointPositions[nJoints] = {-0.4, 0.0, 0.4, 0.0};


void boatInit(int segments){
	increment[hullLeft] = 2/segments;
	increment[hullRight] = 2/segments;
}

void drawBoat(float y, float angle, Joint hull, int r, int g, int b){
	angle = atan(angle)*180/PI;
	
	glColor3f(r, g, b);
	glTranslatef(jointPositions[hull], y, 0.0);
	glRotatef(angle, 0, 0, 1.0);
	glScalef(0.1, 0.1, 0.1);

	//Hull
	glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(1.0, 0.25, 0);
    glVertex3f(-1.0, 0.25, 0);
    glEnd();

	//Bridge
	glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.25, 0);
    glVertex3f(0.25, -0.25, 0);
    glVertex3f(0.25, 0.25, 0);
    glVertex3f(-0.25, 0.25, 0);
    glEnd();
    glPopMatrix();
}

void drawCannon(Joint cannon){
    glRotatef(jointPositions[cannon], 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.1, -0.25, 0);
    glVertex3f(0.1, -0.25, 0);
    glVertex3f(0.1, 0.25, 0);
    glVertex3f(-0.1, 0.25, 0);
    glEnd();
}



void drawBoatLeft(float y, float angle){
	glPushMatrix();
	drawBoat(y, angle, hullLeft, 0, 0, 1);

	//Draw Cannon
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.0);
	drawCannon(cannonLeft);
	glPopMatrix();

	glPopMatrix();
}

void drawBoatRight(float y, float angle){
	glPushMatrix();
	drawBoat(y, angle, hullRight, 0, 1, 0);

	//Draw Cannon
	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0.0);
	drawCannon(cannonRight);
	glPopMatrix();

	glPopMatrix();
}

float getLeftBoatX(){
	return jointPositions[hullLeft];
}

float getRightBoatX(){
	return jointPositions[hullRight];
}

void turnCannonRight(){
	jointPositions[cannonLeft] += increment[cannonLeft];
}

void turnCannonLeft(){
	jointPositions[cannonLeft] -= increment[cannonLeft];
}

void moveBoatRight(){
	jointPositions[hullLeft] += increment[hullLeft];
}

void moveBoatLeft(){
	jointPositions[hullLeft] -= increment[hullLeft];
}