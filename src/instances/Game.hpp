/*
 * Game.h
 *
 *  Created on: Jul 16, 2012
 *      Author: jacob
 */

#ifndef GAME_H_
#define GAME_H_

#include "../includes.hpp"

//renderables
#include "../renderable/Entity.hpp"
#include "../renderable/scenery/Map.hpp"
#include "../renderable/ModelSystem.hpp"
#include "../renderable/scenery/map/Terrain.hpp"
#include "../renderable/scenery/map/Level.hpp"


//utils
#include "../utils/shader.hpp"
#include "../utils/controls.hpp"
#include "../utils/Collision.hpp"



class Game {
public:
    Game();
    virtual ~Game();

    void init();
    void run();
    void run(bool update);
    void clean();

    void render();
    void update();
private:
    void takeInput();

    std::vector<Entity*> *entities;
    ModelSystem modelSystem;
    Collision collision;

    Terrain terrain;

    LightSystem light;

    GLuint shader;
    GLuint VertexArrayID;

    GLuint ProjectionID;
    GLuint nMatrixID;
    GLuint ViewID;
    GLuint ModelID;


    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 playerPos;
};

#endif /* GAME_H_ */
