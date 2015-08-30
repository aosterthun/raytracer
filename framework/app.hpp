#ifndef BUW_RAYTRACER_HPP
#define BUW_RAYTRACER_HPP

#include "renderer.hpp"

class App
{
public:
	App(std::string const& sceneFilename);
	App(std::string const& sceneFilename,int minIndex,int maxIndex);
	~App();

	void run();
private:
	Renderer _renderEngine;
	SDFLoader _sdfLoader;
	std::vector<Scene> _scenes;

};

#endif