#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <memory>
#include <map>
#include <vector>
#include <tuple>
#include "camera.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"


struct Scene
{
	Scene()
	{}
	~Scene()
	{}

	float _ambientLight;
	Camera _camera;
	std::map<std::string,std::shared_ptr<Shape>> _shapes;
	std::map<std::string,Light> _lights;
	std::tuple<int,int> _resolution;
	std::string _renderFilename;

};

#endif	// BUW_SCENE_HPP