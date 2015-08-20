#include "camera.hpp"

//constructors
Camera::Camera() :
_position{0.0},
_direction{1.0,0.0,0.0},
_angle{40.0}
{}

Camera::Camera(glm::vec3 const& direction, float angle) :
_direction{direction},
_angle{angle}
{}

//destructors
Camera::~Camera()
{}

//get-methods

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
	return (width/2)/tan(_angle/2);
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