/*
 * Entity.h
 *
 *  Created on: Jul 16, 2012
 *      Author: jacob
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "../includes.hpp"
#include "ModelSystem.hpp"
#include "shapes/Shape.hpp"
#include "shapes/LoadModel.hpp"
#include <iostream>

class Entity {
public:
    Entity(glm::vec3 position);
    Entity(glm::vec3 position, glm::vec3 rotation);
    Entity(glm::vec3 position, std::string type);
    Entity(glm::vec3 position, glm::vec3 rotation, std::string type);
    Entity(glm::vec3 position, int type);
    Entity(glm::vec3 position, glm::vec3 rotation, int type);
    Entity(glm::vec3 position, float f, int type);
    virtual ~Entity();

    int modelNumber;

    glm::mat4 model;

    void render(glm::mat4 view, GLuint M, GLuint nM, ModelSystem modelSystem);
    void update();
};

#endif /* ENTITY_H_ */
