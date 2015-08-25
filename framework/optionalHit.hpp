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
	_t{}
	{}
	
	OptionalHit(bool hit, std::shared_ptr<Shape> shape, double t) :
	_hit{hit},
	_shape{shape},
	_t{t}
	{}

	//variables
	bool _hit;
	std::shared_ptr<Shape> _shape;
	double _t;
	Ray _r;
};

#endif //#define BUW_OPTIONALHIT_HPP