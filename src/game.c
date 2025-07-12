#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "stdlib.h"

#include "renderer.h"
#include "game.h"

struct _Game {
    GLFWwindow* window;
    Renderer* renderer;
};

Game* game_create() {
    Game* self = malloc(sizeof(Game));
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    self->window = glfwCreateWindow(1280, 720, "tennis-gl", NULL, NULL);
    glfwMakeContextCurrent(self->window);

    self->renderer = renderer_create();

    return self;
}

void game_destroy(Game* self) {
    renderer_destroy(self->renderer);

    glfwDestroyWindow(self->window);
    glfwTerminate();

    free(self);
}

bool game_is_running(const Game* self) {
    return !glfwWindowShouldClose(self->window);
}

void game_update(Game* self) {
    glfwPollEvents();

    renderer_clear(self->renderer);
    renderer_draw_rect(self->renderer, NULL);

    glfwSwapBuffers(self->window);
}
