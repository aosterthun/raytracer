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

		Color color = trace(eyeRay);
		Pixel p{x, y, color};

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
	if(hit._hit)
	{
		Color shade;

		for(auto light : _scene._lights)
		{
			//ray for intersect() method
			Ray lightRay{light.second.position(),getLightVec(hit,light.second)};

			for(auto shape : _scene._shapes)
			{
				float tmpDist;
				OptionalHit inShadow = shape.second->intersect(lightRay,tmpDist);
				
				if(inShadow._hit && (inShadow._shape->name() == hit._shape->name()))
				{
					shade += light.second.ld()*(calcDiffuse(light.second,hit));
				}
				tmpDist = 0.0;
			}
		}
		shade += calcAmbient(hit);
		return shade;
	}
	else
	{
		return BACKGROUND_COLOR;
	}
}

glm::vec3 Renderer::getCamVec(OptionalHit const& optHit)
{
	//Vector that spans between the intersected object and the camera
	glm::vec3 camVec{optHit._intersect-_scene._camera.position()};
	return camVec;
}

glm::vec3 Renderer::getLightVec(OptionalHit const& optHit, Light const& light)
{
	//Vector that spans between the intersected object
	glm::vec3 lightVec{optHit._intersect - light.position()};
	return lightVec;
}

glm::vec3 Renderer::getLightReflectionVec(OptionalHit const& optHit, Light const& light)
{
	//Calculates thr reflection vector of the given light
	glm::vec3 lightReflectionVec{getLightVec(optHit,light)-2*glm::dot(getLightVec(optHit,light),glm::normalize(optHit._normal))*glm::normalize(optHit._normal)};
	return lightReflectionVec;
}

Color Renderer::calcSpecular(Light const& light, OptionalHit const& optHit)
{
	Color specularLight{optHit._shape->material().ks()*std::pow(glm::dot(getLightReflectionVec(optHit,light),getCamVec(optHit)),optHit._shape->material().m())};
	return specularLight;
}

Color Renderer::calcDiffuse(Light const& light, OptionalHit const& optHit)
{
	Color diffuseLight{optHit._shape->material().kd() * glm::dot(glm::normalize(optHit._normal),glm::normalize(light.position()-optHit._intersect))};
	return diffuseLight;
}


Color Renderer::calcAmbient(OptionalHit const& optHit)
{
	Color tmp{};
	for(std::map<std::string, Light>::iterator i = _scene._lights.begin(); i != _scene._lights.end(); ++i)
	{
		tmp = tmp + i->second.la();
	}
	return tmp * optHit._shape->material().ka();
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