#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <light.hpp>
#include <camera.hpp>

#include <fstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

/*

//	SDF Test

TEST_CASE("SDFRead","[SDF]")
{
	std::string line;
	std::ifstream sdf("../sdf/test.txt");
	if(sdf.is_open())
	{
		while(std::getline(sdf,line))
		{
			std::cout << line << '\n';
		}
		sdf.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}


//	Sphere tests


TEST_CASE("sphereDefaultConstructor","[Sphere]")
{
	Sphere s = Sphere{};
	REQUIRE(s.center() == glm::vec3{0});  
	REQUIRE(s.radius() == 0);
	REQUIRE(s.name() == "untitled_sphere");
	REQUIRE(s.color() == Color{0.0});
}

TEST_CASE("sphereCenterConstructor","[Sphere]")
{
	glm::vec3 center{2};
	Sphere s = Sphere{center};
	REQUIRE(s.center() == center);  
	REQUIRE(s.radius() == 0);
	REQUIRE(s.name() == "untitled_sphere");
	REQUIRE(s.color() == Color{0.0});
}

TEST_CASE("sphereRadiusConstructor","[Sphere]")
{
	Sphere s = Sphere{2};
	REQUIRE(s.center() == glm::vec3{0});  
	REQUIRE(s.radius() == 2);
	REQUIRE(s.name() == "untitled_sphere");
	REQUIRE(s.color() == Color{0.0});
}

TEST_CASE("sphereConstructor","[Sphere]")
{
	glm::vec3 center{2};
	Sphere s = Sphere{center, 3.5,"test",Color{1.0}};
	REQUIRE(s.center() == center);  
	REQUIRE(s.radius() == 3.5);
	REQUIRE(s.name() == "test");
	REQUIRE(s.color() == Color{1.0});
}

TEST_CASE("sphereGetter","[Sphere]")
{
	Sphere s = Sphere{};
	glm::vec3 center{0};
	REQUIRE(s.center() == center);  
	REQUIRE(s.radius() == 0);
	REQUIRE(s.name() == "untitled_sphere");
	REQUIRE(s.color() == Color{0.0});
}

TEST_CASE("sphereArea","[Sphere]")
{
	glm::vec3 center{2};
	Sphere s = Sphere{center, 2};
	REQUIRE(s.area() == Approx(50.2655));
}

TEST_CASE("sphereVolume","[Sphere]")
{
	glm::vec3 center{2};
	Sphere s = Sphere{center, 2};
	REQUIRE(s.volume() == Approx(33.5103));
}


//	Box tests

TEST_CASE("boxDefaultConstructor","[Box]")
{
	Box b = Box{};
	REQUIRE(b.min() == glm::vec3{0});
	REQUIRE(b.max() == glm::vec3{0});
	REQUIRE(b.name() == "untitled_box");
	REQUIRE(b.color() == Color{0.0});
}

TEST_CASE("boxConstructor","[Box]")
{
	Box b = Box{glm::vec3{0},glm::vec3{1},"test",Color{1.0}};
	REQUIRE(b.min() == glm::vec3{0});
	REQUIRE(b.max() == glm::vec3{1});
	REQUIRE(b.name() == "test");
	REQUIRE(b.color() == Color{1.0});
}

TEST_CASE("boxGetter","[Box]")
{
	Box b = Box{glm::vec3{0},glm::vec3{1}};
	REQUIRE(b.min() == glm::vec3{0});
	REQUIRE(b.max() == glm::vec3{1});
	REQUIRE(b.name() == "untitled_box");
	REQUIRE(b.color() == Color{0.0});	
}

TEST_CASE("boxArea","[Box]")
{
	Box b = Box{glm::vec3{0},glm::vec3{1}};
	REQUIRE(b.area() == 6);
}

TEST_CASE("boxVolume","[Box]")
{
	Box b = Box{glm::vec3{0},glm::vec3{1}};
	REQUIRE(b.volume() == 1);
}

TEST_CASE("printShape","[Shape]")
{
	Box b = Box{};
	Sphere s = Sphere{};
	std::cout << b;
	std::cout << s;
}


//		Ray tests


TEST_CASE("rayDefaultConstructor", "[ray]")
{
	Ray r = Ray{};
	REQUIRE(r.origin == glm::vec3{0});
	REQUIRE(r.direction == glm::vec3{0});
}

TEST_CASE("rayCustomConstructor", "[ray]")
{
	Ray r = Ray{glm::vec3{1}, glm::vec3{5}};
	REQUIRE(r.origin == glm::vec3{1});
	REQUIRE(r.direction == glm::vec3{5});
}


//		Intersect tests


TEST_CASE("intersectRaySphere","[intersect]")
{
	//Ray
	glm::vec3 ray_origin(0.0,0.0,0.0);
	glm::vec3 ray_direction(0.0,0.0,1.0);
	//Sphere
	glm::vec3 sphere_center(0.0,0.0,5.0);
	float sphere_radius(1.0);
	float distance(0.0);
	auto result = glm::intersectRaySphere(
					ray_origin,ray_direction,
					sphere_center,sphere_radius,
					distance);
	REQUIRE(distance==Approx(4.0f));
}

TEST_CASE("customIntersectRaySphere","[intersect]")
{
	Ray ray{glm::vec3{6.0,6.0,6.0},glm::vec3{-1.0,-1.0,-1.0}};
	Sphere sphere{glm::vec3{0.0,0.0,0.0}, 7.0};
	float d;
	REQUIRE(sphere.intersect(ray,d));
}


//		Virtual destructor test


TEST_CASE("virtualDestructor","[destruct]")
{
	std::cout << "============================================\n";
	Color red{255,0,0};
	glm::vec3 position{0.0};
	Sphere* s1 = new Sphere{position , 1.2 ,"sphere0" ,red};
	Shape* s2 = new Sphere{position , 1.2 , "sphere1" , red};
	//std::cout << s1 << "\n";
	//std::cout << s2;
	s1->print(std::cout);
	s2->print(std::cout);
	delete s1 ;
	delete s2 ;
}


//	light test cases


TEST_CASE("lightDefaultConstructor","light")
{
	Light light{};

	std::cout << light;

	REQUIRE(light.name() == "untitledLight");
	REQUIRE(light.position().x == 0.0);
	REQUIRE(light.position().y == 0.0);
	REQUIRE(light.position().z == 0.0);
	REQUIRE(light.ld() == 0.0);
	REQUIRE(light.la() == 0.0);
}

TEST_CASE("lightCustomConstructor","light")
{
	glm::vec3 vec{1.0};
	Light light{"light1",vec,1.0,1.0};

	std::cout << light;

	REQUIRE(light.name() == "light1");
	REQUIRE(light.position().x == 1.0);
	REQUIRE(light.position().y == 1.0);
	REQUIRE(light.position().z == 1.0);
	REQUIRE(light.ld() == 1.0);
	REQUIRE(light.la() == 1.0);
}


//	camera test cases


*/
TEST_CASE("cameraDefaultConstructor","camera")
{
	Camera camera{};

	std::cout << camera;

	REQUIRE(camera.position().x == 0.0);
	REQUIRE(camera.position().y == 0.0);
	REQUIRE(camera.position().z == 0.0);

	REQUIRE(camera.direction().x == 1.0);
	REQUIRE(camera.direction().y == 0.0);
	REQUIRE(camera.direction().z == 0.0);
}

TEST_CASE("cameraCustomConstructor","camera")
{
	glm::vec3 vec1{0.0};
	glm::vec3 vec2{3.0};

	Camera camera{vec1,vec2};

	std::cout << camera;

	REQUIRE(camera.position().x == 0.0);
	REQUIRE(camera.position().y == 0.0);
	REQUIRE(camera.position().z == 0.0);

	REQUIRE(camera.direction().x == 3.0);
	REQUIRE(camera.direction().y == 3.0);
	REQUIRE(camera.direction().z == 3.0);
}

TEST_CASE("lightDefaultConstructor","light")
{

}

TEST_CASE("lightCustomConstructor","light")
{

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
