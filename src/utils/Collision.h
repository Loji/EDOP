/*
 * collision.hpp
 *
 *  Created on: Nov 7, 2012
 *      Author: jacob
 */

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../includes.h"
#include "../entities.h"

class Collision {
public:
	Collision();
	virtual ~Collision();


	void initColl();
	void tickColl();
	void tickColl(float time);

	void addStaticCollision();
	void addStaticCollisionCube(bool high, glm::vec3 position);


	btDiscreteDynamicsWorld *world;

	btDispatcher *dispatcher;
	btBroadphaseInterface *broadphase;
	btConstraintSolver *solver;
	btCollisionConfiguration *collisionConfiguration;

	std::vector<btRigidBody*> bodies;


};

namespace collided {

	void initInput();
	void initInput(Collision &collision);
	void initInput(Collision &collision, glm::vec3 p);
	void initInput(glm::vec3 p);

	void computeMatricesFromInputs();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPosition();
	glm::vec3 getDirection();


}


#endif
