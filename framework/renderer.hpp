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

#include <memory>
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:

	Renderer(unsigned w, unsigned h, std::string const& file);

	void render();
	void write(Pixel const& p);

	void raycast(std::vector<Color> &colorbuffer, Camera &camera);

	inline std::vector<Color> const& colorbuffer() const
	{
		return colorbuffer_;
	}

private:

	unsigned width_;
	unsigned height_;
	std::vector<Color> colorbuffer_;
	std::string filename_;
	PpmWriter ppm_;

	Color trace(Ray r);

	Color shade(std::shared_ptr<Shape> s, Ray r, double t);
};

#endif // #ifndef BUW_RENDERER_HPP
