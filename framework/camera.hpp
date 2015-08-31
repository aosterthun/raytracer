#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#define GLM_FORCE_RADIANS

#include "sceneobject.hpp"
#include "ray.hpp"

#include <tuple>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>

class Camera : public SceneObject
{
public:

	//constructors
	Camera();
	Camera(glm::vec3 const& direction, float aperture);
	Camera(std::string const& name, float aperture);

	//destructors
	~Camera();

	//get-methods
	std::string const& name() const;
	glm::vec3 const& position() const;
	glm::vec3 const& direction() const;

	//non-member functions
	Ray getCameraRay(int x, int y, float &distance) const;
	float getDistance(int width) const;
	void setResolution(int width, int height);
	void setPosition(glm::vec3 const& position);
	std::tuple<int,int> getResolution() const;

	//outstream methods
	std::ostream& print(std::ostream&) const;
	
private:
	glm::vec3 _position;
	glm::vec3 _direction;
	std::string _name;
	float _aperture;
	std::tuple<int,int> _resolution;
};

//operators
std::ostream& operator<<(std::ostream&, Camera const&);

#endif // define BUW_CAMERA_HPP