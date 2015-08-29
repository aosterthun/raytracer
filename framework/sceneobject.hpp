#ifndef BUW_SCENEOBJECT_HPP
#define BUW_SCENEOBJECT_HPP
#define GLM_FORCE_RADIANS
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <iosfwd>

bool operator==(glm::mat4 const& a,glm::mat4 const& b);
class SceneObject
{
	public:
		SceneObject();
		SceneObject(glm::mat4 const& transfomrMatrix);
		void rotate(float angle, glm::vec3 const& axis);
		void scale(glm::vec3 const& scaleVector);
		void translate(glm::vec3 const& translateVector);
		glm::mat4 inverseTransformMatrix() const;
		glm::mat4 transformMatrix() const;

	protected:
		glm::mat4 _transformMatrix;
};

#endif