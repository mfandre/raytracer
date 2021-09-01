#include "Scene.hh"
#include "PerspectiveCamera.hh"
#include "OrthogonalCamera.hh"
#include "Sphere.hh"
#include "Triangle.hh"
#include "Group.hh"
#include "PhongShader.hh"
#include "FlatShader.hh"
#include "EyeLightTextureShader.hh"
#include "EyeLightShader.hh"
//#include "MirrorShader.hxx"
#include "PointLight.hxx"
#include "OffObject.hh"
#define LINESIZE 1000

#define NORM(x)   if((x) > 1) x = 1; else if((x) < 0) x = 0;

bool Scene::Intersect(Ray &ray){
	Group *g;
	vector<Group *>::iterator iter = grupos_primitivas.begin();
	for(int i=0;i < grupos_primitivas.size();i++,iter++){
		g = (Group*)*iter;
		if(g->Intersect(ray)){
			//cout << i << endl;
			//return true;
		}
	}
	if(ray.hit)
    		return true;
  	else
    		return false;
}

Vec3f Scene::RayTrace(Ray& ray)
{
	Vec3f result = bgColor;
	if(ray.maxBounce < 0)
		return result;	
	
	if (Intersect(ray) && ray.maxBounce > 0)
	{
		if (ray.hit->shader)
		{
			result = ray.hit->shader->Shade(ray); // shade  primitive

			/********Reflexao**********/	
			Vec3f normal = ray.hit->GetNormal(ray);
			float cos = Dot(normal,ray.dir);
						
			// compute reflection vector
			Vec3f reflect = ray.dir - 2*cos*normal;
			
			// change ray direction and position
			ray.org = ray.getHitPoint(-Epsilon);

			ray.dir = reflect;
			ray.t = Infinity;

			ray.hit = NULL;
			ray.u = ray.v = 0.0;
			ray.contribution = 1.0f/8.0f; 

			// trace the ray back into the scene 
			result = result + ray.contribution*RayTrace(ray);
			result.assertInterval(0,1);
		}
		else
			result = Vec3f(0,0,0);
		--(ray.maxBounce);
	}
	return result;
}

void Scene::ParseNFF(char *fileName)
{
  // parse file, add all items to 'primitives'
  ParseNFF(NULL,fileName,&primitives);
}

