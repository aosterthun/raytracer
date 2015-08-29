#include "box.hpp"

Box::Box():
Shape::Shape("untitled_box", Material{}),
_min{glm::vec3{0}},
_max{glm::vec3{0}}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape::Shape("untitled_box", Material{}),
_min{min},
_max{max}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, Material const& material):
Shape::Shape(name, material),
_min{min},
_max{max}
{}

Box::~Box()
{
	//std::cout << "Box destruct \n";
}

std::ostream& Box::print(std::ostream& os) const
{
	os << "[Box]\n" <<
				"Name: " << _name << "\n" <<
 				"Material: " << _material <<
 				"Min: " << glm::to_string(_min) << "\n" <<
 				"Max: " << glm::to_string(_max) << "\n\n"; 
	return os;
}

OptionalHit Box::intersect(Ray const& r, float& distance) const
{	
	double tx1 = (_min.x - r.origin.x)/glm::normalize(r.direction).x;
	double tx2 = (_max.x - r.origin.x)/glm::normalize(r.direction).x;

	double tnear = std::min(tx1, tx2);
	double tfar = std::max(tx1, tx2);

	double ty1 = (_min.y - r.origin.y)/glm::normalize(r.direction).y;
	double ty2 = (_max.y - r.origin.y)/glm::normalize(r.direction).y;

	tnear = std::max(tnear, std::min(ty1, ty2));
	tfar = std::min(tfar, std::max(ty1, ty2));

	double tz1 = (_min.z - r.origin.z)/glm::normalize(r.direction).z;
	double tz2 = (_max.z - r.origin.z)/glm::normalize(r.direction).z;

	tnear = std::max(tnear, std::min(tz1, tz2));
	tfar = std::min(tfar, std::max(tz1, tz2));

	OptionalHit intersection;

    if(tfar > std::max(0.0, tnear))
    {
    	//freaking important
    	Ray tmpR{r.origin,glm::normalize(r.direction)};


    	//std::cout << "Ray origin: " << glm::to_string(r.origin) << "\n";
		//std::cout << "Ray direction: " << glm::to_string(r.direction) << "\n";
    	//std::cout << "tnear:" << tnear << "DirectionvVec" << glm::to_string(r.direction) << "\n";
		
		intersection._intersect = glm::vec3{tnear*tmpR.direction.x, tnear*tmpR.direction.y, tnear*tmpR.direction.z};

		intersection._normal = normal(intersection._intersect);

		intersection._t = sqrt(tnear*tnear*(tmpR.direction.x*tmpR.direction.x + tmpR.direction.y*tmpR.direction.y + tmpR.direction.z*tmpR.direction.z));

		//std::cout << "_t: " << intersection._t << "\n";

		intersection._shape = std::make_shared<Box>(*this);
		intersection._hit = true;
    }
	else
	{
		intersection._t = INFINITY;
		intersection._intersect = glm::vec3{INFINITY,INFINITY,INFINITY};
		intersection._normal = glm::vec3{INFINITY,INFINITY,INFINITY};
		intersection._shape = nullptr;
		intersection._hit = false;
	}
    return intersection;
}

glm::vec3 Box::normal(glm::vec3 const& intersection) const
{

	//float sucks
	const double epsilon = 5.97e-4;

	glm::vec3 planeNormal;
	glm::vec3 front{0.0, 0.0, 1.0};
	glm::vec3 right{1.0, 0.0, 0.0};
	glm::vec3 back{0.0, 0.0, -1.0};
	glm::vec3 left{-1.0, 0.0, 0.0};
	glm::vec3 top{0.0, 1.0, 0.0};
	glm::vec3 down{0.0, -1.0, 0.0};

	if(glm::dot(front,(intersection-_min)) == 0.0)
	{
		return front;
	}
	else if(glm::dot(left,(intersection-_min)) == 0.0)
	{
		return left;
	}
	else if(glm::dot(down,(intersection-_min)) == 0.0)
	{
		return down;
	}
	else if(glm::dot(top,(intersection-_max)) == 0.0)
	{
		return top;
	}
	else if(glm::dot(right,(intersection-_max)) == 0.0)
	{
		return right;
	}
	else if(glm::dot(back,(intersection-_max)) == 0.0)
	{
		return back;
	}
	/*
	//these if statements check wether the intersection with the plane is the intersection with the right plane!

	//front
	glm::intersectRayPlane(origin, vecDir, _min, { 0.0, 0.0, 1.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		planeNormal = glm::vec3{ 0.0, 0.0, 1.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	//bottom
	glm::intersectRayPlane(origin, vecDir, _min, { 0.0, -1.0, 0.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		planeNormal = glm::vec3{ 0.0, -1.0, 0.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	//left
	glm::intersectRayPlane(origin, vecDir, _min, { -1.0, 0.0, 0.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		planeNormal = glm::vec3{ -1.0, 0.0, 0.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	//back
	glm::intersectRayPlane(origin, vecDir, _max, { 0.0, 0.0, -1.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		planeNormal = glm::vec3{ 0.0, 0.0, -1.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	//top
	glm::intersectRayPlane(origin, vecDir, _max, { 0.0, 1.0, 0.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		planeNormal = glm::vec3{ 0.0, 1.0, 0.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	//right
	glm::intersectRayPlane(origin, vecDir, _max, { 1.0, 0.0, 0.0}, intersectionDis);
	if(fabs(intersectionDis - realDis) < epsilon) 
	{
		//std::cout << "intDis: " << intersectionDis << "realDis: " << realDis << "\n";
		planeNormal = glm::vec3{ 1.0, 0.0, 0.0};
	}
	//std::cout << "intersectionDis: " << intersectionDis << "\n";
	intersectionDis = 0.0;
	*/
}

