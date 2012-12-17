/*
 * Player.hpp
 *
 *  Created on: Dec 1, 2012
 *      Author: jacob
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../includes.hpp"
#include "../utils/Collision.hpp"
#include "../renderable/Entity.hpp"
#include "../renderable/ModelSystem.hpp"

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
