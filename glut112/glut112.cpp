// OpenGL
// - Fog Filter
// fogfilter=0 --> Nearest Filtered Texture
// fogfilter=1 --> Linear Interpolation Texture
// fogfilter=2 --> Mipmapped Texture
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdarg.h>
#include "../glut/glut.h"

#include "bmp.h"

float z_pos = -5.0f;
float rot = 0.0f;
GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };
/* array to hold texture handles */
GLuint filter; // Which Filter To Use
GLuint texture[3]; // Storage For 3 Textures
// Fog
bool gp;
GLuint fogfilter;
GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR };
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
	int Status = FALSE; // Status Indicator
	AUX_RGBImageRec *TextureImage[1]; // Create Storage Space For The Texture
	memset(TextureImage, 0, sizeof(void *) * 1); // Set The Pointer To NULL
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP("special.bmp"))
	{
		Status = TRUE;
		// Set The Status To TRUE
		glGenTextures(3, &texture[0]); // Create Three Textures
		// Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX,
			TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}
	if (TextureImage[0]) // If Texture Exists
	{
		if (TextureImage[0]->data) // If Texture Image Exists
		{
			free(TextureImage[0]->data); // Free The Texture Image Memory
		}
		free(TextureImage[0]); // Free The Image Structure
	}
	return Status; // Return The Status
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myTimeOut(int id)
{
	// called if timer event
	// ...advance the state of animation incrementally...
	rot += 1;
	glutPostRedisplay(); // request redisplay
	glutTimerFunc(100, myTimeOut, 0); // request next timer event
}

void myKeyboard(unsigned char key, int x, int y)
{
	if ((key == '<') || (key == ',')) z_pos -= 0.1f;
	else if ((key == '>') || (key == '.')) z_pos += 0.1f;
	else if ((key == 'F') || (key = 'f'))
	{
		filter += 1;
		if (filter>2)
		{
			filter = 0;
		}
		printf("filter: %i \n", filter);
	}
	else if ((key == 'G') || (key == 'g'))
	{
		if (gp == FALSE)
		{
			gp = TRUE;
			fogfilter += 1;
			if (fogfilter>2) // Is fogfilter Greater Than 2?
			{
				fogfilter = 0; // If So, Set fogfilter To Zero
			}
			glFogi(GL_FOG_MODE, fogMode[fogfilter]); // Fog Mode
		}
		else
		{
			gp = FALSE;
		}
		printf("filter: %i \n", fogfilter);
	}
}

void mydisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLoadIdentity();
	glTranslatef(0.0, 0.0f, z_pos);
	glRotatef(rot, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texture[filter]);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void init()
{
	if (!LoadGLTextures()) // Jump To Texture Loading Routine
	{
		return; // If Texture Didn't Load Return FALSE
	}
	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	// FOG
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // We'll Clear To The Color Of The Fog
	glFogi(GL_FOG_MODE, fogMode[fogfilter]); // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor); // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.35f); // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE); // Fog Hint Value
	glFogf(GL_FOG_START, 100.0f); // Fog Start Depth
	glFogf(GL_FOG_END, 1000.0f); // Fog End Depth
	glEnable(GL_FOG);
	glClearDepth(1.0f);
	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); // Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); // Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); // Position The Light
	glEnable(GL_LIGHT1);
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**) argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	// callbacks
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(100, myTimeOut, 0);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}
