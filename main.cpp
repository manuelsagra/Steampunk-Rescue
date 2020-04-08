#include "types.h"
#include "game.h"

extern
game_t              game;
extern
Pokitto::Core       pkt;

int main(){
    initGame();
    startGame();

    // Game loop
    while(pkt.isRunning()) {
        if (pkt.update()) {
            switch (game.status) {
                case STATUS_LOGO:
                    //showLogo();
                    break;
                    
                case STATUS_TITLE:
                    //showTitle();
                    break;
                    
                case STATUS_STARTING:
                    //startLevel();
                    break;
                    
                case STATUS_PLAYING:
                    playLevel();
                    break;
                    
                case STATUS_GAMEOVER:
                    //levelGameOver();
                    break;
            }
        }
    }
    
    return 0;
}
