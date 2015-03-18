#include "stdafx.h"
#include <windows.h>
#include "../glut/glut.h"
#include "texture.h"
#include "3dsloader.h"

// The width and height of your window, change them as you like
int screen_width = 640;
int screen_height = 480;
// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x = 0, rotation_x_increment = 0.1;
double rotation_y = 0, rotation_y_increment = 0.05;
double rotation_z = 0, rotation_z_increment = 0.03;
// Flag for rendering as lines or filled polygons
int filling = 1; //0=OFF 1=ON
//Now the object is generic, the cube has annoyed us a little bit, or not ?
obj_type object;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
	glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	// Viewport transformation
	glViewport(0, 0, screen_width, screen_height);
	// Projection transformation
	glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
	glLoadIdentity(); // We initialize the projection matrix as identity
	gluPerspective(45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 10.0f,
		10000.0f); // We define the "viewing volume"
	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode(polygon filled)
	glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping
	// from http://tf3dm.com/3d-model/box-63249.html , opened in Blender then exported as 3DS
	// texture is saved from Blender to BMP
	Load3DS(&object, "GabrielI1B.3ds");
	object.id_texture = LoadBitmap("GabrielI1B.bmp"); // The Function LoadBitmap() return the current texture ID
	// If the last function returns -1 it means the file was not found so we exit from the program
	if (object.id_texture == -1)
	{
		MessageBox(NULL, _T("Image file: GabrielI1B.bmp not found"),
			_T("Zetadeck"), MB_OK | MB_ICONERROR);
		exit(0);
	}
}

void resize(int width, int height)
{
	screen_width = width; // We obtain the new screen width values and store it
	screen_height = height; // Height value
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
	glViewport(0, 0, screen_width, screen_height); // Viewport transformation
	glMatrixMode(GL_PROJECTION); // Projection transformation
	glLoadIdentity(); // We initialize the projection matrix as identity
	gluPerspective(45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 10.0f,
		10000.0f);
	glutPostRedisplay(); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		rotation_x_increment = 0;
		rotation_y_increment = 0;
		rotation_z_increment = 0;
		break;
	case 'r': case 'R':
		if (filling == 0)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode(polygon filled)
			filling = 1;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode(polygon outlined)
			filling = 0;
		}
		break;
	}
}

void keyboard_s(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotation_x_increment = rotation_x_increment + 0.005;
		break;
	case GLUT_KEY_DOWN:
		rotation_x_increment = rotation_x_increment - 0.005;
		break;
	case GLUT_KEY_LEFT:
		rotation_y_increment = rotation_y_increment + 0.005;
		break;
	case GLUT_KEY_RIGHT:
		rotation_y_increment = rotation_y_increment - 0.005;
		break;
	}
}

void display(void)
{
	int l_index;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // Modeling transformation
	glLoadIdentity(); // Initialize the model matrix as identity
	glTranslatef(0.0, 0.0, -15); // We move the object forward (the model matrix is multiplied by the translation matrix)
	rotation_x = rotation_x + rotation_x_increment;
	rotation_y = rotation_y + rotation_y_increment;
	rotation_z = rotation_z + rotation_z_increment;
	if (rotation_x > 359) rotation_x = 0;
	if (rotation_y > 359) rotation_y = 0;
	if (rotation_z > 359) rotation_z = 0;
	glRotatef(rotation_x, 1.0, 0.0, 0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
	glRotatef(rotation_y, 0.0, 1.0, 0.0);
	glRotatef(rotation_z, 0.0, 0.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture
	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive(in our case triangles)
	for (l_index = 0; l_index<object.polygons_qty; l_index++)
	{
		//----------------- FIRST VERTEX -----------------
		// Texture coordinates of the first vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,
			object.mapcoord[object.polygon[l_index].a].v);
		// Coordinates of the first vertex
		glVertex3f(object.vertex[object.polygon[l_index].a].x,
			object.vertex[object.polygon[l_index].a].y,
			object.vertex[object.polygon[l_index].a].z);
		//Vertex definition
		//----------------- SECOND VERTEX -----------------
		// Texture coordinates of the second vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u,
			object.mapcoord[object.polygon[l_index].b].v);
		// Coordinates of the second vertex
		glVertex3f(object.vertex[object.polygon[l_index].b].x,
			object.vertex[object.polygon[l_index].b].y,
			object.vertex[object.polygon[l_index].b].z);
		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u,
			object.mapcoord[object.polygon[l_index].c].v);
		// Coordinates of the Third vertex
		glVertex3f(object.vertex[object.polygon[l_index].c].x,
			object.vertex[object.polygon[l_index].c].y,
			object.vertex[object.polygon[l_index].c].z);
	}
	glEnd();
	glFlush(); // This force the execution of OpenGL commands
	glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_width, screen_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard_s);
	init();
	glutMainLoop();
	return(0);
}
