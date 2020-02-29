
#ifndef ENGINE_MODEL_INFO_H
#define ENGINE_MODEL_INFO_H

#include <iostream>
#include <vector>

using namespace std;

//--------------------------------------------------------------------------------------

class POINT_3D {
    public:
        POINT_3D(float x, float y, float z);

    private:
            float x;
            float y;
            float z;
    public:
        float getX() const;

        void setX(float x);

        float getY() const;

        void setY(float y);

        float getZ() const;

        void setZ(float z);
};

//--------------------------------------------------------------------------------------

class MODEL_INFO {

    private:
        string name;
        vector<POINT_3D> vertices;
        int total_vertices{};
public:
    void setTotalVertices(int totalVertices);

public:

        int getTotalVertices() const;

        const string &getName() const;

        const vector<POINT_3D> &getVertices() const;

        void setVertices(const vector<POINT_3D> &vertices);

        void addPoint(POINT_3D point);

        void setName(const string &name);

        explicit MODEL_INFO(const string &name);
};

#endif