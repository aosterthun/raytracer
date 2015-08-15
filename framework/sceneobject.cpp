#include "sceneobject.hpp"

bool operator==(glm::mat4 const& a,glm::mat4 const& b)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			float epsilon = a[i][j] - b[i][j];
			if(epsilon < 0)
				epsilon *= -1;

			if (epsilon > 0.1)
			{
				return false;
			}
		}
	}
	return true;
}

SceneObject::SceneObject(){
	_transformMatrix = glm::mat4{0};
}
SceneObject::SceneObject(glm::mat4 const& transfomrMatrix){
	_transformMatrix = transfomrMatrix;
}
glm::mat4 SceneObject::rotate(float angle, glm::vec3 const& axis){ return glm::mat4{};}
glm::mat4 SceneObject::scale(glm::vec3 const& scaleVector){return glm::mat4{};}
glm::mat4 SceneObject::translate(glm::vec3 const& translateVector){return glm::mat4{};}
glm::mat4 SceneObject::inverseTransformMatrix() const{return glm::mat4{};}
glm::mat4 SceneObject::transformMatrix() const{return glm::mat4{};}

