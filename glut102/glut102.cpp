// glut102.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
	glEnd();
	glFlush();
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Triangle\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}

