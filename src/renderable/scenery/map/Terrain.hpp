/*
 * Terrain.hpp
 *
 *  Created on: Sep 20, 2012
 *      Author: jacob
 */

#ifndef TERRAIN_HPP_
#define TERRAIN_HPP_

#include "../../../includes.hpp"

class Terrain {
public:
    Terrain();
    virtual ~Terrain();

    void render(glm::mat4 view, GLuint M, GLuint nM);

    void generate();
    void generate(int x, int y, int z);

    std::vector<glm::vec3> data;
    std::vector<glm::vec3> dataColor;
    std::vector<glm::vec3> dataNormal;

    GLuint vbo;
    GLuint nbo;
    GLuint cbo;


private:
    int sizeX;
    int sizeY;

    void recalculate();
    glm::vec3 calculateNormal(glm::vec3 U, glm::vec3 V);


    glm::vec3 *getAt(int x, int y);
    float generateY(int x, int y, int mX, int mY);

    void genBuff();
};

#endif /* TERRAIN_HPP_ */
