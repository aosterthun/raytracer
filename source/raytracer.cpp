#include <thread>
#include <renderer.hpp>
#include <scene.hpp>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{	
	std::string const filename = "../scene.sdf";

	SDFLoader loader{};

	Scene scene = loader.loadScene(filename);
	
	Renderer app{scene};

	unsigned const width = std::get<0>(scene._camera.getResolution());
	unsigned const height = std::get<1>(scene._camera.getResolution());
	
	std::cout << scene;

	std::thread thr([&app]() { app.render(); });

	Window win(glm::ivec2( width ,height));

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