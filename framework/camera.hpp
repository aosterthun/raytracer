#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#define GLM_FORCE_RADIANS

#include "sceneobject.hpp"
#include "ray.hpp"

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
	Camera(glm::vec3 const& diection, float aperture);
	Camera(std::string const& name, float aperture);

	//destructors
	~Camera();

	//get-methods
	std::string const& name() const;
	glm::vec3 const& position() const;
	glm::vec3 const& direction() const;

	//non-member functions
	Ray getEyeRay(int x, int y, float &distance) const;
	float getDistance(int width) const;

	//outstream methods
	std::ostream& print(std::ostream&) const;
	
private:
	glm::vec3 _position;
	glm::vec3 _direction;
	std::string _name;
	float _aperture;
};

//operators
std::ostream& operator<<(std::ostream&, Camera const&);

#endif // define BUW_CAMERA_HPP