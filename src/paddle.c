#include "stdlib.h"

#include "game.h"
#include "paddle.h"

#define PADDLE_WIDTH 10.0
#define PADDLE_HEIGHT 100.0
#define PADDLE_SPEED 800.0

struct _Paddle {
    Rect rect;
    uint32_t up_key;
    uint32_t down_key;
};

static float clamp(float value, float left, float right) {
    if (value < left) {
        return left;
    }
    if (value > right) {
        return right;
    }

    return value;
}

Paddle* paddle_create(PaddleType type) {
    Paddle* self = malloc(sizeof(Paddle));

    self->rect.y = (GAME_HEIGHT - PADDLE_HEIGHT) / 2;
    self->rect.w = PADDLE_WIDTH;
    self->rect.h = PADDLE_HEIGHT;

    if (type == PADDLE_TYPE_LEFT) {
        self->rect.x = 0.0;
        self->up_key = GLFW_KEY_W;
        self->down_key = GLFW_KEY_S;
    } else {
        self->rect.x = GAME_WIDTH - PADDLE_WIDTH;
        self->up_key = GLFW_KEY_UP;
        self->down_key = GLFW_KEY_DOWN;
    }

    return self;
}

void paddle_destroy(Paddle* self) {
    free(self);
}

void paddle_handle_input(Paddle* self, GLFWwindow* window, float delta) {
    if (glfwGetKey(window, self->up_key) == GLFW_PRESS) {
        self->rect.y += PADDLE_SPEED * delta;
    }
    if (glfwGetKey(window, self->down_key) == GLFW_PRESS) {
        self->rect.y -= PADDLE_SPEED * delta;
    }

    self->rect.y = clamp(self->rect.y, 0.0, GAME_HEIGHT - PADDLE_HEIGHT);
}

const Rect* paddle_get_rect(const Paddle* self) {
    return &self->rect;
}
