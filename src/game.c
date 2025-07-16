#include "GLFW/glfw3.h"
#include "stdlib.h"

#include "paddle.h"
#include "game.h"

struct _Game {
    GLFWwindow* window;
    Renderer* renderer;

    float last_frame_time;
    float current_frame_time;
    float delta;

    Paddle* left_paddle;
    Paddle* right_paddle;
};

Game* game_create() {
    Game* self = malloc(sizeof(Game));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    self->window = glfwCreateWindow((int32_t)GAME_WIDTH, (int32_t)GAME_HEIGHT, "tennis-gl", NULL, NULL);
    glfwMakeContextCurrent(self->window);

    self->renderer = renderer_create();

    self->left_paddle = paddle_create(PADDLE_TYPE_LEFT);
    self->right_paddle = paddle_create(PADDLE_TYPE_RIGHT);

    return self;
}

void game_destroy(Game* self) {
    paddle_destroy(self->left_paddle);
    paddle_destroy(self->right_paddle);

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

    self->current_frame_time = glfwGetTime();
    self->delta = self->current_frame_time - self->last_frame_time;
    self->last_frame_time = self->current_frame_time;

    paddle_handle_input(self->left_paddle, self->window, self->delta);
    paddle_handle_input(self->right_paddle, self->window, self->delta);

    renderer_clear(self->renderer);

    renderer_draw_rect(self->renderer, paddle_get_rect(self->left_paddle));
    renderer_draw_rect(self->renderer, paddle_get_rect(self->right_paddle));

    glfwSwapBuffers(self->window);
}
