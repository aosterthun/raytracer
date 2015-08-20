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

void Renderer::render()
{
	
	reserveColorbuffer(_scene._resolution);

	_ppm.setResolution(_scene._resolution);

	raycast();

	/*
	//some testing
	Pixel p(std::get<0>(scene._resolution)/2,std::get<1>(scene._resolution)/2);
	
	p.color = Color(1.0, 1.0, 1.0);
	write(p);
	*/

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

void Renderer::raycast()
{
	
	float distance = _scene._camera.getDistance(std::get<0>(_scene._resolution));

	Color white{1.0,1.0,1.0};
	Color black{0.0,0.0,0.0};

	//float distance{0.0};

	for (std::vector<Color>::iterator i = _colorbuffer.begin(); i != _colorbuffer.end(); ++i)
	{
		int x = (i - _colorbuffer.begin()) % std::get<0>(_scene._resolution);
		int y =	floor((i - _colorbuffer.begin()) / std::get<0>(_scene._resolution)); 

		*i = trace(_scene._camera.getEyeRay( x, y, distance));
	}
	
}

Color Renderer::trace(Ray r)
{
	for(std::map<std::string, std::shared_ptr<Shape>>::iterator i = _scene._shapes.begin(), i != _scene._shapes.end(); ++i)
	{
		i
	}

	return ;
}

Color Renderer::shade(std::shared_ptr<Shape> s, Ray r, double t)
{

	return ;
}

void Renderer::write(Pixel const& p)
{
	// flip pixels, because of opengl glDrawPixels
	size_t position = (std::get<0>(_resolution)*p.y + p.x);

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

/*
const std::size_t checkersize = 20;

for (unsigned y = 0; y < height_; ++y)
{
	for (unsigned x = 0; x < width_; ++x)
	{
		Pixel p(x,y);
		if ( ((x/checkersize)%2) != ((y/checkersize)%2))
		{
		p.color = Color(0.0, 1.0, float(x)/height_);
		}
		else
		{
		p.color = Color(1.0, 0.0, float(y)/width_);
		}

		write(p);
	}
}
ppm_.save(filename_);
*/