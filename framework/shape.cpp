#include "shape.hpp"

Shape::Shape(): 
_name{"untitled_shape"}, 
_material{Material{}} 
{}

Shape::Shape(std::string const& name, Material const& material): 
_name{name}, 
_material{material} 
{}

std::ostream& Shape::print(std::ostream& os) const
{
	os << "[Shape ID: " << this << "]\n" <<
				"Name: " << _name << "\n" <<
 				"Material: " << _material;
	return os;
}

Material Shape::material() const
{
	return _material;
}

std::string Shape::name() const
{
	return _name;
}

Shape::~Shape()
{
	//std::cout << "Shape destruct \n";
}

std::ostream& operator<<(std::ostream& os , std::shared_ptr<Shape> const& s)
{
	return s->print(os);
}

std::ostream& operator<<(std::ostream& os , Shape const& s)
{
	return s.print(os);
}