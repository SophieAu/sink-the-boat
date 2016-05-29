#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.141592653589

typedef enum { hullLeftX, hullLeftZ, cannonLeft, rotationLeft, /**/hullRightX, hullRightZ, cannonRight, rotationRight, nJoints } Joint;
float increment[nJoints] = {0.01, 0.01, 1.0, 1.0, /**/0.01, 0.01, 1.0, 1.0};
float jointPositions[nJoints] = {-0.4, 0.0, 0.0, 0.0, /**/0.4, 0.0, 0.0, 0.0};
int healthLeft = 10;
int healthRight = 10;


// Health bar, drawn as a quad strip with #health rectangles
void drawHealthBar(float yOffset, int health){

	glPushMatrix();
	//world rotation is temporarily reversed to make placing the health bars into the top left corner easier
	glRotatef(45, 0, 1.0, 0);
	glRotatef(45, 1.0, 0, 0);	

	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i<=health; i++){
		float x = 0.05*i;
		glVertex3f(-0.97 + x, 0.97 - yOffset, 1.0);
   		glVertex3f(-0.97 + x, 0.92 - yOffset, 1.0);
	}
	glEnd();
	glPopMatrix();
}

void drawBoat(float y, float angle, Joint hullX, Joint hullZ, Joint rotation){
	angle = atan(angle)*180/PI;
	
	glTranslatef(jointPositions[hullX], y, jointPositions[hullZ]);
	glRotatef(angle, 0, 0, 1.0); //rotation along the sinus wave
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

void drawCannon(float xTranslation, Joint cannon){
	glPushMatrix();
	glTranslatef(xTranslation, 0.25, 0.0);
    glRotatef(jointPositions[cannon], 0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(-0.1, 0, 0);
    glVertex3f(0.1, 0, 0);
    glVertex3f(0.1, 0.5, 0);
    glVertex3f(-0.1, 0.5, 0);
    glEnd();

	glPopMatrix();
}



void drawBoatLeft(float y, float angle){
	glPushMatrix();
	glColor3f(0, 0, 1); //Blue

	drawHealthBar(0.0, healthLeft);
	drawBoat(y, angle, hullLeftX, hullLeftZ, rotationLeft);
	drawCannon(0.5, cannonLeft);

	glPopMatrix();
}

void drawBoatRight(float y, float angle){
	glPushMatrix();
	glColor3f(0, 1, 0); //Green

	drawHealthBar(0.08, healthRight);

	drawBoat(y, angle, hullRightX, hullRightZ, rotationRight);
	drawCannon(-0.5, cannonRight);

	glPopMatrix();
}

float getLeftBoatX(){
	return jointPositions[hullLeftX];
}

float getRightBoatX(){
	return jointPositions[hullRightX];
}





//Functions regarding boat movement
void checkInBounds(Joint hull){
	if (jointPositions[hull] < -1)
		jointPositions[hull] = -1;
	if (jointPositions[hull] > 1)
		jointPositions[hull] = 1;
}

//the angle of the boats need to be considered when moving the boats
void plusMinusQuad(Joint hullX, Joint hullZ, float rotation){
	jointPositions[hullX] += increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] -= increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}

void minusPlusQuad(Joint hullX, Joint hullZ, float rotation){ // -x, +z
	jointPositions[hullX] -= increment[hullX]*cosf(rotation*PI/180);
	checkInBounds(hullX);
	jointPositions[hullZ] += increment[hullZ]*sinf(rotation*PI/180);
	checkInBounds(hullZ);
}


/*since boatLeft and boatRight are facing each other, they de-facto act as if one of them was simply
the wrong way round, hence the opposite us of the plusMinus and minusPlus functions*/
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


void turnLeftBoatRight(){
	jointPositions[rotationLeft] += increment[rotationLeft];
	if(jointPositions[rotationLeft]>=360)
		jointPositions[rotationLeft] -=360;
}

void turnLeftBoatLeft(){
	jointPositions[rotationLeft] -= increment[rotationLeft];
	if(jointPositions[rotationLeft]<0)
		jointPositions[rotationLeft] += 360;
}

void turnRightBoatLeft(){
	jointPositions[rotationRight] -= increment[rotationRight];
	if(jointPositions[rotationRight]>=360)
		jointPositions[rotationRight] -=360;
}
void turnRightBoatRight(){
	jointPositions[rotationRight] += increment[rotationRight];
	if(jointPositions[rotationRight]<0)
		jointPositions[rotationRight] +=360;
}





//Functions regarding the boats' cannons
void cannonMinus(Joint cannon){ //cannon turns in -x direction
	jointPositions[cannon] -= increment[cannon];
	if (jointPositions[cannon] < -90)
		jointPositions[cannon] = -90;	
}

void cannonPlus(Joint cannon){ //cannon turns in +x direction
	jointPositions[cannon] += increment[cannon];
	if (jointPositions[cannon] > 90)
		jointPositions[cannon] = 90;
}


void turnLeftCannonRight(){ //Front
	cannonPlus(cannonRight);
}

void turnLeftCannonLeft(){ //Back
	cannonMinus(cannonLeft);
}

void turnRightCannonRight(){ //Back
	cannonPlus(cannonRight);
}

void turnRightCannonLeft(){ //Front
	cannonMinus(cannonRight);
}

void shootLeftBoat(){
}

void shootRightBoat(){
}