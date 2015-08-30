#include "app.hpp"
#include <thread>
#include <fensterchen.hpp>

template <typename T>
std::string NumberToString ( T Number )
{
std::ostringstream ss;
ss << Number;
return ss.str();
}

App::App(std::string const& sceneFilename)
{
	_scenes.push_back(_sdfLoader.loadScene(sceneFilename));
}

App::App(std::string const& sceneFilenameWithoutIndex, int minIndex, int maxIndex)
{
	for (int i = minIndex; i <= maxIndex; ++i)
	{
		std::ostringstream os;
		os << sceneFilenameWithoutIndex << i << ".sdf"; 
		std::string sceneFilenameWithIndex = os.str();
		_scenes.push_back(_sdfLoader.loadScene(sceneFilenameWithIndex));
	}
}

App::~App()
{}

void App::run()
{
	std::cout << "App started";
	for(auto scene : _scenes)
	{
		std::cout << scene;
		unsigned const width = std::get<0>(scene._camera.getResolution());
		unsigned const height = std::get<1>(scene._camera.getResolution());
		_renderEngine.setScene(scene);
		std::thread thr([this]() { _renderEngine.render(); });

		Window win(glm::ivec2( width ,height));

		while (!win.shouldClose())
		{
			if (win.isKeyPressed(GLFW_KEY_ESCAPE))
			{
				win.stop();
			}

			glDrawPixels( width, height, GL_RGB, GL_FLOAT, _renderEngine.colorbuffer().data());
			
			win.update();
		}
		thr.join();
	}

}

