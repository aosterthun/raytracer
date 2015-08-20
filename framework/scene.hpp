#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <vector>
#include <tuple>
#include "camera.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <memory>

struct Scene
{
	Scene()
	{}
	~Scene()
	{}

	float _ambientLight;
	Camera _camera;
	std::map<std::string name,std::shared_ptr<Shape>> _shapes;
	std::map<std::string name,Light> _lights;
	std::tuple<int,int> _resolution;

};

#endif	// BUW_SCENE_HPP