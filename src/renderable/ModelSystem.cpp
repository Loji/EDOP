/*
 * ModelSystem.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: jacob
 */

#include "ModelSystem.hpp"

ModelSystem::Model::Model(std::string path) {
	loadShape(path);
	textured = false;
	createBuffers();
}

ModelSystem::Model::Model(std::string path, std::string pathTexture) {
	loadShape(path);
	loadTexture(pathTexture);
	textured = true;
	createBuffers();
}

ModelSystem::Model::~Model() {
	// TODO Auto-generated destructor stub
}

void ModelSystem::Model::render() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(*textureShaderID, 0);

	// enabling specific arrays
	// every instance of model have it own arrays
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_TRIANGLES, 0, ver.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void ModelSystem::Model::setShaderID(GLuint &textureShaderID) {
	this->textureShaderID = &textureShaderID;
}

void ModelSystem::Model::createBuffers() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(glm::vec3), &ver[0],
			GL_STATIC_DRAW);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec3), &nor[0],
			GL_STATIC_DRAW);

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, tex.size() * sizeof(glm::vec2), &tex[0],
			GL_STATIC_DRAW);

}

void ModelSystem::Model::loadShape(std::string path) {
	LoadModel *shape = new LoadModel();
	shape->loadModel(path.c_str());

	this->ver = shape->vertices;
	this->tex = shape->texture;
	this->col = shape->colors;
	this->nor = shape->normals;

	delete shape;
}

void ModelSystem::Model::loadTexture(std::string path) {
	LoadTexture *texture = new LoadTexture();
	this->textureID = texture->loadTGA(path);
}

ModelSystem::ModelSystem() {

}

ModelSystem::ModelSystem(GLuint &shader) {
	this->shader = &shader;
	textureShaderID = glGetUniformLocation(*this->shader, "textureSampler");
}

// pushing some models to models list so they can be refered to later
void ModelSystem::create() {
	//modelList.clear();

	modelList.push_back(
			new Model("/home/jacob/git/edop/res/1.obj",
					"/home/jacob/git/edop/res/1.tga"));
	modelList.at(0)->setShaderID(textureShaderID);

	modelList.push_back(
			new Model("/home/jacob/git/edop/res/2.obj",
					"/home/jacob/git/edop/res/2.tga"));
	modelList.at(1)->setShaderID(textureShaderID);

	modelList.push_back(
			new Model("/home/jacob/git/edop/res/pistol.obj",
					"/home/jacob/git/edop/res/pistol.tga"));
	modelList.at(2)->setShaderID(textureShaderID);

	modelList.push_back(
			new Model("/home/jacob/git/edop/res/3.obj",
					"/home/jacob/git/edop/res/3.tga"));
	modelList.at(3)->setShaderID(textureShaderID);

}

void ModelSystem::render(int number) {
	modelList.at(number)->render();
}

