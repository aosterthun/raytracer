#define CATCH_CONFIG_RUNNER

#include <catch.hpp>

#include <sphere.hpp>
#include <box.hpp>
#include <sceneobject.hpp>
#include <sdfloader.hpp>
#include <shapecomposite.hpp>
#include <light.hpp>
#include <camera.hpp>
#include <sdfloader.hpp>
#include <iostream>

namespace glm
{
	std::ostream& operator<<(std::ostream& os, glm::mat4 const& mat)
	{
		os << glm::to_string(mat);
		return os;
	}
}


int main(int argc, char *argv[])
{
	//SDFLoader sdfLoader{};
	//auto scene = sdfLoader.loadScene("../scene.sdf");
	//std::cout << scene;
	//return Catch::Session().run(argc, argv);
}
