#ifndef BUW_SHAPECOMPOSITE_HPP
#define BUW_SHAPECOMPOSITE_HPP
#include <map>
#include <memory>
#include <utility>
#include "shape.hpp"
#include "material.hpp"
class ShapeComposite : public Shape
{
	public:
		ShapeComposite();
		ShapeComposite(std::map<std::string,std::shared_ptr<Shape>> const& shapes);
		ShapeComposite(std::string const& name,std::map<std::string,std::shared_ptr<Shape>> const& shapes);
		ShapeComposite(std::shared_ptr<Shape> shape);
		ShapeComposite(std::string const& name,std::shared_ptr<Shape> shape);
		void add(std::shared_ptr<Shape> shape);
		void remove(std::string const& name);
		std::map<std::string,std::shared_ptr<Shape>> getChilds();
		std::shared_ptr<Shape> getShape(std::string const& name);
		bool intersect(Ray const& ray, float& distance) const override;
		~ShapeComposite();

	private:
		std::map<std::string,std::shared_ptr<Shape>> _shapes;
	
};

#endif