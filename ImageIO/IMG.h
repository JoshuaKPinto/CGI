#include "lodepng.h"
#include "lodepng.cpp"
#include <iostream>
#include <string>
#include <vector>
#include "Pixel.h"

/*   CLASS IMAGE DECLERATION*/

using namespace std;


class Image{
	unsigned HEIGHT, WIDTH;
	std :: string imageName;
	std :: vector<unsigned char> imageDataRaw;
	std :: vector<Pixel> imageDataPixel;

public:
	// Geters 
	int GetWidth(void);
	int GetHeight(void);
	Pixel GetPixelValue(int, int);
	void SetPixelValue(int, int, Pixel);

	// Initialization
	Image(string);
	int loadImage(void);
	int saveImage(string);
	int saveImage(void);
	
	// Functions
	void ConvertToPixelData(void);
	int ConvertToRawData(std::vector<Pixel>&);
	void ClearRawData(void);
	void CreateImage(int,int);
};

/* ********* CLASS IMAGE DEFINATION ***************** */

int Image::GetHeight(){ return HEIGHT;} // getter definations
int Image::GetWidth(){ return WIDTH;}

void Image :: ClearRawData(){
	imageDataRaw.clear();
}

Pixel Image :: GetPixelValue(int coloum, int row){
	if((coloum < 0) || (coloum > WIDTH) || (row < 0) || (row > HEIGHT)){
		if(coloum < 0){coloum = 0;} else
		if(coloum > WIDTH){coloum = WIDTH;}
		if(row < 0){row = 0;} else
		if(row > HEIGHT){row = HEIGHT;};
	}
	int index = row * WIDTH + coloum;
	//cout<<"Index Value:"<<index<<endl;
	return imageDataPixel[index];
}

void Image :: SetPixelValue(int coloum, int row, Pixel pxl){
	if((coloum < 0) || (coloum > WIDTH) || (row < 0) || (row > HEIGHT)){
		return;
	}
	int index = row * WIDTH + coloum;
	//cout<<"Index Value:"<<index<<endl;
	imageDataPixel[index] = pxl;
}

Image :: Image(string filename){
	imageName = filename;
	//loadImage(filename);
}

int Image :: loadImage(){
	unsigned error = lodepng::decode(imageDataRaw, WIDTH, HEIGHT, imageName);
	if(error){ std :: cout<< "decode error" << error << ":" << lodepng_error_text(error) << std :: endl; return 1;}
	return 0;
}

int Image :: saveImage(string filename){
	//cout << "Saving image" <<endl;
	ConvertToRawData(imageDataPixel);
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(png, imageDataRaw, WIDTH, HEIGHT);
	if(!error) lodepng::save_file(png, filename);

  //if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
	return 0;
}

int Image :: saveImage(){
	//cout << "Saving image" <<endl;
	string filename = imageName;
	ConvertToRawData(imageDataPixel);
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(png, imageDataRaw, WIDTH, HEIGHT);
	if(!error) lodepng::save_file(png, filename);

  //if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
	return 0;
}

void Image :: ConvertToPixelData(){
	//cout<<"Converting to pixel data...\n";
	for(int i=0; i < imageDataRaw.size(); i+=4){
		imageDataPixel.push_back(Pixel(
			imageDataRaw[i],
			imageDataRaw[i+1],
			imageDataRaw[i+2],
			imageDataRaw[i+3]
			));
	}

	//cout<<"Done Converting\n";
}

void Image :: CreateImage(int w, int h){
	imageDataPixel.clear();
	WIDTH = w;
	HEIGHT = h;
	for (int i=0;i<w*h;i++)
		imageDataPixel.push_back(Pixel(0,0,0,255));
	//cout << "Image Created with Width "<< WIDTH << " and height " << HEIGHT <<endl;	
}

int Image :: ConvertToRawData(vector<Pixel>& image){
	// Overwrite the image with the date in the Pixel buffer.
	int i;
	for(i=0;i<image.size();i++){
		imageDataRaw.push_back(image[i].GetR());
		imageDataRaw.push_back(image[i].GetG());
		imageDataRaw.push_back(image[i].GetB());
		imageDataRaw.push_back(image[i].GetA());
	}
	return 0;
}
