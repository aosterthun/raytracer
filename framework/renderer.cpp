// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
	/*
	//NOTE: MIGHT BE OUTSIDE
	SDFloader loader{};
	loader.readSdf(filename_);

	//retrieving the scene from the loader
	Scene scene = loader.scene();
	//////////////////////////////////////////

	raycast(colorbuffer_, scene.camera);

	Pixel p(300,300);
	p.color = Color(1.0, 1.0, 1.0);
	write(p);

	ppm_.save(filename_);
	
	*/
}

void Renderer::raycast(std::vector<Color> &colorbuffer, Camera &camera)
{
	/*
	float distance = camera.getDistance(width_);
	for(auto pixel : colorbuffer)
	{
		pixel = trace(camera.getEyeRay( (pixel.x)-960, (pixel.y)-960, distance));
	}
	*/
}


Color Renderer::trace(Ray r)
{

	return ;
}

Color Renderer::shade(std::shared_ptr<Shape> s, Ray r, double t)
{

	return ;
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
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