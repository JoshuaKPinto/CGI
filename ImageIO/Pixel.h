// Header file for the Pixel class
// Uses the sRGB (Standard RGB) colour space.
// All values are unnormalized 0-255 integers.

#include <stdint.h>

class Pixel{
	int R,G,B,A;

public:
	// Constructor
	Pixel(int, int, int, int);
	Pixel(int, int, int);
	Pixel();

	//Getters
	int GetR(){return R;}
	int GetG(){return G;}
	int GetB(){return B;}
	int GetA(){return A;}

	//operators
	Pixel operator +(Pixel);
	Pixel operator +(int);
	Pixel operator -(Pixel);
	Pixel operator *(Pixel);
	Pixel operator /(int);
	void operator =(Pixel);
	bool operator ==(Pixel);
	

	//Functions
	void Clamp();
};

// FUNCTIONS

void Pixel :: Clamp(){
	if(R > 255) R = 255;
	if(R <   0) R =   0;
	if(G > 255) G = 255;
	if(G <   0) G =   0;
	if(B > 255) B = 255;
	if(B <   0) B =   0;
	if(A > 255) A = 255;
	if(A <   0) A =   0;

}


// OPERATORS

Pixel Pixel :: operator +(Pixel pxl){
	int _r = R + pxl.GetR();
	int _g = G + pxl.GetG();
	int _b = B + pxl.GetB();
	int _a = A;// + pxl.GetA();
	return Pixel(_r, _g, _b, _a);
}

Pixel Pixel :: operator +(int p){
	return Pixel(
		R + p, 
		G + p, 
		B + p, 
		A + p
		);
}

Pixel Pixel :: operator -(Pixel pxl){
	int _r = R - pxl.GetR();
	int _g = G - pxl.GetG();
	int _b = B - pxl.GetB();
	int _a = A;
	return Pixel(_r, _g, _b, _a);
}

Pixel Pixel :: operator *(Pixel pxl){
	int _r = R * pxl.GetR();
	int _g = G * pxl.GetG();
	int _b = B * pxl.GetB();
	int _a = A;// + pxl.GetA();
	return Pixel(_r, _g, _b, _a);
}

void Pixel :: operator =(Pixel pxl){
	R = pxl.GetR();
	G = pxl.GetG();
	B = pxl.GetB();
	A = pxl.GetA();
	
}

Pixel Pixel :: operator /(int n){
	if(n==0) return Pixel(0,0,0,0);
	int _r = R/n;
	int _g = G/n;
	int _b = B/n;
	int _a = A;
	return Pixel(_r, _g, _b, _a);
}

bool Pixel :: operator ==(Pixel pxl){
	if((pxl.GetR() == R) && (pxl.GetG() == G) && (pxl.GetB() == B)) return true;
	return false;
}

Pixel :: Pixel(int r, int g, int b, int a){
	R = r;
	G = g;
	B = b;
	A = a;
}

Pixel :: Pixel(int r, int g, int b){
	R = r;
	G = g;
	B = b;
	A = 255;
}

Pixel :: Pixel(){
	R = G = B = 0;
	A = 255;
}

