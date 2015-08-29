#ifndef BUW_SDF_HPP
#define BUW_SDF_HPP
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <material.hpp>
#include <map>
#include <scene.hpp>

class SDFLoader
{
public:
	//Constructor
	SDFLoader();
	~SDFLoader();

	Scene loadScene(std::string const& filePath);
private:
	std::map<std::string,Material> _materials;
	std::map<std::string,Camera> _cameras;
	Material createMaterial(std::istringstream& textStream);
	std::shared_ptr<Shape> createSphere(std::istringstream& textStream);
	std::shared_ptr<Shape> createBox(std::istringstream& textStream);
	std::shared_ptr<Shape> createShapeComposite(std::istringstream& textStream, std::map<std::string,std::shared_ptr<Shape>>& shapes);
	Light createLight(std::istringstream& textStream);
	Camera createCamera(std::istringstream& textStream);
	void setRenderData(std::istringstream& textStream, Scene& scene);
};


#endif // BUW_SDF_HPP