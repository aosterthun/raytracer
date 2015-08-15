#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

#define GLM_FORCE_RADIANS

#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:

	//constructors
	Camera();

	Camera(glm::vec3 const& position, glm::vec3 const& diection);

	//destructors
	~Camera();


	//get-methods

	glm::vec3 const& position() const;

	glm::vec3 const& direction() const;

	//non-member functions

	//marix-operations
	void scale();

	void translate();

	void rotate();

	//outstream methods
	std::ostream& print(std::ostream&);
	
private:

	glm::vec3 _position;
	
	glm::vec3 _direction;
};

//operators
std::ostream& operator<<(std::ostream&, Camera const&);

#endif // define BUW_CAMERA_HPP