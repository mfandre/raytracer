#include "Texture.hh"
#include <math.h>
using namespace std;

Vec3f Texture::GetTexel(float u, float v)
{
/*	float	u_, v_;
	u_ = floor(u);
	v_ = floor(v);
	u_ = u - u_;
	v_ = v - v_;

	//cout << "[" << u << "," << v << "]" << endl;

	int x = (int)(u_ * resX);
	int y = (int)(v_ * resY);
*/
	int px = max(0, min(int(u*resX), resX - 1));
        int py = max(0, min(int(v*resY), resY - 1));
	
	/*
	int px = int(resX*u);
	int py = int(resY*v);

	//esse funciona
	px = int(resX + px % resX) % resX;
        py = int(resY + py % resY) % resY;
		
	*/
	return GetValuePixel(px, py);
}
/*
Vec3f Texture::GetTexel(float u, float v) {
	u -= (int)u;
	if (u < 0) u += 1;
	v -= (int)v;
	if (v < 0) v += 1;

	return GetValuePixel((int)(u*resX), resY-1-(int)(v*resY));
	//return (*this)[resY-1-(int)(v*resY)][(int)(u*resX)];
    }


/*Vec3f Texture::GetTexel(float u, float v) {
	
	// compute texel coordinates
         // we add 0.5, since the texel is sampled in the middle of the pixel (see OpenGL linear interpolation)
         float px = resX * u + 0.5;
         float py = resY * v + 0.5;
 
	
	 return GetValuePixel(px,py);
         // return new value
         //return result;
}*/

