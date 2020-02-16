#include <iostream>
#include <fstream>
#include <sstream>
#include "model.h"

// credit to https://github.com/ssloy/tinyrenderer/blob/master/model.cpp

Model::Model(const char *filename) : verts(), faces(), norms(), uv_(){
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    // case fail to open the file
    if (in.fail()) {
        std::cerr << "Failed to open the file : " << filename << std::endl;
        return;
    }
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f n;
            for (int i=0;i<3;i++) iss >> n[i];
            norms.push_back(n);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f uv;
            for (int i=0;i<2;i++) iss >> uv[i];
            uv_.push_back(uv);
        }  else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << verts.size() << " f# "  << faces.size() << " vt# " << uv_.size() << " vn# " << norms.size() << std::endl;
}

Model::~Model() {}

int Model::nverts() {
    return (int)verts.size();
}

int Model::nfaces() {
    return (int)faces.size();
}

Vec3f Model::vert(int i) {
    return verts[i];
}

Vec3f Model::vert(int ifa, int nthv) {
    return verts[faces[ifa][nthv][0]];
}

Vec2f Model::uv(int ifa, int nthv) {
    return uv_[faces[ifa][nthv][1]];
}

Vec3f Model::normal(int ifa, int nthv) {
    int idx = faces[ifa][nthv][2];
    return norms[idx].normalize();
}
