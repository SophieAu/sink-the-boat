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


void drawOSD()
{
  char buffer[30];
  char *bufp;
  int w, h;
    
  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  /* Set up orthographic coordinate system to match the 
     window, i.e. (0,0)-(w,h) */
  w = glutGet(GLUT_WINDOW_WIDTH);
  h = glutGet(GLUT_WINDOW_HEIGHT);
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  /* Frame rate */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(10, 60);
  snprintf(buffer, sizeof buffer, "fr (f/s): %6.0f", fps.frameRate);
  for (bufp = buffer; *bufp; bufp++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

  /* Time per frame */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(10, 40);
  snprintf(buffer, sizeof buffer, "ft (ms/f): %5.0f", 1.0 / fps.frameRate * 1000.0);
  for (bufp = buffer; *bufp; bufp++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);

  /* Pop modelview */
  glPopMatrix();  
  glMatrixMode(GL_PROJECTION);

  /* Pop projection */
  glPopMatrix();  
  glMatrixMode(GL_MODELVIEW);

  /* Pop attributes */
  glPopAttrib();
}


void animationSpeed(){
	time.t = glutGet(GLUT_ELAPSED_TIME) - waitTime;
	time.t /= 1000.0; //convert from ms to s
	time.deltat = time.t - time.previoust;
	time.previoust = time.t;
}

// typedef struct { int frames;
// 	float frameRate, frameRateInterval, lastFrameRateT
// 	} Fps;


void frameRate(){
	fps.frameRateInterval = 0.3;
	time.deltat = time.t - fps.lastFrameRateT;
	if(time.deltat > fps.frameRateInterval){
		fps.frameRate = fps.frames / time.deltat;
		fps.lastFrameRateT = time.t;
		fps.frames = 0;
	}
}

void idle(){
	if (animationBool % 2 == 0)
		animationSpeed();
	else
		waitTime = glutGet(GLUT_ELAPSED_TIME) - (staticTime*1000);
	
	frameRate();

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
