#include <iostream>
#include <fstream>
#include "model.h"
#include "geometry.h"

// credit to https://github.com/ssloy/tinyraytracer 
// author : SALHI Mohamed Elridha

//-----------------------------------------------------------
void fbToFile(std::vector<Vec3f> &framebuffer, int h, int w){
    //creating the out.ppm image
    std::ofstream ofs;
    ofs.open("../out/out_second.ppm", std::ios::binary);// rendred images are called "out.ppm" and can be found in out folder
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for(size_t i = 0; i < h*w; i++){
        Vec3f &c = framebuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1./max);
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

// after following drwaing lines bresenham algorithm, now we drw traingles 
// noting that this is not the best code in term of execution time 
void line(int x0, int y0, int x1, int y1, std::vector<Vec3f> &framebuffer, Vec3f color, int width, int height) {
    bool steep = false;
    /* 
    * swaaping the x && y of each passed x0 and x1 and y1 and x1
    */ 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
 		std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 

    if (x0>x1) { 
    // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    //
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        if (steep) { 
           framebuffer[y+x*width] = color; 
        } else { 
           framebuffer[x+y*width] = color;
        } 
    } 
}

void render(){
	const Vec3f bleuCool = Vec3f (0.1 ,1 , 1);

	//image height and width
	const int width = 1024;
    const int height = 768;
    
    std::vector<Vec3f> framebuffer(width*height);

    int nbL = 3 ;

    // drawing things
    int d1[3] = {50, 50,975};
    int d2[3] = {718, 50, 718};
    
    for(int i = 0; i < nbL - 1 ; i++){
    	// calling line function
        line(d1[i], d2[i], d1[i+1], d2[i+1],framebuffer, bleuCool, width, height);
    }
    if(nbL > 1){
    	// calling line function
        line(d1[0], d2[0], d1[nbL-1], d2[nbL-1], framebuffer, bleuCool, width, height);
    }
    // creating ppm image function
    fbToFile(framebuffer, height, width);
}

int main() {
	std::cout << "hello boys !!" << std::endl;
    render();
    std::cout << "finished!!" << std::endl;
}