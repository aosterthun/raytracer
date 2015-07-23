#ifndef BUW_SDFFILE_HPP
#define BUW_SDFFILE_HPP

class SDFFile
{
	public:
		Scene loadScene() const;
	protected:
		std::map<Shape> getShapes;

}

#endif