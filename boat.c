#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

typedef enum { hullLeft, cannonLeft, hullRight, cannonRight, nJoints } Joint;
float increment[nJoints] = {0.1, 1.0, 0.1, 1.0};
float jointPositions[nJoints] = {-0.4, 0.0, 0.4, 0.0};


void boatInit(int segments){
	increment[hullLeft] = 2/segments;
	increment[hullRight] = 2/segments;
}

void drawBoat(float y, Joint hull){
	glColor3f(1, 1, 1);
	glTranslatef(jointPositions[hull], y, 0.0);
	glScalef(0.1, 0.1, 0.1);

	//Hull
	glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5, -0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(1.0, 0.25, 0);
    glVertex3f(-1.0, 0.25, 0);
    glEnd();

	//Bridge
	glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.25, -0.25, 0);
    glVertex3f(0.25, -0.25, 0);
    glVertex3f(0.25, 0.25, 0);
    glVertex3f(-0.25, 0.25, 0);
    glEnd();
    glPopMatrix();
}

void drawCannon(Joint cannon){
    glRotatef(jointPositions[cannon], 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.25, 0);
    glVertex3f(0.1, -0.25, 0);
    glVertex3f(0.1, 0.25, 0);
    glVertex3f(-0.1, 0.25, 0);
    glEnd();
}



void drawBoatLeft(float y){
	glPushMatrix();
	drawBoat(y, hullLeft);

	//Draw Cannon
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.0);
	drawCannon(cannonLeft);
	glPopMatrix();

	glPopMatrix();
}

void drawBoatRight(float y){
	glPushMatrix();
	drawBoat(y, hullRight);

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