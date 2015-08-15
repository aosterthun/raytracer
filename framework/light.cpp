#include "light.hpp"


//constructors
Light::Light() :
_name{"untitledLight"},
_position{0.0},
_ld{0.0},
_la{0.0}
{}

Light::Light(std::string const& name, glm::vec3 const& position, double ld, double la) :
_name{name},
_position{position},
_ld{ld},
_la{la}
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

double Light::ld() const
{
	return _ld;
}

double Light::la() const
{
	return _la;
}

//outstream methods
std::ostream& Light::print(std::ostream& os) const
{
	os << "[Shape ID: " << this << "]\n" <<
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