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

App::App()
{}

App::~App()
{}

App::App(std::string const& sceneFilename)
{
	_scenes.push_back(_sdfLoader.loadScene(sceneFilename));
}

void App::run()
{
	std::cout << "App started";
	for(auto scene : _scenes)
	{
		std::cout << scene;
		unsigned const width = std::get<0>(scene._camera.getResolution());
		unsigned const height = std::get<1>(scene._camera.getResolution());
		_renderEngine.setScene(scene);

		//bool as return value for render()
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

bool App::createScenes()
{
	//might be a input parameter
	Scene scene = _sdfLoader.loadScene("../default_scene.sdf");

	int frames = 24;
	int seconds = 5;

	std::vector<Scene> scenes{(int)frames*seconds};

	//Variables to be modified
	float x = -100, y = 5, z = 10;

	//Modificators

	float xMod = 100;

	glm::vec3 pos{ x, y, z};

	saveSDF(scene, "test.sdf");
	/*
	for(int i = 0; i < (frames*seconds); ++i)
	{	
		Scene tmpScene = scene;
		tmpScene._lights.begin()->second.setPosition(pos);
		
		//extra just for testing
		_scenes.push_back(tmpScene);

		scenes[i] = tmpScene;


		x += xMod;

		//sceneToSDF("scene" + string(i+1) + ".sdf");
	}
	*/
	return true;
}

void App::loadScenes(std::string const& sceneFilenameWithoutIndex, int minIndex, int maxIndex)
{
	for (int i = minIndex; i <= maxIndex; ++i)
	{
		std::ostringstream os;
		os << sceneFilenameWithoutIndex << i << ".sdf";
		std::string sceneFilenameWithIndex = os.str();
		_scenes.push_back(_sdfLoader.loadScene(sceneFilenameWithIndex));
	}
}

void App::saveSDF(Scene const& scene, std::string const filename)
{
	std::map<std::string,Material> materials = _sdfLoader.materials();
	std::fstream file{filename.c_str(), std::ios::out};
	file.clear();

	//materials
	for(auto material : materials)
	{
		file << "define material "  << material.second.m() << " "
									<< material.second.ka().r << " "
									<< material.second.ka().g << " "
									<< material.second.ka().b << " "
									<< material.second.kd().r << " "
									<< material.second.kd().g << " "
									<< material.second.kd().b << " "
									<< material.second.ks().r << " "
									<< material.second.ks().g << " "
									<< material.second.ks().b << " "
									<< material.second.l() << "\n";
	}
	/*
	//shapes
	for(ShapeComposite composites : scene._shapes)
	{
		if(composites.second->className() == "composites")
		{
			std::map<std::string, std::shared_ptr<Shape>> childs = composites.second->getChilds();
			
			for(std::map<std::string, std::shared_ptr<Shape>>::iterator i = childs.begin(); i != childs.end(); ++i)
			{

				if(i->second.className() == "box")
				{
					file << "define shape"  << i->second.className() << " "
											<< i->second.name() << " ";
				}
				if(i->second.className() == "sphere")
				{
					file << "define shape"  << i->second.className() << " "
											<< i->second.name() << " "
											<< i->second.position();
				}	
			}
		}
	}
	
	//composites
	for(auto composites : scene._shapes)
	{
		if
		file << "define composite " << composites.second->className() << " "
									<< composites.second->name() << " ";
	}
	*/
	file.close();
}