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
	Scene() :
	_camera{},
	_shapes{},
	_lights{}
	{}

	~Scene()
	{}

	Camera _camera;
	std::map<std::string,std::shared_ptr<Shape>> _shapes;
	std::map<std::string,Light> _lights;
	std::string _renderFilename;
	
	friend std::ostream& operator<<(std::ostream& os , Scene const& s)
	{
		for(auto shapePair : s._shapes)
		{
			os << shapePair.second << "\n";
		}
		for(auto light : s._lights)
		{
			os << light.second << "\n";
		}
		os << s._camera;
		os << "RenderFilename: " << s._renderFilename << "\n";
		
		return os;
	}
};

#endif	// BUW_SCENE_HPP