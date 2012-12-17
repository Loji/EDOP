/*
 * Terrain.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: jacob
 */

#include "Terrain.hpp"

// old terrain plane generator, generates array of vertexes

Terrain::Terrain() {
    // TODO Auto-generated constructor stub

}

Terrain::~Terrain() {
    // TODO Auto-generated destructor stub
}

void Terrain::render(glm::mat4 view, GLuint M, GLuint nM) {
    glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(4.f));

    glm::mat3 n = glm::inverse(glm::transpose(glm::mat3(view * model)));
    glUniformMatrix3fv(nM, 1, GL_FALSE, &n[0][0]);
    glUniformMatrix4fv(M, 1, GL_FALSE, &model[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLES, 0, data.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Terrain::genBuff() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0],
            GL_STATIC_DRAW);

    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, dataNormal.size() * sizeof(glm::vec3),
            &dataNormal[0], GL_STATIC_DRAW);

    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, dataColor.size() * sizeof(glm::vec3),
            &dataColor[0], GL_STATIC_DRAW);
}

void Terrain::generate() {

}

float avarge(float a, float b, float c, float d) {
    return ((a + b + c + d) / 4);
}

float avarge(float a, float b, float c) {
    return ((a + b + c) / 3);
}

float avarge(float a, float b) {
    return ((a + b) / 2);
}

float genF(float size) {
    return (float) rand() / ((float) RAND_MAX / (float) size);
}

glm::vec3 *Terrain::getAt(int x, int y) {
    return &data.at(x * sizeY + y);;
}

glm::vec3 Terrain::calculateNormal(glm::vec3 U, glm::vec3 V) {
    glm::vec3 normal;

//Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
//Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
//Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)

    normal.x = (U.y * V.z) - (U.z * V.y);
    normal.y = (U.z * V.x) - (U.x * V.z);
    normal.z = (U.x * V.y) - (U.y * V.x);

    return normal;
}

float genS(int x, int y, float seed) {
    float temp = 0;

    return temp;
}

float Terrain::generateY(int x, int y, int mX, int mY) {
    float temp = 0.f;

    static const float ss = 0.2;
    static const float seed = 0.1f;

    if (x != 0) {
        if (x != mX) {
            if (y != 0) {
                if (y != mY) {
                    temp = avarge(getAt(x - 1, y - 1)->y,
                            getAt(x - 1, y + 1)->y, getAt(x + 1, y - 1)->y,
                            getAt(x + 1, y + 1)->y);
                } else {
                    temp = avarge(getAt(x - 1, y - 1)->y,
                            getAt(x + 1, y - 1)->y);
                }
            } else {
                if (y != mY) {
                    temp = avarge(getAt(x - 1, y + 1)->y,
                            getAt(x + 1, y + 1)->y);
                }
            }
        } else {
            if (y != 0) {
                if (y != mY) {
                    temp = avarge(getAt(x - 1, y - 1)->y,
                            getAt(x - 1, y + 1)->y, getAt(x + 1, y - 1)->y);
                } else {
                    temp = getAt(x - 1, y - 1)->y;
                }
            } else {
                if (y != mY) {
                    temp = getAt(x - 1, y + 1)->y;
                }
            }
        }
    } else {
        if (x != mX) {
            if (y != 0) {
                if (y != mY) {
                    temp = avarge(getAt(x + 1, y - 1)->y,
                            getAt(x + 1, y + 1)->y);
                } else {
                    temp = getAt(x + 1, y - 1)->y;
                }
            } else {
                if (y != mY) {
                    temp = getAt(x + 1, y + 1)->y;
                }
            }
        }
    }

    temp += genS(x, y, seed) + (genF(ss) - ss / 2);

    return temp;
}

void Terrain::recalculate() {
    std::vector<glm::vec3> temp;
    std::vector<glm::vec3> tempColor;
    std::vector<glm::vec3> tempNormal;

    for (int i = 0; i < sizeY - 1; i++) {
        for (int j = 0; j < sizeX - 1; j++) {

            temp.push_back(*getAt(j, i));
            temp.push_back(*getAt(j + 1, i));
            temp.push_back(*getAt(j, i + 1));

            glm::vec3 normal = glm::vec3(0.f);
            normal = calculateNormal(
                    temp.at(temp.size() - 2) - temp.at(temp.size() - 3),
                    temp.at(temp.size() - 1)
                            - temp.at(temp.size() - 3));

            tempNormal.push_back(normal);
            tempNormal.push_back(normal);
            tempNormal.push_back(normal);

            tempColor.push_back(glm::vec3(1.f));
            tempColor.push_back(glm::vec3(1.f));
            tempColor.push_back(glm::vec3(1.f));

            temp.push_back(*getAt(j + 1, i));
            temp.push_back(*getAt(j + 1, i + 1));
            temp.push_back(*getAt(j, i + 1));

            normal = calculateNormal(
                    temp.at(temp.size() - 2) - temp.at(temp.size() - 3),
                    temp.at(temp.size() - 1)
                            - temp.at(temp.size() - 3));

            tempNormal.push_back(normal);
            tempNormal.push_back(normal);
            tempNormal.push_back(normal);

            tempColor.push_back(glm::vec3(1.f));
            tempColor.push_back(glm::vec3(1.f));
            tempColor.push_back(glm::vec3(1.f));
        }
    }

    data.clear();
    data = temp;
    temp.clear();

    dataNormal.clear();
    dataNormal = tempNormal;
    tempNormal.clear();

    dataColor.clear();
    dataColor = tempColor;
    tempColor.clear();

}

void Terrain::generate(int x, int y, int z) {
    glm::vec3 temp;
    sizeY = y;
    sizeX = x;

    for (int n = 0; n < x * y * y; n++)
        data.push_back(glm::vec3(0.f));

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {

            temp.x = (j * 0.2f) + (genF(0.05) - 0.05 / 2);
            temp.z = (i * 0.2f) + (genF(0.05) - 0.05 / 2);
            temp.y = generateY(j, i, x, y);

            data.at((j * sizeY) + i).x = temp.x;
            data.at((j * sizeY) + i).y = temp.y;
            data.at((j * sizeY) + i).z = temp.z;
        }
    }
    recalculate();
    genBuff();
}

