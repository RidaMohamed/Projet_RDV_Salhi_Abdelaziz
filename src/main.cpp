#include <iostream>
#include <fstream>
#include "geometry.h"




void render(){
	//image height and width
	const int width = 1024;
    const int height = 768;
    const int fov = 90;
    std::vector<Vec3f> framebuffer(width*height);

    
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            framebuffer[i+j*width] = Vec3f (0.1 ,1 , 1);
        }
    }

    
    //creating the out.ppm image
    std::ofstream ofs;
    ofs.open("../out/out3.ppm", std::ios::binary);// rendred images are called "out.ppm" and can be found in out folder
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for(size_t i = 0; i < height*width; i++){
        Vec3f &c = framebuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1./max);
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

int main() {
    render();
    std::cout << "hello boys !!" << std::endl;
}