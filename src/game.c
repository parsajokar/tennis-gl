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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    self->window = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, "tennis-gl", NULL, NULL);
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

    Rect rect = {
        .x = 100.0,
        .y = 100.0,
        .w = 100.0,
        .h = 100.0
    };

    renderer_clear(self->renderer);
    renderer_draw_rect(self->renderer, &rect);

    glfwSwapBuffers(self->window);
}
