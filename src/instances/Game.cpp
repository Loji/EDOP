/*
 * Game.cpp
 *
 *  Created on: Jul 16, 2012
 *      Author: jacob
 */

#include "Game.h"

static const int HEIGHT = 1024;
static const int WIDTH = 768;

void Game::init() {
	glClearColor(0.25f, 0.f, 0.25f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glViewport(0, 0, HEIGHT, WIDTH);

	modelSystem.create();

	///////////
	terrain.generate(20, 20, 2);

	Level level;
	level.generate(100, 100);

	// creates collisions in the bullet physics engine
	// used for computing camera position
	collision.initColl();

	// passes pointer to entities list as it pushes walls and floor blocks of level to entities list
	// and collisions object so it can add objects to collisions queue
	level.create(*entities, collision);

	//////////
	collided::initInput(collision, level.getStablePosition());

}

int boxCount = 0;

bool pressed[255];
glm::vec3 directionP;
glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);

void Game::update() {
	takeInput();

	// Sends a timer to collision counter, need to be done
	collision.tickColl(1 / 60.f);

	// Computing camera position with collisions
	collided::computeMatricesFromInputs();
	view = collided::getViewMatrix();
	playerPos = collided::getPosition();
	directionP = collided::getDirection();
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glUseProgram(shader);

	//Projection and View matrices
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);

	//light system rendering
	light.render();

	if (!entities->empty()) {
		std::vector<Entity*>::iterator en;
		for (en = entities->begin(); en != entities->end(); ++en) {
			(*en)->render(view, ModelID, nMatrixID, modelSystem);
		}
	}

	//terrain.render(view, ModelID, nMatrixID);

	glUseProgram(0);
}

static const int lightLimit = 32;
int lightCounter = 0;

void Game::takeInput() {
	// creating light in player position
	if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS && pressed[0] == false
			&& lightCounter < lightLimit) {
		light.addPoint(playerPos, color);

		entities->push_back(new Entity(playerPos, 0.1f, 1));
		pressed[0] = true;

		lightCounter++;
	}
	if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE)
		pressed[0] = false;
	///////////////////////////////////////////////////////////////////////////

	// adding some models to the player position
	if (glfwGetKey(69) == GLFW_PRESS && pressed[1] == false) {
		entities->push_back(new Entity(playerPos, 0));
		pressed[1] = true;
	}
	if (glfwGetKey(69) == GLFW_RELEASE)
		pressed[1] = false;

	if (glfwGetKey(81) == GLFW_PRESS && pressed[2] == false) {
		entities->push_back(new Entity(playerPos, 2));
		pressed[2] = true;
	}
	if (glfwGetKey(81) == GLFW_RELEASE)
		pressed[2] = false;
	///////////////////////////////////////////////////////////////////////////

	// changing light colors
	if (glfwGetKey(49) == GLFW_PRESS && pressed[3] == false) {
		color = glm::vec3(1.f, 0.f, 0.f);
		pressed[3] = true;
	}
	if (glfwGetKey(49) == GLFW_RELEASE)
		pressed[3] = false;

	if (glfwGetKey(50) == GLFW_PRESS && pressed[4] == false) {
		color = glm::vec3(0.f, 1.f, 0.f);
		pressed[4] = true;
	}
	if (glfwGetKey(50) == GLFW_RELEASE)
		pressed[4] = false;

	if (glfwGetKey(51) == GLFW_PRESS && pressed[5] == false) {
		color = glm::vec3(0.f, 0.f, 1.f);
		pressed[5] = true;
	}
	if (glfwGetKey(51) == GLFW_RELEASE)
		pressed[5] = false;

	if (glfwGetKey(52) == GLFW_PRESS && pressed[6] == false) {
		color = glm::vec3(1.f, 1.f, 1.f);
		pressed[6] = true;
	}
	if (glfwGetKey(51) == GLFW_RELEASE)
		pressed[6] = false;

}

void Game::clean() {
	if (!entities->empty()) {
		/*std::vector<Entity*>::iterator en;
		for (en = entities->begin(); en != entities->end(); ++en) {

		}*/
		for (unsigned int i = 0; i<entities->size(); ++i)
			delete entities->at(i);
	}
	delete entities;

}

void Game::run() {
	update();
	render();
}

void Game::run(bool update) {
	render();
}

Game::Game() {
	entities = new std::vector<Entity*>;
	light = LightSystem(glm::vec3(0.25f), shader);

	// loading shaders, full path since I want to keep them in sources, later will be moved somewhere else
	shader = LoadShaders(
			"/home/jacob/git/EDOP/src/renderable/shader/SimpleShader.vert",
			"/home/jacob/git/EDOP/src/renderable/shader/SimpleShader.frag");

	modelSystem = ModelSystem(shader);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	light.init();

	//light.addPoint(glm::vec3(1.f), glm::vec3(0.5f, 0.5f, 0.5f));
	//entities->push_back(new Entity(glm::vec3(1.f), 0.2f, 0));

	// Creating handles to matrices from shader
	nMatrixID = glGetUniformLocation(shader, "nM");

	ModelID = glGetUniformLocation(shader, "M");
	ViewID = glGetUniformLocation(shader, "V");
	ProjectionID = glGetUniformLocation(shader, "P");

	projection = glm::perspective(60.0f, 1.f, 0.1f, 100.0f);
	view = glm::lookAt(glm::vec3(15.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 1.f, 0.f));

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

