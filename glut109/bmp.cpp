#include "stdafx.h"
#include <windows.h>
#include <stdio.h> // Header File For Standard Input / Output
#include <gl/GL.h> // Header File For The OpenGL32 Library
#include <gl/GLU.h> // Header File For The GLu32 Library
#include "../glut/glaux.h"
#include "bmp.h"

AUX_RGBImageRec *LoadBMP(char *filename) // Loads A Bitmap Image
{
	FILE *File = NULL; // File Handle
		if (!filename)
			// Make Sure A filename Was Given
		{
			return NULL;
			// If Not Return NULL
		}
	File = fopen(filename, "r"); // Check To See If The File Exists
		if (File)
			// Does The File Exist?
		{
			fclose(File);
			// Close The Handle
			return auxDIBImageLoadA(filename); // Load The Bitmap And Return A Pointer
		}
	return NULL;
	// If Load Failed Return NULL
}
