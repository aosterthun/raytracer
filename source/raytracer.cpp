#include <thread>
#include <renderer.hpp>
#include <scene.hpp>
#include <fensterchen.hpp>
#include <app.hpp>

int main(int argc, char* argv[])
{	
	App raytracer{"../scene1.sdf"};
	raytracer.run();

	//App raytracer{};

	//raytracer.createScenes();

	//raytracer.loadScenes

	//raytracer.run();

	return 0;
}