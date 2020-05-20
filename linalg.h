#ifndef LINALG_H
#define LINALG_H

#define PI 3.14159265359

#include<iostream>
#include<math.h>

class Mat44f {
private:
	float data[4][4] = { {1,0,0,0},
						 {0,1,0,0},
						 {0,0,1,0},
						 {0,0,0,1} };

public:
	Mat44f(float [][4]);
	Mat44f(void);
	float det();
	Mat44f inverse();
	float* operator[](int i) { return data[i]; }
	Mat44f operator* (float);
	Mat44f operator* (Mat44f);
	Mat44f& zeros();
	Mat44f& ones();
};

Mat44f::Mat44f(float d[][4]) {
	for (int i = 0; i < 4;i++) 
		for (int j = 0;j < 4;j++)
			data[i][j] = d[i][j];
}
Mat44f::Mat44f(void) {
	for (int i = 0;i < 4;i++)
		data[i][i] = 1;
}

Mat44f Mat44f :: operator*(float scale) {
	float x[4][4];
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			x[i][j] = data[i][j] * scale;
		}
	}
	Mat44f mat(x);
	return mat;
}

/*
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/

Mat44f Mat44f :: operator*(Mat44f M) {
	Mat44f mul;
	int i, j, k;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			float sum = 0;
			for (k = 0;k < 4;k++) {
				sum += M[i][k] * data[k][j];
			}
			mul[i][j] = sum;
		}
	}

	return mul;
}

float Mat44f::det() {
	float m1 = data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
		data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
		data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
	
	float m2 = data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
		data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
		data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);

	float m3 = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
		data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
		data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

	float m4 = data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
		data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
		data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

	// std :: cout << m1 << " " << m2 << " " << m3 << " " << m4 << "\n";

	float detm = (data[0][0] * m1) - (data[0][1] * m2) + (data[0][2] * m3) - (data[0][3] * m4);
	return detm;

}

Mat44f Mat44f::inverse() {
	float adj[4][4];
	float M[3][3];

	float d = det();
	if (d == 0)
		return *this;
	
	d = 1.0 / d;

	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			// Get the co-factor matrix of i,j 
			int x = 0, y = 0;
			for (int row = 0; row < 4; row++) {
				for (int coloumn = 0; coloumn < 4;coloumn++) {
					if ((i == row) || (j == coloumn)) {
						continue;
					}
					M[x][y++] = data[row][coloumn];
				}
				if (y > 0) {
					y = 0;
					x++;
				}
			}
			/*
			00 01 02
			10 11 12
			20 21 22
			*/

			float det_sub = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
				M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
				M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

			adj[j][i] = (float) pow(-1, i + j) * det_sub;
		}
	}

	Mat44f mat(adj);
	return mat * d;
}

Mat44f& Mat44f::zeros(){
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4;j++)
			data[i][j] = 0;

	return *this;
}

Mat44f& Mat44f::ones() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4;j++)
			data[i][j] = 1;
	return *this;
}

// Vector 3 Class Declaration
class Vec3f {
private:
	float point[3] = { 0,0,0 };

public:
	Vec3f(float, float, float);
	Vec3f() { point[0] = 0; };

	float operator[](int i) const { return point[i]; }
	float& operator[](int i) { return point[i]; }
	float dot(Vec3f&);
	Vec3f operator +(Vec3f);
	Vec3f operator -(Vec3f);
	Vec3f operator *(Vec3f);
	Vec3f operator *(Mat44f);
	float length_sqr(void);

	float x() const { return point[0]; };
	float y() const { return point[1]; };
	float z() const { return point[2]; };

};

Vec3f::Vec3f(float x, float y, float z) {
	point[0] = x;
	point[1] = y;
	point[2] = z;
}

float Vec3f :: dot(Vec3f& v)
{
	return v[0] + point[0] + v[1] * point[1] + v[2] * point[2];
}
float Vec3f :: length_sqr() {
	return point[0] * point[0] + point[1] * point[1] + point[2] * point[2];
}

Vec3f Vec3f :: operator+(Vec3f v)
{
	Vec3f V(v[0] + point[0], v[1] + point[1], v[2] + point[2]);
	return V;
}
Vec3f Vec3f :: operator-(Vec3f v)
{
	Vec3f V(v[0] - point[0], v[1] - point[1], v[2] - point[2]);
	return V;
}

Vec3f Vec3f :: operator*(Mat44f M) {
	float x = point[0] * M[0][0] + point[1] * M[1][0] + point[2] * M[2][0] + M[3][0];
	float y = point[0] * M[0][1] + point[1] * M[1][1] + point[2] * M[2][1] + M[3][1];
	float z = point[0] * M[0][2] + point[1] * M[1][2] + point[2] * M[2][2] + M[3][2];
	Vec3f v(x, y, z);
	return v;

}
Vec3f Vec3f :: operator*(Vec3f v)
{
	Vec3f V(v[0] * point[0], v[1] * point[1], v[2] * point[2]);
	return V;
}

std::ostream& operator<<(std::ostream& os, const Vec3f& obj)
{
	os << "<" << obj.x() << ", " << obj.y() << ", " << obj.z() << ">";
	return os;
}
/*
std::ostream& operator<<(std::ostream& os, const Vec2f& obj)
{
	os << "<" << obj.x() << ", " << obj.y() << ">";
	return os;
}

*/

// Vector 2 

class Vec2f {
	float point[2] = { 0,0};

public:
	Vec2f(float, float);
	Vec2f() { point[0] = 0; };

	float operator[](int i) const { return point[i]; }
	float& operator[](int i) { return point[i]; }
	float dot(Vec2f&);
	Vec2f operator +(Vec2f);
	Vec2f operator -(Vec2f);
	Vec2f operator *(Vec2f);
	Vec2f operator /(float);
	float length_sqr(void);

	float x() const { return point[0]; };
	float y() const { return point[1]; };
};


Vec2f::Vec2f(float x, float y) {
	point[0] = x;
	point[1] = y;
}

float Vec2f::dot(Vec2f& v)
{
	return v[0] + point[0] + v[1] * point[1];
}
float Vec2f::length_sqr() {
	return point[0] * point[0] + point[1] * point[1];
}

Vec2f Vec2f :: operator+(Vec2f v)
{
	Vec2f V(v[0] + point[0], v[1] + point[1]);
	return V;
}
Vec2f Vec2f :: operator-(Vec2f v)
{
	Vec2f V(v[0] - point[0], v[1] - point[1]);
	return V;
}
Vec2f Vec2f :: operator*(Vec2f v)
{
	Vec2f V(v[0] * point[0], v[1] * point[1]);
	return V;
}
Vec2f Vec2f :: operator/(float v) {
	Vec2f p;
	p[0] = point[0] / v;
	p[1] = point[1] / v;
	return p;
}
// General function Definations

#endif 