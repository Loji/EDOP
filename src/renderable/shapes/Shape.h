/*
 * Shape.hpp
 *
 *  Created on: Jul 28, 2012
 *      Author: jacob
 */

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include "../../includes.h"

class Shape {
public:
    Shape();
    Shape(const char *path);
    virtual ~Shape();

    virtual void kill();
    virtual bool loadModel(const char* path);
    int numberElements;

    std::vector <glm::vec3> vertices;
    std::vector <glm::vec3> colors;
    std::vector <glm::vec3> normals;
    std::vector <glm::vec2> texture;
};

#endif /* SHAPE_HPP_ */
