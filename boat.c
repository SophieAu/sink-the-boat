#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.141592653589

typedef enum { hullLeft, cannonLeft, hullRight, cannonRight, nJoints } Joint;
float increment[nJoints] = {0.01, 1.0, 0.01, -1.0};
float jointPositions[nJoints] = {-0.4, 0.0, 0.4, 0.0};
int healthLeft = 10;
int healthRight = 10;


void turnBoatWorld(){
	glRotatef(45, 1.0, 0, 0);	
	glRotatef(-45, 0, 1.0, 0);
}

void unturnBoatWorld(){
	glRotatef(45, 0, 1.0, 0);
	glRotatef(-45, 1.0, 0, 0);	
}

void drawHealth(float yOffset, int health){
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i<=health; i++){
		float x = 0.05*i;
		glVertex3f(-0.97 + x, 0.97 - yOffset, 1.0);
   		glVertex3f(-0.97 + x, 0.92 - yOffset, 1.0);
	}
	glEnd();
}

void drawBoat(float y, float angle, Joint hull){
	angle = atan(angle)*180/PI;
	
	glTranslatef(jointPositions[hull], y, 0.0);
	glRotatef(angle, 0, 0, 1.0);
	glScalef(0.2, 0.2, 0.2);

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
	glVertex3f(-0.1, 0, 0);
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 0.5, 0);
    glVertex3f(-0.1, 0.5, 0);
    glEnd();
}



void drawBoatLeft(float y, float angle){
	glPushMatrix();

	glColor3f(0, 0, 1);

	unturnBoatWorld();
	drawHealth(0.0, healthLeft);
	turnBoatWorld();

	drawBoat(y, angle, hullLeft);

	//Draw Cannon
	glPushMatrix();
	glTranslatef(0.5, 0.25, 0.0);
	drawCannon(cannonLeft);
	glPopMatrix();

	glPopMatrix();
}

void drawBoatRight(float y, float angle){
	glPushMatrix();

	glColor3f(0, 1, 0);

	unturnBoatWorld();
	drawHealth(0.08, healthRight);
	turnBoatWorld();

	drawBoat(y, angle, hullRight);

	//Draw Cannon
	glPushMatrix();
	glTranslatef(-0.5, 0.25, 0.0);
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


//Methods for key-press actions
void turnLeftCannonRight(){
	jointPositions[cannonLeft] += increment[cannonLeft];
	if (jointPositions[cannonLeft] > 90)
		jointPositions[cannonLeft] = 90;
}

void turnLeftCannonLeft(){
	jointPositions[cannonLeft] -= increment[cannonLeft];
	if (jointPositions[cannonLeft] < -90)
		jointPositions[cannonLeft] = -90;
}

void moveLeftBoatRight(){
	jointPositions[hullLeft] += increment[hullLeft];
	if (jointPositions[hullLeft] > 1)
		jointPositions[hullLeft] = 1;
}

void moveLeftBoatLeft(){
	jointPositions[hullLeft] -= increment[hullLeft];
	if (jointPositions[hullLeft] < -1)
		jointPositions[hullLeft] = -1;
}

void turnRightCannonRight(){
	jointPositions[cannonRight] += increment[cannonRight];
	if (jointPositions[cannonRight] < -90)
		jointPositions[cannonRight] = -90;
}

void turnRightCannonLeft(){
	jointPositions[cannonRight] -= increment[cannonRight];
	if (jointPositions[cannonRight] > 90)
		jointPositions[cannonRight] = 90;
}

void moveRightBoatRight(){
	jointPositions[hullRight] += increment[hullRight];
	if (jointPositions[hullRight] > 1)
		jointPositions[hullRight] = 1;
}

void moveRightBoatLeft(){
	jointPositions[hullRight] -= increment[hullRight];
	if (jointPositions[hullRight] < -1)
		jointPositions[hullRight] = -1;
}

void shootLeftBoat(){

}

void shootRightBoat(){

}