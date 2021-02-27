/*
Joshua Kenneth Pinto
Demo of projection of 3D points on a 2D screen.
*/

#include <iostream>
#include "lib/faces.h"
#include <vector>
#include "lib/wavefront_parser.h"
#include "lib/linalg.h"
#include "ImageIO/IMG.h"

using namespace std;

Mat44f CreateCamera(Vec3f, Vec3f);

 int main(int argc, char const *argv[])
{
	std::vector<Vec3f> v;
	std::vector<face> f;
	std::string fname = argc >= 2 ? argv[1] : "C:\\cube.obj";
	cout << "Reading file : " << fname << "\n";

	int WIDTH = 512, HEIGTH = 512;
	float canvWidth = 7, canvHeight = 7;

	Parser p(fname, v, f);
	cout << "Number of vertices : " << v.size() << "\n";
	cout << "Number of faces : " << f.size() << "\n";

	Image render("Rendered.png");
	render.CreateImage(WIDTH, HEIGTH);
	Pixel pxl = Pixel(255, 255, 255);

	// Camera setup

	Vec3f cameraTranslation(0, 0, -2);
	Vec3f cameraRotation(0, 0, 0);

	Mat44f camera = CreateCamera(cameraRotation, cameraTranslation);
	Mat44f camera_inv = camera.inverse();

	for (int i = 0; i < v.size(); i++) {
		Vec3f point = v[i];
		Vec3f wtc = point * camera_inv;

		if (wtc.z() <= 0)
			continue;
		Vec2f p(wtc.x() / -wtc.z(), wtc.y() / -wtc.z()); // NDC Space

		p[0] = (p.x() + (canvWidth / 2)) / canvWidth;
		p[1] = (p.y() + (canvHeight / 2)) / canvHeight;

		p[0] = floor(p.x() * WIDTH);
		p[1] = floor(p.y() * HEIGTH);

		render.SetPixelValue(p.x(), p.y(), pxl);
	}
	render.saveImage("final_rendered_img.png");
	return 0;
}

 Mat44f CreateCamera(Vec3f rotation, Vec3f translation) {
	 Mat44f mat_x, mat_y, mat_z;

	 float cos_x = cos(rotation.x());
	 float sin_x = sin(rotation.x());

	 float cos_y = cos(rotation.y());
	 float sin_y = sin(rotation.y());

	 float cos_z = cos(rotation.z());
	 float sin_z = sin(rotation.z());

	 mat_x.zeros();
	 mat_x[0][0] = 1;
	 mat_x[1][1] = cos_x;
	 mat_x[1][2] = -sin_x;
	 mat_x[2][1] = sin_x;
	 mat_x[2][2] = cos_x;

	 mat_y.zeros();
	 mat_y[0][0] = cos_y;
	 mat_y[0][2] = sin_y;
	 mat_y[1][1] = 1;
	 mat_y[2][0] = -sin_y;
	 mat_y[2][2] = cos_y;

	 mat_z.zeros();
	 mat_z[0][0] = cos_z;
	 mat_z[0][1] = -sin_z;
	 mat_z[1][0] = sin_z;
	 mat_z[1][1] = cos_z;
	 mat_z[2][2] = 1;

	 mat_x  =  mat_x * mat_y * mat_z;
	 mat_x[3][0] = translation.x();
	 mat_x[3][1] = translation.y();
	 mat_x[3][2] = translation.z();
	 mat_x[3][3] = 1;

	 return mat_x;

 }
