#pragma once
#include "Util.h"

#include <QVector3D>
#include <QDataStream>
#include <limits>

class Voxel
{
public:
	Voxel() {}
	Voxel(const size_t& id): id(id) {}
	Voxel(const Vec3f& p_dims, const Vec3f& p_center, const std::vector<Vec3f>& points, const size_t& id);
	void Update(const std::vector<Vec3f>& points); //Update the Voxel info with new points
	void UpdateDistance();
	Vec3f getField();
	Vec3f* getNormal() { return &normal; };
	
	size_t getNumPoints() const { return numPoints; };
	float getSurfaceVariation() const { return surfaceVariation; };
	QDataStream& save(QDataStream& out) const;
	void load(QDataStream& in);

	Vec3f center;
	Vec3f normal = Vec3f(0, 0, 0);
	float distance = 0; //distance from center to the average of points
	size_t id;
	Voxel* parent = nullptr; //Parent and childrens used in octree structures
	std::vector<Voxel*> children = std::vector<Voxel*>(8, nullptr);
	bool hasChildren = false;
	Vec3f averagePoints = Vec3f(0, 0, 0);
	int surfaceType = 0;
	int group = -1;

	//To load data
	size_t layer;
	Voxel* root;
	std::vector<std::vector<Voxel*>> VoxelsLayers;

	

private:
	void UpdateCovariance(const std::vector<Vec3f>& points);
	void UpdateNormal();
	

	
	Vec3f dims;
	size_t numPoints = 0;
	
	float surfaceVariation = 0 ;
	Eigen::MatrixXd sumPoints = Eigen::MatrixXd::Zero(3, 3);
	Eigen::MatrixXd Covariance = Eigen::MatrixXd::Zero(3, 3);
	
	
	Vec3f field = Vec3f(0, 0, 0);
};

QDataStream& operator<<(QDataStream& out, const Voxel& voxel); //Used to save file
QDataStream& operator>>(QDataStream& in, Voxel& voxel); //Used to Open file

