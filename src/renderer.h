#ifndef RENDERER_HEADER
#define RENDERER_HEADER

typedef struct _Renderer Renderer;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} Rect;

Renderer* renderer_create();
void renderer_destroy(Renderer* self);

void renderer_clear(const Renderer* self);
void renderer_draw_rect(const Renderer* self, const Rect* rect);

#endif // !RENDERER_HEADER
