#ifndef BUW_SHAPECOMPOSITE_HPP
#define BUW_SHAPECOMPOSITE_HPP
#include <map>
#include <utility>
#include "shape.hpp"
#include "material.hpp"
class ShapeComposite : public Shape
{
	public:
		ShapeComposite();
		ShapeComposite(std::map<std::string,Shape*> const& shapes);
		ShapeComposite(std::string const& name,std::map<std::string,Shape*> const& shapes);
		ShapeComposite(Shape *shape);
		ShapeComposite(std::string const& name,Shape *shape);
		void add(Shape *shape);
		void remove(std::string const& name);
		std::map<std::string,Shape*> getChilds();
		Shape* getShape(std::string const& name);
		bool intersect(Ray const& ray, float& distance) const override;
		~ShapeComposite();

	private:
		std::map<std::string,Shape*> _shapes;
	
};

#endif