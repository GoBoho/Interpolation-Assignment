//g++ -o squareInterpolation.exe squareInterpolation.cpp -O2 -lgdi32

#include <iostream>
#include "CImg_latest\Cimg-2.8.2\CImg.h"

using namespace cimg_library;
using namespace std;

int main(){
	CImg<unsigned char> colorImage(300,300, 1, 3, 0);

	//Top-Left
	colorImage(0, 0, 0, 0) = 90.0; //Red
	colorImage(0, 0, 0, 1) = 84.0; //Green
	colorImage(0, 0, 0, 2) = 32.0; //Blue

	//Top-Right
	colorImage(299, 0, 0, 0) = 58.0; //Red
	colorImage(299, 0, 0, 1) = 200.0; //Green
	colorImage(299, 0, 0, 2) = 65.0; //Blue

	//Bottom-Left
	colorImage(0, 299, 0, 0) = 200.0; //Red
	colorImage(0, 299, 0, 1) = 33.0; //Green
	colorImage(0, 299, 0, 2) = 50.0; //Blue

	//Bottom-Right
	colorImage(299, 299, 0, 0) = 62.0; //Red
	colorImage(299, 299, 0, 1) = 42.0; //Green
	colorImage(299, 299, 0, 2) = 200.0; //Blue
	
	//Iterate through the image for Interpolation.
	for (int i = 0; i < 299; i++){
		
		float d1 = i;
		float d2 = 299 - d1;
		
		//Creates the Top Horizontal Line, Interpolated.
		colorImage(i,0,0,0) = ((d2/299)*colorImage(0,0,0,0))+((d1/299)*colorImage(299,0,0,0)); //Red
		colorImage(i,0,0,1) = ((d2/299)*colorImage(0,0,0,1))+((d1/299)*colorImage(299,0,0,1)); //Green
		colorImage(i,0,0,2) = ((d2/299)*colorImage(0,0,0,2))+((d1/299)*colorImage(299,0,0,2)); //Blue
		
		//Creates the Bottom Horizontal Line, Interpolated.
		colorImage(i,299,0,0) = ((d2/299)*colorImage(0,299,0,0))+((d1/299)*colorImage(299,299,0,0)); //Red
		colorImage(i,299,0,1) = ((d2/299)*colorImage(0,299,0,1))+((d1/299)*colorImage(299,299,0,1)); //Green
		colorImage(i,299,0,2) = ((d2/299)*colorImage(0,299,0,2))+((d1/299)*colorImage(299,299,0,2)); //Blue
		
	}
	
	for (int i = 0; i < 300; i++){
		for (int j = 0; j < 299; j++){
			
			float d1 = j;
			float d2 = 299 - d1;
			
			//Creates the Vertical Line, Interpolated.
			colorImage(i,j,0,0) = ((d2/299)*colorImage(i,0,0,0))+((d1/299)*colorImage(i,299,0,0)); //Red
			colorImage(i,j,0,1) = ((d2/299)*colorImage(i,0,0,1))+((d1/299)*colorImage(i,299,0,1)); //Green
			colorImage(i,j,0,2) = ((d2/299)*colorImage(i,0,0,2))+((d1/299)*colorImage(i,299,0,2)); //Blue
			
		}
	}
	
	//Display and save filtered image
	CImgDisplay disp(colorImage); 
	while (!disp.is_closed()){
		disp.wait(); 
	}
	colorImage.save("colorImage.bmp");
}