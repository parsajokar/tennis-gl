#ifndef PADDLE_HEADER
#define PADDLE_HEADER

#include "GLFW/glfw3.h"

#include "renderer.h"

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
