#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <wingdi.h>
#include <GL/glut.h>

#define BITMAP_ID 0x4D42		      // the universal bitmap ID
#define MAP_X	32			         // size of map along x-axis
#define MAP_Z	32				         // size of map along z-axis
#define MAP_SCALE	20.0f		         // the scale of the terrain map
#define middle 	MAP_X*MAP_Z/4

////// Texture Information
BITMAPINFOHEADER 	bitmapInfoHeader;	// temp bitmap info header
BITMAPINFOHEADER	landInfo1;			// land texture info header
BITMAPINFOHEADER	landInfo2;
BITMAPINFOHEADER	landInfo3; // land texture info header
BITMAPINFOHEADER	waterInfo;			// water texture info header

//AUX_RGBImageRec
unsigned char*	      imageData;		   // the map image data
unsigned char*       landTexture1;	   // land texture data
unsigned char*       landTexture2;	   // land texture data
unsigned char*       landTexture3;	   // land texture data
unsigned int		   land1;
unsigned int		   land2;	 // the land texture object
unsigned int		   land3;

float terrain[MAP_X][MAP_Z][3];





unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							      // the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	int					imageIdx = 0;		   // image index counter
	unsigned char		tempRGB;				   // swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
}


bool LoadTextures() {
    // load the first land texture data
    landTexture1 = LoadBitmapFile("snow.bmp", &landInfo1);
    if (!landTexture1)
        return false;

    // generate the first land texture as a mipmap
    glGenTextures(1, &land1);
    glBindTexture(GL_TEXTURE_2D, land1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo1.biHeight, landInfo1.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture1);

    // load the second land texture data
    landTexture2 = LoadBitmapFile("green.bmp", &landInfo2);
    if (!landTexture2)
        return false;

    // generate the second land texture as a mipmap
    glGenTextures(1, &land2);
    glBindTexture(GL_TEXTURE_2D, land2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo2.biHeight, landInfo2.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture2);


    landTexture3 = LoadBitmapFile("stone.bmp", &landInfo3);
       if (!landTexture3)
           return false;

       // generate the second land texture as a mipmap
       glGenTextures(1, &land3);
       glBindTexture(GL_TEXTURE_2D, land3);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
       gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo3.biHeight, landInfo3.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture3);

    return true;

}

void water(){
	glEnable(GL_DEPTH_TEST);
    for (int z = 0; z < MAP_Z - 1; z++)
    {
    	glBegin(GL_TRIANGLE_STRIP);

        for (int x = 0; x < MAP_X - 1; x++)
        {

        	glColor3f(0,0,255);
            glVertex3f(terrain[x][z][0],terrain[x][z][1],140);

            glColor3f(0,0,255);
            glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],140);

            glColor3f(0,0,255);
            glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],140);

            glColor3f(0,0,255);
            glVertex3f(terrain[x+1][z+1][0],terrain[x+1][z+1][1],140);
}
        glEnd();
    }
    glEnd();
}

void rock(){
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, land3);
    for (int z = 0; z < MAP_Z - 1; z++)
    {
    	glBegin(GL_TRIANGLE_STRIP);

        for (int x = 0; x < MAP_X - 1; x++)
        {
        	if (terrain[x][z][2] < 175 && terrain[x][z][2] > 150){
        		glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x][z][0],terrain[x][z][1], terrain[x][z][2]+0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],terrain[x+1][z][2]+0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],terrain[x][z+1][2]+0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1],terrain[x+1][z+1][2]+0.5);
        	}
        	else {

        		glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x][z][0],terrain[x][z][1], terrain[x][z][2]-0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],terrain[x+1][z][2]-0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],terrain[x][z+1][2]-0.5);

                glTexCoord2f(1.0f, 1.0f);
            	glColor3f(128,128,128);
                glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1],terrain[x+1][z+1][2]-0.5);

        	}
}
        glEnd();
    }
    glEnd();
}

void snow(){
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, land1);
	    for (int z = 0; z < MAP_Z - 1; z++)
	    {
	    	glBegin(GL_TRIANGLE_STRIP);

	        for (int x = 0; x < MAP_X - 1; x++)
	        {
	        	if (terrain[x][z][2] > 175){
	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(128,255,255);
	                glVertex3f(terrain[x][z][0],terrain[x][z][1], terrain[x][z][2]+0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],terrain[x+1][z][2]+0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],terrain[x][z+1][2]+0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1],terrain[x+1][z+1][2]+0.5);
	        	}
	        	else {

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x][z][0],terrain[x][z][1], terrain[x][z][2]-0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1],terrain[x+1][z][2]-0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1],terrain[x][z+1][2]-0.5);

	                glTexCoord2f(1.0f, 1.0f);
	            	glColor3f(255,255,255);
	                glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1],terrain[x+1][z+1][2]-0.5);
	        	}
	}
	        glEnd();
	    }
	    glEnd();

}
