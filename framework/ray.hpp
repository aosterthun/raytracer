#ifndef BUW_RAY_HPP
#define BUW_RAY_HPP
#include <glm/glm.hpp>
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
};
#endif