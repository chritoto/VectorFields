#include "VoxelBox.h"

VoxelBox::VoxelBox(PointCloud& p_Points,const int& p_min, const Vec3f& p_dims, const bool& p_count, QProgressDialog* p_progressBar)
{
	QLabel* label = new QLabel();
	p_progressBar->setValue(30);
	label->setText("Preparing Voxels parameters");
	p_progressBar->setLabel(label);
	Bounds[0] = p_Points.getBounds()[0];
	Bounds[1] = p_Points.getBounds()[1];
	minPoints = p_min;
	if (p_count)
	{
		count = Vec3i(int(p_dims.x), int(p_dims.y), int(p_dims.z));
		setDims();
	}
	else
	{
		dims = p_dims;
		setCount();
	}

	p_Points.WhiteSpace(dims);
	root = new Voxel(0);

	setCenters();
	p_progressBar->setValue(70);
	label->setText("Initializing voxels");
	p_progressBar->setLabel(label);
	initializeVoxels(p_Points);
	closestPoints();
	p_progressBar->setValue(90);
	label->setText("Setting surface types");
	p_progressBar->setLabel(label);
	setSurfaceType();
	p_progressBar->close();
}

VoxelBox::VoxelBox(PointCloud& p_Points,const int& p_min, const size_t& p_divisions, const double& p_surfaceThreshold, QProgressDialog* p_progressBar)
{
	QLabel* label = new QLabel();
	p_progressBar->setValue(30);
	label->setText("Preparing Voxels parameters");
	p_progressBar->setLabel(label);
	surfaceThreshold = p_surfaceThreshold;
	Bounds[0] = p_Points.getBounds()[0];
	Bounds[1] = p_Points.getBounds()[1];
	minPoints = p_min;

	divisions = p_divisions;
	VoxelsLayers.resize(p_divisions);
	for (int i = 0; i < p_divisions; i++) {
		VoxelsLayers[i].resize(pow(8, i+1), nullptr);
	}
	
	count = Vec3i(pow(2, divisions), pow(2, divisions), pow(2, divisions)); //smallest count
	setDims();
	p_Points.WhiteSpace(dims);

	root = new Voxel(0);

	p_progressBar->setValue(70);
	label->setText("Initializing voxels");
	p_progressBar->setLabel(label);
	initializeVoxels(p_Points.points, 0, Bounds[1]-Bounds[0], Bounds[0], Vec3f(0,0,0), root);
	closestPoints();
	p_progressBar->setValue(90);
	label->setText("Setting surface types");
	p_progressBar->setLabel(label);
	setSurfaceType();
	p_progressBar->close();
}

VoxelBox::~VoxelBox()
{
	for (auto layer = VoxelsLayers.begin(); layer != VoxelsLayers.end(); ++layer)
	{
		for (auto voxel = layer->begin(); voxel != layer->end(); ++voxel)
		{
			if (*voxel != nullptr) delete *voxel;
		}
	}
}

float VoxelBox::getMaxBound(const int& axis)
{
	float max = 0;
	if (axis == 1 || axis == 0) {
		if (abs(Bounds[0].x) > max) max = abs(Bounds[0].x);
		if (abs(Bounds[1].x) > max) max = abs(Bounds[1].x);
	}
	if (axis == 2 || axis == 0) {
		if (abs(Bounds[0].y) > max) max = abs(Bounds[0].y);
		if (abs(Bounds[1].y) > max) max = abs(Bounds[1].y);
	}
	if (axis == 3 || axis == 0) {
		if (abs(Bounds[0].z) > max) max = abs(Bounds[0].z);
		if (abs(Bounds[1].z) > max) max = abs(Bounds[1].z);
	}
	return max;
}

size_t VoxelBox::getMaxNum()
{
	size_t maxNum = 0;
	for (auto voxel = VoxelsLayers[currentLayer-1].begin(); voxel != VoxelsLayers[currentLayer-1].end(); ++voxel)
	{
		if(*voxel != nullptr) {
			if ((*voxel)->getNumPoints() > maxNum) maxNum = (*voxel)->getNumPoints();
		}
	}
	return maxNum;
}

float VoxelBox::getMaxVariaton()
{
	float maxNum = 0;
	for (auto voxel = VoxelsLayers[currentLayer - 1].begin(); voxel != VoxelsLayers[currentLayer - 1].end(); ++voxel)
	{
		if (*voxel != nullptr) {
			if ((*voxel)->getSurfaceVariation() > maxNum) maxNum = (*voxel)->getSurfaceVariation();
		}
	}
	return maxNum;
}


void VoxelBox::setCount()
{
	Vec3f range = Bounds[1] - Bounds[0];
	//x
	count.x = std::ceil(range.x / dims.x);
	//y
	count.y = std::ceil(range.y / dims.y);
	//z
	count.z = std::ceil(range.z / dims.z);
}

void VoxelBox::setDims()
{
	Vec3f range = Bounds[1] - Bounds[0] + Vec3f(0.001,0.001,0.001);
	//x
	dims.x = range.x / (float)count.x;
	//y
	dims.y = range.y / (float)count.y;
	//z
	dims.z = range.z / (float)count.z;
}

void VoxelBox::setCenters()
{
	Centers.resize(count.x * count.y * count.z);
	for (size_t i = 0; i < count.x; i++)
	{
		for (size_t j = 0; j < count.y; j++)
		{
			for (size_t k = 0; k < count.z; k++)
			{
				Centers[i * count.y * count.z + j * count.z + k] = Vec3f((i + 0.5) * dims.x, (j + 0.5) * dims.y, (k + 0.5) * dims.z)+Bounds[0];
			}
		}
	}
}

