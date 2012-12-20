/*
 * Game.h
 *
 *  Created on: Jul 16, 2012
 *      Author: jacob
 */

#ifndef GAME_H_
#define GAME_H_

#include "../includes.h"

//renderables
#include "../renderable/Entity.h"
#include "../renderable/scenery/Map.h"
#include "../renderable/ModelSystem.h"
#include "../renderable/scenery/map/Terrain.h"
#include "../renderable/scenery/map/Level.h"


//utils
#include "../utils/shader.h"
#include "../utils/controls.h"
#include "../utils/Collision.h"



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
