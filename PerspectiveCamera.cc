#include "PerspectiveCamera.hh"


int PerspectiveCamera::InitRay(float x, float y, vector<Ray>& rays,int num_rays)
{
        for(int i=0;i<num_rays;i++){
			Ray mRay;
	
			mRay.org = pos;
			mRay.dir = ( 2.0f * (((x+0.08*i) / static_cast<float>(resX) - 0.5f) * aspect) * xAxis)
		+ ( 2.0f * ( (y+0.08*i) / static_cast<float>(resY) - 0.5f)           * yAxis)
		+ (focus * zAxis);
			
			/* ortogonal

			ray.dir= dir; 
  ray.org = dir_X*2.0f * ((x/(float)resX - .5f)*aspect)+dir_Y*2.0f * (y/(float)resY - .5f);
			*/
			
			mRay.t = Infinity; 
			mRay.hit = NULL;
			mRay.contribution = 1.0f;
			mRay.xCoord = (int)x;
			mRay.yCoord = (int)y;
	
			Normalize(mRay.dir);
			rays.push_back(mRay);
		}
        return num_rays;
}

