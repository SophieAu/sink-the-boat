#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>

//Graphics Libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


typedef struct { float xRotation, yRotation;
	float previousXRotation, previousYRotation;
	float passiveX, passiveY;
    } Camera;
Camera camera;



void drawAxis(float length){
	glBegin(GL_LINES);
    // X
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);
    //Y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
	// Z   
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);
    
    
    glColor3f(1, 1, 1);
    glEnd();
}


void drawGrid(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
//    glEnable(GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLE_STRIP);
    glColor4f(0, 1, 1, 0.5);


    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

}


void tuteFour(){

	glRotatef(22.5, 1.0, 0, 0);
	glRotatef(-45, 0, 1.0, 0);
	drawAxis(1);

	glTranslatef(0.7, 0, 0);
	glRotatef(camera.yRotation, 0, 1.0, 0);
	glRotatef(camera.xRotation, 1.0, 0, 0);
	glScalef(0.2f, 0.2f, 0.2f);
	drawAxis(1);
	glutSolidTeapot(1.0f);
}

void lighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat lightpos[] = {.5, 1., 1., 0.};
	GLfloat ambientpos[] = {.5, 1., 1., 0.};

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientpos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientpos);

	
	GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cyan);

}

void turnWorld(){
	glRotatef(45, 1.0, 0, 0);
	glRotatef(-45, 0, 1.0, 0);
	
}

void display(){
	int errorCode;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	turnWorld();
	//lighting()	
	drawAxis(1);
	drawGrid();
	//tuteFour();

	glutSwapBuffers();
	if ((errorCode = glGetError()) != GL_NO_ERROR)
		printf("display: %i %s\n",errorCode, gluErrorString(errorCode));
}

void mouseMotion(int x, int y){
	camera.yRotation = camera.previousYRotation + x - camera.passiveX;
	camera.xRotation = camera.previousXRotation + y - camera.passiveY;

	glutPostRedisplay(); //needs to go when I have an idleFunc()
}

void passiveMouseMotion(int x, int y){
	camera.passiveY = y;
	camera.passiveX = x;
	camera.previousYRotation = camera.yRotation;
	camera.previousXRotation = camera.xRotation;

	glutPostRedisplay(); //needs to go when I have an idleFunc()
}

void mousePress(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("left pressed\n");
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("right pressed\n");
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		printf("left not pressed\n");
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		printf("right not pressed\n");
	}

}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800); 
	glutCreateWindow("Sink the Boat");
	
	glutMouseFunc(mousePress);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutDisplayFunc(display);

	glutMainLoop();
}

