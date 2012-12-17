/*
 * main.cpp
 *
 *  Created on: Jul 15, 2012
 *      Author: jacob
 */

#include "includes.hpp"
#include "instances/Game.hpp"

int main() {

    glewExperimental = GL_TRUE;

    if (!glfwInit()) {
        return -1;
    }

    //glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);


    if (!glfwOpenWindow(700, 700, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        glfwTerminate();
        return -1;
    }

    if (glewInit() != GLEW_OK) {
        return -1;
    }
    glfwSetWindowTitle("Debugg");

    bool running = true;
    glfwEnable(GLFW_STICKY_KEYS);

    srand(time(NULL));

    Game game = Game();

    game.init();

    while (running) {
        if ((glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS))
            running = false;
        game.run();
        glfwSwapBuffers();

    }
    game.clean();
    return 1;
}
