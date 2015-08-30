#include "material.hpp"

//constructors

Material::Material() :
	_name{"untitledMaterial"}, _ka{}, _kd{}, _ks{}, _m{0.0}
{}

Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m, float l) :
	_name{name}, _ka{ka}, _kd{kd}, _ks{ks}, _m{m}, _l{l}
{}

//destructors

Material::~Material()
{}

//get-methods

std::string const& Material::name() const
{
	return _name;
}

Color& Material::ka()
{
	return _ka;
}

Color& Material::kd()
{
	return _kd;
}

Color& Material::ks()
{
	return _ks;
}

float Material::m() const
{
	return _m;
}

float Material::l() const
{
	return _l;
}

//outstream methods
std::ostream& Material::print(std::ostream& os) const
{
	os << "Name: " << _name << "\nColors:\n" << _ka << _kd << _ks << "Reflection:" <<  _m << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Material const& m)
{
	return m.print(os);
}

bool operator==(Material const& m1, Material const& m2)
{
	return (m1.name() == m2.name());
}