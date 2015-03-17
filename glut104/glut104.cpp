// glut104.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2f(0, 0);
	glColor3f(0, 1, 1);
	glVertex2f(-0.75, 0);
	glColor3f(1, 1, 0);
	glVertex2f(-0.5, 0.5);
	glColor3f(0, 0.5, 0);
	glVertex2f(0, 0.75);
	glColor3f(0.5, 1, 0);
	glVertex2f(0.5, 0.5);
	glColor3f(0, 0.5, 1);
	glVertex2f(0.75, 0);
	glColor3f(1, 1, 0);
	glVertex2f(0.5, -0.5);
	glColor3f(1, 0, 1);
	glVertex2f(0, -0.75);
	glEnd();
	glFlush();
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Polygon Berwarna\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}

