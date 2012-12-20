/*
 * Player.hpp
 *
 *  Created on: Dec 1, 2012
 *      Author: jacob
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../includes.h"
#include "../utils/Collision.h"
#include "../renderable/Entity.h"
#include "../renderable/ModelSystem.h"

class Player {
public:
	Player();
	virtual ~Player();

	void render();
	void update();

	Collision collision;
	Entity *gun;

};

#endif /* PLAYER_HPP_ */
