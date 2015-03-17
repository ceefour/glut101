// glut103.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.75, 0);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0, 0.75);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.75, 0);
		glVertex2f(0.5, -0.5);
		glVertex2f(0, -0.75);
	glEnd();
	glFlush();
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Polygon Segi Delapan\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}

