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

OptionalHit Box::intersect(Ray const& ray, float& distance) const
{
	double t1 = -(_min.x - ray.origin.x)*ray.direction.x;
    double t2 = -(_max.x - ray.origin.x)*ray.direction.x;
    double tnear = std::min(t1, t2);
    double tfar = std::max(t1, t2);

    t1 = -(_min.y - ray.origin.y)*ray.direction.y;
    t2 = -(_max.y - ray.origin.y)*ray.direction.y;
    tnear = std::max(tnear, std::min(t1, t2));
    tfar = std::min(tfar, std::max(t1, t2));

    t1 = -(_min.z - ray.origin.z)*ray.direction.z;
    t2 = -(_max.z - ray.origin.z)*ray.direction.z;
    tnear = std::max(tnear, std::min(t1, t2));
    tfar = std::min(tfar, std::max(t1, t2));

	if(tfar >= std::max(0.0, tnear))
	{
		OptionalHit intersection;
		intersection._hit = true;
		intersection._shape = std::make_shared<Box>(*this);
		intersection._t = sqrt(tnear*tnear*(ray.direction.x*ray.direction.x +ray.direction.y*ray.direction.y +ray.direction.z*ray.direction.z));
		intersection._intersect = glm::vec3{tnear*ray.direction.x, tnear*ray.direction.y, tnear*ray.direction.z};
		intersection._normal = normal(intersection._intersect);
		return intersection;
	}
	else
	{
		return OptionalHit{false,nullptr,INFINITY};
	}
}

glm::vec3 Box::normal(glm::vec3 const& intersect) const {

	glm::vec3 tmp_normal{ INFINITY, INFINITY, INFINITY };
	const double epsilon = 5.97e-5;

	if (abs(_min.x - intersect.x) < epsilon)
	{
		tmp_normal = glm::vec3{ -1.0, 0.0, 0.0 };
	}
	else if (abs(_min.y - intersect.y) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, -1.0, 0.0 };
	}
	else if (abs(_min.z - intersect.z) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 0.0, 1.0 };
	}
	else if (abs(_max.x - intersect.x) < epsilon)
	{
		tmp_normal = glm::vec3{ 1.0, 0.0, 0.0 };
	}
	else if (abs(_max.y - intersect.y) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 1.0, 0.0 };
	}
	else if (abs(_max.z - intersect.z) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 0.0, -1.0 };
	}

	return tmp_normal;
}

glm::vec3 Box::min() const
{
	return _min;
}

glm::vec3 Box::max() const
{
	return _max;
}