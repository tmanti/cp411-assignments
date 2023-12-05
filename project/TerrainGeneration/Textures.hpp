#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <wingdi.h>
#include <GL/glut.h>

#define BITMAP_ID 0x4D42		      // the universal bitmap ID

////// Texture Information
BITMAPINFOHEADER 	bitmapInfoHeader;	// temp bitmap info header
BITMAPINFOHEADER	rockInfo;			// land texture info header
BITMAPINFOHEADER	grassInfo;			// land texture info header
BITMAPINFOHEADER	snowInfo;			// land texture info header

//AUX_RGBImageRec
unsigned char*       rockTexture;	   // land texture data
unsigned char*       grassTexture;	   // land texture data
unsigned char*       snowTexture;	   // land texture data

unsigned int		   rock_id;
unsigned int		   grass_id;	 // the land texture object
unsigned int		   snow_id;	 // the land texture object

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

#endif  /* TEXTURES_HPP_ */