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
	//std::cout << "App started" << std::endl;
	for(auto scene : _scenes)
	{
		
		unsigned const width = std::get<0>(scene._camera.getResolution());
		unsigned const height = std::get<1>(scene._camera.getResolution());
		_renderEngine.setScene(scene);
		_renderEngine.render();
		//std::cout << "after Render" << std::endl;
		//bool as return value for render()
		std::thread thr([this]() { _renderEngine.render(); });
		
		/*Window win(glm::ivec2( width ,height));

		while (!win.shouldClose())
		{
			if (win.isKeyPressed(GLFW_KEY_ESCAPE))
			{
				win.stop();
			}

			glDrawPixels( width, height, GL_RGB, GL_FLOAT, _renderEngine.colorbuffer().data());
			
			win.update();
		}*/
		thr.join();
	}
}

bool App::createScenes(std::string const& sceneFilenameWithoutIndex)
{
	//might be a input parameter
	Scene scene = _sdfLoader.loadScene("../default_scene.sdf");

	int frames = 24;
	int seconds = 5;

	std::vector<Scene> scenes(static_cast<int>(frames*seconds));

	for (int i = 0; i < (seconds*frames); ++i)
	{
		std::ostringstream osPPM,osSDF;
		
		osSDF << sceneFilenameWithoutIndex << i << ".sdf";
		std::string sceneFilenameWithIndex = osSDF.str();
		
		osPPM << sceneFilenameWithoutIndex << i << ".ppm";
		std::string renderFilenameWithIndex = osPPM.str();

		auto sphereToMoveIt = scene._shapes.find("sphere1");
		Sphere* sphereToMove = dynamic_cast<Sphere*>(sphereToMoveIt->second.get());
		auto curSphereToMovePos = sphereToMove->center();
		sphereToMove->center({curSphereToMovePos.x + 0.16,curSphereToMovePos.y,curSphereToMovePos.z});


		auto lightToMove = scene._lights.find("sun2");
		auto curLightToMovePos = lightToMove->second.position();
		lightToMove->second.position({curLightToMovePos.x + 1,curLightToMovePos.y,curLightToMovePos.z});
		
		scene._renderFilename = renderFilenameWithIndex;
		saveSDF(scene, sceneFilenameWithIndex);	
	}
	
	
	return true;
}

void App::loadScenes(std::string const& sceneFilenameWithoutIndex, int minIndex, int maxIndex)
{
	for (int i = minIndex; i <= maxIndex; ++i)
	{
		std::ostringstream os;
		os << sceneFilenameWithoutIndex << i << ".sdf";
		std::string sceneFilenameWithIndex = os.str();
		//std::cout << sceneFilenameWithIndex << std::endl;
		_scenes.push_back(_sdfLoader.loadScene(sceneFilenameWithIndex));
		//std::cout << "After scene load<" << std::endl;
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
		file << "define material "  << material.second.name() << " "
									<< material.second.ka().r << " "
									<< material.second.ka().g << " "
									<< material.second.ka().b << " "
									<< material.second.kd().r << " "
									<< material.second.kd().g << " "
									<< material.second.kd().b << " "
									<< material.second.ks().r << " "
									<< material.second.ks().g << " "
									<< material.second.ks().b << " "
									<< material.second.m() << " "
									<< material.second.r() << " "
									<< material.second.l() << "\n";
	}
	
	//shapes
	for(auto shape : scene._shapes)
	{
		/*if(shape.second->className() == "composite")
		{
			ShapeComposite* comp = dynamic_cast<ShapeComposite*>(shape.second.get());
			for(auto compShape : comp->getChilds())
			{
*/
				if(shape.second->className() == "box")
				{
					Box* box = dynamic_cast<Box*>(shape.second.get());
					file << "define shape "  << box->className() << " "
											<< box->name() << " "
											<< box->min().x << " "
											<< box->min().y << " "
											<< box->min().z << " "
											<< box->max().x << " "
											<< box->max().y << " "
											<< box->max().z << " "
											<< box->material().name() << "\n";
				}
				if(shape.second->className() == "sphere")
				{
					Sphere* sphere = dynamic_cast<Sphere*>(shape.second.get());
					file << "define shape "  << sphere->className() << " "
											<< sphere->name() << " "
											<< sphere->center().x << " "
											<< sphere->center().y << " "
											<< sphere->center().z << " "
											<< sphere->radius() << " "
											<< sphere->material().name() << "\n";
				}	
			/*}
		}*/
		
	}

	//composites
	for(auto shape : scene._shapes)
	{
		if(shape.second->className() == "composite")
		{
			ShapeComposite* comp = dynamic_cast<ShapeComposite*>(shape.second.get());
			file << "define shape "  << comp->className() << " " << comp->name() << " ";
			for(auto compShape : comp->getChilds())
			{
				file << compShape.second->name() << " ";
			}
			file << "\n";
		}
	}

	//lights
	for(auto light : scene._lights)
	{
		file << "define light " << light.second.name() << " "
								<< light.second.position().x << " "
								<< light.second.position().y << " "
								<< light.second.position().z << " "
								<< light.second.la().r << " "
								<< light.second.la().g << " "
								<< light.second.la().b << " "
								<< light.second.ld().r << " "
								<< light.second.ld().g << " "
								<< light.second.ld().b << "\n"; 
	}

	//cam
	file << "camera " << scene._camera.name() << " " << scene._camera.aperture() << "\n";

	//render
	file << "render " << scene._camera.name() << " " << scene._renderFilename << " " << std::get<0>(scene._camera.getResolution()) << " " << std::get<1>(scene._camera.getResolution());
	

	file.close();
}