#include "RayCaster.h"

void RayCaster::renderType(const size_t& x, const size_t& y, const Vec3f& Cam, Vec3f& p_dir, const Vec3f& light)
{

	float type = 0;

	std::tuple<float, float> t = entryExit(Cam, p_dir);
	if (std::get<0>(t) == -1)
		type = -1;
	else {
		levelsRen = 1;

		hit value = DDALevels(Cam, p_dir, light, std::get<0>(t), std::get<1>(t));
		Vec3f normal = value.normal;
		if (normal == Vec3f(0, 0, 0)) type = -1;
		else {
			Vec3f normalCorrected = normal;
			float intensity = (normalCorrected * light);
			intensity = -intensity * (intensity <= 0);
			float backgroundIntensity = Box->background * Box->ambientLight;
			intensity = backgroundIntensity + (1 - backgroundIntensity) * intensity; //Ambient lighting
			if (intensity >= 1) intensity = 0.99999;
			if (normalCorrected * p_dir <= 0) normalCorrected = -normalCorrected;

			if (!Box->renderSeg) {
				type = value.renderVoxel->surfaceType;
				if (normal * p_dir < 0) type = Box->inverseType[int(type)];
				type += intensity;
			}
			else {
				type = value.renderVoxel->group;
				type += intensity;
			}
		}
	}


	int index = int(type);
	float intensity = type - index;
	if (index != -1) {
		if (!Box->renderSeg) {
			QColor color = colors[colorMap[index]];
			buffer_[4 * int(y * size.x + x)] = color.blue() * intensity;
			buffer_[4 * int(y * size.x + x) + 1] = color.green() * intensity;
			buffer_[4 * int(y * size.x + x) + 2] = color.red() * intensity;
			buffer_[4 * int(y * size.x + x) + 3] = 255;
		}
		else {
			QColor color = colorNames[(index * 3) % 148];
			buffer_[4 * int(y * size.x + x)] = color.blue() * intensity;
			buffer_[4 * int(y * size.x + x) + 1] = color.green() * intensity;
			buffer_[4 * int(y * size.x + x) + 2] = color.red() * intensity;
			buffer_[4 * int(y * size.x + x) + 3] = 255;
		}
	}
	else if (alpha) {
		buffer_[4 * int(y * size.x + x) + 3] = 0;
	}
	
}

void RayCaster::render(const size_t& x, const size_t& y, const Vec3f& Cam, Vec3f& p_dir, const Vec3f& light)
{
	float res;

	std::tuple<float, float> t = entryExit(Cam, p_dir);
    if (std::get<0>(t) == -1)
        res = 2 ;
	else {

		if (Box->divisions == 1) levelsRen = 1;

		Vec3f normalCorrected = (DDALevels(Cam, p_dir, light, std::get<0>(t), std::get<1>(t))).normal;
		if (normalCorrected == Vec3f(0,0,0)) res = 2;
		else {
			if (normalCorrected * p_dir <= 0) normalCorrected = -normalCorrected;
			res = (light * normalCorrected);
			res = -res * (res <= 0);
			float backgroundIntensity = Box->background * Box->ambientLight;
			res = backgroundIntensity + (1 - backgroundIntensity) * res; //Ambient lighting
			if (res >= 1) res = 0.99999;
		}
	}

	int color = int(res * 255);
	if (color != 510) {
		buffer_[4 * int(y * size.x + x)] = color;
		buffer_[4 * int(y * size.x + x) + 1] = color;
		buffer_[4 * int(y * size.x + x) + 2] = color;
		buffer_[4 * int(y * size.x + x) + 3] = 255;
	}
	else if (alpha) {
		buffer_[4 * int(y * size.x + x) + 3] = 0;
	}
}


std::tuple<float, float> RayCaster::entryExit(const Vec3f& Cam, Vec3f& dir)
{
	char sign[3];

	sign[0] = (dir.x < 0);
	sign[1] = (dir.y < 0);
	sign[2] = (dir.z < 0);

	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	Vec3f invdir = Vec3f(1) | dir;

	tmin = (Bounds[sign[0]].x - Cam.x) * invdir.x;
	tmax = (Bounds[1 - sign[0]].x - Cam.x) * invdir.x;
	tymin = (Bounds[sign[1]].y - Cam.y) * invdir.y;
	tymax = (Bounds[1 - sign[1]].y - Cam.y) * invdir.y;

	if ((tmin > tymax) || (tymin > tmax))
		return std::make_tuple(-1,0);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	tzmin = (Bounds[sign[2]].z - Cam.z) * invdir.z;
	tzmax = (Bounds[1 - sign[2]].z - Cam.z) * invdir.z;

	if ((tmin > tzmax) || (tzmin > tmax))
		return std::make_tuple(-1, 0);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	return std::make_tuple(tmin, tmax);

}

