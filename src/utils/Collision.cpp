/*
 * collision.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: jacob
 */

#include "Collision.h"

Collision::Collision() {

}

Collision::~Collision() {
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete world;
}

void Collision::initColl() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
			collisionConfiguration);
	world->setGravity(btVector3(0, -150, 0));
}

void Collision::tickColl() {

}

void Collision::tickColl(float time) {
	world->stepSimulation(time);
}

void Collision::addStaticCollision() {

}

void Collision::addStaticCollisionCube(bool high, glm::vec3 position) {
	btTransform t;
	t.setIdentity();
	if (high)
		t.setOrigin(btVector3(position.x, position.y, position.z));
	else
		t.setOrigin(btVector3(position.x, position.y - 1, position.z));

	btBoxShape *box = new btBoxShape(btVector3(1, 1, 1));
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, box);
	btRigidBody* body = new btRigidBody(info);
	world->addRigidBody(body);
	bodies.push_back(body);
}

namespace collided {

int screenHeight;
int screenWidth;

btRigidBody *cameraBody;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 position = glm::vec3(0, 0, 15);
glm::vec3 direction;

Collision *coll;

float mass = 0.3f;
unsigned int cameraIndex;

void initInput() {
	GLFWvidmode vid;
	glfwGetDesktopMode(&vid);
	screenHeight = vid.Height;
	screenWidth = vid.Width;

	btCylinderShape *shape = new btCylinderShape(btVector3(0.2f, 2, 0.2f));

	btVector3 iner(0, 0, 0);
	if (mass != 0)
		shape->calculateLocalInertia(mass, iner);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(0, 0, 5));
	btMotionState *motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, iner);

	cameraBody = new btRigidBody(info);
}

void initInput(Collision &collision) {
	GLFWvidmode vid;
	glfwGetDesktopMode(&vid);
	screenHeight = vid.Height;
	screenWidth = vid.Width;

	//btCylinderShape *shape = new btCylinderShape(btVector3(1, 0.1, 1));
	btSphereShape *shape = new btSphereShape(0.3f);

	btVector3 iner(0, 0, 0);
	if (mass != 0)
		shape->calculateLocalInertia(mass, iner);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(0, 0, 15));
	btMotionState *motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, iner);

	cameraBody = new btRigidBody(info);
	collision.world->addRigidBody(cameraBody);
	cameraIndex = collision.bodies.size();

	coll = &collision;
}

void initInput(Collision &collision, glm::vec3 p) {
	GLFWvidmode vid;
	glfwGetDesktopMode(&vid);
	screenHeight = vid.Height;
	screenWidth = vid.Width;

	//btCylinderShape *shape = new btCylinderShape(btVector3(1, 0.1, 1));
	btSphereShape *shape = new btSphereShape(0.3f);

	btVector3 iner(0, 0, 0);
	if (mass != 0)
		shape->calculateLocalInertia(mass, iner);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(p.x, p.y, p.z));
	btMotionState *motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, iner);

	cameraBody = new btRigidBody(info);
	collision.world->addRigidBody(cameraBody);

	position = p;
	coll = &collision;
}

void initInput(glm::vec3 p) {
	GLFWvidmode vid;
	glfwGetDesktopMode(&vid);
	screenHeight = vid.Height;
	screenWidth = vid.Width;

	btSphereShape *shape = new btSphereShape(1);

	btVector3 iner(0, 0, 0);
	if (mass != 0)
		shape->calculateLocalInertia(mass, iner);

	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(p.x, p.y, p.z));
	btMotionState *motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, iner);

	cameraBody = new btRigidBody(info);

	position = p;
}

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::vec3 getPosition() {
	return position;
}
glm::vec3 getDirection() {
	return direction;
}

float horizontalAngle = 0.f;
float verticalAngle = 1.f;

float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;

bool lockMouse = true;
bool lockMousePressed = false;

bool gravity = true;
bool gravityPressed = false;

void computeMatricesFromInputs() {

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();

	float deltaTime = float(currentTime - lastTime);

	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);

	if (lockMouse) {
		glfwSetMousePos(200, 200);

		horizontalAngle += mouseSpeed * float(200 - xpos);
		verticalAngle += mouseSpeed * float(200 - ypos);
		if (verticalAngle < -2.f)
			verticalAngle = -2.f;
		if (verticalAngle > 2.f)
			verticalAngle = 2.f;
	}

	direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	glm::vec3 front;
	if (gravity)
		front = glm::vec3(cos(0) * sin(horizontalAngle), sin(0),
				cos(0) * cos(horizontalAngle));
	else
		front = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0,
			cos(horizontalAngle - 3.14f / 2.0f));

	glm::vec3 up = glm::cross(right, direction);

	// test

	glm::vec3 testVec(0, 0, 0);

	// /test

	speed = 3.0f;
	if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS) {
		speed = 7.0f;
	}
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(87) == GLFW_PRESS) {
		position += front * deltaTime * speed;
		testVec += front * deltaTime * speed;
	}
	if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(83) == GLFW_PRESS) {
		position -= front * deltaTime * speed;
		testVec -= front * deltaTime * speed;
	}
	if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(68) == GLFW_PRESS) {
		position += right * deltaTime * speed;
		testVec += right * deltaTime * speed;
	}
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(65) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
		testVec -= right * deltaTime * speed;
	}

	//lock screen for tab
	if (glfwGetKey(GLFW_KEY_TAB) == GLFW_PRESS && lockMousePressed) {
		lockMouse = !lockMouse;
		lockMousePressed = false;
	}
	if (glfwGetKey(GLFW_KEY_TAB) == GLFW_RELEASE)
		lockMousePressed = true;

	//gravity on/off key
	if (glfwGetKey(90) == GLFW_PRESS && gravityPressed) {
		gravity = !gravity;
		if(!gravity) {
			coll->world->setGravity(btVector3(0,0,0));
		} else {
			coll->world->setGravity(btVector3(0,-150.f,0));
		}

		gravityPressed = false;
	}
	if (glfwGetKey(90) == GLFW_RELEASE)
		gravityPressed = true;

	float FoV = initialFoV;

	cameraBody->setLinearVelocity(
			btVector3(testVec.x * 25, testVec.y * 25, testVec.z * 25));
	cameraBody->setMassProps(mass, btVector3(0,0,0));

	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(
			glm::vec3(cameraBody->getCenterOfMassPosition().x(),
					cameraBody->getCenterOfMassPosition().y(),
					cameraBody->getCenterOfMassPosition().z()),
			glm::vec3(cameraBody->getCenterOfMassPosition().x(),
					cameraBody->getCenterOfMassPosition().y(),
					cameraBody->getCenterOfMassPosition().z()) + direction, up);

	position.x = cameraBody->getCenterOfMassPosition().x();
	position.y = cameraBody->getCenterOfMassPosition().y();
	position.z = cameraBody->getCenterOfMassPosition().z();

	lastTime = currentTime;
}

} // namespace collided
