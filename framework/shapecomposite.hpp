#ifndef BUW_SHAPECOMPOSITE_HPP
#define BUW_SHAPECOMPOSITE_HPP
#include <map>
#include <memory>
#include <utility>
#include "shape.hpp"
#include "material.hpp"
#include "optionalhit.hpp"

class ShapeComposite : public Shape
{
	public:
		ShapeComposite();
		ShapeComposite(std::string const& name);
		ShapeComposite(ShapeComposite const& sc);
		ShapeComposite(std::string const& name,ShapeComposite const& sc);
		ShapeComposite(std::shared_ptr<Shape> shape);
		ShapeComposite(std::string const& name,std::shared_ptr<Shape> shape);
		std::ostream& print(std::ostream& os) const override;
		void add(std::shared_ptr<Shape> shape);
		void remove(std::string const& name);
		std::map<std::string,std::shared_ptr<Shape>> getChilds() const;
		std::shared_ptr<Shape> getShape(std::string const& name);
		OptionalHit intersect(Ray const& ray, float& distance) const override;
		std::string className() const override;
		~ShapeComposite();

	private:
		std::map<std::string,std::shared_ptr<Shape>> _shapes;
	
};

#endif