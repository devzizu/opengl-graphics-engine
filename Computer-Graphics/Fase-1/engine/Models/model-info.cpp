
#include "model-info.h"

POINT_3D::POINT_3D(float x, float y, float z) : x(x), y(y), z(z) {}

float POINT_3D::getX() const {
    return x;
}

void POINT_3D::setX(float x) {
    POINT_3D::x = x;
}

float POINT_3D::getY() const {
    return y;
}

void POINT_3D::setY(float y) {
    POINT_3D::y = y;
}

float POINT_3D::getZ() const {
    return z;
}

void POINT_3D::setZ(float z) {
    POINT_3D::z = z;
}

const string &MODEL_INFO::getName() const {
    return name;
}

void MODEL_INFO::setName(const string &name) {
    MODEL_INFO::name = name;
}

const vector<POINT_3D> &MODEL_INFO::getVertices() const {
    return vertices;
}

void MODEL_INFO::addPoint(POINT_3D point) {
    this->vertices.push_back(point);
}

int MODEL_INFO::getTotalVertices() const {
    return total_vertices;
}

MODEL_INFO::MODEL_INFO(const string &name) : name(name) {}

void MODEL_INFO::setTotalVertices(int totalVertices) {
    total_vertices = totalVertices;
}

void MODEL_INFO::setVertices(const vector<POINT_3D> &vertices) {
    MODEL_INFO::vertices = vertices;
}
