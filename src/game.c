#include "GLFW/glfw3.h"
#include "stdlib.h"

#include "game.h"

struct _Game {
    GLFWwindow* window;
};

Game* game_create() {
    Game* self = malloc(sizeof(Game));
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    self->window = glfwCreateWindow(1280, 720, "tennis-gl", NULL, NULL);
    glfwMakeContextCurrent(self->window);

    return self;
}

void game_destroy(Game* self) {
    glfwDestroyWindow(self->window);
    glfwTerminate();
}

bool game_is_running(const Game* self) {
    return !glfwWindowShouldClose(self->window);
}

void game_update(Game* self) {
    glfwPollEvents();

    glClearColor(0.2, 0.3, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(self->window);
}
