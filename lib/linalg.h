#pragma once

#define PI 3.14159265359

#include<iostream>
#include<math.h>


template <typename T>
class Mat44 {
private:
	T data[4][4] = { {1,0,0,0},
					 {0,1,0,0},
					 {0,0,1,0},
					 {0,0,0,1}};

public:
	Mat44(T[][4]);
	Mat44(void);
	T det();
	Mat44 inverse();
	T* operator[](int i) { return data[i]; }
	Mat44 operator* (T);
	Mat44 operator* (Mat44);
	Mat44& zeros();
	Mat44& ones();
};

template <typename T>
Mat44<T>::Mat44(T d[][4]) {
	for (int i = 0; i < 4;i++) 
		for (int j = 0;j < 4;j++)
			data[i][j] = d[i][j];
}
template <typename T>
Mat44<T>::Mat44(void) {
	for (int i = 0;i < 4;i++)
		data[i][i] = 1;
}

template <typename T>
Mat44<T> Mat44<T> :: operator*(T scale) {
	T x[4][4];
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			x[i][j] = data[i][j] * scale;
		}
	}
	Mat44 mat(x);
	return mat;
}

template <typename T>
Mat44<T> Mat44<T> :: operator*(Mat44<T> M) {
	Mat44 mul;
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

template <typename T>
T Mat44<T>::det() {
	T m1 = data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
		data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
		data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]);
	
	T m2 = data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
		data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
		data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]);

	T m3 = data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
		data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
		data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

	T m4 = data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
		data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
		data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]);

	// std :: cout << m1 << " " << m2 << " " << m3 << " " << m4 << "\n";

	T detm = (data[0][0] * m1) - (data[0][1] * m2) + (data[0][2] * m3) - (data[0][3] * m4);
	return detm;

}
template <typename T>
Mat44<T> Mat44<T>::inverse() {
	T adj[4][4];
	T M[3][3];

	T d = det();
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

			T det_sub = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
				M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
				M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

			adj[j][i] = (T) pow(-1, i + j) * det_sub;
		}
	}

	Mat44 mat(adj);
	return mat * d;
}

template <typename T>
Mat44<T>& Mat44<T>::zeros(){
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4;j++)
			data[i][j] = 0;

	return *this;
}

template <typename T>
Mat44<T>& Mat44<T>::ones() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4;j++)
			data[i][j] = 1;
	return *this;
}

// Vector 3 Class Declaration
template <typename T>
class Vec3 {
private:
	T point[3] = { 0,0,0 };

public:
	Vec3(T, T, T);
	Vec3() { point[0] = 0; };

	T operator[](int i) const { return point[i]; }
	T& operator[](int i) { return point[i]; }
	T dot(Vec3&);
	Vec3<T> operator +(Vec3<T>);
	Vec3<T> operator -(Vec3<T>);
	Vec3<T> operator *(Vec3<T>);
	Vec3<T> operator *(Mat44<T>);
	T length_sqr(void);

	T x() const { return point[0]; };
	T y() const { return point[1]; };
	T z() const { return point[2]; };

};

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) {
	point[0] = x;
	point[1] = y;
	point[2] = z;
}

template <typename T>
T Vec3<T> :: dot(Vec3<T>& v)
{
	return v[0] + point[0] + v[1] * point[1] + v[2] * point[2];
}
template <typename T>
T Vec3<T> :: length_sqr() {
	return point[0] * point[0] + point[1] * point[1] + point[2] * point[2];
}

template <typename T>
Vec3<T> Vec3<T> :: operator+(Vec3 v)
{
	Vec3 V(v[0] + point[0], v[1] + point[1], v[2] + point[2]);
	return V;
}

template <typename T>
Vec3<T> Vec3<T> :: operator-(Vec3 v)
{
	Vec3 V(v[0] - point[0], v[1] - point[1], v[2] - point[2]);
	return V;
}

template <typename T>
Vec3<T> Vec3<T> :: operator*(Mat44<T> M) {
	T x = point[0] * M[0][0] + point[1] * M[1][0] + point[2] * M[2][0] + M[3][0];
	T y = point[0] * M[0][1] + point[1] * M[1][1] + point[2] * M[2][1] + M[3][1];
	T z = point[0] * M[0][2] + point[1] * M[1][2] + point[2] * M[2][2] + M[3][2];
	Vec3 v(x, y, z);
	return v;

}


template <typename T>
Vec3<T> Vec3<T> :: operator*(Vec3 v)
{
	Vec3 V(v[0] * point[0], v[1] * point[1], v[2] * point[2]);
	return V;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& obj)
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

template <typename T>
class Vec2 {
	T point[2] = { 0,0};

public:
	Vec2(T, T);
	Vec2() { point[0] = 0; };

	T operator[](int i) const { return point[i]; }
	T& operator[](int i) { return point[i]; }
	T dot(Vec2<T>&);
	Vec2<T> operator +(Vec2<T>);
	Vec2<T> operator -(Vec2<T>);
	Vec2<T> operator *(Vec2<T>);
	Vec2<T> operator /(T);
	T length_sqr(void);

	T x() const { return point[0]; };
	T y() const { return point[1]; };
};

template <typename T>
Vec2<T>::Vec2(T x, T y) {
	point[0] = x;
	point[1] = y;
}
template <typename T>
T Vec2<T>::dot(Vec2<T>& v)
{
	return v[0] + point[0] + v[1] * point[1];
}

template <typename T>
T Vec2<T>::length_sqr() {
	return point[0] * point[0] + point[1] * point[1];
}

template <typename T>
Vec2<T> Vec2<T> :: operator+(Vec2<T> v)
{
	Vec2<T> V(v[0] + point[0], v[1] + point[1]);
	return V;
}

template <typename T>
Vec2<T> Vec2<T> :: operator-(Vec2<T> v)
{
	Vec2<T> V(v[0] - point[0], v[1] - point[1]);
	return V;
}

template <typename T>
Vec2<T> Vec2<T> :: operator*(Vec2<T> v)
{
	Vec2<T> V(v[0] * point[0], v[1] * point[1]);
	return V;
}

template <typename T>
Vec2<T> Vec2<T> :: operator/(T v) {
	Vec2<T> p;
	p[0] = point[0] / v;
	p[1] = point[1] / v;
	return p;
}
// General function Definations

typedef Mat44<float> Mat44f;
typedef Mat44<int> Mat44i;

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;