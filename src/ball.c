#include "stdlib.h"
#include "stdint.h"
#include "math.h"

#include "game.h"
#include "paddle.h"
#include "ball.h"

#define DEG2RAD (M_PI / 180.0)

struct _Ball {
    Rect rect;
    uint32_t rotation_state;
    float speed;
};

static const float rotation_list[4] = {
    45.0 * DEG2RAD,
    135.0 * DEG2RAD,
    225.0 * DEG2RAD,
    315.0 * DEG2RAD
};

Ball* ball_create() {
    Ball* self = malloc(sizeof(Ball));
    ball_reset(self);

    return self;
}

void ball_destroy(Ball* self) {
    free(self);
}

void ball_move(Ball* self, float delta) {
    float rotation = rotation_list[self->rotation_state];

    float direction_x = cosf(rotation);
    float direction_y = sinf(rotation);

    self->rect.x += direction_x * self->speed * delta;
    self->rect.y += direction_y * self->speed * delta;

    if (self->rect.y < 0.0) {
        self->rect.y = 0.0;

        if (self->rotation_state == 2) {
            self->rotation_state = 1;
        } else {
            self->rotation_state = 0;
        }
    }
    if (self->rect.y > GAME_HEIGHT - BALL_HEIGHT) {
        self->rect.y = GAME_HEIGHT - BALL_HEIGHT;

        if (self->rotation_state == 0) {
            self->rotation_state = 3;
        } else {
            self->rotation_state = 2;
        }
    }
}

void ball_collide_with_paddle(Ball* self) {
    if (self->rotation_state == 0) {
        self->rotation_state = 1;
        self->rect.x = GAME_WIDTH - PADDLE_WIDTH;
    } else if (self->rotation_state == 1) {
        self->rotation_state = 0;
        self->rect.x = PADDLE_WIDTH;
    } else if (self->rotation_state == 2) {
        self->rotation_state = 3;
        self->rect.x = PADDLE_WIDTH;
    } else {
        self->rotation_state = 2;
        self->rect.x = GAME_WIDTH - PADDLE_WIDTH;
    }
}

void ball_reset(Ball* self) {
    self->rect.x = (GAME_WIDTH - BALL_WIDTH) / 2;
    self->rect.y = (GAME_HEIGHT - BALL_HEIGHT) / 2;
    self->rect.w = BALL_WIDTH;
    self->rect.h = BALL_HEIGHT;

    self->rotation_state = 0;
    self->speed = BALL_INITIAL_SPEED;
}

const Rect* ball_get_rect(const Ball* self) {
    return &self->rect;
}
