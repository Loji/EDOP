/*
 * Level.hpp
 *
 *  Created on: Sep 29, 2012
 *      Author: jacob
 */

#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "../../../includes.hpp"
#include "../../Entity.hpp"
#include "../../../utils/Collision.hpp"

class Miner {
public:
    Miner();
    Miner(int x, int y);
    Miner(int x, int y, int way);

    int x;
    int y;

    bool wayX;
    bool wayY;
    bool hor;
    bool add;

    bool alive;

    void init();
    void go();
    void turn();
    bool turn(bool clockWise);
    bool turnFast();

    void directionChecking();

    bool populate();

    void checkWall(std::vector<bool*> *list);
    //bool checked[4];
    int checked;


private:
    bool chanceH();
    bool chanceM();
    bool chanceL();

    bool directionC;
};

class Level {
public:
    Level();
    Level(int x, int y);
    virtual ~Level();

    void init();
    void create(std::vector<Entity*> &entities);
    void create(std::vector<Entity*> &entities, Collision &collisions);
    glm::vec3 getStablePosition();
    void render();

    void generate(int x, int y);
    void generate();

    bool dataAt(int x, int y);
    bool dataAt(int x, int y, bool set);

    int sizeX;
    int sizeY;

    bool checkWall(int x, int y, bool hor, bool add);

    std::vector<bool> data;
    std::vector<Miner*> miners;
    std::vector<Miner*> minersToAdd;
};

#endif /* LEVEL_HPP_ */
