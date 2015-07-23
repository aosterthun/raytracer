#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape
{
	public:
		Box();
		Box(glm::vec3 const& min, glm::vec3 const& max);
		Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Color const& color);
		double area() const override;
		double volume() const override;
		std::ostream& print(std::ostream& os) const override;
		bool intersect(Ray const& ray, float& distance) const override;
		glm::vec3 min() const;
		glm::vec3 max() const;
		~Box() override; 
	private:
		glm::vec3 _min;
		glm::vec3 _max;
};
#endif