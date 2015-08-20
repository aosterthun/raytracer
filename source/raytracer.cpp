#include <thread>
#include <renderer.hpp>
#include <scene.hpp>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
	/*
	SDFloader loader{};

	loader.readSdf(filename_);

	//retrieving the scene from the loader
	Scene scene = loader.scene();

	Renderer app{scene.widht(), scene.height()};
	*/

	unsigned const width = 600;
	unsigned const height = 600;
	std::string const filename = "./checkerboard.ppm";

	Scene scene{};

	scene._resolution = std::make_tuple(width, height);

	Renderer app{};

	//std::thread thr([&app]() { app.render(); });

	std::thread thr([&app]() { app.render(); });

	Window win(glm::ivec2(width,height));

	while (!win.shouldClose())
	{
		if (win.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			win.stop();
		}

		glDrawPixels( width, height, GL_RGB, GL_FLOAT, app.colorbuffer().data());

		win.update();
	}

	thr.join();

	return 0;
}