//modified from https://www.scratchapixel.com/lessons/advanced-rendering/introduction-acceleration-structure/grid
hit RayCaster::DDALevels(const Vec3f& Cam, Vec3f& dir, const Vec3f& light, const float& tmin, const float& tmax)
{
	Vec3f min = Vec3f(Cam.x + (dir.x * tmin), Cam.y + (dir.y * tmin), Cam.z + (dir.z * tmin));
	if (tmin < 0) min = Cam;

	Vec3f invdir = Vec3f(1) | dir;
	size_t power = power2(levelsRen - 1);
	Vec3i countres = Box->getCount() / power;
	Vec3f dimsres = Box->getDims() * power;

	float t = tmin * (tmin > 0);
	Vec3f rayOrigCell(min - Bounds[0]);
	Vec3i step = Vec3i((dir.x > 0) - (dir.x < 0), (dir.y > 0) - (dir.y < 0), (dir.z > 0) - (dir.z < 0));
	Vec3f precision = Vec3f(dimsres[0] * step[0], dimsres[1] * step[1], dimsres[2] * step[2]) / 1000;
	Vec3i cell = ((rayOrigCell + precision) | dimsres).toInt();
	if (cell[0] == countres[0]) cell[0]--; //Might happen with bigger models. Prevents from crashing
	if (cell[1] == countres[1]) cell[1]--;
	if (cell[2] == countres[2]) cell[2]--;
	if (cell[0] < 0) cell[0]++;
	if (cell[1] < 0) cell[1]++;
	if (cell[2] < 0) cell[2]++;


	Vec3f deltaT = dimsres & invdir & Vec3f(step.x, step.y, step.z);
	Vec3f nextCrossingT = (Vec3f(t) + ((((Vec3f(cell.x, cell.y, cell.z) + Vec3f((step.x == 1), (step.y == 1), (step.z == 1))) & dimsres) - rayOrigCell) & invdir)).absolute();
	Vec3i exit = Vec3i(-1) + (Vec3i((step.x == 1), (step.y == 1), (step.z == 1)) & (countres + 1));


	for (int j = 1; j < levelsRen; j++) {
		if (j <= Box->divisions - Box->currentLayer)Box->layer[j] = Box->layer[j - 1];
		else Box->layer[j] = Box->layer[j - 1] / 2;
	}

	size_t o;
	uint8_t axis;

	hit res;

	while (1) {
		o = cell[0] * countres[1] * countres[2] + cell[1] * countres[2] + cell[2];

		if (Box->layer_enabled) {
			//If cross Layer display
			if (Box->Axis == 0 && cell[0] == Box->layer.at(levelsRen - 1)) { if (Box->divisions - levelsRen + 1 == Box->currentLayer) { res.normal = Vec3f(1, 0, 0); return res; } else if (Box->currentLayer > Box->divisions - levelsRen + 1) { hit temp = (Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step)); if (!(temp.normal == Vec3f(0, 0, 0))) return temp; } }
			if (Box->Axis == 1 && cell[1] == Box->layer.at(levelsRen - 1)) { if (Box->divisions - levelsRen + 1 == Box->currentLayer) { res.normal = Vec3f(0, 1, 0); return res; } else if (Box->currentLayer > Box->divisions - levelsRen + 1) { hit temp = (Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step)); if (!(temp.normal == Vec3f(0, 0, 0))) return temp; } }
			if (Box->Axis == 2 && cell[2] == Box->layer.at(levelsRen - 1)) { if (Box->divisions - levelsRen + 1 == Box->currentLayer) { res.normal = Vec3f(0, 0, 1); return res; } else if (Box->currentLayer > Box->divisions - levelsRen + 1) { hit temp = (Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step)); if (!(temp.normal == Vec3f(0, 0, 0))) return temp; }
			}
		}

		if (Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o) != nullptr) {
			if (Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o)->hasChildren) {
				res = (Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step));
				if (!(res.normal == Vec3f(0, 0, 0))) { return res; }
			}
			else {
				if ((Box->renderSeg && Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o)->surfaceType == Box->segType) || !Box->renderSeg) {
					if ((Box->renderIsolate && Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o)->group == Box->renderGroup) || !Box->renderIsolate) {
						res.normal = *Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o)->getNormal();
						res.renderVoxel = Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o);
						return res;
					}
				}
			}
		}

		if (nextCrossingT[0] <= nextCrossingT[1] && nextCrossingT[0] <= nextCrossingT[2]) axis = 0;
		else if (nextCrossingT[1] <= nextCrossingT[0] && nextCrossingT[1] <= nextCrossingT[2]) axis = 1;
		else axis = 2;


		t = nextCrossingT[axis];

		if (tmax < nextCrossingT[axis]) { res.normal = Vec3f(0, 0, 0); return res; }
		cell[axis] += step[axis];
		if (cell[axis] == exit[axis]) { res.normal = Vec3f(0, 0, 0); return res; }
		nextCrossingT[axis] += deltaT[axis];

	}
}

