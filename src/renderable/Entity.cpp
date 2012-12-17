/*
 * Entity.cpp
 *
 *  Created on: Jul 16, 2012
 *      Author: jacob
 */

#include "Entity.hpp"

void Entity::render(glm::mat4 view, GLuint M, GLuint nM, ModelSystem modelSystem) {
    //sending normal matrix and model matrix to shader
    glm::mat3 n = glm::inverse(glm::transpose(glm::mat3(view * model)));
    glUniformMatrix3fv(nM, 1, GL_FALSE, &n[0][0]);
    glUniformMatrix4fv(M, 1, GL_FALSE, &model[0][0]);

    modelSystem.render(modelNumber);
}

void Entity::update() {

}

// bunch of various constructors, most will be deleted
Entity::Entity(glm::vec3 position) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position);

}

Entity::Entity(glm::vec3 position, glm::vec3 rotation) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position)
            * glm::rotate(model, 90.f, rotation);

}

Entity::Entity(glm::vec3 position, std::string type) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position);

}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, std::string type) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position)
            * glm::rotate(model, 180.f, rotation);
}

Entity::Entity(glm::vec3 position, int type) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position);

    modelNumber = type;
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, int type) {
    model = glm::mat4(1.f);
    model = glm::translate(model, position)
            * glm::rotate(model, 180.f, rotation);

    modelNumber = type;
}

Entity::Entity(glm::vec3 position, float f, int type){
    model = glm::mat4(1.f);
    model = glm::scale(glm::mat4(1.f), glm::vec3(f, f, f)) * glm::translate(model, position/f);

    modelNumber = type;
}

Entity::~Entity() {
    // TODO Auto-generated destructor stub
}

