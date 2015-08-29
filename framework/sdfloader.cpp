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
		//std::cout << "Word:" << word << "\n";
		
		if(word == "camera")
		{
			//std::cout << "Is Camera \n";
			auto tmpCamera = createCamera(textStream);
			_cameras.insert(std::make_pair(tmpCamera.name(),tmpCamera));
		}

		if(word == "render")
		{
			//std::cout << "Is Render \n";
			setRenderData(textStream,scene);
		}
		if(word == "define")
		{
			//std::cout << "Is Define \n";
			textStream >> word;
			if(word == "light")
			{
				//std::cout << "Is Light \n";
				auto tmpLight = createLight(textStream);
				scene._lights.insert(std::make_pair(tmpLight.name(),tmpLight));
			}

			if(word == "material")
			{
				//std::cout << "Is Material \n";
				auto tmpMaterial = createMaterial(textStream);
				_materials.insert(std::make_pair(tmpMaterial.name(),tmpMaterial));
			}
			
			if (word == "shape")
			{
				//std::cout << "Is Shape \n";
				textStream >> word;
				if(word == "sphere")
				{
					//std::cout << "Is Sphere \n";
					auto tmpSphere = createSphere(textStream);
					scene._shapes.insert(std::make_pair(tmpSphere->name(),tmpSphere));
				}
				if(word == "box")
				{
					//std::cout << "Is Box \n";
					auto tmpBox = createBox(textStream);
					scene._shapes.insert(std::make_pair(tmpBox->name(),tmpBox));
				}
				if(word == "composite")
				{
					//std::cout << "Is Compsite \n";
					auto tmpShapeComposite = createShapeComposite(textStream,scene._shapes);
					scene._shapes.insert(std::make_pair(tmpShapeComposite->name(),tmpShapeComposite));	
				}
			}
		}
		if(word == "transform")
		{
			textStream >> word;
			//Get object
			auto shape = scene._shapes.find(word)->second;


			textStream >> word;
			if(word == "translate")
			{
				float x,y,z;
				textStream >> x >> y >> z;
				glm::vec3 vec{x,y,z};
				shape->translate(vec);
			}
			if(word == "rotate")
			{
				float angle;
				float x,y,z;
				textStream >> angle >> x >> y >> z;
				glm::vec3 vec{x,y,z};
				shape->rotate(angle,vec);	
			}
			if(word == "scale")
			{
				float x,y,z;
				textStream >> x >> y >> z;
				glm::vec3 vec{x,y,z};
				shape->scale(vec);
			}
		}
	}
	return scene;
}

std::shared_ptr<Shape> SDFLoader::createSphere(std::istringstream& textStream)
{
	std::string name,materialName;
	float x,y,z,rad;
	textStream >> name >> x >> y >> z >> rad >> materialName;
	//std::cout << name << x << y << z << rad <<materialName; 
	return std::make_shared<Sphere>(glm::vec3(x,y,z),(double)rad,name,_materials.find(materialName)->second);
}

std::shared_ptr<Shape> SDFLoader::createBox(std::istringstream& textStream)
{
	std::string name,materialName;
	float x0,y0,z0,x1,y1,z1;
	textStream >> name >> x0 >> y0 >> z0 >> x1 >> y1 >> z1 >> materialName;
	//std::cout << name << x0 << y0 << z0 << x1 << y1 << z1 << materialName;
	return std::make_shared<Box>(glm::vec3(x0,y0,z0),glm::vec3(x1,y1,z1),name,_materials.find(materialName)->second);
}

std::shared_ptr<Shape> SDFLoader::createShapeComposite(std::istringstream& textStream, std::map<std::string,std::shared_ptr<Shape>>& shapes)
{
	std::string name;
	std::string newName;
	textStream >> name;
	auto sc = std::make_shared<ShapeComposite>(name);
	//To edit
	textStream >> newName;
	while(textStream)
	{
		sc->add(shapes.find(newName)->second);
		shapes.erase(shapes.find(newName));
		textStream >> newName;
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

Light SDFLoader::createLight(std::istringstream& textStream)
{
	std::string name;
	float lar,lag,lab,ldr,ldg,ldb;
	float x,y,z;
	textStream >> name >> x >> y >> z >> lar >> lag >> lab >> ldr >> ldg >> ldb;
	//std::cout << name << x << y << z << la << ld;
	return Light(name,glm::vec3{x,y,z},Color{lar,lag,lab},Color{ldr,ldg,ldb});
}

Camera SDFLoader::createCamera(std::istringstream& textStream)
{
	std::string name;
	float aperture;
	textStream >> name >> aperture;
	return Camera(name,aperture);
}

void SDFLoader::setRenderData(std::istringstream& textStream, Scene& scene)
{
	std::string camName;
	int width, height;

	textStream >> camName;
	scene._camera = _cameras.find(camName)->second;
	textStream >> scene._renderFilename;
	textStream >> width >> height;
	scene._camera.setResolution(width, height);
}