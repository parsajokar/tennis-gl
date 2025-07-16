#include "matrix.h"

Mat4 get_transform(const Rect* rect) {
    return (Mat4){
        .data = {
            rect->w, 0.0, 0.0, 0.0,
            0.0, rect->h, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            rect->x, rect->y, 1.0, 1.0
        }
    };
}

Mat4 get_projection(const ProjectionSpec* spec) {
    return (Mat4){
        .data = {
            2.0 / (spec->right - spec->left), 0.0, 0.0, 0.0,
            0.0, 2.0 / (spec->top - spec->bottom) , 0.0, 0.0,
            0.0, 0.0, 2.0 / (spec->far - spec->near), 0.0,
            (spec->left + spec->right) / (spec->left - spec->right),
            (spec->bottom + spec->top) / (spec->bottom - spec->top),
            (spec->near + spec->far) / (spec->near - spec->far), 1.0
        }
    };
}
