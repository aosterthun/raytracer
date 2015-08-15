#include "camera.hpp"

//constructors
Camera::Camera() :
_position{0.0},
_direction{1.0,0.0,0.0}
{}

Camera::Camera(glm::vec3 const& position, glm::vec3 const& direction) :
_position{position},
_direction{direction}
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

void Camera::scale()
{
	throw std::runtime_error("not implemented");
}

void Camera::translate()
{
	throw std::runtime_error("not implemented");
}

void Camera::rotate()
{
	throw std::runtime_error("not implemented");
}

std::ostream& Camera::print(std::ostream& os)
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