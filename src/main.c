#include "game.h"

int main() {
    Game* game = game_create();
    while (game_is_running(game)) {
        game_update(game);
    }
    game_destroy(game);

    return 0;
}
