#include <thread>
#include <renderer.hpp>
#include <scene.hpp>
#include <fensterchen.hpp>
#include <app.hpp>
int main(int argc, char* argv[])
{	
	App raytracer{"../scene",1,2};
	raytracer.run();
	return 0;
}