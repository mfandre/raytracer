#ifndef TEXTURE_HH
#define TEXTURE_HH

#include "Basic.hh"
#include "Image.hh"

class Texture : public Image
{
public:
	Texture(int x = 0, int y = 0) 
	 : Image(x, y) 
	 {};
	~Texture();

	Vec3f GetTexel(float u, float v);
};

#endif










