#ifndef GAME_HEADER
#define GAME_HEADER

#include "stdbool.h"

typedef struct _Game Game;

Game* game_create();
void game_destroy(Game* self);
bool game_is_running(const Game* self);
void game_update(Game* self);

#endif // !GAME_HEADER