size_t VoxelBox::indexFromPoint(const Vec3f& point)
{
	size_t xvoxel = int((point.x - Bounds[0].x) / dims.x);
	size_t yvoxel = int((point.y - Bounds[0].y) / dims.y);
	size_t zvoxel = int((point.z - Bounds[0].z) / dims.z);

	return xvoxel * count.y * count.z + yvoxel * count.z + zvoxel;
}

void VoxelBox::initializeVoxels(const PointCloud& p_Points)
{
	std::vector<std::vector<Vec3f>> Points;
	Points.resize(count.x * count.y * count.z);
	for (auto point = p_Points.points.begin(); point != p_Points.points.end(); ++point)
	{
		Points[indexFromPoint(*point)].push_back(*point);
	}
	VoxelsLayers[0].resize(count.x * count.y * count.z);
	for (size_t i = 0; i < count.x * count.y * count.z; i++)
	{
		if (Points[i].size() < minPoints) VoxelsLayers[0][i] = nullptr;
		else VoxelsLayers[0][i] = new Voxel(dims, Centers[i], Points[i], i+1);
	}
}

void VoxelBox::initializeVoxels(const std::vector<Vec3f>& p_Points, const size_t& p_divisions, const Vec3f& p_dims, const Vec3f& p_origin, const Vec3f& p_voxOrig, Voxel* p_parent)
{
	size_t id = 1;
	std::vector<std::vector<Vec3f>> Points;
	Points.resize(8);
	for (auto point = p_Points.begin(); point != p_Points.end(); ++point)
	{
		size_t x = int((point->x - p_origin.x) / (p_dims.x/2 + 0.0001) ); //0.0001 for numerical imprecisions
		size_t y = int((point->y - p_origin.y) / (p_dims.y/2 + 0.0001) );
		size_t z = int((point->z - p_origin.z) / (p_dims.z/2 + 0.0001) );
		Points[x * 4 + y * 2 + z].push_back(*point);
	}
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			for (size_t k = 0; k < 2; k++)
			{
				if (Points[i*4+j*2+k].size() > minPoints-1) {
					Vec3f Center = Vec3f(p_dims.x/2 * i + p_dims.x / 4 + p_origin.x,
										p_dims.y/2 * j + p_dims.y / 4 + p_origin.y,
										p_dims.z/2 * k + p_dims.z / 4 + p_origin.z);
					count = Vec3i(pow(2, p_divisions+1), pow(2, p_divisions+1), pow(2, p_divisions+1));
					id++;
					Voxel* voxelPres = new Voxel(dims/2, Center, Points[i * 4 + j * 2 + k], (i + p_voxOrig.x) * count.y * count.z + (j + p_voxOrig.y) * count.z + (k + p_voxOrig.z)+1);
					VoxelsLayers[p_divisions][(i + p_voxOrig.x) * count.y * count.z + (j + p_voxOrig.y) * count.z + (k + p_voxOrig.z)] = voxelPres;

					p_parent->children[i * 4 + j * 2 + k] = voxelPres;
					p_parent->hasChildren = true;
					voxelPres->parent = p_parent;

					if (p_divisions < divisions - 1) {
						if (voxelPres->getSurfaceVariation() > surfaceThreshold)
							initializeVoxels(Points[i * 4 + j * 2 + k], p_divisions + 1, p_dims / 2,
								Vec3f(p_dims.x * i / 2 + p_origin.x,
									p_dims.y * j / 2 + p_origin.y,
									p_dims.z * k / 2 + p_origin.z), Vec3f((p_voxOrig.x + i) * 2, (p_voxOrig.y + j) * 2, (p_voxOrig.z + k) * 2),
								voxelPres);
					}
				}
			}
		}
	}
}