/*
glm::vec3 Box::normal(glm::vec3 const& vecDir) const {
    // Use `INFINITY` vector instead of origin for when the detection doesn’t
    // work. This prevents division by zero when using glm::normalize().
    glm::vec3 tmp_normal{ INFINITY, INFINITY, INFINITY };
    const double epsilon = 5.97e-4;
    //const double epsilon = 5.97e-5;

	if (abs(_min.x - vecDir.x) < epsilon)
	{
		tmp_normal = glm::vec3{ -1.0, 0.0, 0.0 };
	}
	else if (abs(_min.y - vecDir.y) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, -1.0, 0.0 };
	}
	else if (abs(_min.z - vecDir.z) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 0.0, 1.0 };
	}
	else if (abs(_max.x - vecDir.x) < epsilon)
	{
		tmp_normal = glm::vec3{ 1.0, 0.0, 0.0 };
	}
	else if (abs(_max.y - vecDir.y) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 1.0, 0.0 };
	}
	else if (abs(_max.z - vecDir.z) < epsilon)
	{
		tmp_normal = glm::vec3{ 0.0, 0.0, -1.0 };
	}

    return tmp_normal;
}
*/
/*
OptionalHit Box::intersect(Ray const& r, float& distance) const
 {
	double tx1 = (_min.x - r.origin.x)/glm::normalize(r.direction).x;
	double tx2 = (_max.x - r.origin.x)/glm::normalize(r.direction).x;

	double tnear = std::min(tx1, tx2);
	double tfar = std::max(tx1, tx2);

	double ty1 = (_min.y - r.origin.y)/glm::normalize(r.direction).y;
	double ty2 = (_max.y - r.origin.y)/glm::normalize(r.direction).y;

	tnear = std::max(tnear, std::min(ty1, ty2));
	tfar = std::min(tfar, std::max(ty1, ty2));

	double tz1 = (_min.z - r.origin.z)/glm::normalize(r.direction).z;
	double tz2 = (_max.z - r.origin.z)/glm::normalize(r.direction).z;

	tnear = std::max(tnear, std::min(tz1, tz2));
	tfar = std::min(tfar, std::max(tz1, tz2));

	OptionalHit intersection;

    if(tfar > std::max(0.0, tnear))
    {
    	//freaking important
    	r.direction = glm::normalize(r.direction);

		intersection._t = sqrt(tnear*tnear*(r.direction.x*r.direction.x + r.direction.y*r.direction.y + r.direction.z*r.direction.z));
		intersection._intersect = glm::vec3{tnear*r.direction.x, tnear*r.direction.y, tnear*r.direction.z};
		intersection._normal = normal(intersection._intersect);

		std::cout << glm::to_string(intersection._intersect) << "\n";

		intersection._shape = std::make_shared<Box>(*this);
		intersection._hit = true;
    }
	else
	{
		intersection._t = INFINITY;
		intersection._intersect = glm::vec3{INFINITY,INFINITY,INFINITY};
		intersection._normal = glm::vec3{INFINITY,INFINITY,INFINITY};
		intersection._shape = nullptr;
		intersection._hit = false;
	}
    return intersection;
 }
*/


glm::vec3 Box::min() const
{
	return _min;
}

glm::vec3 Box::max() const
{
	return _max;
}