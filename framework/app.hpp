#ifndef BUW_APP_HPP
#define BUW_APP_HPP

#include <fstream>
#include <iostream>

#include "renderer.hpp"
#include "shapecomposite.hpp"
#include "material.hpp"

class App
{
public:
	
	App();
	App(std::string const& sceneFilename);
	~App();

	void run();

	//NEEDS TO BE std::vector<Scene> createScenes();
	bool createScenes();
	void saveSDF(Scene const& scene, std::string const filename);

private:
	Renderer _renderEngine;
	SDFLoader _sdfLoader;
	std::vector<Scene> _scenes;

	void loadScenes(std::string const& sceneFilenameWithoutIndex, int minIndex, int maxIndex);

};

#endif