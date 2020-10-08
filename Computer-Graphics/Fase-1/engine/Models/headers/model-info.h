
#ifndef ENGINE_MODEL_INFO_H
#define ENGINE_MODEL_INFO_H

#include <iostream>
#include <vector>

using namespace std;

//--------------------------------------------------------------------------------------

/*
 * Implementação de um ponto 3D em C++
 * */
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

/*
 * Contém informação de um modelo, nomeadamente,
 * o nome do ficheiro que contém os vertices e
 * o vetor de vértices que será carregado para a
 * memória principal.
 * */
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