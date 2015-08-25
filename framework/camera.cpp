#include "camera.hpp"

//constructors
Camera::Camera() :
_position{0.0},
_direction{0.0,0.0,-1.0},
_aperture{40.0}
{}

Camera::Camera(glm::vec3 const& direction, float aperture) :
_direction{direction},
_aperture{aperture}
{}

Camera::Camera(std::string const& name, float aperture) :
_name{name},
_direction{0.0,0.0,-1.0},
_aperture{aperture}
{}

//destructors
Camera::~Camera()
{}

//get-methods

std::string const& Camera::name() const
{
	return _name;
}

glm::vec3 const& Camera::position() const
{
	return _position;
}

glm::vec3 const& Camera::direction() const
{
	return _direction;
}

//non-member functions

Ray Camera::getEyeRay(int x, int y, float &distance) const
{
	return Ray{glm::vec3{_position}, glm::vec3{x, y, distance}};
}

float Camera::getDistance(int width) const
{
	return (width/2)/tan(_aperture/2);
}

std::ostream& Camera::print(std::ostream& os) const
{
	os << "[Camera] " <<
 				"position: " << glm::to_string(_position) << "\n" <<
 				"direction: " << glm::to_string(_direction) << "\n"; 
	return os;
}

std::ostream& operator<<(std::ostream& os , Camera const& c)
{
	return c.print(os);
}