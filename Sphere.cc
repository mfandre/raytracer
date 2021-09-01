#include "Sphere.hh"

bool Sphere::Intersect(Ray &ray){
	Vec3f diff = ray.org - center;
	float a = Dot(ray.dir,ray.dir);
	float b = 2*Dot(ray.dir,diff);
	float c = Dot(diff,diff) - radius*radius;

	float inRoot = b*b - 4*a*c;
	if(inRoot < 0)
		return false;
	float root = sqrt(inRoot);

	float dist = (-b-root)/(2*a);
	if(dist > ray.t)
		return false;
	
	if(dist < Epsilon){
		dist = (-b-root)/(2*a);
		if(dist < Epsilon || dist > ray.t)
			return false;
	}
	ray.hit = this;
	ray.t = dist;

	Vec3f hitP = ray.getHitPoint(0.0f) - center;
	float theta = 1.0f - (atan2f(hitP.y,hitP.x) + M_PI)*0.5f/M_PI;
	float phi = atan2f(sqrt(hitP.x*hitP.x + hitP.y*hitP.y),hitP.z)/M_PI;

	ray.u = theta;
	ray.v = phi;

	return true;
}

Vec3f Sphere::GetNormal(Ray &ray){
	Vec3f	intersect = ray.t * ray.dir + ray.org;
	Vec3f	normal = intersect - center;
	Normalize(normal);
	return normal;
	/*float theta = (1.0f - ray.u)*2*M_PI - M_PI;
	float phi   = ray.v*M_PI;
	
	Vec3f norm(sinf(phi)*cosf(theta), sinf(phi)*sinf(theta), cosf(phi));
	Normalize(norm);
	return norm;*/
/*
	Vec3f	intersect = (ray.t) * ray.dir + ray.org;
	Vec3f	normal = intersect - center;
	Normalize(normal);
	return normal;
*/
}
/*
bool Sphere::Intersect(Ray &ray)
{
	float coef_a, coef_b, coef_c;
	float delta, t;
	float dist_x, dist_y, dist_z;

	dist_x = ray.org.x - center.x;
	dist_y = ray.org.y - center.y;
	dist_z = ray.org.z - center.z;

	Normalize(ray.dir);

	coef_a = 1; //ray.dir.x*ray.dir.x + ray.dir.y*ray.dir.y + ray.dir.z*ray.dir.z = 1 (normalized)
	coef_b = 2 * (dist_x*ray.dir.x + dist_y*ray.dir.y + dist_z*ray.dir.z);
	coef_c = dist_x*dist_x + dist_y*dist_y + dist_z*dist_z - radius*radius;

	delta = coef_b*coef_b - 4*coef_a*coef_c;

	if (delta < 0)
		return false; // No intersection

	float delta_sqrt = sqrt(delta);

	float t1 = (-coef_b + delta_sqrt) / (2*coef_a);
	float t2 = (-coef_b - delta_sqrt) / (2*coef_a);

	if(t1>t2)
	{
		float temp;
		temp = t1;
		t1 = t2;
		t2 = temp;
	}

	if(t2 < 0)
		return false;

	if(t1 < 0)
		t = t2;
	else
		t = t1;

	ray.t = t;
	ray.hit = this;

	return true;
}

Vec3f Sphere::GetNormal(Ray &ray)
{
	Vec3f	intersect = ray.t * ray.dir + ray.org;
	Vec3f	normal = intersect - center;
	Normalize(normal);
	return normal;
}
*/

