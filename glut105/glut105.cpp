// glut105.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, -0.5, 1);
	glColor3f(0, 0, 1);
	glVertex3f(-0.75, 0, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, 1);
	glColor3f(0, 01, 0);
	glVertex3f(0, 0.75, 1);
	glColor3f(0, 0, 1);
	glVertex3f(0.5, 0.5, -1);
	glColor3f(1, 0, 0);
	glVertex3f(0.75, 0, -1);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, -0.5, -1);
	glColor3f(0, 0, 1);
	glVertex3f(0, -0.75, -1);
	glEnd();
	glFlush();
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: 3 Dimensional Vertex\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}

