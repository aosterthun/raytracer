#define CATCH_CONFIG_RUNNER

#include <catch.hpp>

#include <sphere.hpp>
#include <box.hpp>
#include <sceneobject.hpp>
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

//ShapeComposite TestCase
TEST_CASE("shapecompositeIntersect","[ShapeComposite]")
{
	Ray ray{glm::vec3{6.0,6.0,6.0},glm::vec3{-1.0,-1.0,-1.0}};
	auto sphere = std::make_shared<Sphere>(glm::vec3{0.0,0.0,0.0}, 7.0);
	ShapeComposite sc{sphere};
	float d;
	REQUIRE(sphere->intersect(ray,d));
	REQUIRE(sc.intersect(ray,d));
}

int main(int argc, char *argv[])
{
	SDFLoader sdfLoader{};
	auto scene = sdfLoader.loadScene("../scene.sdf");
	return Catch::Session().run(argc, argv);
}
