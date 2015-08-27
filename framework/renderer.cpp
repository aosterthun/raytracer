// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

const int RECURSION_DEPTH = 2;

const Color BACKGROUND_COLOR = Color{0.0, 0.0, 0.0};

Renderer::Renderer() :
_scene{},
_colorbuffer{},
_ppm{}
{}

Renderer::Renderer(Scene const& scene) :
_scene{scene},
_colorbuffer{},
_ppm{}
{}

void Renderer::render()
{
	reserveColorbuffer(_scene._camera.getResolution());

	_ppm.setResolution(_scene._camera.getResolution());

	raycast();

	_ppm.save("test1");
}

void Renderer::setScene(Scene const& scene)
{
	_scene = scene;
}

void Renderer::reserveColorbuffer(std::tuple<int,int> const& resolution)
{
	float size = std::get<0>(resolution) * std::get<1>(resolution);
	_colorbuffer.resize(size, Color(0.0, 0.0, 0.0));
}

//Idea: std::vector<Color> Renderer::raycast();
void Renderer::raycast()
{	
	float distance = _scene._camera.getDistance(std::get<0>(_scene._camera.getResolution()));

	//might be a member variable for class App
	float counter = 0;

	Ray eyeRay{};

	//normal integer for loop?
	for( std::vector<Color>::iterator i = _colorbuffer.begin(); i != _colorbuffer.end(); ++i)
	{
		int x = (i - _colorbuffer.begin()) % std::get<0>(_scene._camera.getResolution());
		int y =	floor((i - _colorbuffer.begin()) / std::get<0>(_scene._camera.getResolution())); 

		eyeRay = _scene._camera.getEyeRay( x, y, distance);

		Color col = trace(eyeRay);

		Pixel p;
		p.x = x;
		p.y = y;
		p.color = col;

		write(p);

		//++counter;
		//std::cout << getPercentage(counter);
	}
}

Color Renderer::trace(Ray r)
{	
	float distance{0.0};

	OptionalHit nearestHit{};

	for(std::map<std::string, std::shared_ptr<Shape>>::iterator i = _scene._shapes.begin(); i != _scene._shapes.end(); ++i)
	{
		OptionalHit optHit = i->second->intersect(r, distance);

		if(optHit._t <= nearestHit._t || nearestHit._t == 0.0)
		{
			nearestHit = optHit;
		}
	}
	return shade(nearestHit);
}

/*
Color Renderer::shade(OptionalHit hit)
{
	Color backgroundColor{0.0, 0.0, 0.0};
	Color testColor{ 1.0, 1.0, 1.0};

	glm::vec3 light_pos{10.0, 0.0, -25.0};

	glm::vec3 intersect{hit._intersect};

	glm::vec3 test = light_pos - intersect;

	if(hit._hit)
	{
		Color ambient = getAmbient() * hit._shape->material().ka();
		
		Color diffuse = glm::distance(hit._intersect, light_pos) * hit._shape->material().kd() *  getDiffuse() * glm::dot(glm::normalize(hit._normal), glm::normalize(test));

		std::cout << "distance: " << glm::distance(hit._intersect, light_pos) << "\n";
		std::cout << "shape_material_kd: " << hit._shape->material().kd() << "\n";
		std::cout << "light_diffuse" << getDiffuse() << "\n";
		std::cout << "dot: " << glm::dot(glm::normalize(hit._normal), glm::normalize(test)) << "\n";

		std::cout << "normal: " << glm::to_string(hit._normal) << "\n" << "test: " << glm::to_string(test) <<"\n";

		std::cout << "ambient: " << ambient << "\n";

		std::cout << "diffuse: " << diffuse << "\n";

		std::cout << "################################\n";

		return ambient + diffuse;
		//return hit._shape->material().ka();
	}
	else
	{
		return backgroundColor;
	}
}
*/

Color Renderer::shade(OptionalHit hit)
{
	Color backgroundColor{1.0, 1.0, 1.0};
	Color diffuse_whole{};
	if(hit._hit)
	{
		Color ambient, diffuse;

		for(auto light : _scene._lights)
		{
			//ambient += light.second.la();

			//second vector to compute the angle
			glm::vec3 lightVec = hit._intersect - light.second.position();

			glm::vec3 lightVec2 = light.second.position() - hit._intersect;

			//ray for intersect() method
			Ray lightRay{light.second.position(),lightVec};

			for(auto shape : _scene._shapes)
			{
				float tmpDist;

				OptionalHit inShadow = shape.second->intersect(lightRay,tmpDist);
				
				if(inShadow._hit && (inShadow._shape->name() == hit._shape->name()))
				{
					//std::cout << glm::to_string(hit._normal) << "\n";
					//std::cout << glm::to_string(lightVec2) << "\n";
					double test = glm::dot(glm::normalize(hit._normal),glm::normalize(lightVec2));
					//double test = std::cos(glm::dot(glm::normalize(hit._normal),glm::normalize(lightVec2)));

					//glm::distance(hit._intersect,light.second.position());

					diffuse += hit._shape->material().kd() * light.second.ld() * test;
					
					//std::cout << "Dot: " << test << "\n";
				}
				else
				{
					//std::cout << "test mama";
				}
				tmpDist = 0.0;

			}
		}

		//std::cout << "ka(): " << hit._shape->material().ka() << "\n";
		//std::cout << "getAmbient(): " << getAmbient() << "\n";

		ambient = getAmbient() * hit._shape->material().ka();

		//std::cout << "ambient: " << ambient << "\n";
		//std::cout << "diffuse: " << diffuse << "\n";

		//std::cout << diffuse;
		auto col = ambient + diffuse;
		
		//std::cout << "gesamt: " << col << "\n";

		return col;
	}
	else
	{
		return backgroundColor;
	}
}

Color Renderer::getAmbient()
{
	Color tmp{};
	for(std::map<std::string, Light>::iterator i = _scene._lights.begin(); i != _scene._lights.end(); ++i)
	{
		tmp = tmp + i->second.la();
	}
	return tmp;
}

Color Renderer::getDiffuse()
{
	//THIS IS NOT RIGHT, GO LEFT...lel

	Color tmp{};
	for(std::map<std::string, Light>::iterator i = _scene._lights.begin(); i != _scene._lights.end(); ++i)
	{
		tmp = tmp + i->second.ld();
	}
	return tmp;
}

std::string Renderer::getPercentage(int counter) const
{	
	float result = 100 * (counter/(float)_colorbuffer.size());
	return std::to_string(result) + " Prozent \n";
}

void Renderer::write(Pixel const& p)
{
	// flip pixels, because of opengl glDrawPixels
	size_t position = (std::get<0>(_scene._camera.getResolution())*p.y + p.x);

	if (position >= _colorbuffer.size() || (int)position < 0)
	{
		std::cerr << "Fatal Error Renderer::write(Pixel p) : "
		<< "pixel out of ppm_ : "
		<< (int)p.x << "," << (int)p.y
		<< std::endl;
	}
	else
	{
		_colorbuffer[position] = p.color;
	}

	//extra for the image-file output
	_ppm.write(p);
}