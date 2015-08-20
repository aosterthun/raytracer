#ifndef BUW_OPTIONALHIT_HPP
#define BUW_OPTIONALHIT_HPP

#include <iostream>

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
};

#endif //#define BUW_OPTIONALHIT_HPP