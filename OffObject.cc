#include "OffObject.hh"

int main(int argc, char *argv[]){
	/*if(argc < 2)
	{
		printf("obj <inputfile.off>\n");
		return 0;
	}*/

	OffObject mesh;

	mesh.loadObject("./hair/drake.obj",0);

	for (int j=0;j<mesh.getNumberTriangles();++j)
	{
		int v0 = mesh.getTriangleObject(j).getIndex(0);
		int v1 = mesh.getTriangleObject(j).getIndex(1);
		int v2 = mesh.getTriangleObject(j).getIndex(2);
	
		Vec3f vx = mesh.getVertex( v0 );
		Vec3f vy = mesh.getVertex( v1 );
		Vec3f vz = mesh.getVertex( v2 );
	}

}
