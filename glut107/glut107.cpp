// glut107.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../glut/glut.h"

float z_pos = 0.0f;
float rot = 0.0f;

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, z_pos);
	glRotatef(rot, 0, 0, 1);

	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		glVertex3f(-0.5, -0.5, -5);
		glColor3f(0, 0, 1);
		glVertex3f(-0.75, 0, -5);
		glColor3f(1, 0, 0);
		glVertex3f(-0.5, 0.5, -5);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0.75, -5);

		glColor3f(0, 0, 1);
		glVertex3f(0.5, 0.5, -5);
		glColor3f(1, 0, 0);
		glVertex3f(0.75, 0, -5);
		glColor3f(0, 1, 0);
		glVertex3f(0.5, -0.5, -5);
		glColor3f(0, 1, 0);
		glVertex3f(0, -0.75, -5);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void init(void) {
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLdouble)500.0 / (GLdouble) 500.0, 0, 100);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h) {
	//if (w >= h) {
	//	glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	//} else {
	//	glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	//}
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLdouble)w / (GLdouble) h, 0, 100);
	glMatrixMode(GL_MODELVIEW);
}

void myTimeout(int id) {
	// called if timer event
	// advance state of animation incrementally
	rot += 10;
	glutPostRedisplay();
	glutTimerFunc(100, myTimeout, 0);
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key == '<' || key == ',') z_pos -= 0.1f;
	if (key == '>' || key == '.') z_pos += 0.1f;
}
int _tmain(int argc, _TCHAR* argv[])
{
	printf("OpenGL Primitives: Proyeksi Perspektif\n");

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");

	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(100, myTimeout, 0);
	glutReshapeFunc(reshape);

	init();
	glutMainLoop();
	return 0;
}

