#pragma once
#include "Util.h"

class PointCloud
{
public:
	PointCloud() {}
	PointCloud(const std::string& filepath);
	void read_ply_file(const std::string& filepath);
	void read_stl_file(const std::string& filepath);
	int shift_to_origin(); //Bring centroid to the origin
	std::vector<Vec3f> getBounds();
	void Rectify(); //Rotate the points on the principal axis of variation
	void WhiteSpace(const Vec3f& p_dims); //Adds a margin around the points for the marching cubes algorithm

	size_t numVertices = 0;
	std::vector<Vec3f> points;

private:
	float min_x = 0;
	float min_y = 0;
	float min_z = 0;
	float max_x = 0;
	float max_y = 0;
	float max_z = 0;
	float average_x = 0;
	float average_y = 0;
	float average_z = 0;
	float absMax_x = 0;
	float absMax_y = 0;
	float absMax_z = 0;
};

