#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <sceneobject.hpp>
#include <shapecomposite.hpp>
#include <light.hpp>
#include <camera.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>

namespace glm
{
	std::ostream& operator<<(std::ostream& os, glm::mat4 const& mat)
	{
		os << glm::to_string(mat);
	}
}


int main(int argc, char *argv[])
{
	return Catch::Session().run(argc, argv);
}
