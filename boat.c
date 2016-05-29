#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.141592653589

typedef enum { hullLeftX, hullLeftZ, cannonLeft, hullRightX, hullRightZ, cannonRight, rotationLeft, rotationRight, nJoints } Joint;
float increment[nJoints] = {0.01, 0.01, 1.0, 0.01, 0.01, 1.0, 1.0, 1.0};
float jointPositions[nJoints] = {-0.4, 0.0, 0.0, 0.4, 0.0, 0.0, 0.0, 0.0};
int healthLeft = 10;
int healthRight = 10;


void turnBoatWorld(){
	glRotatef(45, 1.0, 0, 0);	
	glRotatef(-45, 0, 1.0, 0);
}

void unturnBoatWorld(){
	glRotatef(45, 0, 1.0, 0);
	glRotatef(45, 1.0, 0, 0);	
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

void drawBoat(float y, float angle, Joint hullX, Joint hullZ, Joint rotation){
	angle = atan(angle)*180/PI;
	
	glTranslatef(jointPositions[hullX], y, jointPositions[hullZ]);
	glRotatef(angle, 0, 0, 1.0);
	glRotatef(jointPositions[rotation], 0.0, 1.0, 0.0);
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

	glColor3f(0, 0, 1); //Blue
	glPushMatrix();
	unturnBoatWorld();
	drawHealth(0.0, healthLeft);
	glPopMatrix();

	drawBoat(y, angle, hullLeftX, hullLeftZ, rotationLeft);
	
	//Draw Cannon
	glPushMatrix();
	glTranslatef(0.5, 0.25, 0.0);
	drawCannon(cannonLeft);
	glPopMatrix();

	glPopMatrix();
}

void drawBoatRight(float y, float angle){
	glPushMatrix();

	glColor3f(0, 1, 0); //Green

	glPushMatrix();
	unturnBoatWorld();
	drawHealth(0.08, healthRight);
	glPopMatrix();

	drawBoat(y, angle, hullRightX, hullRightZ, rotationRight);
	
	//Draw Cannon
	glPushMatrix();
	glTranslatef(-0.5, 0.25, 0.0);
	drawCannon(cannonRight);
	glPopMatrix();

	glPopMatrix();
}

float getLeftBoatX(){
	return jointPositions[hullLeftX];
}

float getRightBoatX(){
	return jointPositions[hullRightX];
}










void checkInBounds(Joint hull){
	if (jointPositions[hull] < -1)
		jointPositions[hull] = -1;
	if (jointPositions[hull] > 1)
		jointPositions[hull] = 1;
}

void minusMinusQuad(Joint hullX, Joint hullZ, float rotation){ // -x, -z
	jointPositions[hullX] -= increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] -= increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}

void plusMinusQuad(Joint hullX, Joint hullZ, float rotation){ // +x, -z
	jointPositions[hullX] += increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] -= increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}
void plusPlusQuad(Joint hullX, Joint hullZ, float rotation){ // +x, +z
	jointPositions[hullX] += increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] += increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}

void minusPlusQuad(Joint hullX, Joint hullZ, float rotation){ // -x, +z
	jointPositions[hullX] -= increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] += increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}




//Methods for key-press actions
void moveRightBoatBack(){
	plusMinusQuad(hullRightX, hullRightZ, jointPositions[rotationRight]);
}

void moveRightBoatForward(){
	minusPlusQuad(hullRightX, hullRightZ, jointPositions[rotationRight]);
}


void moveLeftBoatBack(){
	minusPlusQuad(hullLeftX, hullLeftZ, jointPositions[rotationLeft]);}






void moveLeftBoatForward(){
	plusMinusQuad(hullLeftX, hullLeftZ, jointPositions[rotationLeft]);
}




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





void shootLeftBoat(){

}

void shootRightBoat(){

}



void turnLeftBoatRight(){ // "adding" degrees
	jointPositions[rotationLeft] += increment[rotationLeft];
	if(jointPositions[rotationLeft]>=360)
		jointPositions[rotationLeft] -=360;
}

void turnLeftBoatLeft(){ // "subtracting" degrees
	jointPositions[rotationLeft] -= increment[rotationLeft];
	if(jointPositions[rotationLeft]<0)
		jointPositions[rotationLeft] += 360;
}

void turnRightBoatLeft(){ // "adding" degrees
	jointPositions[rotationRight] -= increment[rotationRight];
	if(jointPositions[rotationRight]>=360)
		jointPositions[rotationRight] -=360;
}
void turnRightBoatRight(){ // "subtracting" degrees
	jointPositions[rotationRight] += increment[rotationRight];
	if(jointPositions[rotationRight]<0)
		jointPositions[rotationRight] +=360;
}
