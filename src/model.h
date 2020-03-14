#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include <string>
#include "geometry.h"

// using code from ssloy git
// credit to https://github.com/ssloy/tinyrenderer/blob/master/model.cpp

class Model {

private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<Vec3i> > faces; // attention, this Vec3i means vertex/uv/normal
    std::vector<Vec3f> norms;
    std::vector<Vec2f> uv_;

public:
    Model(const char *filename);
    ~Model();
    int nverts();
    int nfaces();
    int dot(int ifa, int nthv);  
    Vec2f uv(int ifa, int nthv);
    Vec3f &vert(int i);
    Vec3f vert(int iface, int nthvert);
    Vec3f normal(int ifa, int nthv);
};
#endif //__MODEL_H__