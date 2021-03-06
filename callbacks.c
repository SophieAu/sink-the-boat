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



//time-related functions and variables
float staticTime = 0.0;
float waitTime = 0.0;
int animationBool = 0;

/*displaying the frame rate etc. this function was completely taken from the tutorial about
projectile motion and only the fps variables were modified*/
void drawOSD(){
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


void animationSpeed(){ //time elapsed since the last call of this function
	time.t = glutGet(GLUT_ELAPSED_TIME) - waitTime;
	time.t /= 1000.0; //convert from ms to s
	time.deltat = time.t - time.previoust;
	time.previoust = time.t;
}

void frameRate(){ // calculation of the frame rate
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
		//Tesselation
		case '+':
		globalSegments *= 2;
		resetSegments();
		glutSwapBuffers();
		break;
		case '-':
		globalSegments /= 2;
		if(globalSegments < 4)
			globalSegments = 4;
		resetSegments();
		glutSwapBuffers();
		break;

		//Boat movement (mostly left boaz)
		case 'w':
		moveLeftBoatForward();
		glutSwapBuffers();
		break;
		case 'a':
		turnLeftBoatLeft();
		glutSwapBuffers();
		break;
		case 's':
		moveLeftBoatBack();
		glutSwapBuffers();
		break;
		case 'd':
		turnLeftBoatRight();
		glutSwapBuffers();
		break;
		case 'q':
		turnLeftCannonRight();
		glutSwapBuffers();
		break;
		case 'r':
		turnLeftCannonLeft();
		glutSwapBuffers();
		break;

		case 32: //Space
		shootLeftBoat();
		break;
		case 13: //Enter
		shootRightBoat();
		break;

		//Exiting the game
		case 27: //Esc
		exit(0);
		break;

		default:
		break;
	}
}

void specialKeys(int key, int x, int y){
	switch(key){
		//"Right" Boat Controls
		case GLUT_KEY_LEFT:
		turnRightBoatLeft();
		glutSwapBuffers();
		break;
		case GLUT_KEY_UP:
		moveRightBoatForward();
		glutSwapBuffers();
		break;
		case GLUT_KEY_RIGHT:
		turnRightBoatRight();
		glutSwapBuffers();
		break;
		case GLUT_KEY_DOWN:
		moveRightBoatBack();
		glutSwapBuffers();
		break;
		case GLUT_KEY_PAGE_UP:
	    turnRightCannonRight();
		glutSwapBuffers();
	    break;
		case GLUT_KEY_PAGE_DOWN:
	    turnRightCannonLeft();
		glutSwapBuffers();
		break;


		//Rendering Controls
		case GLUT_KEY_F1:
		toggleWireFrame();
		glutSwapBuffers();
		break;
		case GLUT_KEY_F2:
    	toggleTransparency();
    	glutSwapBuffers();
    	break;
		case GLUT_KEY_F3:
		toggleLights();
		glutSwapBuffers();
    	break;
		case GLUT_KEY_F4:
		toggleNormal();
		glutSwapBuffers();
	 	break;
		case GLUT_KEY_F5:
	    toggleTangent();
		glutSwapBuffers();
	    break;
		case GLUT_KEY_F6:
	    animationBool++;
		staticTime = time.t;
	    break;
	    /* unused F keys, kept for convenience in case they were needed in the future
		case GLUT_KEY_F7:
	    F7 function key.
	    break;
		case GLUT_KEY_F8:
	    F8 function key. 
	    break;
		case GLUT_KEY_F9:
	    F9 function key. 
	    break;
		case GLUT_KEY_F10:
	    F10 function key. 
	    break;
		case GLUT_KEY_F11:
	    F11 function key. 
	    break;
		case GLUT_KEY_F12:
	    F12 function key. 
	    break;
	    */
		default:
		break;
	}
}
