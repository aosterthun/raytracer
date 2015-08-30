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

		Ray tmpR{r.origin,glm::normalize(r.direction)};
		
		intersection._hit = true;
		intersection._intersect = glm::vec3{tnear*tmpR.direction.x, tnear*tmpR.direction.y, tnear*tmpR.direction.z};
		intersection._normal = normal(intersection._intersect);
		intersection._ray = Ray{glm::vec3{1,1,1},glm::normalize(r.direction)};
		intersection._t = sqrt(tnear*tnear*(tmpR.direction.x*tmpR.direction.x + tmpR.direction.y*tmpR.direction.y + tmpR.direction.z*tmpR.direction.z));
		intersection._shape = std::make_shared<Box>(*this);
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

/*glm::vec3 Box::normal(glm::vec3 const& intersection) const
{
	 glm::vec3 front{0.0, 0.0, 1.0};
	 glm::vec3 right{1.0, 0.0, 0.0};
	 glm::vec3 back{0.0, 0.0, -1.0};
	 glm::vec3 left{-1.0, 0.0, 0.0};
	 glm::vec3 top{0.0, 1.0, 0.0};
	 glm::vec3 down{0.0, -1.0, 0.0};

	 float epsilon = 4.76837e-06;

	 //std::cout << fabsf(glm::dot(top,(intersection-_max))) << std::endl;

	 if(fabsf(glm::dot(front,(intersection-_min))) < epsilon)
	 {
		 return front;
	 }
	 else if(fabsf(glm::dot(left,(intersection-_min))) < epsilon)
	 {
		 return left;
	 }
	 else if(fabsf(glm::dot(down,(intersection-_min))) < epsilon)
	 {
	 	return down;
	 }
	 else if(fabsf(glm::dot(top,(intersection-_max))) < epsilon)
	 {
	 	return top;
	 }
	 else if(fabsf(glm::dot(right,(intersection-_max))) < epsilon)
	 {
	 	return right;
	 }
	 else if(fabsf(glm::dot(back,(intersection-_max))) < epsilon)
	 {
	 	return back;
	 }
}*/

	 glm::vec3 Box::normal(glm::vec3 const& intersection) const
{
 glm::vec3 front{0.0, 0.0, 1.0};
 glm::vec3 right{1.0, 0.0, 0.0};
 glm::vec3 back{0.0, 0.0, -1.0};
 glm::vec3 left{-1.0, 0.0, 0.0};
 glm::vec3 top{0.0, 1.0, 0.0};
 glm::vec3 down{0.0, -1.0, 0.0};

 std::map<float, glm::vec3> dotMin;

 dotMin.insert(std::make_pair((glm::dot(front,(intersection-_min))), front));
 dotMin.insert(std::make_pair((glm::dot(left,(intersection-_min))), left));
 dotMin.insert(std::make_pair((glm::dot(down,(intersection-_min))), down));
 dotMin.insert(std::make_pair((glm::dot(top,(intersection-_max))), top));
 dotMin.insert(std::make_pair((glm::dot(right,(intersection-_max))), right));
 dotMin.insert(std::make_pair((glm::dot(back,(intersection-_max))), back));

 float closest = INFINITY;
 glm::vec3 closestTemp{};
 
 for(auto dot : dotMin)
 {
 if(dot.first < closest) 
 {
 closestTemp = dot.second;
 }
 }
 return closestTemp; 
}

glm::vec3 Box::min() const
{
	return _min;
}

glm::vec3 Box::max() const
{
	return _max;
}