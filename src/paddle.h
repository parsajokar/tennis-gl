#ifndef PADDLE_HEADER
#define PADDLE_HEADER

#include "GLFW/glfw3.h"

#include "renderer.h"

#define PADDLE_WIDTH 10.0
#define PADDLE_HEIGHT 100.0
#define PADDLE_SPEED 800.0

typedef struct _Paddle Paddle;

typedef enum {
    PADDLE_TYPE_LEFT,
    PADDLE_TYPE_RIGHT
} PaddleType;

Paddle* paddle_create(PaddleType type);
void paddle_destroy(Paddle* self);

void paddle_handle_input(Paddle* self, GLFWwindow* window, float delta);
const Rect* paddle_get_rect(const Paddle* self);

#endif // !PADDLE_HEADER
