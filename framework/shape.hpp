#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP
#define GLM_FORCE_RADIANS
#include "material.hpp"
#include <string>
#include <ray.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <stdexcept>
#include <memory>
#include "sceneobject.hpp"
#include "optionalhit.hpp"

class Shape : public SceneObject
{
	public: 
		Shape();
		Shape(std::string const& name, Material const& material);
		virtual OptionalHit intersect(Ray const& ray, float& distance) const = 0;
		virtual std::ostream& print(std::ostream& os) const;
		Material material() const;
		std::string name() const;
		virtual ~Shape();

	protected:
		std::string _name;
		Material _material;
};

std::ostream& operator<<(std::ostream& os , std::shared_ptr<Shape> const& s);
std::ostream& operator<<(std::ostream& os ,Shape const& s);

#endif