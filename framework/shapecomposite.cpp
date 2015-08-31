#include "shapecomposite.hpp"

ShapeComposite::ShapeComposite():
Shape::Shape("untitled_shapecomposite", Material{})
{}

ShapeComposite::ShapeComposite(std::string const& name):
Shape::Shape(name, Material())
{}


ShapeComposite::ShapeComposite(ShapeComposite const& sc):
Shape::Shape("untitled_shapecomposite", Material())
{
	_shapes.insert(sc.getChilds().begin(),sc.getChilds().end());
}

ShapeComposite::ShapeComposite(std::shared_ptr<Shape> shape):
Shape::Shape("untitled_shapecomposite", Material())
{
	_shapes.insert(std::make_pair(shape->name(),shape));
}

ShapeComposite::ShapeComposite(std::string const& name,std::shared_ptr<Shape> shape):
Shape::Shape(name, Material())
{
	_shapes.insert(std::make_pair(shape->name(),shape));
}

ShapeComposite::ShapeComposite(std::string const& name, ShapeComposite const& sc):
Shape::Shape(name, Material())
{
	_shapes.insert(sc.getChilds().begin(),sc.getChilds().end());
}

ShapeComposite::~ShapeComposite()
{}

void ShapeComposite::add(std::shared_ptr<Shape> shape)
{ 
	_shapes.insert(std::make_pair(shape->name(),shape));
}

void ShapeComposite::remove(std::string const& name)
{
	auto it = _shapes.find(name);
	_shapes.erase(it);
}

std::map<std::string,std::shared_ptr<Shape>> ShapeComposite::getChilds() const
{
	return _shapes;
}

std::shared_ptr<Shape> ShapeComposite::getShape(std::string const& name)
{
	auto it = _shapes.find(name);
	return it->second;
}

std::ostream& ShapeComposite::print(std::ostream& os) const
{
	os << "[ShapeComposite]";
	for(auto shapePair : _shapes)
	{
		os << shapePair.second;
	}
	return os;
}

OptionalHit ShapeComposite::intersect(Ray const& ray, float& distance) const
{	
	/*
	float closest = INFINITY;
	
	OptionalHit hit;
	
	for(auto shape : _shapes)
	{
	
		OptionalHit hit_temp = shape.second->intersect(ray, distance);

		if(hit_temp._t < closest && hit_temp._t>0.01) 
		{
		closest = hit_temp._t;
		hit = hit_temp;
		}
	}
	return hit;
	*/
	OptionalHit tmpHit{};
	for(auto shapePair : _shapes)
	{
		auto optHit = shapePair.second->intersect(ray, distance);
		if(optHit._hit)
		{
			if(optHit._t <= tmpHit._t || tmpHit._t == 0.0)
			{
				tmpHit = optHit;
			}
		}
	}
	//test cout
	if(tmpHit._hit)
	{
	//std::cout << tmpHit._shape << "tmpHit: " << glm::to_string(tmpHit._intersect) << "\n";
	}	
	return tmpHit;
}

std::string ShapeComposite::className() const
{
	return "composite";
}