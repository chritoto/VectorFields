#pragma once
struct float3 { float x, y, z; };
#include <Eigen/Eigenvalues>
#include <math.h>
#include <ostream>

template <typename T>

class Vec3
{
public:
	T x = 0;
	T y = 0;
	T z = 0;
	T* val[3] = { &x,&y,&z };

public:
	Vec3() {}
	Vec3(const T& px, const T& py, const T& pz)
		:
		x(px), y(py), z(pz)
	{}
	Vec3(const T& value)
		:
		x(value), y(value), z(value)
	{}
	Vec3(const float3& data)
		:
		Vec3(data.x, data.y, data.z)
	{}

	Vec3(const Vec3& rhs)
		:
		Vec3(rhs.x, rhs.y, rhs.z)
	{}

	Vec3	operator-() const
	{
		return Vec3(-x, -y, -z);
	}
	Vec3& operator=(const Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	Vec3& operator+=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	Vec3	operator-(const Vec3& rhs) const
	{
		return Vec3(*this) -= rhs;
	}
	Vec3	operator+(const Vec3& rhs) const
	{
		return Vec3(*this) += rhs;
	}
	T		operator*(const Vec3& rhs) const //DOT PRODUCT
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vec3 operator%(const Vec3& rhs) const //CROSS PRODUCT
	{
		return Vec3(y * rhs.z - rhs.y * z, -(x * rhs.z - rhs.x * z), x * rhs.y - rhs.x * y);
	}
	bool operator==(const Vec3& rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	T&		operator[](const size_t& i)
	{
		return *val[i];
	}
	Vec3& operator*=(const T& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	Vec3	operator*(const T& rhs) const
	{
		return Vec3(*this) *= rhs;
	}
	Vec3& operator/=(const T& rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	Vec3	operator/(const T& rhs) const
	{
		return Vec3(*this) /= rhs;
	}
	Vec3	operator|(const Vec3& rhs) //to divide element wise
	{
		Vec3 temp = Vec3(*this);
		temp.x /= rhs.x;
		temp.y /= rhs.y;
		temp.z /= rhs.z;
		return temp;
	}
	Vec3	operator&(const Vec3& rhs) //to multiply element wise
	{
		Vec3 temp = Vec3(*this);
		temp.x *= rhs.x;
		temp.y *= rhs.y;
		temp.z *= rhs.z;
		return temp;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vec3& rhs)
	{
		os << rhs.x << ' ' << rhs.y << ' ' << rhs.z;
		return os;
	}
	Eigen::MatrixXd	MulTranspose() const
	{
		Eigen::MatrixXd m(3, 3);
		m(0, 0) = x * x;
		m(0, 1) = x * y;
		m(0, 2) = x * z;
		m(1, 0) = y * x;
		m(1, 1) = y * y;
		m(1, 2) = y * z;
		m(2, 0) = z * x;
		m(2, 1) = z * y;
		m(2, 2) = z * z;
		return m;
	}
	Vec3 Mul(Eigen::MatrixXd A) const
	{
		return Vec3(x * A(0, 0) + y*A(0,1)+z*A(0,2),
			x * A(1, 0) + y * A(1, 1) + z * A(1, 2),
			x * A(2, 0) + y * A(2, 1) + z * A(2, 2));
	}
	T norm() const
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	Vec3 normalize() const
	{
		return Vec3(*this) / norm();
	}
	Vec3 inv() const
	{
		return Vec3(*this) / pow(norm(), 2);
	}
	Vec3<int> toInt() const
	{
		return Vec3<int>(int(x), int(y), int(z));
	}
	Vec3& absolute()
	{
		x = abs(x);
		y = abs(y);
		z = abs(z);
		return *this;
	}
};


typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<int> Vec3i;
