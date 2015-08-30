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

//#include <glm/gtc/swizzle.hpp>
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

	Color trace(Ray r, int depth);

	Color shade(OptionalHit hit, int depth);

	Color calcAmbient(OptionalHit const& optHit);
	Color calcSpecular(Light const& light, OptionalHit const& optHit);
	Color calcDiffuse(Light const& light, OptionalHit const& optHit);
	glm::vec3 getCamVec(OptionalHit const& optHit);
	glm::vec3 getLightVec(OptionalHit const& optHit, Light const& light);
	glm::vec3 getReflectionVec(OptionalHit const& optHit, glm::vec3 const& origin);
	glm::vec3 getCamReflectionVec(OptionalHit const& optHit, Camera const& cam);

};

#endif // #ifndef BUW_RENDERER_HPP
