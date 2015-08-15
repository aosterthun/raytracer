#include "sphere.hpp"

Sphere::Sphere():
Shape::Shape("untitled_sphere", Color{0.0}),
_center{glm::vec3{0}},
_radius{0}
{
	std::cout << "Sphere construct \n";
}

Sphere::Sphere(glm::vec3 const& center):
Shape::Shape("untitled_sphere", Color{0.0}),
_center{center},
_radius{0}
{
	std::cout << "Sphere construct \n";
}

Sphere::Sphere(double radius):
Shape::Shape("untitled_sphere", Color{0.0}),
_center{glm::vec3{0}},
_radius{radius}
{
	std::cout << "Sphere construct \n";
}

Sphere::Sphere(glm::vec3 const& center, double radius):
Shape::Shape("untitled_sphere", Color{0}),
_center{center},
_radius{radius}
{
	std::cout << "Sphere construct \n";
}

Sphere::Sphere(glm::vec3 const& center, double radius, std::string const& name, Color const& color):
Shape::Shape(name, color),
_center{center},
_radius{radius}
{
	std::cout << "Sphere construct \n";
}

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
 				"Color: " << _color <<
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

double Sphere::area() const
{
	return 4 * M_PI * _radius * _radius;
}

double Sphere::volume() const
{
	return 4.0/3.0 * M_PI * _radius * _radius * _radius;
}

Sphere::~Sphere()
{
	std::cout << "Sphere destruct \n";
}
