// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

const int RECURSION_DEPTH = 30;

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

	Ray eyeRay{};

	for (unsigned y = 0; y < std::get<1>(_scene._camera.getResolution()); ++y) {
		for (unsigned x = 0; x < std::get<0>(_scene._camera.getResolution()); ++x) {

			int x_pos = x - (std::get<1>(_scene._camera.getResolution())/2);
			int y_pos = y - (std::get<0>(_scene._camera.getResolution())/2);

			Ray ray{{0.0, 0.0, 0.0}, {x_pos, y_pos, distance}};
			Pixel p(x,y);
			p.color = trace(ray,depth);
			write(p);
		}
	}
}

Color Renderer::trace(Ray r, int depth)
{	
	float distance{0.0};


	OptionalHit nearestHit{};

	for(auto shape : _scene._shapes)
	{
		//Add invMat form shape to Ray in the intersect add shape matrix to all points
		OptionalHit optHit = shape.second->intersect(r, distance);

		if(optHit._t <= nearestHit._t || nearestHit._t == 0.0)
		{
			nearestHit = optHit;
		}
	}

	return shade(nearestHit, depth);

}

Color Renderer::shade(OptionalHit hit, int depth)
{
	//if an object was hit, the following algorithm computes ambient, diffuse, specular lightning and reflection
	if(hit._hit)
	{
		Color ambient = calcAmbient(hit);

		Color diffuse, specular, reflection;

		if(depth <= RECURSION_DEPTH)
		{
			++depth;

			glm::vec3 direction = getReflectionVec(hit, hit._ray.origin);
			Ray test{hit._ray.origin,direction};

			//preventing useless recursion
			if(hit._shape->material().l() != 0.0)
			{
				reflection += hit._shape->material().l() * trace(test, depth);
			}
			if(!(reflection == Color{0}))
			{
				std::cout << "Reflection Ray direction: " << glm::to_string(hit._ray.origin) << std::endl;
				std::cout << reflection;
				std::cout << test;
			}
		}

		for(auto light : _scene._lights)
		{
			Ray lightRay{light.second.position(),getLightVec(hit,light.second)};

			//detects if the light has a "direct" view to the intersection point
			for(auto shape : _scene._shapes)
			{
				float tmpDist;
				OptionalHit inShadow = shape.second->intersect(lightRay,tmpDist);

				if(inShadow._hit && (inShadow._shape->name() == hit._shape->name()))
				{
					// calculate diffuse
					diffuse += light.second.ld()*calcDiffuse(light.second,hit);

					// calculate specular
					specular += light.second.ld()*calcSpecular(light.second,hit);

					/*
					if(hit._normal == glm::vec3{0.0, 1.0, 0.0} || hit._normal == glm::vec3{1.0, 1.0, 1.0})
					{
						std::cout << "normale: " << glm::to_string(hit._normal) << "\n intersect: " << glm::to_string(hit._intersect) << "\n";
					}*/
					/*
					//DEBUG SECTION		
					if(hit._normal == glm::vec3{ -1.0, 0.0, 0.0 })
					{
						return Color{0.0,0.0,1.0};
					}
					else if (hit._normal == glm::vec3{ 0.0, -1.0, 0.0 })
					{
						return Color{0.0,1.0,0.0};
					}
					else if (hit._normal == glm::vec3{ 0.0, 0.0, 1.0 })
					{
						return Color{0.0,1.0,1.0};
					}
					else if (hit._normal == glm::vec3{ 1.0, 0.0, 0.0 })
					{
						return Color{1.0,0.0,0.0};
					}
					else if (hit._normal == glm::vec3{ 0.0, 1.0, 0.0 })
					{
						return Color{1.0,0.0,1.0};
					}
					else if (hit._normal == glm::vec3{ 0.0, 0.0, -1.0 })
					{
						return Color{1.0,1.0,0.0};
					}
					else if (hit._normal == glm::vec3{1.0, 1.0, 1.0})
					{
						return Color{1.0, 1.0, 1.0};
					}*/
					
				}

				tmpDist = 0.0;
			}
		}

		Color shade = ambient + diffuse + specular + reflection;
		return shade;
	}
	else
	{
		return BACKGROUND_COLOR;
	}
	
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
	return diffuseLight;
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

	return specularLight;
}

glm::vec3 Renderer::getCamVec(OptionalHit const& optHit)
{
	//Vector that spans between the intersected object and the camera
	glm::vec3 camVec{optHit._intersect-_scene._camera.position()};
	return camVec;
}

//Shadow compution
glm::vec3 Renderer::getLightVec(OptionalHit const& optHit, Light const& light)
{
	//Vector that spans between the intersected object
	glm::vec3 lightVec{optHit._intersect - light.position()};
	return lightVec;
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