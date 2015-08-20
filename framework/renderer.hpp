// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "sdfloader.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include <memory>
#include <string>
#include <glm/glm.hpp>

//floor()
#include <math.h> 

class Renderer
{
public:

	Renderer();

	void render();

	//void render();

	void write(Pixel const& p);

	void setScene(Scene const& scene);

	inline std::vector<Color> const& colorbuffer() const
	{
		return _colorbuffer;
	}

private:

	//variables
	std::tuple<int,int> _resolution;

	std::vector<Color> _colorbuffer;

	PpmWriter _ppm;

	Scene _scene;

	//methods

	void reserveColorbuffer(std::tuple<int,int> const& resolution);

	void raycast();

	Color trace(Ray r);

	Color shade(std::shared_ptr<Shape> s, Ray r, double t);

};

#endif // #ifndef BUW_RENDERER_HPP
