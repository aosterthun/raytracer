#include "sceneobject.hpp"

bool operator==(glm::mat4 const& a,glm::mat4 const& b)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
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

SceneObject::SceneObject()
{
	_transformMatrix = glm::mat4{0};
}

SceneObject::SceneObject(glm::mat4 const& transformMatrix)
{
	_transformMatrix = transformMatrix;
}

void SceneObject::rotate(float angle, glm::vec3 const& axis)
{
	_transformMatrix = glm::rotate(_transformMatrix,angle,axis);
}

void SceneObject::scale(glm::vec3 const& scaleVector)
{
	_transformMatrix = glm::scale(_transformMatrix,scaleVector);
}

void SceneObject::translate(glm::vec3 const& translateVector)
{
	_transformMatrix = glm::translate(_transformMatrix,translateVector);
}

glm::mat4 SceneObject::inverseTransformMatrix() const
{
	return glm::inverse(_transformMatrix);
}

glm::mat4 SceneObject::transformMatrix() const
{
	return _transformMatrix;
}

