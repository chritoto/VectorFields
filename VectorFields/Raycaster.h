#pragma once
#include "VoxelBox.h"

#include <tuple>
#include <qthread.h>
#include <QColor>

struct hit {
	Vec3f normal;
	Voxel* renderVoxel;
};

class RayCaster
{
public:
	RayCaster() {}
	RayCaster(VoxelBox* p_Box, unsigned char buffer[], const Vec3f& p_size, QColor colors[], size_t colormap[]) : Box(p_Box), buffer_(buffer), size(p_size), colors(colors), colorMap(colormap) {
		Bounds = Box->getBounds();
		levelsRen = Box->levelsRen;
	}
	~RayCaster() {}
	void renderType(const size_t& x, const size_t& y, const Vec3f& Cam, Vec3f& p_dir, const Vec3f& light);
	void render(const size_t& x, const size_t& y, const Vec3f& Cam, Vec3f& p_dir, const Vec3f& light);

	bool alpha = false;

private:

	std::tuple<float, float> entryExit(const Vec3f& Cam, Vec3f& dir); //Checks if ray falls within bounds
	hit DDALevels(const Vec3f& Cam, Vec3f& p_dir, const Vec3f& light, const float& tmin, const float& tmax); //Travels voxels
	hit Walking(const size_t& invLev, const Voxel* parent, float& t, const Vec3f& Cam, Vec3f& dir, const Vec3f& light, const float& tmax, const Vec3f& precision, Vec3i& step);
	int power2(const size_t& power); //computes the power of 2


	VoxelBox* Box;
	unsigned char* buffer_;
	std::vector<Vec3f> Bounds;
	Vec3f size;

	size_t levelsRen = 2; //For octrees

	QColor* colors;
	size_t* colorMap;
	QStringList colorNames = colors[0].colorNames();
	
};

