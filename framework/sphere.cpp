#include "sphere.hpp"

Sphere::Sphere():
Shape::Shape("untitled_sphere", Material{}),
_center{glm::vec3{0}},
_radius{0}
{}

Sphere::Sphere(glm::vec3 const& center):
Shape::Shape("untitled_sphere", Material{}),
_center{center},
_radius{0}
{}

Sphere::Sphere(double radius):
Shape::Shape("untitled_sphere", Material{}),
_center{glm::vec3{0}},
_radius{radius}
{}

Sphere::Sphere(glm::vec3 const& center, double radius):
Shape::Shape("untitled_sphere", Material{}),
_center{center},
_radius{radius}
{}

Sphere::Sphere(glm::vec3 const& center, double radius, std::string const& name, Material const& material):
Shape::Shape(name, material),
_center{center},
_radius{radius}
{}

bool Sphere::intersect(Ray const& ray, float& distance) const
{
	return glm::intersectRaySphere(
					ray.origin,glm::normalize(ray.direction),
					_center,_radius,distance);
}

std::ostream& Sphere::print(std::ostream& os) const
{
	os << "[Sphere]\n" <<
				"Name: " << _name << "\n" <<
 				"Material: " << _material <<
 				"Center: " << glm::to_string(_center) << "\n" <<
 				"Radius: " << _radius << "\n\n";
	return os;
}

glm::vec3 Sphere::center() const
{
	return _center;
}

double Sphere::radius() const
{
	return _radius;
}

Sphere::~Sphere()
{
	std::cout << "Sphere destruct \n";
}
