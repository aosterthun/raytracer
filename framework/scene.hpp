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
		os << "AmbientLight: " << s._ambientLight << "\n"; 
		os << "RenderFilename: " << s._renderFilename << "\n";
		os << "Resolution: X:" << std::get<0>(s._resolution) << "Y:" << std::get<0>(s._resolution) << "\n";
		
		return os;
	}
};

#endif	// BUW_SCENE_HPP