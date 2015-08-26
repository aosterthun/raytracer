// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{

	//default-constructor
	Color() : r(0.0), g(0.0), b(0.0) {}

	Color(float val) : r(val), g(val), b(val) {}

	Color(Color const& col) : r(col.r), g(col.g), b(col.b) {}

	Color(float red, float green, float blue) : r(red), g(green), b(blue) {}

	//variables
	float r;
	float g;
	float b;

	friend std::ostream& operator<<(std::ostream& os, Color const& c)
	{
		os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
		return os;
	}

	Color& operator+=(Color const& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}

	Color& operator-=(Color const& other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		return *this;
	}

	Color& operator*=(Color const& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}

	/*
	Color& operator*=(float val)
	{
		r *= val;
		g *= val;
		b *= val;
		return *this;
	}
	*/
	bool operator==(Color const& other)
	{
		if( r == other.r &&
			g == other.g &&
			b == other.b)
		{
			return true;
		}
		return false;
	}

	/*
	friend Color operator*(Color const& a,float val)
	{
		auto tmp(a);
		tmp *= val;
		return tmp;
	}
	*/

	friend Color operator+(Color const& a, Color const& b)
	{
		auto tmp(a);
		tmp += b;
		return tmp;
	}

	friend Color operator-(Color const& a, Color const& b)
	{
		auto tmp(a);
		tmp -= b;
		return tmp;
	}

	friend Color operator*(Color const& a, Color const& b)
	{
		auto tmp(a);
		tmp *= b;
		return tmp;
	}
	};

#endif //#define BUW_COLOR_HPP
