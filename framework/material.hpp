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

	Color const& ka() const;

	Color const& kd() const;

	Color const& ks() const;

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

#endif // define BUW_MATERIAL_HPP