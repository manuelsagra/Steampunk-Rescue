#include "types.h"
#include "game.h"
#include "entities.h"
#include "screen.h"
#include "palette.h"

extern
entity_t        player;
extern
entity_t        platform;

Pokitto::Core   pkt;
game_t          game;
SRCookie        cookie;

void checkControls() {
    if (!game.demo) {
        if (pkt.buttons.cBtn() && pkt.buttons.timeHeld(BTN_C) == 1) {
            game.paused = !game.paused;
        }
        
        if (pkt.buttons.leftBtn()) {
            platform.x -= 3;
        } else if (pkt.buttons.rightBtn()) {
            platform.x += 3;
        }
        
        if (pkt.buttons.aBtn() && pkt.buttons.timeHeld(BTN_A) == 1) {
            initEntities();
        }
    }
}

void checkScore() {
    
}

void playLevel() {
    if (!game.paused) {
        checkControls();
        //consumeTime();
        updateEntities();
        
        drawScreen();
        
        checkScore();
    } else {
        drawScreen();
        //drawPause();
        
        if (pkt.buttons.cBtn() && pkt.buttons.timeHeld(BTN_C) == 1) {
            game.paused = !game.paused;
        }
    }
}

void initGame() {
    pkt.begin();
    pkt.display.setColorDepth(8);
    pkt.display.loadRGBPalette(auroraPal);
    pkt.display.invisiblecolor = 0;
    pkt.display.setFont(fontTiny);
    
    game.status = STATUS_LOGO;
    
    cookie.begin("SRSCORE", cookie);
    cookie.loadCookie();
    game.hiScore = cookie.hiScore;
}

void startGame() {
    game.level = 0;
    game.lives = GAME_LIVES;
    game.score = 0;
    game.scoreChanged = false;
    game.demo = false;
    
    initLevel();
    initEntities();
    
    game.status = STATUS_PLAYING;
}

void initLevel() {
    game.gameOver = false;
    game.paused = false;
    
    initTilemap();
}