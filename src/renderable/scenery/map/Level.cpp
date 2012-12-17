/*
 pf  * Level.cpp
 *
 *  Created on: Sep 29, 2012
 *      Author: jacob
 */

#include "Level.hpp"

Miner::Miner() {
}

// creates a Miner on specific position that will head random way
Miner::Miner(int x, int y) {
	alive = true;
	this->x = x;
	this->y = y;
	//this->way = rand() % 4;
	switch (rand() % 4) {
	case 0:
		hor = false;
		add = true;
		break;
	case 1:
		hor = true;
		add = true;
		break;
	case 2:
		hor = false;
		add = false;
		break;
	case 3:
		hor = true;
		add = false;
		break;
	}

}

// creates a Miner on specific position that will head specified way
Miner::Miner(int x, int y, int way) {
	alive = true;
	this->x = x;
	this->y = y;

	switch (way) {
	case 0:
		hor = false;
		add = true;
		break;
	case 1:
		hor = true;
		add = true;
		break;
	case 2:
		hor = false;
		add = false;
		break;
	case 3:
		hor = true;
		add = false;
		break;
	}
}

void Miner::init() {

}

//way 0 = y++ x
//way 1 = y x++
//way 2 = y-- x
//way 3 = y x--

void Miner::turn() {
	if (chanceM()) {
		if (chanceL())
			turn(true);
		else
			turn(false);
	}
}

bool Miner::turn(bool clockWise) {
	if (clockWise) {
		if (hor) {
			if (add) {
				hor = false;
				add = false;
				return true;
			} else {
				hor = false;
				add = true;
				return true;
			}
		} else {
			if (add) {
				hor = true;
				add = true;
				return true;
			} else {
				hor = true;
				add = false;
				return true;
			}
		}
	} else {
		if (hor) {
			if (add) {
				hor = true;
				add = true;
				return true;
			} else {
				hor = true;
				add = false;
				return true;
			}
		} else {
			if (add) {
				hor = false;
				add = false;
				return true;
			} else {
				hor = false;
				add = true;
				return true;
			}
		}
	}

	return false;
}

bool Miner::turnFast() {
	if (checked <= 4) {
		turn(directionC);
		return true;
	} else {
		alive = false;
		return false;
	}
}

void Miner::directionChecking() {
	directionC = chanceL();
}

void Miner::go() {
	if (hor)
		if (add)
			y++;
		else
			y--;
	else if (add)
		x++;
	else
		x--;
}

bool Miner::populate() {
	return chanceH();
}

bool Miner::chanceH() {
	return rand() % 100 > 65;
}

bool Miner::chanceM() {
	return rand() % 100 > 53;
}

bool Miner::chanceL() {
	return rand() % 100 > 49;
}

Level::Level() {
}

Level::Level(int x, int y) {
	sizeX = x;
	sizeY = y;

	data.clear();
//data.reserve(x*y);

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			data.push_back(true);
}

Level::~Level() {
}

void Level::init() {

}

void Level::generate() {

}

void Level::generate(int x, int y) {
	sizeX = x;
	sizeY = y;

	data.clear();
	data.reserve(x * y);

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			data.push_back(true);

//miners.push_back(new Miner(rand() % x - 5 + 5, rand() % y - 5 + 5));
	miners.push_back(new Miner(25, 25, 1));

	bool ifAlive;

	while (!miners.empty()) {
		//for(int aa = 0; aa<30; aa++) {
		ifAlive = false;
		std::vector<Miner*>::iterator mi;
		for (mi = miners.begin(); mi != miners.end(); ++mi) {
			if ((*mi)->alive) {
				(*mi)->directionChecking();
				(*mi)->checked = 0;
				while (!checkWall((*mi)->x, (*mi)->y, (*mi)->hor, (*mi)->add)
						&& (*mi)->alive) {
					(*mi)->turnFast();
					(*mi)->checked++;
				}

				std::cout << (*mi)->x << " " << (*mi)->y << " " << (*mi)->hor
						<< (*mi)->add << "\n";

				(*mi)->go();
				(*mi)->turn();
				if ((*mi)->populate()) {
					minersToAdd.push_back(new Miner((*mi)->x, (*mi)->y));
				}

				//std::cout << (*mi)->x << " " <<  (*mi)->y << " " << (*mi)->way << "\n";
				dataAt((*mi)->x, (*mi)->y, false);
				ifAlive = true;
			}
		}

		while (!minersToAdd.empty()) {
			std::vector<Miner*>::iterator mii;
			for (mii = minersToAdd.begin(); mii != minersToAdd.end(); ++mii) {
				miners.push_back(new Miner((*mii)->x, (*mii)->y));
			}
			minersToAdd.clear();
		}

		if (!ifAlive) {
			miners.clear();
			break;
		}
	}
}

bool Level::dataAt(int x, int y) {
	return data.at(x * sizeY + y);
}

bool Level::dataAt(int x, int y, bool set) {
//if (data.at(x * sizeX + y) == set)
//    return false;
//else {
	data.at(x * sizeX + y) = set;
	return true;
//}
}

void Level::create(std::vector<Entity*> &entities) {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (dataAt(i, j)) {
				entities.push_back(
						new Entity(glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40),
								0));
			} else {
				entities.push_back(
						new Entity(glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40),
								3));
			}
		}
	}
}

// needs adress of entities and collisions to add model and collision entity to it
void Level::create(std::vector<Entity*> &entities, Collision &collisions) {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (dataAt(i, j)) {
				if (i == 0 || j ==  0 || i >= sizeX -1  || j >= sizeY -1 ) {
					entities.push_back(
							new Entity(
									glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40),
									0));
					collisions.addStaticCollisionCube(true,
							glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40));

				} else if (!(dataAt(i - 1, j) && dataAt(i + 1, j)
						&& dataAt(i, j - 1) && dataAt(i, j + 1))) {
					entities.push_back(
							new Entity(
									glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40),
									0));
					collisions.addStaticCollisionCube(true,
							glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40));

				}
			} else {
				entities.push_back(
						new Entity(glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40),
								3));
				collisions.addStaticCollisionCube(false,
						glm::vec3(i * 2.f - 40, -4.f, j * 2.f - 40));
			}
		}
	}
}

glm::vec3 Level::getStablePosition() {
	for (int i = 1; i < sizeX-1; i++) {
			for (int j = 1; j < sizeY-1; j++) {
				if (!dataAt(i, j)) {
					return glm::vec3(i * 2.f - 40, -2.f, j * 2.f - 40);
				}
			}
	}

	return glm::vec3(0);
}

void Level::render() {

}

bool Level::checkWall(int x, int y, bool hor, bool add) {
	int t1X = x;
	int t1Y = y;
	int t2X = x;
	int t2Y = y;

	if (x > 3 && y > 3 && x < sizeX - 3 && y < sizeY - 3) {
		if (hor) {
			if (add) {
				t1X += 1;
				t2X += 2;
			} else {
				t1X -= 1;
				t2X -= 2;
			}
		} else {
			if (add) {
				t1Y += 1;
				t2Y += 2;
			} else {
				t1Y -= 1;
				t2Y -= 2;
			}
		}

		return (data[t1X * sizeX + t1Y] && data[t2X * sizeX + t2Y]);
	}
	return false;
}
