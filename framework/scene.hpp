#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <vector>
#include <tuple>
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <memory>

struct Scene
{
	Scene();
	~Scene();

	float _ambientLight;
	std::vector<std::shared_ptr<Shape>> _shapes;
	std::vector<Light> _lights;
	std::tuple<int,int> _resolution;

};

#endif	// BUW_SCENE_HPP