void VoxelBox::closestPoints()
{
	//Determine closest point for empty voxels arround non-empty
	EmptyVoxelClosestPoint.resize( count.x * count.y * count.z, 0);
	for (size_t x = 0; x < count.x; x++) {
		for (size_t y = 0; y < count.y; y++) {
			for (size_t z = 0; z < count.z; z++) {
				if (VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z] == nullptr) {
					for (int dx = -1; dx < 2; dx++) { //Iterate over neighbours
						for (int dy = -1; dy < 2; dy++) {
							for (int dz = -1; dz < 2; dz++) {
								if ((x + dx) >= 0 && (x + dx) < count.x && (y + dy) >= 0 && (y + dy) < count.y && (z + dz) >= 0 && (z + dz) < count.z) {
									if (VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)] != nullptr) {
										//float distance = VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->normal * (VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->averagePoints - Centers[x * count.y * count.z + y * count.z + z]);
										//if (abs(distance) < EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] || EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] == 0)EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] = distance;
										float distance = (VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->averagePoints - Centers[x * count.y * count.z + y * count.z + z]).norm();
										if (((VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->averagePoints - Centers[x * count.y * count.z + y * count.z + z]) * VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->normal) > 0) distance = -distance;
										if (abs(distance) < EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] || EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] == 0)EmptyVoxelClosestPoint[x * count.y * count.z + y * count.z + z] = distance;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void VoxelBox::setSurfaceType()
{
	float R = (1 / planarThresh) * getMaxBound();
	float averageDim = (dims[0] + dims[1] + dims[2]) / 3;
	float threshold = R - sqrt(R * R - averageDim * averageDim);
	for (size_t x = 0; x < count.x; x++)
	{
		for (size_t y = 0; y < count.y; y++)
		{
			for (size_t z = 0; z < count.z; z++)
			{
				if (VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z] != nullptr)
				{
					
					int signs[3] = { 0,0,0 };
					Vec3f C0 = VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->center + VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->getField();
					Vec3f voxelNormal = *VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->getNormal();
					for (int deltax = -1; deltax < 2; deltax++)
					{
						for (int deltay = -1; deltay < 2; deltay++)
						{
							for (int deltaz = -1; deltaz < 2; deltaz++)
							{
								int nx = x + deltax;
								int ny = y + deltay;
								int nz = z + deltaz;
								if (nx >= 0 && nx < count.x && ny >= 0 && ny < count.y && nz >= 0 && nz < count.z)
								{
									
									if (!(deltax == 0 && deltay == 0 && deltaz == 0))
									{
										if (VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz] != nullptr)
										{
											
											float distance = (VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]->center+ VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]-> getField()- C0) * voxelNormal;
											
											if (distance < -threshold) signs[0]++;
											else if (distance > threshold) signs[2]++;
											else signs[1]++;
											
										}
									}
								}
							}
						}
					}
					int maxVoxels = signs[0];
					if (signs[1] > maxVoxels)maxVoxels = signs[1];
					if (signs[2] > maxVoxels)maxVoxels = signs[2];

					if (signs[0] * 2 < maxVoxels)signs[0] = 0;
					if (signs[1] * 2 < maxVoxels)signs[1] = 0;
					if (signs[2] * 2 < maxVoxels)signs[2] = 0;

					if (signs[0] > 0 && signs[1] > 0 & signs[2] > 0) {
						if (signs[0] < signs[1] && signs[0] < signs[2]) signs[0] = 0;
						else if (signs[1] < signs[0] && signs[1] < signs[2]) signs[1] = 0;
						else signs[2] = 0;
					}
					uint8_t k =
						((signs[0] > 0) << 2) +
						((signs[1] > 0) << 1) +
						((signs[2] > 0));
					
					VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType = k;\
				}
			}
		}
	}

	//Surface Segmentation
	for (size_t x = 0; x < count.x; x++)
	{
		for (size_t y = 0; y < count.y; y++)
		{
			for (size_t z = 0; z < count.z; z++)
			{
				if (VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z] != nullptr)
				{
					if (VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group == -1)
					{
						VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group = groups[VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType]; //Set group
						
						groupsVoxels[VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType].resize(VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group + 1);
						groupsVoxels[VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType][VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group].push_back(VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]);

						std::vector<Vec3i> Vecs = std::vector<Vec3i>(1, Vec3i(x, y, z));
						setGroupNeighbours(Vecs);

						groups[VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType]++; //Add one to the number of groups
						
					}
				}
			}
		}
	}
}


