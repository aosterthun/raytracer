#include "camera.hpp"

//constructors
Camera::Camera() :
_position{0.0},
_direction{0.0,0.0,-1.0},
_aperture{40.0}
{
	std::get<0>(_resolution) = 600;
	std::get<1>(_resolution) = 400;
}

Camera::Camera(glm::vec3 const& direction, float aperture) :
_position{0.0},
_direction{direction},
_aperture{aperture}
{
	std::get<0>(_resolution) = 600;
	std::get<1>(_resolution) = 400;
}

Camera::Camera(std::string const& name, float aperture) :
_position{0.0},
_name{name},
_direction{0.0,0.0,-1.0},
_aperture{aperture}
{
	std::get<0>(_resolution) = 600;
	std::get<1>(_resolution) = 400;
}

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

float const& Camera::aperture() const
{
	return _aperture;
}


//non-member functions
void Camera::setResolution(int width, int height)
{
	std::get<0>(_resolution) = width;
	std::get<1>(_resolution) = height;
}

void Camera::setPosition(glm::vec3 const& position)
{
	_position = position;
}


std::tuple<int,int> Camera::getResolution() const
{
	return _resolution;
}

Ray Camera::getCameraRay(int x, int y, float &distance) const
{
	int width = x - (std::get<0>(_resolution)/2);
	int height = y - (std::get<1>(_resolution)/2);
	return Ray{glm::vec3{_position}, glm::vec3{ width, height, distance}};
}

float Camera::getDistance(int width) const
{
	return -(width/2)/std::tan(((0.5*_aperture * M_PI)/180));
}

std::ostream& Camera::print(std::ostream& os) const
{
	os << "[Camera] " <<
				"name: " << _name << "\n" <<
				"aperture: " << _aperture << "\n" <<
 				"position: " << glm::to_string(_position) << "\n" <<
 				"direction: " << glm::to_string(_direction) << "\n" <<
 				"Resolution: X:" << std::get<0>(_resolution) << "Y:" << std::get<1>(_resolution) << "\n";

	return os;
}

std::ostream& operator<<(std::ostream& os , Camera const& c)
{
	return c.print(os);
}