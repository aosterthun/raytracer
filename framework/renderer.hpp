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
#include "optionalhit.hpp"

#include <memory>
#include <string>
#include <glm/glm.hpp>

//floor()
#include <math.h> 

class Renderer
{
public:

	Renderer();

	Renderer(Scene const& scene);
	
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

	std::string getPercentage(int counter) const;

	void reserveColorbuffer(std::tuple<int,int> const& resolution);

	void raycast();

	Color trace(Ray r);

	Color shade(OptionalHit hit);

	Color calcAmbient();
	Color calcSpecular(Light const& light, OptionalHit const& optHit);
	Color Renderer::calcDeffuse();
	glm::vec3 Renderer::getCamVec(OptionalHit const& optHit);
	glm::vec3 Renderer::getLightVec(OptionalHit const& optHit, Light const& light);
	glm::vec3 Renderer::getLightReflectionVec(OptionalHit const& optHit, Light const& light);
};

#endif // #ifndef BUW_RENDERER_HPP
