#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(): 
	origin{glm::vec3{0}},
	direction{glm::vec3{0}}
	{}

	Ray(glm::vec3 nOrigin, glm::vec3 nDirection): 
	origin{nOrigin}, 
	direction{nDirection}
	{}

	friend std::ostream& operator<<(std::ostream& os , Ray const& r)
	{
		os << "Origin: " << glm::to_string(r.origin) << "\n"
		   << "Direction: " << glm::to_string(r.direction) << "\n";
		return os;
	}
};

#endif