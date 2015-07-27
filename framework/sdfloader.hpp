#ifndef BUW_SDF_HPP
#define BUW_SDF_HPP
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <material.hpp>
#include <scene.hpp>

class SDFloader
{
public:
	//Constructor
	SDFloader();
	//SDFloader(std::string const& path, std::string const& file);
	~SDFloader();

	Scene const& scene() const;

	void readSdf(std::string const& path);

private:

	void create_material(std::istringstream&);

	//MIGHT NEED TO BE SEPERATE
	Scene scene_;

};


#endif // BUW_SDF_HPP