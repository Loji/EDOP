/*
 * LoadTexture.hpp
 *
 *  Created on: Oct 19, 2012
 *      Author: jacob
 */

#ifndef LOADTEXTURE_HPP_
#define LOADTEXTURE_HPP_

#include "../../includes.h"

class LoadTexture {
public:
	LoadTexture();
	virtual ~LoadTexture();

	GLuint loadTGA(std::string path);

};

#endif /* LOADTEXTURE_HPP_ */
