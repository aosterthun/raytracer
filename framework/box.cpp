#include "box.hpp"

Box::Box():
Shape::Shape("untitled_box", Material{}),
_min{glm::vec3{0}},
_max{glm::vec3{0}}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape::Shape("untitled_box", Material{}),
_min{min},
_max{max}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& material):
Shape::Shape(name, material),
_min{min},
_max{max}
{}

Box::~Box()
{
	//std::cout << "Box destruct \n";
}

std::ostream& Box::print(std::ostream& os) const
{
	os << "[Box]\n" <<
				"Name: " << _name << "\n" <<
 				"Material: " << _material <<
 				"Min: " << glm::to_string(_min) << "\n" <<
 				"Max: " << glm::to_string(_max) << "\n\n"; 
	return os;
}

OptionalHit Box::intersect(Ray const& r, float& distance) const
{
	double tx1 = (_min.x - r.origin.x)/glm::normalize(r.direction).x;
	double tx2 = (_max.x - r.origin.x)/glm::normalize(r.direction).x;

	double tnear = std::min(tx1, tx2);
	double tfar = std::max(tx1, tx2);

	double ty1 = (_min.y - r.origin.y)/glm::normalize(r.direction).y;
	double ty2 = (_max.y - r.origin.y)/glm::normalize(r.direction).y;

	tnear = std::max(tnear, std::min(ty1, ty2));
	tfar = std::min(tfar, std::max(ty1, ty2));

	double tz1 = (_min.z - r.origin.z)/glm::normalize(r.direction).z;
	double tz2 = (_max.z - r.origin.z)/glm::normalize(r.direction).z;

	tnear = std::max(tnear, std::min(tz1, tz2));
	tfar = std::min(tfar, std::max(tz1, tz2));

	if(tfar >= std::max(0.0, tnear))
	{
		return OptionalHit{true,std::make_shared<Box>(*this),sqrt(tnear*tnear*(r.direction.x*r.direction.x +r.direction.y*r.direction.y +r.direction.z*r.direction.z))};
	}
	else
	{
		return OptionalHit{false,nullptr,INFINITY};
	}
}

glm::vec3 Box::min() const
{
	return _min;
}

glm::vec3 Box::max() const
{
	return _max;
}