#include <sdfloader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include "sphere.hpp"
#include "box.hpp"
#include "shapecomposite.hpp"

SDFLoader::SDFLoader() 
{}

SDFLoader::~SDFLoader()
{}

Scene SDFLoader::loadScene(std::string const& filePath)
{
	std::ifstream file;
	std::string text;
	Scene scene;
	file.open(filePath, std::ios::in);

	while(!file.eof())
	{
		std::getline(file, text);
		std::istringstream textStream{text};
		std::string word;
		
		textStream >> word;
		
		if(textStream == "define")
		{
			textStream >> word;

			if(word = "camera")
			{
				scene.camera = createCamera(textStream);
			}

			if(word == "light")
			{
				auto tmpLight = createLight(textStream);
				scene._lights.push_back(tmpLight);
			}

			if(word == "material")
			{
				auto tmpMaterial = createMaterial(textStream);
				_materials.insert(std::make_pair(tmpMaterial.name(),tmpMaterial));
			}
			
			if (word == "shape")
			{
				textStream >> word;
				if(word == "sphere")
				{
					auto tmpSphere = createSphere(textStream);
					scene._shapes.insert(std::make_pair(tmpSphere->name(),tmpSphere));
				}
				if(word == "box")
				{
					auto tmpBox = createBox(textStream);
					scene._shapes.insert(std::make_pair(tmpBox->name(),tmpBox));
				}
				if(word == "composite")
				{
					auto tmpShapeComposite = createShapeComposite(textStream,scene._shapes);
					scene._shapes.insert(std::make_pair(tmpShapeComposite->name(),tmpShapeComposite));	
				}
			}
		}
	}
	return scene;
}

std::shared_ptr<Shape> SDFLoader::createSphere(std::istringstream &textStream)
{
	std::string name,materialName;
	float x,y,z,rad;
	textStream >> name >> x >> y >> z >> rad >> materialName;
	Material material = _materials.find(materialName)->second;
	return std::make_shared<Sphere>(glm::vec3(x,y,z),(double)rad,name,material);
}

std::shared_ptr<Shape> SDFLoader::createBox(std::istringstream &textStream)
{
	std::string name,materialName;
	float x0,y0,z0,x1,y1,z1;
	textStream >> name >> x0 >> y0 >> z0 >> x1 >> y1 >> z1 >> materialName;
	Material material = _materials.find(materialName)->second;
	return std::make_shared<Box>(glm::vec3(x0,y0,z0),glm::vec3(x1,y1,z1),name,material);
}

std::shared_ptr<Shape> SDFLoader::createShapeComposite(std::istringstream &textStream, std::map<std::string,std::shared_ptr<Shape>> const& shapes)
{
	std::string name;
	std::string newName;
	textStream >> name;
	auto sc = std::make_shared<ShapeComposite>(name);
	while(textStream)
	{
		textStream >> newName;
		sc->add(shapes.find(newName)->second);
	}
	
	return sc;
}

Material SDFLoader::createMaterial(std::istringstream& textStream)
{
	std::string name;
	float r,g,b,m;

	textStream >> name >> r >> g >> b;
	Color ka{r,g,b};

	textStream >> r >> g >> b;
	Color kd{r,g,b};

	textStream >> r >> g >> b;
	Color ks{r,g,b};

	textStream >> m;

	return Material(name,ka,kd,ks,m);
}

Light& createLight(std::istringstream &textStream)
{
	std::string name;
	double la,ld;
	float x,y,z;
	textStream >> name >> x >> y >> z >> la >> ld;
	return Light(name,glm::vec3{x,y,z},la,ld);
}

Camera& createCamera(std::istringstream &textStream)
{
	std::string name;
	float aperture;
	textStream >> name >> aperture;
	return Camera(name,aperture);
}
