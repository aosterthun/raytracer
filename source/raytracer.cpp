#include <thread>
#include <renderer.hpp>
#include <scene.hpp>
#include <fensterchen.hpp>
#include <app.hpp>

int main(int argc, char* argv[])
{	
	App raytracer{"../default_scene.sdf"};
	//raytracer.run();

	//App raytracer{};

	//raytracer.createScenes("image");

	//raytracer.loadScenes("image",0,119);

	raytracer.run();

	return 0;
}