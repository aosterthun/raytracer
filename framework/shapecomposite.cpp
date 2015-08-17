#include "shapecomposite.hpp"

ShapeComposite::ShapeComposite():
Shape::Shape("untitled_shapecomposite", Material{})
{}

ShapeComposite::ShapeComposite(std::map<std::string,Shape*> const& shapes):
Shape::Shape("untitled_shapecomposite", Material())
{
	//_shapes.insert(shapes);
}

ShapeComposite::ShapeComposite(Shape *shape):
Shape::Shape("untitled_shapecomposite", Material())
{
	_shapes.insert(std::make_pair(shape->name(),shape));
}

ShapeComposite::ShapeComposite(std::string const& name,Shape *shape):
Shape::Shape(name, Material())
{
	_shapes.insert(std::pair<std::string,Shape*>(shape->name(),shape));
}

ShapeComposite::ShapeComposite(std::string const& name, std::map<std::string,Shape*> const& shapes):
Shape::Shape(name, Material())
{
	//_shapes.insert(shapes);
}

void ShapeComposite::add(Shape *shape)
{
	_shapes.insert(std::pair<std::string,Shape*>(shape->name(),shape));
}

void ShapeComposite::remove(std::string const& name)
{
	auto it = _shapes.find(name);
	_shapes.erase(it);
}

std::map<std::string,Shape*> ShapeComposite::getChilds()
{
	return _shapes;
}

Shape* ShapeComposite::getShape(std::string const& name)
{
	auto it = _shapes.find(name);
	return it->second;
}

bool ShapeComposite::intersect(Ray const& ray, float& distance) const
{
	float tmpDist;
	for(auto shapePair : _shapes)
	{
		if(shapePair.second->intersect(ray, distance)){
			if(distance <= tmpDist && distance != 0)
			{
				tmpDist = distance;
			}
		}

	}
	if(distance != 0)
	{
		return true;
	}
	return false;
}
