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
	OptionalHit tmpHit{};
	for(auto shapePair : _shapes)
	{
		auto optHit = shapePair.second->intersect(ray, distance)
		if(optHit._hit){
			if(optHit._t <= tmpHit._t && optHit._t != 0)
			{
				tmpHit = optHit;
			}
		}
	}
	if(distance != 0)
	{
		return tmpHit;
	}
	return OptionalHit{false,nullptr,INFINITY};
}
