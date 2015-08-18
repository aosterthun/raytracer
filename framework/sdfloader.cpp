/*#include <sdfloader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

SDFloader::SDFloader(): scene_{}
{}

SDFloader::~SDFloader()
{}

Scene const& SDFloader::scene() const
{
  return scene_;
}

void SDFloader::readSdf(std::string const& path)
{
	std::ifstream file;
	std::string s;

	file.open(path, std::ios::in);

	while(!file.eof())
	{
		getline(file, s);

		std::istringstream iss(s);

		std::string tmp;

		iss >> tmp;
		
		if(tmp == "define")
		{
			iss >> tmp;

			if(tmp == "material")
			{
				create_material(iss);
			}
			//here could be future classes!
		}

		/*
		if(tmp == "define")
		{
			iss >> tmp;

			switch(tmp)
			{
			case "material": create_material(iss);

			//case "shape": create_shape(iss);

			//case "sphere": create_sphere(iss);

			//case "box": create_box(iss);
			}
		}
		
	}
}

void SDFloader::create_material(std::istringstream& iss)
{
	std::string name;
	float r,g,b,m;

	iss >> name >> r >> g >> b;
	Color ka{r,g,b};

	iss >> r >> g >> b;
	Color kd{r,g,b};

	iss >> r >> g >> b;
	Color ks{r,g,b};

	iss >> m;

	scene_.materials[name] = Material(name,ka,kd,ks,m);
}

*/