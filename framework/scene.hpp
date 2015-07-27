#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <material.hpp>
#include <memory>

struct Scene
{
	Scene();
	~Scene();

	std::map<std::string, Material> materials;
};

#endif	// BUW_SCENE_HPP