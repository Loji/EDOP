/*
 * Light.hpp
 *
 *  Created on: Aug 13, 2012
 *      Author: jacob
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include "../../includes.hpp"

class LightSystem {
public:
    LightSystem();
    LightSystem(GLuint &shader);
    LightSystem(glm::vec3 color, GLuint &shader);
    virtual ~LightSystem();

    void init();

    void render();

    int addPoint(glm::vec3 position, glm::vec3 color);

    void editAmbient(glm::vec3 color);

    void editLp(int index, glm::vec3 position);
    void editLc(int index, glm::vec3 color);
    void editLpc(int index, glm::vec3 position, glm::vec3 color);

private:
    struct Light {
        glm::vec3 position;
        glm::vec3 color;
    };

    struct Point : Light {

    };

    struct Directional : Light {

    };

    void renderLight();

    GLuint LightBuffer;
    GLuint LightCount;

    GLuint *shader;
    GLuint DiffuseID[3];
    GLuint AmbientID;
    glm::vec3 ambientColor;
    std::vector<Light> lightList;
};

#endif /* LIGHT_HPP_ */
