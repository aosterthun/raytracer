// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

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

	_ppm.save("test");
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

Color Renderer::shade(OptionalHit hit)
{
	Color backgroundColor{0.0, 0.0, 0.0};
	Color testColor{ 1.0, 1.0, 1.0};

	if(hit._hit)
	{
		Color ambient = getAmbient() + hit._shape->material().ka();
		Color diffuse;
		return ambient + diffuse;
		//return hit._shape->material().ka();
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