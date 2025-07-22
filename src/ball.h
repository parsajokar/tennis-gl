#ifndef BALL_HEADER
#define BALL_HEADER

#include "renderer.h"

#define BALL_WIDTH 10.0
#define BALL_HEIGHT 10.0
#define BALL_INITIAL_SPEED 1000.0

typedef struct _Ball Ball;

Ball* ball_create();
void ball_destroy(Ball* self);

void ball_move(Ball* self, float delta);
void ball_collide_with_paddle(Ball* self);
void ball_reset(Ball* self);
const Rect* ball_get_rect(const Ball* self);

#endif // !BALL_HEADER
