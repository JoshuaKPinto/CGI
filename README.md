# CGI

## Projection of a 3D point onto a 2D screen
The file  `projection.cpp` contains a demo for projecting 3D points from a wavefront file .
You will need a wavefront format file, eg : `3DObject.obj`
You can create one by using [Blender](https://www.blender.org/) . Then export the object as follows,
 File > Export > Wavefront (.obj)

To compile the program use a C++ compiler which supports C++17.
For a g++ compiler run the following command

    g++ projection.cpp -std=c++17 -o outputfile.exe

Then run the program

	outputfile.exe 3DObject.obj
	
You should see a file `final_rendered_img.png` in your program folder.

 
 ## Note
 This program uses the [lodepng](https://github.com/lvandeve/lodepng) libary to save .png data
 which is available in the ImageIO file.
