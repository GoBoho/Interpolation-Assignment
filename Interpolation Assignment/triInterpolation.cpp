//g++ -o triInterpolation.exe triInterpolation.cpp -O2 -lgdi32

#include <iostream>
#include "CImg_latest\Cimg-2.8.2\CImg.h"
#include <cmath>

using namespace cimg_library;
using namespace std;

//Area of Triangle.
float triArea(int x1, int y1, int x2, int y2, int x3, int y3) { 
	float area = abs((x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))/2.0); 
	return area;
}
 

//Check if inside of Triangle.	
bool insideCheck(int x1, int y1, int x2, int y2, int x3, int y3, int xC, int yC) { 
	   float areaWhole = triArea(x1, y1, x2, y2, x3, y3); //Area of whole triangle.
	   float area1 = triArea(xC, yC, x2, y2, x3, y3); //Area of triangle in relation to V1.
	   float area2 = triArea(x1, y1, xC, yC, x3, y3); //Area of triangle in relation to V2.
	   float area3 = triArea(x1, y1, x2, y2, xC, yC); //Area of triangle in relation to V3.
	   if ((area1 + area2 + area3) == areaWhole){
			return true;
	   } else {
			return false;
	   }
} 

int main(){
	CImg<unsigned char> triImage(500,500, 1, 3, 0);
	
	//Vertex 1
	triImage(100, 100, 0, 0) = 255.0; //Red
	triImage(100, 100, 0, 1) = 0.0; //Green
	triImage(100, 100, 0, 2) = 0.0; //Blue

	//Vertex 2
	triImage(400, 150, 0, 0) = 0.0; //Red
	triImage(400, 150, 0, 1) = 255.0; //Green
	triImage(400, 150, 0, 2) = 0.0; //Blue

	//Vertex 3
	triImage(200, 300, 0, 0) = 0.0; //Red
	triImage(200, 300, 0, 1) = 0.0; //Green
	triImage(200, 300, 0, 2) = 255.0; //Blue
	
	//Side 1 Interpolation. V1 to V2.
	int j = 100;
	for (int i = 100; i < 400; i++){
		float d1 = i;
		float d2 = 400 - d1;
		triImage(i, j, 0, 0) = ((d2/400)*triImage(100,100,0,0))+((d1/400)*triImage(400,150,0,0));
		triImage(i, j, 0, 1) = ((d2/400)*triImage(100,100,0,1))+((d1/400)*triImage(400,150,0,1));
		triImage(i, j, 0, 2) = ((d2/400)*triImage(100,100,0,2))+((d1/400)*triImage(400,150,0,2));
		
		if ((i*150 - i*100 + 100*400 - 100*150 - j*400 + j*100)>0){
			j += 1;
		}
	}
	
	//Side 2 Interpolation. V1 to V3.
	int i = 100;
	for (int j = 100; j < 300; j++){ 
		float d1 = j;
		float d2 = 300 - d1;
		triImage(i, j, 0, 0) = ((d2/300)*triImage(100,100,0,0))+((d1/300)*triImage(200,300,0,0));
		triImage(i, j, 0, 1) = ((d2/300)*triImage(100,100,0,1))+((d1/300)*triImage(200,300,0,1));
		triImage(i, j, 0, 2) = ((d2/300)*triImage(100,100,0,2))+((d1/300)*triImage(200,300,0,2));
		
		if ((j*200 - j*100 + 100*300 - 100*200 - i*300 + i*100)>0){
			i += 1;
		}
	}
	
	//Side 3 Interpolation. V3 to V2.
	int j2 = 300;
	for (int i = 200; i < 400; i++){
		float d1 = i;
		float d2 = 400 - d1;
		triImage(i, j2, 0, 0) = ((d2/400)*triImage(200,300,0,0))+((d1/400)*triImage(400,150,0,0));
		triImage(i, j2, 0, 1) = ((d2/400)*triImage(200,300,0,1))+((d1/400)*triImage(400,150,0,1));
		triImage(i, j2, 0, 2) = ((d2/400)*triImage(200,300,0,2))+((d1/400)*triImage(400,150,0,2));
		
		if ((i*150 - i*300 + 300*400 - 200*150 - j2*400 + j2*200)<0){
			j2 -= 1;
		}
	}
	
	//Interior Interpolation.
	float areaWhole = triArea(100, 100, 400, 150, 200, 300); 
	for (int i = 0; i < 500; i++){
		for (int j = 0; j < 500; j++){
			
			float area1 = triArea(i, j, 400, 150, 200, 300); 
			float area2 = triArea(100, 100, i, j, 200, 300); 
			float area3 = triArea(100, 100, 400, 150, i, j); 
			
			if (insideCheck(100,100,400,150,200,300,i,j) == true){
				triImage(i,j,0,0)= ((area1/areaWhole)*(triImage(100, 100, 0, 0))) + ((area2/areaWhole)*(triImage(400, 150, 0, 0))) + ((area3/areaWhole)*(triImage(200, 300, 0, 0)));
				triImage(i,j,0,1)= ((area1/areaWhole)*(triImage(100, 100, 0, 1))) + ((area2/areaWhole)*(triImage(400, 150, 0, 1))) + ((area3/areaWhole)*(triImage(200, 300, 0, 1)));
				triImage(i,j,0,2)= ((area1/areaWhole)*(triImage(100, 100, 0, 2))) + ((area2/areaWhole)*(triImage(400, 150, 0, 2))) + ((area3/areaWhole)*(triImage(200, 300, 0, 2)));
			} 
		}
	}
	
	//Display and save filtered image
	CImgDisplay disp(triImage); 
	while (!disp.is_closed()){
		disp.wait(); 
	}
	triImage.save("triImage.bmp");
}	


