/*
 * LoadTexture.cpp
 *
 *  Created on: Oct 19, 2012
 *      Author: jacob
 */

#include "LoadTexture.h"

LoadTexture::LoadTexture() {
	// TODO Auto-generated constructor stub

}

LoadTexture::~LoadTexture() {
	// TODO Auto-generated destructor stub
}

GLuint LoadTexture::loadTGA(std::string path) {

	GLuint tID;
	glGenTextures(1, &tID);

	glBindTexture(GL_TEXTURE_2D, tID);

	glfwLoadTexture2D(path.c_str(), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return tID;
}

