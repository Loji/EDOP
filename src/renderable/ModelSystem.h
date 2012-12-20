/*
 * ModelSystem.h
 *
 *  Created on: Sep 15, 2012
 *      Author: jacob
 */

#ifndef MODELSYSTEM_HPP
#define MODELSYSTEM_HPP

#include "../includes.h"
#include "shapes/Shape.h"
#include "shapes/LoadModel.h"
#include "shapes/LoadTexture.h"

class ModelSystem {
public:
	ModelSystem();
	ModelSystem(GLuint &shader);

	class Model {
	public:
		Model(std::string path);
		Model(std::string path, std::string pathTexture);
		virtual ~Model();

		void createBuffers();
		void render();

		void setShaderID(GLuint &textureShaderID);

		GLuint vbo;  //vertex
		GLuint cbo;  //color
		GLuint tbo;  //texture
		GLuint nbo;  //normal

		bool textured;
		GLuint textureID;
		GLuint *textureShaderID;

		std::vector<glm::vec3> ver;
		std::vector<glm::vec3> col;
		std::vector<glm::vec3> nor;
		std::vector<glm::vec2> tex;


	private:
		void loadShape(std::string path);
		void loadTexture(std::string path);
	};

	std::vector<Model*> modelList;
	GLuint *shader;

	void create();
	void render(int number);

	GLuint textureShaderID;
private:
};

#endif