hit RayCaster::Walking(const size_t& invLev, const Voxel* parent, float& t, const Vec3f& Cam, Vec3f& dir, const Vec3f& light, const float& tmax, const Vec3f& precision, Vec3i& step) {
	//Recursion method for DDA. Very similar to DDALevels with stopping conditions
	size_t power = power2(invLev - 1);
	Vec3i countres = Box->getCount() / power;
	Vec3f dimsres = Box->getDims() * power;

	Vec3f invdir = Vec3f(1) | dir;
	Vec3f rayOrigCell = (Vec3f(Cam.x + (dir.x * t), Cam.y + (dir.y * t), (Cam.z + (dir.z * t))) - Bounds[0]);
	Vec3i cell = ((rayOrigCell + precision) | dimsres).toInt();
	if (cell[0] == countres[0]) cell[0]--;
	if (cell[1] == countres[1]) cell[1]--;
	if (cell[2] == countres[2]) cell[2]--;
	if (cell[0] < 0) cell[0]++;
	if (cell[1] < 0) cell[1]++;
	if (cell[2] < 0) cell[2]++;

	float nextCrossingT[3];
	float deltaT[3];
	int exit[3];


	for (int i = 0; i < 3; ++i) {
		if (dir[i] < 0) {
			nextCrossingT[i] = abs(t + ((cell[i] * dimsres[i] - rayOrigCell[i]) * invdir[i]));
			deltaT[i] = -dimsres[i] * invdir[i];
			exit[i] = cell[i] - 1 - (cell[i] % 2);
		}
		else {
			nextCrossingT[i] = abs(t + (((cell[i] + 1) * dimsres[i] - rayOrigCell[i]) * invdir[i]));
			deltaT[i] = dimsres[i] * invdir[i];
			exit[i] = cell[i] + 1 + (cell[i] % 2 == 0);
		}
	}

	size_t o;
	uint8_t axis;

	hit res;

	while (1) {

		o = cell[0] * countres[1] * countres[2] + cell[1] * countres[2] + cell[2];
		if (Box->layer_enabled) {
			if (Box->Axis == 0 && cell[0] == Box->layer[invLev - 1]) { if (Box->divisions - invLev + 1 == Box->currentLayer) { res.normal = Vec3f(1, 0, 0); return res; } else if (Box->currentLayer > Box->divisions - invLev + 1) { return Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step); } }
			if (Box->Axis == 1 && cell[1] == Box->layer[invLev - 1]) { if (Box->divisions - invLev + 1 == Box->currentLayer) { res.normal = Vec3f(0, 1, 0); return res; } else if (Box->currentLayer > Box->divisions - invLev + 1) { return Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step); } }
			if (Box->Axis == 2 && cell[2] == Box->layer[invLev - 1]) { if (Box->divisions - invLev + 1 == Box->currentLayer) { res.normal = Vec3f(0, 0, 1); return res; } else if (Box->currentLayer > Box->divisions - invLev + 1) { return Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step); } }
		}
		if (Box->VoxelsLayers.at(Box->divisions - invLev).at(o) != nullptr) {
			if (Box->VoxelsLayers.at(Box->divisions - invLev).at(o)->parent != parent) { res.normal = Vec3f(0, 0, 0); return res; }
			if (Box->VoxelsLayers.at(Box->divisions - invLev).at(o)->hasChildren) {
				res = (Walking(levelsRen - 1, Box->VoxelsLayers.at(Box->divisions - levelsRen).at(o), t, Cam, dir, light, tmax, precision, step));
				if (!(res.normal == Vec3f(0, 0, 0))) return res;
			}
			else {
				res.normal = *Box->VoxelsLayers.at(Box->divisions - invLev).at(o)->getNormal();
				return res;
			}
		}
		/*
		uint8_t k =
			((nextCrossingT[invLev - 1][0] < nextCrossingT[invLev - 1][1]) << 2) +
			((nextCrossingT[invLev - 1][0] < nextCrossingT[invLev - 1][2]) << 1) +
			((nextCrossingT[invLev - 1][1] < nextCrossingT[invLev - 1][2]));
		uint8_t axis = map[k];
		*/

		if (nextCrossingT[0] <= nextCrossingT[1] && nextCrossingT[0] <= nextCrossingT[2]) axis = 0;
		else if (nextCrossingT[1] <= nextCrossingT[0] && nextCrossingT[1] <= nextCrossingT[2]) axis = 1;
		else axis = 2;

		t = nextCrossingT[axis];

		if (tmax < nextCrossingT[axis]) { res.normal = Vec3f(0, 0, 0); return res; }
		cell[axis] += step[axis];
		if (cell[axis] == exit[axis]) { res.normal = Vec3f(0, 0, 0); return res; }
		nextCrossingT[axis] += deltaT[axis];
	}
	
}

int RayCaster::power2(const size_t& power)
{
	int r = 1;
	int n = power;
	while (n > 0) {
		r *= 2;
		--n;
	}
	return r;
}