#include <iostream>
#include <fstream>
#include <limits>
#include "model.cpp"
#include "geometry.h"

// credit to https://github.com/ssloy/tinyraytracer 
// authors : SALHI Mohamed Elridha && ABDELAZIZ Yamina
// 
//-----------------------------------------------------------
void fbToFile(std::vector<Vec3f> &framebuffer, int h, int w){
    //creating the out.ppm image
    std::ofstream ofs;
    ofs.open("../out/out_ninth.ppm", std::ios::binary);// rendred images are called "out.ppm" and can be found in out folder
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for(size_t i = 0; i < h*w; i++){
        Vec3f &c = framebuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1.f/max);
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}

// after following drwaing lines bresenham algorithm, now we draw traingles with 
// best algorithme in term of time execution
void line(int x0, int y0, int x1, int y1, std::vector<Vec3f> &framebuffer, const Vec3f &color, int width, int height) {
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
    // make it left to right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    //
    int dx = x1-x0; 
    int dy = y1-y0; 
    int offset = std::abs(dy)*2; 
    int error2 = 0;  
    int relocate = dx * 2;
    int shift = (y0 > y1) ? -1 : 1;
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            framebuffer[y+x*width] = color;
        } else { 
            framebuffer[x+y*width] = color;
        } 
        //
        error2 += offset;
        if (error2 > dx) {
           y += shift;
           error2 -= relocate;
        }
    } 

}

// methode to draw polygon in forme of mesh
void drawPolygon(std::vector<Vec3f> &framebuffer, const Vec3f &color, Vec3f points[], int nbL, int width, int height){
    for(int i = 0; i < nbL - 1 ; i++){
    	// calling line function to draw each line
        line(points[i].x, points[i].y, points[i+1].x, points[i+1].y, framebuffer, color, width, height);
    }
    if(nbL > 1){
    	// calling line function to draw each line
        line(points[0].x, points[0].y, points[nbL-1].x, points[nbL-1].y, framebuffer, color, width, height);
    }
}

//
Vec3f getBarycentricCoordinates(Vec3f AB, Vec3f AC, Vec3f PA){
    Vec3f coor;
    Vec3f vecX = Vec3f(AB.x, AC.x, PA.x);
    Vec3f vecY = Vec3f(AB.y, AC.y, PA.y);
    coor.x = vecX.y*vecY.z - vecX.z*vecY.y;
    coor.y = vecX.z*vecY.x - vecX.x*vecY.z;
    coor.z = vecX.x*vecY.y - vecX.y*vecY.x;
    return Vec3f((coor.x / coor.z), (coor.y / coor.z), (1.f - (coor.x + coor.y)/coor.z));
}

// Using sweeping algorithm tp draw a triangle 
void toSweepTriangle(Vec3f points[], std::vector<float> &zBuffer, std::vector<Vec3f> &framebuffer, const Vec3f &color, int width, int height){

    Vec3f A = points[0];
    Vec3f B = points[1];
    Vec3f C = points[2];
    // sorting vertices of the triangles by their y-coordinates;
    if(A.y > B.y) std::swap(A, B);
    if(B.y > C.y) std::swap(B, C);
    if(A.y > B.y) std::swap(A, B);

    //
    Vec3f AB = Vec3f(std::abs(B.x - A.x),std::abs(B.y - A.y), std::abs(B.z - A.z));// getting the vec AB
    Vec3f BC = Vec3f(std::abs(B.x - C.x),std::abs(B.y - C.y), std::abs(B.z - C.z));// getting the vec BC
    Vec3f AC = Vec3f(std::abs(C.x - A.x),std::abs(C.y - A.y), std::abs(C.z - A.z));// getting the vec AC

    // getting points
    Vec3f dAC = A;
    Vec3f dAB = A;
    Vec3f dBC = B;

    
    if(AB.y > 0){//upper part of the triangle
        for (float i = 0; i < AB.y; i++) {
            // linear interpolation to retrieve x position of dAC
            if(A.x < C.x){
				dAC.x = A.x + (AC.x * i) / AC.y ;
            }else{
				dAC.x = A.x - (AC.x * i) / AC.y ;
            }
            //
            dAC.y = A.y + i;

            if(A.x < B.x){
				dAB.x = A.x + (AB.x * i) / AB.y ;
            }else{
				dAB.x = A.x - (AB.x * i) / AB.y ;
            }
            dAB.y = dAC.y;

            line(dAB.x, dAB.y, dAC.x, dAC.y, framebuffer, color, width, height);
        }
    }else{
            line(A.x, A.y, B.x, B.y, framebuffer, color, width, height);
    }


    //lower part of the triangle
    if(BC.y > 0){
        for(float i = AB.y; i < AC.y; i++){
        	if(A.x < C.x ){
        		dAC.x = A.x + (AC.x * i) / AC.y ;
        	}else{
        		dAC.x = A.x - (AC.x * i) / AC.y;
        	}
        	//
            dAC.y = A.y + i;

            if(B.x < C.x  ){
        		dBC.x = B.x + (BC.x * (i-AB.y)) / BC.y;
        	}else{
        		dBC.x = B.x - (BC.x * (i-AB.y)) / BC.y;
        	}
            //
            dBC.y = dAC.y;

            line(dBC.x, dBC.y, dAC.x, dAC.y, framebuffer, color, width, height);
        }
    }else{

        line(B.x, B.y, C.x, C.y, framebuffer, color, width, height);
    }

    line(A.x, A.y, B.x, B.y, framebuffer, color, width, height);
    line(A.x, A.y, C.x, C.y, framebuffer, color, width, height);
    line(B.x, B.y, C.x, C.y, framebuffer, color, width, height);

}



 // cette methode fait la mise a jour de z_buffer 
 // si c'est le cas elle retourne true 
