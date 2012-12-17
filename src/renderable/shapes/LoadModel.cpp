/*
 * LoadModel.cpp
 *
 *  Created on: Jul 30, 2012
 *      Author: jacob
 */

#include "LoadModel.hpp"

LoadModel::LoadModel() {
    //numberElements = 0;
    vertices.clear();
    colors.clear();
    normals.clear();
}

LoadModel::~LoadModel() {
}


bool LoadModel::loadModel(const char* path) {
    std::cout << "adding\n";
    std::vector<unsigned int> iVer, iTex, iNor;
    std::vector<glm::vec3> ver;
    std::vector<glm::vec2> tex;
    std::vector<glm::vec3> nor;

    FILE *file = fopen(path, "r");

    while (true) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;  // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            ver.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            //uv.y = -uv.y;
            tex.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            nor.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches == 9) {
                iVer.push_back(vertexIndex[0]);
                iVer.push_back(vertexIndex[1]);
                iVer.push_back(vertexIndex[2]);
                iTex.push_back(uvIndex[0]);
                iTex.push_back(uvIndex[1]);
                iTex.push_back(uvIndex[2]);
                iNor.push_back(normalIndex[0]);
                iNor.push_back(normalIndex[1]);
                iNor.push_back(normalIndex[2]);
            } else {

                return false;
            }

        } else {
            char nomBuffer[1000];
            fgets(nomBuffer, 1000, file);
        }

    }

    int test = iVer.size();
    // For each vertex of each triangle
    for (unsigned int i = 0; i < iVer.size(); i++) {
        test--;
        // Get the indices of its attributes
        unsigned int vertexIndex = iVer[i];
        unsigned int uvIndex = iTex[i];
        unsigned int normalIndex = iNor[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = ver[vertexIndex - 1];
        glm::vec2 uv = tex[uvIndex - 1];
        glm::vec3 normal = nor[normalIndex - 1];
        glm::vec3 color = glm::vec3(1.f);

        // Put the attributes in buffers
        vertices.push_back(vertex);
        texture.push_back(uv);
        normals.push_back(normal);
        colors.push_back(color);
    }
    std::cout << "added\n";
    return true;
}
