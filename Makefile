all: 
	g++ -c Render.cpp Triangle.cc Image.cc Sphere.cc Group.cc PhongShader.cc Scene.cc PerspectiveCamera.cc Texture.cc kmeans2.cc
	g++ -s Render.o Triangle.o Image.o Sphere.o Group.o PhongShader.o Scene.o kmeans2.o PerspectiveCamera.o Texture.o -o Render -O3 -mmacosx-version-min=11.5

	#./Render testflat.nff img_flat.ppm 5
	./Render shells.nff img_shell.ppm 5
	#./Render sombrero.nff img_sombrero.ppm 5
	#./Render testphong.nff img_phong.ppm 1
	#./Render testtex.nff img_tex.ppm 10
	#./Render testobj.nff img_obj.ppm 1
	#./Render teapot.nff img_teapot.ppm 5
clean:
	rm *.o