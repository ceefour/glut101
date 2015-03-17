// glut103b.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0, 1, 0);
	glVertex2f(-0.5, -0.5);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0.5);
	glColor3f(1, 0, 1);
	glVertex2f(0.5, 0.5);
	glColor3f(0, 0, 1);
	glVertex2f(0.4, 0.75);
	glEnd();
	glFlush();
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Triangle Strip\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}

