#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

#define GLM_FORCE_RADIANS

#include "sceneobject.hpp"

#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>

class Light : public SceneObject
{
public:

	//constructors
	Light();

	Light(std::string const& name, glm::vec3 const& position, double ld, double la);

	//destructors
	~Light();


	//get-methods
	
	std::string const& name() const;

	glm::vec3 const& position() const;

	double ld() const;

	double la() const;

	//non-member functions

	//outstream methods
	std::ostream& print(std::ostream&) const;

private:

	std::string _name;

	glm::vec3 _position;

	double _ld;

	double _la;

};

//operators
std::ostream& operator<<(std::ostream&, Light const&);

#endif // define BUW_LIGHT_HPP