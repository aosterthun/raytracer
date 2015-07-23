#include "box.hpp"

Box::Box():
Shape::Shape("untitled_box", Color{0.0}),
_min{glm::vec3{0}},
_max{glm::vec3{0}}
{
	std::cout << "Box construct \n";
}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape::Shape("untitled_box", Color{0.0}),
_min{min},
_max{max}
{
	std::cout << "Box construct \n";
}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Color const& color):
Shape::Shape(name, color),
_min{min},
_max{max}
{
	std::cout << "Box construct \n";
}

std::ostream& Box::print(std::ostream& os) const
{
	os << "[Box ID: " << std::addressof(this) << "]\n" <<
				"Name: " << _name << "\n" <<
 				"Color: " << _color <<
 				"Min: " << glm::to_string(_min) << "\n" <<
 				"Max: " << glm::to_string(_max) << "\n\n"; 
	return os;
}

bool Box::intersect(Ray const& ray, float& distance) const
{
	throw std::runtime_error("not implemented");
}

glm::vec3 Box::min() const
{
	return _min;
}

glm::vec3 Box::max() const
{
	return _max;
}

double Box::area() const
{
	glm::vec3 v = _max - _min;
	return 2 * (v.x * v.y) + 2 * (v.x * v.z) + 2 * (v.z * v.y);
}

double Box::volume() const
{
	glm::vec3 v = _max - _min;
	return v.x * v.y * v.z;
}

Box::~Box()
{
	std::cout << "Box destruct \n";
}