void Scene::ParseNFF(FILE *fileToUse, char *fileName, Group *groupToAddTo)
{
	FILE *file = fileToUse;

	if(!file) {
		file = fopen(fileName,"r");
		if(!file) {
			cerr << "could not open input file " << fileName << endl;
			exit(1);
		}
	}

	char line[LINESIZE+1];
	char token[LINESIZE+1];
	char *str;

	static Shader *currentShader = new EyeLightShader(Vec3f(1,1,1));
	// just to have a default ahder, in case the file doesn't define one !

	while((str = fgets(line,LINESIZE,file)) && !feof(file)) {

		if(str[0] == '#')	// '#' : comment
			continue;

		int numtokens = sscanf(line,"%s",token);
		if(numtokens <= 0)
			continue; // empty line, except for whitespaces

		if(!strcmp(token,"begin_hierarchy")) {
			line[strlen(line)-1] = 0; // remove trailing eol indicator '\n'
			Group *subGroup = new Group;
			groupToAddTo->Add(subGroup);
			ParseNFF(file,fileName,subGroup);
			continue;
		}

		if(!strcmp(token,"end_hierarchy"))
			return;

		if(!strcmp(token,"v")) {
			// FORMAT:
			//     v
			//     from %g %g %g
			//     at %g %g %g
			//     up %g %g %g
			//     angle %g
			//     hither %g
			//     resolution %d %d
			Vec3f pos, at, up;
			float angle, hither;
			int resX, resY;
			fscanf(file,"from %g %g %g\n",&pos.x,&pos.y,&pos.z);
			fscanf(file,"at %g %g %g\n",&at.x,&at.y,&at.z);
			fscanf(file,"up %g %g %g\n",&up.x,&up.y,&up.z);
			fscanf(file,"angle %g\n",&angle);
			fscanf(file,"hither %g\n",&hither);
			fscanf(file,"resolution %d %d\n",&resX,&resY);

			if (camera) delete camera;
			camera = new PerspectiveCamera(pos,at-pos,up,angle,resX,resY);

			continue;
		}

		if(!strcmp(token,"s")) {
			Vec3f pos;
			float rad;
			sscanf(str,"s %g %g %g %g",&pos.x,&pos.y,&pos.z,&rad);
			groupToAddTo->Add(new Sphere(pos,rad,currentShader));
			initAmostras(amostras,pos);
			continue;
		}

		if(!strcmp(token,"pp")) {
			int vertices;
			sscanf(str,"pp %d",&vertices);
			Vec3f *vertex = new Vec3f[vertices];
			Vec3f *normal = new Vec3f[vertices];

			/* IGNORE normals for now...  */
			for(int i=0;i<vertices;i++)
				fscanf(file,"%g %g %g %g %g %g\n",
					&vertex[i].x,&vertex[i].y,&vertex[i].z,
					&normal[i].x,&normal[i].y,&normal[i].z);

			assert(currentShader != NULL);
			for(int i=2 ;i<vertices; i++) {
				// ignore vertex normals for now, just add a plain triangle
				//groupToAddTo->Add(new SmoothTriangle(vertex[0], vertex[i-1], vertex[i],
				//		normal[0], normal[i-1], normal[i], currentShader));

				groupToAddTo->Add(new Triangule(vertex[0], vertex[i-1], vertex[i], currentShader));
			}
			delete[] vertex;
			delete[] normal;
			continue;
		}

		/*if(!strcmp(token, "tpp"))
		{
			int	vertices;
			sscanf(str, "tpp %d", &vertices);
			Vec3f	*vertex = new Vec3f[vertices];
			Vec3f	*normal = new Vec3f[vertices];
			Vec3f	*tex = new Vec3f[vertices];

			/* IGNORE normals for now...  
			for(int i = 0; i < vertices; i++)
				fscanf(file,"%g %g %g %g %g %g %g %g %g\n",
					&vertex[i].x, &vertex[i].y, &vertex[i].z,
					&normal[i].x, &normal[i].y, &normal[i].z,
					&tex[i].x, &tex[i].y, &tex[i].z);

			assert(currentShader != NULL);
			for(int i = 2; i < vertices; i++)
				groupToAddTo->Add(new TextureSmoothTriangle(vertex[0], vertex[i-1], vertex[i],
						normal[0], normal[i-1], normal[i], tex[0], tex[i-1], tex[i], currentShader));

			delete[] vertex;
			delete[] normal;
			delete[] tex;
			continue;
		}*/

		if(!strcmp(token,"b")) {
			sscanf(line,"b %g %g %g",&bgColor.x,&bgColor.y,&bgColor.z);
			continue;
		}

		if(!strcmp(token,"p")) {
			int vertices;
			sscanf(str,"p %d",&vertices);
			Vec3f *vertex = new Vec3f[vertices];
			for(int i=0; i<vertices; i++)
				fscanf(file,"%g %g %g\n",&vertex[i].x,&vertex[i].y,&vertex[i].z);
			assert(currentShader != NULL);
			for(int i=2; i<vertices; i++){
				groupToAddTo->Add(new Triangule(vertex[0], vertex[i-1], vertex[i], currentShader));
				Vec3f pos = vertex[0] + vertex[i-1] + vertex[i];
				pos = pos/3;
				initAmostras(amostras,pos);
			}
			delete[] vertex;
			continue;
		}

		if(!strcmp(token,"include")) {
			if (!fgets(line,LINESIZE,file)) {
				cerr << " error in include, cannot read filename to include" << endl;
				exit(0);
			}
			line[strlen(line)-1] = 0; // remove trailing eol indicator '\n'
			cout << "including file " << line << endl;

			Group *subGroup = new Group;
			groupToAddTo->Add(subGroup);
			ParseNFF(NULL,line,subGroup);
			continue;
		}

		if(!strcmp(token,"f")) {
			float r,g,b,kd,ks,shine,t,ior;

			sscanf(str,"f %g %g %g %g %g %g %g %g\n", &r,&g,&b,&kd,&ks,&shine,&t,&ior);
			Vec3f color(r,g,b);
			//currentShader = new PhongShader(color, 0.2, ks, kd, shine, this);
			currentShader = new FlatShader(color);
			//currentShader = new EyeLightShader(color);
			continue;
		}

		if(!strcmp(token,"fe")) {
			float r,g,b,kd,ks,shine,t,ior;

			sscanf(str,"f %g %g %g %g %g %g %g %g\n", &r,&g,&b,&kd,&ks,&shine,&t,&ior);
			Vec3f color(r,g,b);
			//currentShader = new PhongShader(color, 0.2, ks, kd, shine, this);
			//currentShader = new FlatShader(color);
			currentShader = new EyeLightShader(color);
			continue;
		}

		if(!strcmp(token,"fp")) {
			float r,g,b,kd,ks,shine,t,ior;

			sscanf(str,"fp %g %g %g %g %g %g %g %g\n", &r,&g,&b,&kd,&ks,&shine,&t,&ior);
			Vec3f color(r,g,b);
			//color = color * kd;
			currentShader = new PhongShader(color, 0.2, ks, kd, shine, this);
			//currentShader = new FlatShader(color);
			continue;
		}

		if(!strcmp(token,"shader"))
		{
			char	param[1000], material[1000];
			sscanf(str, "shader %s %s", param, material);
			currentShader = new EyeLightTextureShader(Vec3f(1,1,1), material);
			//((EyeLightTextureShader *)currentShader)->ParseParams(param, material);
			continue;
		}

		if(!strcmp(token,"obj"))
		{
			char	param[1000];
			sscanf(str, "obj %s", param);
			OffObject mesh;

			mesh.loadObject(param,0);
			cout << "================>" << mesh.getNumberTriangles() << endl;
			for (int j=0;j<mesh.getNumberTriangles();++j)
			{
				int v0 = mesh.getTriangleObject(j).getIndex(0);
				int v1 = mesh.getTriangleObject(j).getIndex(1);
				int v2 = mesh.getTriangleObject(j).getIndex(2);
			
				Vec3f vx = mesh.getVertex( v0 );
				Vec3f vy = mesh.getVertex( v1 );
				Vec3f vz = mesh.getVertex( v2 );
				groupToAddTo->Add(new Triangule(vx, vy, vz, currentShader));

				Vec3f pos = vx + vy + vz;
				pos = pos/3;
				initAmostras(amostras,pos);
			}
			continue;
		}

		if(!strcmp(token,"l")) {
			// light source
			Vec3f pos, col;
			int num = sscanf(line,"l %g %g %g %g %g %g", &pos.x,&pos.y,&pos.z,&col.x,&col.y,&col.z);
			if(num == 3) {
				// light source with position only
				col = Vec3f(1,1,1);
			}
			else
				if(num == 6) 
				{
				 // light source with position and color
				 lights.push_back( new PointLight(pos, col,(Scene*)this) );
//				 AddLight(new DirectionalLight(pos, col, this));	
				}
				else
					cout << "error in " << fileName << " : " << line << endl;
			continue;
		}


		cout << "error in " << fileName << " : " << line << endl;
		exit(0);
	}
	if(fileToUse)
		fclose(file);
}
