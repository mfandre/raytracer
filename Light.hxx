#ifndef LIGHT_HXX
#define LIGHT_HXX

class Light
{
 public:
    // exercise 4.1
    virtual Vec3f Illuminate(Vec3f &dir, Vec3f org, int index=0) = 0;

};

#endif // LIGHT_HXX