void VoxelBox::setGroupNeighbours(std::vector<Vec3i>& vec)
{
	std::vector<Vec3i> newVec;
	//iterate over each neighbour
	for (auto i = vec.begin(); i != vec.end(); ++i)
	{
		int x = i->x;
		int y = i->y;
		int z = i->z;
		for (int deltax = -1; deltax < 2; deltax++)
		{
			for (int deltay = -1; deltay < 2; deltay++)
			{
				for (int deltaz = -1; deltaz < 2; deltaz++)
				{
					int nx = x + deltax;
					int ny = y + deltay;
					int nz = z + deltaz;
					if (nx >= 0 && nx < count.x && ny >= 0 && ny < count.y && nz >= 0 && nz < count.z)
					{
						if (!(deltax == 0 && deltay == 0 && deltaz == 0))
						{
							if (VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz] != nullptr)
							{
								if (VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]->surfaceType == VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->surfaceType)
								{
									if (VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]->group == -1)
									{
										VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]->group = VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group;
										newVec.push_back(Vec3i(nx, ny, nz)); //append to list of neighbour to visit
										groupsVoxels[VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]->surfaceType][VoxelsLayers[divisions - 1][x * count.y * count.z + y * count.z + z]->group].push_back(VoxelsLayers[divisions - 1][nx * count.y * count.z + ny * count.z + nz]);//Add Voxel to the corresponding vector of Voxels of group
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(newVec.size()>0) setGroupNeighbours(newVec);

}

// Based on the implementation by Mohammad Rouhani, Morpheo Team, INRIA Rhone Alpes
// https://www.mathworks.com/matlabcentral/fileexchange/44654-surface-reconstruction-using-implicit-b-splines
void VoxelBox::BSpline(const int& N, const float& r, const float& R, const float& step)
{
	progressBar = new QProgressDialog();
	QLabel* label = new QLabel();
	progressBar->setMinimumDuration(0);
	progressBar->setRange(0, 100);
	progressBar->setCancelButton(false);
	progressBar->setWindowModality(Qt::WindowModal);
	QCoreApplication::processEvents();

	int type = 0;
	QString types[7] = { "","peak","planar","ridge","pit","saddle","valley" };

	std::vector< Eigen::Tensor<float, 3>> Ps;
	std::vector<std::vector<Vec3f>> points;

	float offset = r;

	for(auto groupType = groupsVoxels.begin();groupType!= groupsVoxels.end();++groupType){
		if (type > 0 && type < 7) {
			int num = 0;
			for (auto group = groupType->begin(); group != groupType->end(); ++group) {
				if (group->size() > 16) {

					progressBar->setValue(0);
					num++;
					label->setText("computing B-Spline " + types[type] + "  " + QString::number(num) + "/" + QString::number(groupType->size()));
					progressBar->setLabel(label);
					std::vector<float> x;
					std::vector<float> y;
					std::vector<float> z;

					std::vector<float> xplus;
					std::vector<float> yplus;
					std::vector<float> zplus;

					std::vector<float> xminus;
					std::vector<float> yminus;
					std::vector<float> zminus;

					Vec3f boundsGroup[2] = { Vec3f(1,1,1),Vec3f(0,0,0) };


					std::vector<Vec3f> sectionPoints;

					//Set points, outside points and inside points
					for (auto voxel = group->begin(); voxel != group->end(); ++voxel) {
						if (*voxel != nullptr) {
							Vec3f point = (*voxel)->averagePoints;
							//point = (point - Bounds[0]) / (2 * getMaxBound() * (1 + r)) + Vec3f(r); //normalize to be in a unit cube
							point = (point - Bounds[0]);
							point.x = point.x / (2 * getMaxBound(1) * (1 + offset)) + offset;
							point.y = point.y / (2 * getMaxBound(2) * (1 + offset)) + offset;
							point.z = point.z / (2 * getMaxBound(3) * (1 + offset)) + offset;
							x.push_back(point.x);
							if (point.x < boundsGroup[0].x)boundsGroup[0].x = point.x;
							if (point.x > boundsGroup[1].x)boundsGroup[1].x = point.x;
							y.push_back(point.y);
							if (point.y < boundsGroup[0].y)boundsGroup[0].y = point.y;
							if (point.y > boundsGroup[1].y)boundsGroup[1].y = point.y;
							z.push_back(point.z);
							if (point.z < boundsGroup[0].z)boundsGroup[0].z = point.z;
							if (point.z > boundsGroup[1].z)boundsGroup[1].z = point.z;

							sectionPoints.push_back(Vec3f(point.x, point.y, point.z));

							Vec3f pointplus = point + ((*voxel)->normal * r);
							xplus.push_back(pointplus.x);
							yplus.push_back(pointplus.y);
							zplus.push_back(pointplus.z);

							Vec3f pointminus = point - ((*voxel)->normal * r);
							xminus.push_back(pointminus.x);
							yminus.push_back(pointminus.y);
							zminus.push_back(pointminus.z);
						}
					}

					points.push_back(sectionPoints);

					Eigen::Tensor<float, 3> P(N, N, N);

					iteration = 0; //For ProgressBar
					Eigen::SparseMatrix<double> M0 = MMatrix(P, x, y, z);
					iteration++;
					Eigen::SparseMatrix<double> M1 = MMatrix(P, xminus, yminus, zminus);
					iteration++;
					Eigen::SparseMatrix<double> M2 = MMatrix(P, xplus, yplus, zplus);


					Eigen::SparseMatrix<double> M(M0.rows() + M1.rows() + M2.rows(), M0.cols()); //Stack M0,M1,M2
					M.reserve(M0.nonZeros() + M1.nonZeros() + M2.nonZeros());
					for (Eigen::Index c = 0; c < M0.cols(); ++c)
					{
						progressBar->setValue(int(70 + int(c) / (float)M0.cols() * 10));
						M.startVec(c); // Important: Must be called once for each column before inserting!
						for (Eigen::SparseMatrix<double>::InnerIterator it0(M0, c); it0; ++it0)
							M.insertBack(it0.row(), c) = it0.value();
						for (Eigen::SparseMatrix<double>::InnerIterator it1(M1, c); it1; ++it1)
							M.insertBack(it1.row() + M0.rows(), c) = it1.value();
						for (Eigen::SparseMatrix<double>::InnerIterator it2(M2, c); it2; ++it2)
							M.insertBack(it2.row() + M0.rows() + M1.rows(), c) = it2.value();
					}
					M.finalize();


					//Set expected values
					int n = x.size();
					Eigen::VectorXd b = Eigen::VectorXd::Zero(n * 3);
					b.segment(n, n) = Eigen::VectorXd::Constant(n, 1);
					b.tail(n) = Eigen::VectorXd::Constant(n, -1);

					Eigen::SparseMatrix<double> A = M.transpose() * M;
					for (size_t i = 0; i < pow(N, 3); i++) {
						A.coeffRef(i, i) += 1;
					}
					A.makeCompressed();
					progressBar->setValue(85);
					Eigen::LeastSquaresConjugateGradient<Eigen::SparseMatrix<double>> solver(A);
					//Eigen::SparseQR <Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int> > solver(A);

					Eigen::VectorXd bb = M.transpose() * b;

					Eigen::VectorXd vP = solver.solve(bb);
					progressBar->setValue(90);

					for (int l = 0; l < pow(N, 3); l++) {
						int ind = l;
						int i = int((ind) / (N * N));
						ind = ind - (i)*N * N;
						int j = int((ind) / N);
						int k = ind - (j)*N;
						P(i, j, k) = vP(l);
					}


					//Display
					//isoSurface(P, r, step, boundsGroup,x,y,z);
					Ps.push_back(P);
					
				}
			}
		}
		type++;
	}

	label->setText("Rendering");
	progressBar->setValue(90);
	QCoreApplication::processEvents();

	isoSurfaceBlended(Ps, r, step, points, R);

	

	progressBar->close();
}


// Based on the implementation by Mohammad Rouhani, Morpheo Team, INRIA Rhone Alpes
// https://www.mathworks.com/matlabcentral/fileexchange/44654-surface-reconstruction-using-implicit-b-splines
Eigen::SparseMatrix<double> VoxelBox::MMatrix( Eigen::Tensor<float, 3>& P, std::vector<float>& px, std::vector<float>& py, std::vector<float>& pz)
{
	x = px;
	y = py;
	z = pz;
	size_t n = x.size();
	size_t N = P.dimension(0);

	M = Eigen::SparseMatrix<double, Eigen::RowMajor>(n,pow(N, 3));
	M.reserve(Eigen::VectorXi::Constant(n,100));

	//MMatrixWorker(0, n, N, P);

	 //Semi-successful threading test
	int numWorkers = 6;
	int numPointsPerWorkers = n / numWorkers;
	if (numPointsPerWorkers == 0)numPointsPerWorkers = 1;

	std::vector<QFuture<void>> future;
	for (size_t i = 0; i < n; i+= numPointsPerWorkers)
	{
		int numPoints = numPointsPerWorkers;
		if (i + numPointsPerWorkers >= n) numPoints = n - i-1;
		progressBar->setValue(int(10 + (i* numPointsPerWorkers + n * iteration) / (float)(3 * n) * 60));
		future.push_back(QtConcurrent::run(this, &VoxelBox::MMatrixWorker, i, numPoints,N));
	}
	for (auto fut = future.begin(); fut != future.end(); ++fut) fut->waitForFinished(); //Wait all threads done

	return M;
}

void VoxelBox::MMatrixWorker(const size_t& i, const int& numPointsPerWorkers, const size_t& N) {
	for (int o = i; o < (i+ numPointsPerWorkers); o++) {
		//progressBar->setValue(int(10 + (j + x.size() * iteration) / (float)(3 * x.size()) * 60)); //comment out if multi-thread
		float stepX = 1 / float(N - 3);
		float stepY = 1 / float(N - 3);
		float stepZ = 1 / float(N - 3);

		int i = floor(x[o] / stepX);
		int j = floor(y[o] / stepY);
		int k = floor(z[o] / stepZ);
		float u = x[o] / stepX - i;
		float v = y[o] / stepY - j;
		float w = z[o] / stepZ - k;

		Eigen::MatrixXd B(4, 4);
		B << -1, 3, -3, 1,
			3, -6, 3, 0,
			-3, 0, 3, 0,
			1, 4, 1, 0;
		B = B / 6;
		Eigen::RowVector4d bu(pow(u, 3), pow(u, 2), u, 1);
		bu = bu * B;
		Eigen::RowVector4d bv(pow(v, 3), pow(v, 2), v, 1);
		bv = bv * B;
		Eigen::RowVector4d bw(pow(w, 3), pow(w, 2), w, 1);
		bw = bw * B;
		int h = 0;
		for (int ii = 0; ii < 4; ii++) {
			for (int jj = 0; jj < 4; jj++) {
				for (int kk = 0; kk < 4; kk++) {
					if (((i + ii >= 0) && (j + jj >= 0) && (k + kk >= 0)) && ((i + ii < N) && (j + jj < N) && (k + kk < N))) {
						int new_index = N * N * (i + ii) + N * (j + jj) + k + kk;
						float value = bu.coeff(ii) * bv.coeff(jj) * bw.coeff(kk);
						
						mutex.lock();
						M.coeffRef(o,new_index) = value;
						mutex.unlock();
						h++;
					}
				}
			}
		}
		
	}
}

float VoxelBox::Spline3D(const Eigen::Tensor<float, 3>& P, const float& x, const float& y, const float& z)
{
	size_t N = P.dimension(1);
	float stepX = 1 / float(N - 3); 
	float stepY = 1 / float(N - 3); 
	float stepZ = 1 / float(N - 3);

	int i = floor(x / stepX);
	int j = floor(y / stepY);
	int k = floor(z / stepZ);
	float u = x / stepX - i;
	float v = y / stepY - j;
	float w = z / stepZ - k;

	float f = 0; 

	Eigen::MatrixXd B(4, 4); 
	B << -1, 3, -3, 1,
		3, -6, 3, 0, 
		-3, 0, 3, 0,
		1, 4, 1, 0;
	B = B / 6;
	Eigen::RowVector4d bu(pow(u, 3), pow(u, 2), u, 1);
	bu = bu * B;
	Eigen::RowVector4d bv(pow(v, 3), pow(v, 2), v, 1);
	bv = bv * B;
	Eigen::RowVector4d bw(pow(w, 3), pow(w, 2), w, 1);
	bw = bw * B;

	
	for (int ii = 0; ii < 4; ii++) {
		for (int jj = 0; jj < 4; jj++) {
			for (int kk = 0; kk < 4; kk++) {
				if (((i + ii >= 0) && (j + jj >= 0) && (k + kk >= 0))&&((i + ii < N) && (j + jj < N) && (k + kk < N))) {
					f += P.coeff(i + ii, j + jj, k + kk) * bu.coeff(ii) * bv.coeff(jj) * bw.coeff(kk);
				}
			}
		}
	}
	return f;
}

void VoxelBox::MarchingCubes()
{
	normalsMesh.resize(0);
	indicesMesh.resize(0);

	for (size_t x = 0; x < count.x-1; x++) {
		for (size_t y = 0; y < count.y-1; y++) {
			for (size_t z = 0; z < count.z-1; z++) { 
				//For each cube
				int cubeindex = 0;
				int vertice[2][2][2] = { {{0,4},{3,7}},{{1,5},{2,6}} };
				float values[2][2][2];
				bool surface = false;

				for (size_t dx = 0; dx < 2; dx++) {
					for (size_t dy = 0; dy < 2; dy++) {
						for (size_t dz = 0; dz < 2; dz++) {
							//For each voxel
							float value = 0;
							if (VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)] != nullptr) {
								surface = true;
								//value = VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->distance;
								value = (VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->averagePoints - VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->center).norm();
								if (((VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->averagePoints - VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->center) * VoxelsLayers[divisions - 1][(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)]->normal) > 0) value = -value;
							}
							else {
								value = EmptyVoxelClosestPoint[(x + dx) * count.y * count.z + (y + dy) * count.z + (z + dz)];
								/*
								for (size_t ddx = 0; ddx < 2; ddx++) {
									for (size_t ddy = 0; ddy < 2; ddy++) {
										for (size_t ddz = 0; ddz < 2; ddz++) {
											if (VoxelsLayers[divisions - 1][(x + ddx) * count.y * count.z + (y + ddy) * count.z + (z + ddz)] != nullptr) {
												float distance = VoxelsLayers[divisions - 1][(x + ddx) * count.y * count.z + (y + ddy) * count.z + (z + ddz)]->normal * (VoxelsLayers[divisions - 1][(x + ddx) * count.y * count.z + (y + ddy) * count.z + (z + ddz)]->averagePoints - Centers[(x+dx) * count.y * count.z + (y+dy) * count.z + (z+dz)]);
												if (abs(distance) < value || value == 0)value = distance;
											}
										}
									}
								}
								*/
								
							}
							values[dx][dy][dz] = value;
							
							if (value > 0) cubeindex |= 1 << vertice[dx][dy][dz];
						}
					}
				}
				int index = 0;
				if (surface) {
					while (triTable[cubeindex][index] != -1) {
						std::vector<Vec3f> indicesTriangle = std::vector<Vec3f>(0);
						for (int i = 0; i < 3; i++) {
							Vec3i corner1 = edgeTable[triTable[cubeindex][index]][0];
							Vec3i corner2 = edgeTable[triTable[cubeindex][index]][1];
							Vec3f center1 = Centers[(x + corner1.x) * count.y * count.z + (y + corner1.y) * count.z + (z + corner1.z)];
							Vec3f center2 = Centers[(x + corner2.x) * count.y * count.z + (y + corner2.y) * count.z + (z + corner2.z)];
							float u = abs(values[corner1.x][corner1.y][corner1.z]) / abs(values[corner1.x][corner1.y][corner1.z] - values[corner2.x][corner2.y][corner2.z]);
							Vec3f point = center1 * (1-u) + center2 * (u);
							indicesTriangle.push_back(point);
							index++;
						}
						indicesMesh.push_back(indicesTriangle);
						Vec3f normalTriangle = (indicesTriangle[1] - indicesTriangle[0]) % (indicesTriangle[2] - indicesTriangle[0]);
						normalsMesh.push_back(normalTriangle);
					}
				}
			}
		}
	}
}

void VoxelBox::isoSurface(const Eigen::Tensor<float, 3>& P, const float& r, const float& step, Vec3f* boundsGroup, const std::vector<float>& px, const std::vector<float>& py, const std::vector<float>& pz) //MarchingCubes for B-Spline OBSOLETE, use blended variation
{
	normalsSpline.resize(0);
	indicesSpline.resize(0);

	for (float x = boundsGroup[0].x; x < boundsGroup[1].x; x += step) {
		for (float y = boundsGroup[0].y; y < boundsGroup[1].y; y += step) {
			for (float z = boundsGroup[0].z; z < boundsGroup[1].z; z += step) {
				//For each cube
				int cubeindex = 0;
				bool surface = true;
				int vertice[2][2][2] = { {{0,4},{3,7}},{{1,5},{2,6}} };
				float values[2][2][2];

				for (size_t dx = 0; dx < 2; dx++) {
					for (size_t dy = 0; dy < 2; dy++) {
						for (size_t dz = 0; dz < 2; dz++) {
							//For each voxel
							float value = Spline3D(P, x + dx * step, y + dy * step, z + dz * step);
							values[dx][dy][dz] = value;
							if (value == 0) surface = false;
							if (value >= 0) cubeindex |= 1 << vertice[dx][dy][dz];
						}
					}
				}
				if (surface) {
					bool close = false;
					for (int i = 0; i < px.size(); i++) {
						if ((Vec3f(px[i], py[i], pz[i]) - Vec3f(x, y, z)).norm() < (1 / (float)count.x)) close = true;
					}
					close = true;
					if (close) {
						int index = 0;
						while (triTable[cubeindex][index] != -1) {
							std::vector<Vec3f> indicesTriangle = std::vector<Vec3f>(0);
							for (int i = 0; i < 3; i++) {
								Vec3i corner1 = edgeTable[triTable[cubeindex][index]][0];
								Vec3i corner2 = edgeTable[triTable[cubeindex][index]][1];
								Vec3f center1 = Vec3f(x + corner1.x * step, y + corner1.y * step, z + corner1.z * step);
								Vec3f center2 = Vec3f(x + corner2.x * step, y + corner2.y * step, z + corner2.z * step);
								float u = abs(values[corner1.x][corner1.y][corner1.z]) / abs(values[corner1.x][corner1.y][corner1.z] - values[corner2.x][corner2.y][corner2.z]);
								Vec3f point = center1 * (1 - u) + center2 * (u);
								point.x = (point.x-r) * 2 * getMaxBound(1) * (1 + r);
								point.y = (point.y-r) * 2 * getMaxBound(2) * (1 + r);
								point.z = (point.z-r) * 2 * getMaxBound(3) * (1 + r);
								point += Bounds[0];
								indicesTriangle.push_back(point);
								index++;
							}
							indicesSpline.push_back(indicesTriangle);
							Vec3f normalTriangle = (indicesTriangle[1] - indicesTriangle[0]) % (indicesTriangle[2] - indicesTriangle[0]);
							normalsSpline.push_back(normalTriangle);
						}
					}
				}
			}
		}
	}
}

void VoxelBox::isoSurfaceBlended(const std::vector<Eigen::Tensor<float, 3>>& Ps, const float& r, const float& step, const std::vector<std::vector<Vec3f>>& points, const float& R) //MarchingCubes for B-Spline with BLENDING
{
	normalsSpline.resize(0);
	indicesSpline.resize(0);

	float radius = R/(float)count.x;
	int countSteps = int(1 / step);
	std::vector<std::vector<float>> sectionsMaps(points.size(), std::vector<float>(pow(countSteps, 3))); //maps of points affected by each section
	
	for (int i = 0; i < points.size(); i++) { //for each section
		for (int j = 0; j < points[i].size(); j++) {//for each point
			for (float y = -radius; y <= radius; y += step)
				for (float x = -radius; x <= radius; x += step)
					for (float z = -radius; z <= radius; z += step)
						if (x * x + y * y + z * z <= radius * radius)
							if ((points[i][j].x + x) >= 0 && (points[i][j].x + x) < 1-step && (points[i][j].y + y) >= 0 && (points[i][j].y + y) < 1 - step && (points[i][j].z + z) >= 0 && (points[i][j].z + z) < 1 - step) {
								float val = exp(-(x * x + y * y + z * z) / (0.25 * radius * radius))*10;
								if(val > sectionsMaps[i][int((points[i][j].x + x) * countSteps) * countSteps * countSteps + int((points[i][j].y + y) * countSteps) * countSteps + int((points[i][j].z + z) * countSteps)])
									sectionsMaps[i][int((points[i][j].x + x) * countSteps) * countSteps * countSteps + int((points[i][j].y + y) * countSteps) * countSteps + int((points[i][j].z + z) * countSteps)] = val;
							}
		}
	}

	std::vector<float> scalarField(pow(countSteps, 3),0);//Scalar field
	for (float x = 0; x <= (1); x += step) {
		for (float y = 0; y <= (1); y += step) {
			for (float z = 0; z <= (1); z += step) {
				std::vector<int> closeSurfaces;
				std::vector<float> multipliers;
				for (int section = 0; section < sectionsMaps.size(); section++) {
					if (sectionsMaps[section][int(x * countSteps) * countSteps * countSteps + int(y * countSteps) * countSteps + int(z * countSteps)] > 0) {
						closeSurfaces.push_back(section);
						multipliers.push_back(sectionsMaps[section][int(x * countSteps) * countSteps * countSteps + int(y * countSteps) * countSteps + int(z * countSteps)]);
					}
				}
				float xLim = x;
				float yLim = y;
				float zLim = z;
				if (x == 1) xLim = 0.99999;
				if (y == 1) yLim = 0.99999;
				if (z == 1) zLim = 0.99999;
				if (x == 0) xLim = 0.00001;
				if (y == 0) yLim = 0.00001;
				if (z == 0) zLim = 0.00001;
				if (closeSurfaces.size() >= 0) {
					Eigen::Tensor<float, 3> Psum(Ps[0].dimension(0), Ps[0].dimension(1), Ps[0].dimension(2));
					Psum.setZero();
					float sumMultipliers = 0;
					for (int i = 0; i < closeSurfaces.size(); i++) {
						Psum += Ps[closeSurfaces[i]] * multipliers[i];
						sumMultipliers += multipliers[i];
					}
					/*
					for (auto section = closeSurfaces.begin(); section != closeSurfaces.end(); ++section) {
						Psum += Ps[*section] * multipliers[*section];
						sumMultipliers += multipliers[*section];
					}*/
					Psum = Psum / sumMultipliers;
					scalarField[int(x*countSteps) * countSteps * countSteps + int(y*countSteps) * countSteps + int(z*countSteps)] = Spline3D(Psum, xLim, yLim, zLim);
				}
				else
					scalarField[int(x * countSteps) * countSteps * countSteps + int(y * countSteps) * countSteps + int(z * countSteps)] = 0;
				
			}
		}
	}

	float offset = r;

	for (float x = 0; x < (1- step * 0.5); x += step) {
		for (float y = 0; y < (1- step * 0.5); y += step) {
			for (float z = 0; z < (1- step * 0.5); z += step) {
				//For each cube
				int cubeindex = 0;
				bool surface = true;
				int vertice[2][2][2] = { {{0,4},{3,7}},{{1,5},{2,6}} };
				float values[2][2][2];
				
				for (size_t dx = 0; dx < 2; dx++) {
					for (size_t dy = 0; dy < 2; dy++) {
						for (size_t dz = 0; dz < 2; dz++) {
							float value = scalarField[int((x + dx * step)*countSteps) * countSteps * countSteps + int((y + dy * step)*countSteps) * countSteps + int((z + dz * step)*countSteps)];
							values[dx][dy][dz] = value;
							if (value == 0) surface = false;
							if (value > 0) cubeindex |= 1 << vertice[dx][dy][dz];
						}
					}
				}
				if (surface) {
					int index = 0;
					while (triTable[cubeindex][index] != -1) {
						std::vector<Vec3f> indicesTriangle = std::vector<Vec3f>(0);
						for (int i = 0; i < 3; i++) {
							Vec3i corner1 = edgeTable[triTable[cubeindex][index]][0];
							Vec3i corner2 = edgeTable[triTable[cubeindex][index]][1];
							Vec3f center1 = Vec3f(x + corner1.x * step, y + corner1.y * step, z + corner1.z * step);
							Vec3f center2 = Vec3f(x + corner2.x * step, y + corner2.y * step, z + corner2.z * step);
							float u = abs(values[corner1.x][corner1.y][corner1.z]) / abs(values[corner1.x][corner1.y][corner1.z] - values[corner2.x][corner2.y][corner2.z]);
							Vec3f point = center1 * (1 - u) + center2 * (u);
							point.x = (point.x- offset) * 2 * getMaxBound(1) * (1 + offset);
							point.y = (point.y- offset) * 2 * getMaxBound(2) * (1 + offset);
							point.z = (point.z- offset) * 2 * getMaxBound(3) * (1 + offset);
							point += Bounds[0];
							indicesTriangle.push_back(point);
							index++;
						}
						indicesSpline.push_back(indicesTriangle);
						Vec3f normalTriangle = (indicesTriangle[1] - indicesTriangle[0]) % (indicesTriangle[2] - indicesTriangle[0]);
						normalsSpline.push_back(normalTriangle);
					}
				}
			}
		}
	}
}

void VoxelBox::SaveOBJ(const QString& Filename, unsigned char ptype)
{
	std::stringstream vertices;
	std::stringstream faces;
	int verticeCount = 1;

	if (ptype == 0) {
		for (int i = 0; i < indicesMesh.size(); i++) {
			faces << "f";
			for (int j = 0; j < 3; j++) {
				vertices << "v " + std::to_string(indicesMesh[i][j].x) + " " + std::to_string(indicesMesh[i][j].y) + " " + std::to_string(indicesMesh[i][j].z) + "\n";
				faces << " " + std::to_string(verticeCount);
				verticeCount++;
			}
			faces << "\n";
		}
	}
	else if (ptype == 1) {
		for (int i = 0; i < indicesSpline.size(); i++) {
			faces << "f";
			for (int j = 0; j < 3; j++) {
				vertices << "v " + std::to_string(indicesSpline[i][j].x) + " " + std::to_string(indicesSpline[i][j].y) + " " + std::to_string(indicesSpline[i][j].z) + "\n";
				faces << " " + std::to_string(verticeCount);
				verticeCount++;
			}
			faces << "\n";
		}
	}
	std::ofstream obj;
	obj.open(Filename.toUtf8().constData());
	obj << vertices.rdbuf();
	obj << faces.rdbuf();
	obj.close();
}

QDataStream& VoxelBox::saveFile(QDataStream& out) const
{
	out << background << divisions << planarThresh << surfaceThreshold << QVector3D(count.x, count.y, count.z) << QVector3D(dims.x, dims.y, dims.z);
	for (size_t i = 0; i < count.x * count.y * count.z; i++)
	{
		out << QVector3D(Centers[i].x, Centers[i].y, Centers[i].z);
	}
	out << *root;
	for (auto layer = VoxelsLayers.begin(); layer != VoxelsLayers.end(); ++layer)
	{
		out << layer->size();
		for (auto voxel = layer->begin(); voxel != layer->end(); ++voxel)
		{
			bool isNull = (*voxel == nullptr);
			out << isNull;
			if (!isNull) {
				out << *(*voxel);
			}
		}
	}
	for (size_t i = 0; i < 7; i++) out << groups[i];
	out << QVector3D(Bounds[0].x, Bounds[0].y, Bounds[0].z) << QVector3D(Bounds[1].x, Bounds[1].y, Bounds[1].z);
	return out;
}

QDataStream& VoxelBox::loadFile(QDataStream& in)
{
	QVector3D countQ;
	QVector3D dimsQ;
	QVector3D centersQ;
	QVector3D boundsQ;

	in >> background >> divisions >> planarThresh >> surfaceThreshold >> countQ >> dimsQ;
	count = Vec3i(countQ.x(), countQ.y(), countQ.z());
	dims = Vec3f(dimsQ.x(), dimsQ.y(), dimsQ.z());

	Centers.resize(count.x * count.y * count.z);
	for (int i = 0; i < count.x * count.y * count.z; i++)
	{
		in >> centersQ;
		Centers[i] = Vec3f(centersQ.x(), centersQ.y(), centersQ.z());
	}
	Voxel* root = new Voxel;
	in >> *root;
	VoxelsLayers.resize(divisions);
	for (int i = 0; i < divisions; i++) {
		size_t num;
		in >> num;
		VoxelsLayers[i].resize(num);
		for (size_t j = 0; j < num; j++) {
			bool isNull;
			in >> isNull;
			if (isNull) VoxelsLayers[i][j] = nullptr;
			else {
				Voxel* voxel = new Voxel;
				voxel->layer = i;
				voxel->root = root;
				voxel->VoxelsLayers = VoxelsLayers;
				in >> *voxel;
				VoxelsLayers[i][j] = voxel;
			}
		}
	}

	for (size_t i = 0; i < 7; i++) in >> groups[i];
	in >> boundsQ;
	Bounds[0] = Vec3f(boundsQ.x(), boundsQ.y(), boundsQ.z());
	in >> boundsQ;
	Bounds[1] = Vec3f(boundsQ.x(), boundsQ.y(), boundsQ.z());
	return in;
}

QDataStream& operator<<(QDataStream& out, const VoxelBox& voxels)
{
	return voxels.saveFile(out);
}

QDataStream& operator>>(QDataStream& in, VoxelBox& voxels)
{
	voxels.loadFile(in);
	return in;
}
