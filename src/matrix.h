#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include "renderer.h"

typedef struct {
    float data[16];
} Mat4;

typedef struct {
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
} ProjectionSpec;

Mat4 get_transform(const Rect* rect);
Mat4 get_projection(const ProjectionSpec* spec);

#endif // !MATRIX_HEADER
