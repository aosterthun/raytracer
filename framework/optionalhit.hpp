#ifndef BUW_OPTIONALHIT_HPP
#define BUW_OPTIONALHIT_HPP

#include <iostream>
#include <memory>

#include "shape.hpp"

class Shape;

struct OptionalHit
{
	//default-constructor
	OptionalHit() :
	_hit{},
	_shape{},
	_depth{0},
	_t{0.0}
	{}
	
	OptionalHit(bool hit, std::shared_ptr<Shape> shape, double t) :
	_hit{hit},
	_depth{0},
	_shape{shape},
	_t{t}
	{}

	OptionalHit(bool hit, std::shared_ptr<Shape> shape, double t, glm::vec3 const& intersect, Ray const& ray, glm::vec3 const& normal) :
	_hit{hit},
	_depth{0},
	_shape{shape},
	_t{t},
	_intersect{intersect},
	_ray{ray},
	_normal{normal}
	{}

	//variables

	//wether the object was hit or not
	bool _hit;
	//recursion depth
	int _depth;
	//the object that was hit
	std::shared_ptr<Shape> _shape;
	//distance between _ray.origin and _intersect
	double _t;

	//intersecting point
	glm::vec3 _intersect;

	//intersecting ray
	Ray _ray;

	glm::vec3 _normal;
};

#endif //#define BUW_OPTIONALHIT_HPP