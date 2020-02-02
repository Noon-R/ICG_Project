#pragma once

typedef struct Vec3{
	double x, y, z;

	const Vec3 operator+(const Vec3& value) {
		Vec3 ret;
		ret.x = this->x + value.x;
		ret.y = this->y + value.y;
		ret.z = this->z + value.z;
		return ret;
	}

	const Vec3 operator*(double value) {
		
		Vec3 ret = {
			this->x * value,
			this->y * value,
			this->z * value
		};

		return ret;
	}

	Vec3& operator+=(const Vec3& value) {
		this->x += value.x;
		this->y += value.y;
		this->z += value.z;

		return *this;
	}

}Vec3;

typedef struct {
	double x, y, z, w;
}Vec4;