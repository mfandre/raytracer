#ifndef IMAGE_HH
#define IMAGE_HH

#include <iostream>
#include <fstream>
#include "Vec3f.hh"

class Image
{
public:
	int resX, resY;
	Vec3f* data;

	// Constructor
	Image()
	{};

	// Constructor
	Image(int rX, int rY)
	: resX(rX), resY(rY)
	{
		data = new Vec3f[resY * resX]; // Creating a list of lines
	}

	int SavePPM(char *fileName);
	
	//Image *ReadPPM(char *fileName);

	int LoadPPM(char *fileName);

	void Clear();

	void SetValuePixel(int x, int y, Vec3f &data);

	Vec3f GetValuePixel(int x, int y);

	// Destructor
    	~Image()
	{
		delete []data;
	}
};

#endif