bool MAJZBuffer(int x, int y, Vec3f points[], const Vec3f &barycenter, std::vector<float> &zBuffer, std::vector<Vec3f> &framebuffer, const Vec3f &color, int width, int height ){
    bool res = false;
    float z;
    if(x >= 0 && y >= 0 && x < width && y < height ){
        z = points[0].z * barycenter.x + points[1].z * barycenter.y + points[2].z * barycenter.z;
        // verfier is z dans z-buffer est inf
        if(z >= zBuffer[y*width + x]){
            zBuffer[y*width + x] = z;
            framebuffer[y*width + x] = color;
            //res = true;
        }
    }
    return res;
}


// using barycentric coordinates algorithm we draw a triangle 
void algoRasterize(Vec3f points[], std::vector<float> &zBuffer, std::vector<Vec3f> &framebuffer, const Vec3f &color, int width, int height){
    Vec3f P, PA;
    Vec3f A = points[0];
    Vec3f B = points[1];
    Vec3f C = points[2];

    Vec3f AB = Vec3f(B.x - A.x,B.y - A.y,B.z - A.z);
    Vec3f AC = Vec3f(C.x - A.x,C.y - A.y,C.z - A.z);

    // finding bounding box
    int minX, maxX, minY, maxY;
    minX = std::min(A.x, std::min(B.x, C.x));
    maxX = std::max(A.x, std::max(B.x, C.x));
    minY = std::min(A.y, std::min(B.y, C.y));
    maxY = std::max(A.y, std::max(B.y, C.y));

    // iterating on bounding box
    for(int x = minX; x <= maxX; x++){
        for(int y = minY; y <= maxY; y++){
            Vec3f P = Vec3f(x, y, 1);
            Vec3f PA = Vec3f(
                    A.x - P.x,
                    A.y - P.y,
                    A.z - P.z
            );

            Vec3f barycenter = getBarycentricCoordinates(AB, AC, PA);

            // checking if it is inside the triangle and faire la MAJ
            if(barycenter.x >= 0 && barycenter.y >= 0 && barycenter.z >= 0 ) 
            {
                 MAJZBuffer(x, y, points, barycenter, zBuffer, framebuffer, color, width, height);
            }
        }
    }
}

// 
// creation de la matrice viewport
Matrix viewport(float x, float y, float w, float h, float depth) {
    Matrix Viewport = Matrix::identity(4);
    Viewport[0][3] = x+w/2.f;
    Viewport[1][3] = y+h/2.f;
    Viewport[2][3] = depth/2.f;
    Viewport[0][0] = w/2.f;
    Viewport[1][1] = h/2.f;
    Viewport[2][2] = depth/2.f;
    return Viewport;
}

Matrix projection(const float c){
    Matrix Projection = Matrix::identity(4);
    Projection[3][2] = -1.f/c;
    return Projection;
}

Vec3f m2v(Matrix m) {
    return Vec3f(m[0][0]/m[3][0], m[1][0]/m[3][0], m[2][0]/m[3][0]);
}


Matrix v2m(const Vec3f v) {
    Matrix m(4, 1);
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1.f;
    return m;
}

void render(){
	const Vec3f bleuCol = Vec3f (0.1 ,1 , 1);
	const Vec3f redCol = Vec3f(1, 0, 0);
    const Vec3f greenCol = Vec3f(0, 1, 0);
    const Vec3f normalBleuCol = Vec3f(0, 0, 1);

	//image height and width et depth
	const int width = 1280;
    const int height = 720;
    const int depth = 255;
    
    std::vector<Vec3f> framebuffer(width*height);
    std::vector<float> zBuffer(width*height);
    Vec3f camera = Vec3f(0, 0, 2);
    Vec3f orient = Vec3f(0, 0, 5);

    Vec3f ambient_light_direction_vector = Vec3f( 0, 0, -1);// ajouts de la lumiere 

    Matrix VP = viewport(width/8, height/8, width*3/4, height*3/4, depth); // recuperer la matrice viewport creer par la fontion (git de prof)
    Matrix P  = projection(camera.z);// recuperer la matrice perspective

    std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<float>::lowest());
    //our model "Diablo"
    Model modelDiablo = Model("../obj/diablo3_pose.obj");
    int nbL = 3 ;

    Vec3f points[nbL];
    //calling polygon function for each diablo face
    //drawPolygon(framebuffer, zBuffer, d1, d2, nbL, width, height);
    Vec3f point;
    Vec3f colorForMaticeUse;
    int k = 0 ; 
    for(int i = 0; i < modelDiablo.nfaces(); i++){ // each diablo face
        for(int j = 0; j < nbL; j++){
            point = modelDiablo.vert(i, j);
            points[j] = m2v(VP * P * v2m(point));
            points[j].y = height - points[j].y;
        }
        Vec3f e1 = points[1] - points[0];
        Vec3f e2 = points[2] - points[0];

        // compute triangle normal
        Vec3f N = (e1^e2).normalize();

        // compute illumination for the triangle
        float  illumination = N*ambient_light_direction_vector;
        // checking if > 0 
        if(illumination > 0){
            algoRasterize(points, zBuffer, framebuffer, Vec3f(illumination, illumination, illumination), width, height);
        }

    }
    
    // creating ppm image function
    fbToFile(framebuffer, height, width);
}

int main() {
	std::cout << "hello boys !!" << std::endl;
    render();
    std::cout << "fini!!" << std::endl;
}