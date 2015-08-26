#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include "color.hpp"

class Material
{
public:

	//constructors
	Material();

	Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m);

	//destructors
	~Material();

	//non-member functions

	//get-methods
	std::string const& name() const;

	Color& ka();

	Color& kd();

	Color& ks();

	float m() const;

	std::ostream& print(std::ostream&) const;

private:
	std::string _name;
	Color _ka;
	Color _kd;
	Color _ks;
	float _m;

};

//operators
std::ostream& operator<<(std::ostream&, Material const&);
bool operator==(Material const& m1, Material const& m2);

#endif // define BUW_MATERIAL_HPP