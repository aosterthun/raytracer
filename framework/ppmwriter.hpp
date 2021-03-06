// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andre Schollmeyer and Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// PpmWriter
// -----------------------------------------------------------------------------

#ifndef BUW_PPMWRITER_HPP
#define BUW_PPMWRITER_HPP

// header, system
#include <string>
#include <vector>

// header, project
#include <pixel.hpp>

class PpmWriter
{
public:
	PpmWriter();
	PpmWriter(std::size_t w, std::size_t h, std::string const& file);
	PpmWriter(std::size_t w, std::size_t h);

	void write(Pixel const& p);
	void save(std::string const& file);
	void save();
	void setResolution(std::tuple<int,int> const& resolution);
	void setFilename(std::string const& file);

private:
	std::string file_;
	std::vector<unsigned int> data_;
	size_t width_;
	size_t height_;
};

#endif // BUW_PPMWRITER
