#include "light.hpp"


//constructors
Light::Light() :
_name{"untitledLight"},
_position{0.0},
_ld{Color{}},
_la{Color{}}
{}

Light::Light(std::string const& name, glm::vec3 const& position, Color const& la, Color const& ld) :
_name{name},
_position{position},
_la{la},
_ld{ld}
{}

//destructors
Light::~Light()
{}

//get-methods

std::string const& Light::name() const
{
	return _name;
}

glm::vec3 const& Light::position() const
{
	return _position;
}

void Light::position(glm::vec3 const& newPos)
{
	_position = newPos;
}

Color Light::ld() const
{
	return _ld;
}

Color Light::la() const
{
	return _la;
}

glm::vec3 const& Light::setPosition(glm::vec3 const& position)
{
	_position = position;
}


//outstream methods
std::ostream& Light::print(std::ostream& os) const
{
	os << "[Light]\n" <<
				"Name: " << _name << "\n" <<
 				"Position: " << glm::to_string(_position) << "\n" <<
 				"ld-value: " << _ld << "\n" <<
 				"la-value: " << _la << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os , Light const& l)
{
	return l.print(os);
}