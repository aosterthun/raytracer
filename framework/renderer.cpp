// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

const int RECURSION_DEPTH = 50;

const float SHADOW_BIAS = 0.9;

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

	_ppm.save(_scene._renderFilename);
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

	int depth = 0;

	for (unsigned y = 0; y < std::get<1>(_scene._camera.getResolution()); ++y)
	{
		for (unsigned x = 0; x < std::get<0>(_scene._camera.getResolution()); ++x)
		{
			Ray cameraRay{_scene._camera.getCameraRay(x, y, distance)};
			Pixel p(x,y);
			p.color = trace(cameraRay,depth);
			write(p);
		}
	}
}

Color Renderer::trace(Ray const& r, int depth)
{	
	float distance{0.0};

	OptionalHit nearestHit{};

	for(auto shape : _scene._shapes)
	{
		//Add invMat from shape to Ray in the intersect add shape matrix to all points
		OptionalHit optHit = shape.second->intersect(r, distance);

		//computes the nearest, interecting object. The: "|| nearestHit._t == 0.0" is for the first loop
		if(optHit._t <= nearestHit._t || nearestHit._t == 0.0)
		{
			nearestHit = optHit;
		}
	}

	//if an object was hit, the following algorithm computes the color values of the pixel/intersected object
	if(nearestHit._hit)
	{
		return shade(nearestHit, depth);
	}
	else
	{
		//if the object wasn't hit, the predefined background color is the return value
		return BACKGROUND_COLOR;
	}
}

Color Renderer::shade(OptionalHit hit, int depth)
{
	float shade = 1.0f;

	Color whole, diffuse, specular, reflection, refraction;

	/*
		Algorithm for diffuse and specular lightning:
		- loops through all given lights
		- computes a ray from the light position to the intersection point
			- loops through all shapes and computes if there is another object between thelight and original object
			- computes the shadow value if neccessary
			- adds um the diffuse and specular values
	*/
	for(auto light : _scene._lights)
	{
		//ray from intersection point to light position
		glm::vec3 direction1 = hit._intersect - light.second.position();
		glm::vec3 direction2 =  light.second.position() - hit._intersect;

		//Ray lightRay{direction, direction1};
		Ray lightRay{hit._intersect, direction2};


		float tmpDist = INFINITY;


		for(auto shapeComposite : _scene._shapes)
		{
			//shape composite intersect() returns the closest object
			OptionalHit otherShape = shapeComposite.second->intersect(lightRay,tmpDist);

			if(otherShape._hit && (otherShape._shape->name() != hit._shape->name()))
			{
				shade -= SHADOW_BIAS;
				if(shade < 0.0)
				{
					shade = 0.0f;
				}
			}

			// calculate diffuse
			diffuse += calcDiffuse(light.second, hit);

			// calculate specular
			specular += calcSpecular(light.second, hit);
		}

		if(depth <= RECURSION_DEPTH)
		{
		//increment the depth
		++depth;

		//calculate reflectation
		if(hit._shape->material().l() != 0.0)
		{
		glm::vec3 camVec = glm::normalize(hit._ray.direction);
		glm::vec3 N = glm::normalize(hit._normal);
		glm::vec3 R = camVec - (2.0f* glm::dot(camVec, N) * N);
		reflection += hit._shape->material().l() * trace(Ray{hit._intersect+ R, R}, depth);
		}

		//calculate refraction
		float refr = hit._shape->material().r();

		if (refr > 0)
		{
		glm::vec3 incomingVec = glm::normalize(hit._intersect-hit._ray.origin);
		glm::vec3 hitNormal = glm::normalize(hit._normal);

		glm::vec3 refractionVec = (1/refr)*((incomingVec-hitNormal)*glm::dot(incomingVec,hitNormal))-hitNormal*(float)sqrt(1-((1*1)*(1-(glm::dot(incomingVec,hitNormal)*glm::dot(incomingVec,hitNormal))/(refr*refr))));
		refraction = hit._shape->material().r() * trace(Ray{hit._intersect+ refractionVec, refractionVec}, depth);
		}
		}
	}
	//the ambient color gets added to every pixel
	Color ambient = calcAmbient(hit);

	//whole = ambient;
	//whole = diffuse;
	//whole = specular;

	whole = ambient + shade * (diffuse + specular);
	//+ reflection + refraction);

	return whole;
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

Color Renderer::calcDiffuse(Light const& light, OptionalHit const& optHit)
{
	Color kd = optHit._shape->material().kd();
	double angle = glm::dot(glm::normalize(optHit._normal), glm::normalize(light.position()-optHit._intersect));
	Color diffuseLight = kd * std::max(angle, 0.0);
	return light.ld() * diffuseLight;
}

Color Renderer::calcSpecular(Light const& light, OptionalHit const& optHit)
{
	//specific material value for specular light
	Color ks = optHit._shape->material().ks();

	//reflectation value
	float m = optHit._shape->material().m();

	//vector from intersection -> camera position
	glm::vec3 camVec = glm::normalize(_scene._camera.position() - optHit._intersect);

	//reflection vector of light position -> intersection
	glm::vec3 lightReflectionVec = glm::normalize(getReflectionVec(optHit, light.position()));

	double angle = glm::dot( lightReflectionVec, camVec);

	double value = std::pow(angle, m);

	Color specularLight = ks * std::max(value, 0.0);

	return light.ld() * specularLight;

	/*
	if(glm::dot(optHit._normal,glm::normalize(light.position() - optHit._intersect)))
	{
		//specific material value for specular light
		Color ks = optHit._shape->material().ks();

		//reflectation value
		float m = optHit._shape->material().m();

		//vector from intersection -> camera position
		glm::vec3 camVec = glm::normalize(optHit._intersect -_scene._camera.position());

		//glm::vec3 camVec = glm::normalize(_scene._camera.position() - optHit._intersect);

		//reflection vector of light position -> intersection
		glm::vec3 lightReflectionVec = glm::normalize(getReflectionVec(optHit, light.position()));

		double angle = glm::dot(lightReflectionVec, camVec);

		double value = std::pow(angle, m);

		Color specularLight = ks * std::max(value, 0.0);

		return light.ld() * specularLight;
	}
	

	Color spec{};

	glm::vec3 camVec = glm::normalize(optHit._normal - _scene._camera.position());

	glm::vec3 lightVec = glm::normalize(optHit._intersect - light.position());

	double angle = glm::dot(lightVec, camVec);
	if(angle < 0)
	{
		double value = std::abs(std::pow(angle, optHit._shape->material().m()));

		Color ks = optHit._shape->material().ks();

		spec = light.ld() * ks * std::max(value, 0.0);
	}
	return spec;
	*/
}

glm::vec3 Renderer::getCamVec(OptionalHit const& optHit)
{
	//Vector that spans between the intersected object and the camera
	glm::vec3 camVec{optHit._intersect-_scene._camera.position()};
	return camVec;
}

//takes the optionalHit and the origin of the position of the incoming vectors
glm::vec3 Renderer::getReflectionVec(OptionalHit const& optHit, glm::vec3 const& origin)
{
	//Calculates the reflection vector of the given light

	//vector needs to point intersect -> origin to compute the angle correctly
	glm::vec3 incomingVec =  glm::normalize(origin - optHit._intersect);

	glm::vec3 normal = glm::normalize(optHit._normal);

	double vecAngle = glm::dot(normal, incomingVec);

	vecAngle = std::max(vecAngle, 0.0);
	
	return { 2*vecAngle*normal.x - incomingVec.x, 2*vecAngle*normal.y - incomingVec.y, 2*vecAngle*normal.z - incomingVec.z};
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