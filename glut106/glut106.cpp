// glut106.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, -0.5, 1);
	glColor3f(0, 0, 1);
	glVertex3f(-0.5, 0.5, 1);
	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 1);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, -0.5, 1);
	glEnd();
	glFlush();
}

void reshape(int w, int h) {
	if (w >= h) {
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	} else {
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Reshape\n");
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

