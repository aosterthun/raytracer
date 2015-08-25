#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include "shape.hpp"
#include "ray.hpp"
#include "optionalhit.hpp"

#include <cmath>
#include <glm/vec3.hpp>

class Sphere : public Shape
{
	public:
		Sphere();
		Sphere(glm::vec3 const& center);
		Sphere(double radius);
		Sphere(glm::vec3 const& center, double radius);
		Sphere(glm::vec3 const& center, double radius, std::string const& name, Material const& material);
		OptionalHit intersect(Ray const& ray, float& distance) const override;
		std::ostream& print(std::ostream& os) const override;
		glm::vec3 center() const;
		glm::vec3 normal(Ray const& ray) const;
		double radius() const;
		~Sphere() override; 
	private:
		glm::vec3 _center;
		double _radius;
};
#endif