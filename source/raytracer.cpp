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
	std::string const filename = "../scene.sdf";

	SDFLoader loader{};

	Scene scene = loader.loadScene(filename);
	
	//auto t1 = std::make_tuple( width, height);
	//scene._resolution = t1;

	
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

	std::cout << "X: " << std::get<0>(scene._resolution) << "Y: " << std::get<1>(scene._resolution);
		
		win.update();
	}

	thr.join();

	return 0;
}