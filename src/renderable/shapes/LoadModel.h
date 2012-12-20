/*
 * LoadModel.hpp
 *
 *  Created on: Jul 30, 2012
 *      Author: jacob
 */

#ifndef LOADMODEL_HPP_
#define LOADMODEL_HPP_

#include "Shape.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>

class LoadModel {
public:
    LoadModel();
    virtual ~LoadModel();

    bool loadModel(const char* path);

    std::vector <glm::vec3> vertices;
    std::vector <glm::vec3> colors;
    std::vector <glm::vec3> normals;
    std::vector <glm::vec2> texture;
};

#endif /* LOADMODEL_HPP_ */
