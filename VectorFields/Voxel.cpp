#include "Voxel.h"


Voxel::Voxel(const Vec3f& p_dims, const Vec3f& p_center, const std::vector<Vec3f>& points, const size_t& id):
	dims(p_dims), center(p_center), id(id)
{
	Update(points);
}

void Voxel::Update(const std::vector<Vec3f>& points)
{
	if (numPoints + points.size() > 2)
	{
		UpdateCovariance(points);
		UpdateNormal();
	}
}

Vec3f Voxel::getField()
{
	return field;
}

QDataStream& Voxel::save(QDataStream& out) const
{
	//Save to file (called from VoxelBox)
	out << QVector3D(center.x, center.y, center.z) << QVector3D(dims.x, dims.y, dims.z) 
		<< quint32(numPoints) << QVector3D(normal.x,normal.y,normal.z) << distance 
		<< QVector3D(field.x, field.y, field.z) << QVector3D(averagePoints.x, averagePoints.y, averagePoints.z)
		<< id << hasChildren << surfaceType << group << surfaceVariation;
	if (parent == nullptr) out << -1;
	else out << parent->id;
	for (int i = 0; i < 8; i++) {
		if (children[i] == nullptr) out << -1;
		else out << children[i]->id;
	}
	return out;
}

void Voxel::load(QDataStream& in)
{
	//Loads from file (called from VoxelBox)
	QVector3D centerQ;
	QVector3D dimsQ;
	QVector3D normalQ;
	QVector3D fieldQ;
	quint32 numPointsQ;
	double p_distance;
	in >> centerQ >> dimsQ >> numPointsQ >> normalQ >> p_distance >> fieldQ;

	center = Vec3f(centerQ.x(), centerQ.y(), centerQ.z());
	dims = Vec3f(dimsQ.x(), dimsQ.y(), dimsQ.z());
	numPoints = size_t(numPointsQ);
	normal = Vec3f(normalQ.x(), normalQ.y(), normalQ.z());
	field = Vec3f(fieldQ.x(), fieldQ.y(), fieldQ.z());
	distance = p_distance;

	QVector3D average;
	in >> average;
	averagePoints = Vec3f(average.x(), average.y(), average.z());

	in >> id >> hasChildren >> surfaceType >> group >> surfaceVariation;

	int idParent;
	in >> idParent;
	if (idParent == -1) parent = nullptr;
	else {
		if (layer > 0)
			parent = VoxelsLayers[layer - 1][idParent-1];
		else parent = root;
	}

	int idChildren;
	for (int i = 0; i < 8; i++) {
		in >> idChildren;
		if (idChildren == -1) children[i] = nullptr;
		else children[i] = VoxelsLayers[layer+1][idChildren-1];
	}
}

void Voxel::UpdateCovariance(const std::vector<Vec3f>& points)
{
	
	Vec3f sumnew(0, 0, 0);
	for (auto point = points.begin(); point != points.end(); ++point) //update average sum and points mul sum
	{
		sumPoints += point->MulTranspose();
		sumnew += *point;
	}
	averagePoints = ((averagePoints * numPoints) + sumnew) / (numPoints + points.size());

	numPoints += points.size();

	Covariance = (sumPoints / numPoints) - averagePoints.MulTranspose();
}

void Voxel::UpdateNormal()
{
	Eigen::EigenSolver<Eigen::MatrixXd> es(Covariance);
	auto values = es.eigenvalues();
	float min = std::numeric_limits<float>::infinity();
	size_t minarg = 4;
	float sum = 0;
	for (size_t i = 0; i < values.size(); i++) //find min
	{
		if (values(i).real() < min) { minarg = i; min = values(i).real(); }
		sum += values(i).real();
	}
	surfaceVariation = abs(min / sum);
	
	Eigen::MatrixXcd V = es.eigenvectors().col(minarg);
	normal = Vec3f(V(0).real(), V(1).real(), V(2).real()).normalize();

	float angle = (averagePoints - Vec3f(0)) * normal;
	if (angle > 0) normal = -normal;

	UpdateDistance();
}

void Voxel::UpdateDistance()
{
	distance = normal * (averagePoints - center);
	field = normal * distance;
}

QDataStream& operator<<(QDataStream& out, const Voxel& voxel)
{
	return voxel.save(out);
}

QDataStream& operator>>(QDataStream& in, Voxel& voxel)
{
	voxel.load(in);
	return in;
}
