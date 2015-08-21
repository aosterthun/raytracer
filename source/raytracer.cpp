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
	std::string const filename = "/home/manuel/Medieninformatik/Programmiersprachen/Aufgaben/Aufgabenblatt8/raytracer/scene.sdf";

	SDFloader loader{};

	Scene scene = loader.loadScene(filename);

	Renderer app{scene};

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