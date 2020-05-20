#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

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
