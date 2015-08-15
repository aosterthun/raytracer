#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <sceneobject.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>



std::ostream& operator<<(std::ostream& os, glm::mat4 const& mat)
{
	os << glm::to_string(mat);
}
/*
	SceneObject tests
*/
//Matrix initalisation for further SceneObject tests
glm::vec4 col0 = glm::vec4{1.0f,2.0f,3.0f,4.0f};
glm::vec4 col1 = glm::vec4{2.0f,3.0f,4.0f,5.0f};
glm::vec4 col2 = glm::vec4{3.0f,4.0f,5.0f,6.0f};
glm::vec4 col3 = glm::vec4{4.0f,5.0f,6.0f,7.0f};
glm::mat4 mat = glm::mat4{col0,col1,col2,col3};
TEST_CASE("sceneObjectDefaultConstructor","[SceneObject]")
{
	SceneObject so = SceneObject{};
	REQUIRE(so.transformMatrix() == glm::mat4{0.0});
};
TEST_CASE("sceneObjectMatrixConstructor","[SceneObject]")
{
	SceneObject so = SceneObject{mat};
	REQUIRE(so.transformMatrix() == mat);	
};
TEST_CASE("sceneObjectInverseMatrix","[SceneObject]"){
	SceneObject so = SceneObject{mat};
	REQUIRE(so.inverseTransformMatrix() == glm::inverse(mat));
};
TEST_CASE("sceneObjectTranslateMatrix","[SceneObject]"){
	SceneObject so = SceneObject{mat};
	REQUIRE(so.translate(glm::vec3(1.0,2.0,3.0)) == glm::translate(mat,glm::vec3(1,2,3)));
};
TEST_CASE("sceneObjectRotateMatrix","[SceneObject]"){
	SceneObject so = SceneObject{mat};
	REQUIRE(so.rotate(45.0f,glm::vec3(1.0,2.0,3.0)) == glm::rotate(mat,45.0f,glm::vec3(1,2,3)));
};
TEST_CASE("sceneObjectScaleMatrix","[SceneObject]"){
	SceneObject so = SceneObject{mat};
	REQUIRE(so.scale(glm::vec3(1.0,2.0,3.0)) == glm::scale(mat,glm::vec3(1,2,3)));
};
/*
	Sphere tests
*/

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

/*
	Box tests
*/
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
/*
 Ray tests
*/
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

/*
 Intersect tests
*/

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

/*
 Virtual destructor test
*/

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

int main(int argc, char *argv[])
{
	glm::vec4 col0 = glm::vec4{1.0f,2.0f,3.0f,4.0f};
	glm::vec4 col1 = glm::vec4{2.0f,3.0f,4.0f,5.0f};
	glm::vec4 col2 = glm::vec4{3.0f,4.0f,5.0f,6.0f};
	glm::vec4 col3 = glm::vec4{4.0f,5.0f,6.0f,7.0f};
	glm::mat4 mat = glm::mat4{col0,col1,col2,col3};
	std::cout << mat;
	return Catch::Session().run(argc, argv);
}
