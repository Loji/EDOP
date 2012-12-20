/*
 * Light.cpp
 *
 *  Created on: Aug 13, 2012
 *      Author: jacob
 */

#include "LightSystem.h"
#include <sstream>

LightSystem::LightSystem() {
}

LightSystem::LightSystem(GLuint &shader) {
    this->shader = &shader;

}

LightSystem::LightSystem(glm::vec3 color, GLuint &shader) {

    this->shader = &shader;
    this->ambientColor = color;

}

void LightSystem::init() {
    AmbientID = glGetUniformLocation(*shader, "ambientCol");
    DiffuseID[0] = glGetUniformLocation(*shader, "diffusePos");
    DiffuseID[1] = glGetUniformLocation(*shader, "diffuseCol");
    DiffuseID[2] = glGetUniformLocation(*shader, "diffuseDir");

    //setting up buffer for lights
    LightCount = glGetUniformLocation(*shader, "LightsCount");

    //names = new GLchar

}

LightSystem::~LightSystem() {

}

int LightSystem::addPoint(glm::vec3 position, glm::vec3 color) {
    Light temp;
    temp.position = position;
    temp.color = color;
    lightList.push_back(temp);

    return lightList.size();
}

// not working function that was supposed to generate table of names for shader reference
std::vector<const GLchar*> getNames(int size) {
    std::vector<const GLchar*> names;

    for (int i = 0; i < size; i++) {
        std::stringstream ss;
        ss << i;
        std::string s = ss.str();
        std::string s1 = "Lights.pos[" + s + "]";
        std::string s2 = "Lights.col[" + s + "]";

        names.push_back(s1.c_str());
        names.push_back(s2.c_str());
    }

    return names;
}

void errorCheck() {
    GLenum errCode;
    const GLubyte *errString;

    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        std::cout << "OpenGL Error: " << errString << "\n";
    }
}


std::vector<GLint> lightUniformOffsets;

// char table containing all the references to light in shader
const GLchar *names[] = { "Lights.cont[0].pos", "Lights.cont[0].col",
        "Lights.cont[1].pos", "Lights.cont[1].col", "Lights.cont[2].pos",
        "Lights.cont[2].col", "Lights.cont[3].pos", "Lights.cont[3].col",
        "Lights.cont[4].pos", "Lights.cont[4].col", "Lights.cont[5].pos",
        "Lights.cont[5].col", "Lights.cont[6].pos", "Lights.cont[6].col",
        "Lights.cont[7].pos", "Lights.cont[7].col", "Lights.cont[8].pos",
        "Lights.cont[8].col", "Lights.cont[9].pos", "Lights.cont[9].col",
        "Lights.cont[10].pos", "Lights.cont[10].col", "Lights.cont[11].pos",
        "Lights.cont[11].col", "Lights.cont[12].pos", "Lights.cont[12].col",
        "Lights.cont[13].pos", "Lights.cont[13].col", "Lights.cont[14].pos",
        "Lights.cont[14].col", "Lights.cont[15].pos", "Lights.cont[15].col",
        "Lights.cont[16].pos", "Lights.cont[16].col", "Lights.cont[17].pos",
        "Lights.cont[17].col", "Lights.cont[18].pos", "Lights.cont[18].col",
        "Lights.cont[19].pos", "Lights.cont[19].col", "Lights.cont[20].pos",
        "Lights.cont[20].col", "Lights.cont[21].pos", "Lights.cont[21].col",
        "Lights.cont[22].pos", "Lights.cont[22].col", "Lights.cont[23].pos",
        "Lights.cont[23].col", "Lights.cont[24].pos", "Lights.cont[24].col",
        "Lights.cont[25].pos", "Lights.cont[25].col", "Lights.cont[26].pos",
        "Lights.cont[26].col", "Lights.cont[27].pos", "Lights.cont[27].col",
        "Lights.cont[28].pos", "Lights.cont[28].col", "Lights.cont[29].pos",
        "Lights.cont[29].col", "Lights.cont[30].pos", "Lights.cont[30].col",
        "Lights.cont[31].pos", "Lights.cont[31].col" };

void LightSystem::renderLight() {
    // creating temporary data that will be send to light buffer
    glGenBuffers(1, &LightBuffer);

    glBindBuffer(GL_UNIFORM_BUFFER, LightBuffer);
    int lc = lightList.size();

    const GLchar *uniformNames[1] = { "Lights.cont" };
    GLuint uniformIndices;

    glGetUniformIndices(*shader, 1, uniformNames, &uniformIndices);

    GLint uniformOffsets[1];
    glGetActiveUniformsiv(*shader, 1, &uniformIndices, GL_UNIFORM_OFFSET,
            uniformOffsets);

    GLuint uniformIndex = glGetUniformBlockIndex(*shader, "Lights");

    GLsizei uniformBlockSize(0);
    glGetActiveUniformBlockiv(*shader, uniformIndex, GL_UNIFORM_BLOCK_DATA_SIZE,
            &uniformBlockSize);

    GLint maxSize;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxSize);
    GLint bufferAlignment;
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &bufferAlignment);

    //std::cout << "Uniform Block size: " << uniformBlockSize << std::endl;
    //std::cout << "Uniform Block max size: " << maxSize << std::endl;
    //std::cout << "Uniform Buffer alignment: " << bufferAlignment << std::endl;

    GLuint indices[lc * 2];

    glGetUniformIndices(*shader, lc * 2, names, indices);

    lightUniformOffsets.clear();
    lightUniformOffsets.resize(lc * 2);

    glGetActiveUniformsiv(*shader, lightUniformOffsets.size(), indices,
            GL_UNIFORM_OFFSET, &lightUniformOffsets[0]);
    GLint *offsets = &lightUniformOffsets[0];

    unsigned int bSize(uniformBlockSize);
    std::vector<unsigned char> buffer(bSize);

    int offset;

    for (unsigned int n = 0; n < lightList.size(); ++n) {
        offset = offsets[0 + n * 2];

        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) = lightList[n].position.x;
        offset += sizeof(GLfloat);
        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) = lightList[n].position.y;
        offset += sizeof(GLfloat);
        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) = lightList[n].position.z;
        offset += sizeof(GLfloat);

        offset = offsets[1 + n * 2];
        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) =
                lightList[n].color.x;
        offset += sizeof(GLfloat);
        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) =
                lightList[n].color.y;
        offset += sizeof(GLfloat);
        *(reinterpret_cast<GLfloat*>(&buffer[0] + offset)) =
                lightList[n].color.z;
        offset += sizeof(GLfloat);
    }

    glUniform1i(LightCount, lc);

    glBufferData(GL_UNIFORM_BUFFER, bSize, &buffer[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, LightBuffer);
    glUniformBlockBinding(*shader, uniformIndex, 0);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightSystem::render() {
    glUniform3f(AmbientID, ambientColor.x, ambientColor.y, ambientColor.z);

    if (!lightList.empty())
        renderLight();
}

void LightSystem::editAmbient(glm::vec3 color) {

}

void LightSystem::editLp(int index, glm::vec3 position) {
    lightList.at(index).position = position;
}

void LightSystem::editLc(int index, glm::vec3 color) {

}

void LightSystem::editLpc(int index, glm::vec3 position, glm::vec3 color) {

}
