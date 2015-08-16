#ifndef BUW_SHAPECOMPOSITE_HPP
#define BUW_SHAPECOMPOSITE_HPP
#include "shape.hpp"
class ShapeComposite : public Shape
{
	public:
		ShapeComposite();
		void add(Shape const& shape);
		void remove(Shape const& shape);
		bool intersect(Ray const& ray, float& distance) const override;
		~ShapeComposite();

	private:
		std::vector<Shape> shapes;
	
};

#endif