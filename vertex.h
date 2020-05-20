#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
class vertex
{
public:
	float e[4] =  {0, 0, 0, 1};

	vertex(){e[0] = e[1] = e[2] = 0;};
	vertex(float, float, float);

	float operator[](int i) {return e[i];};
	float dot(vertex);

};

float vertex :: dot (vertex v){
	return v[0] * e[0] + v[1] * e[1] + v[2] * e[2];
}

vertex :: vertex(float _x, float _y , float _z){
	e[0] = _x;
	e[1] = _y;
	e[2] = _z;

}

class face{
public:
	std::vector<int> faces;

	face(){};
	void set_face(int);
	int operator[](int i) {return faces[i];};
	int Length();
};


void face :: set_face(int index){
	faces.push_back(index);
}

int face :: Length(){
	return faces.size();
}
#endif
