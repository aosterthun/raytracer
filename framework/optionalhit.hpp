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
	_t{0.0}
	{}
	
	OptionalHit(bool hit, std::shared_ptr<Shape> shape, double t) :
	_hit{hit},
	_shape{shape},
	_t{t}
	{}

	OptionalHit(bool hit, std::shared_ptr<Shape> shape, double t, glm::vec3 const& intersect, glm::vec3 const& normal) :
	_hit{hit},
	_shape{shape},
	_t{t},
	_intersect{intersect},
	_normal{normal}
	{}

	//variables
	bool _hit;
	int _depth;
	std::shared_ptr<Shape> _shape;
	double _t;
	glm::vec3 _intersect;
	glm::vec3 _normal;
};

#endif //#define BUW_OPTIONALHIT_HPP