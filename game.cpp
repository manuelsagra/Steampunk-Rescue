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
        
        if (player.status == ENTITY_STATUS_NORMAL) {
            if (pkt.buttons.leftBtn()) {
                platform.x -= 3;
            } else if (pkt.buttons.rightBtn()) {
                platform.x += 3;
            }
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
        
        calculateOffset();
        drawStage();
        //drawEntities();
        drawPlatform();
        drawPlayer();
        drawSidebar();
        
        checkScore();
    } else {
        //drawPause();
        if (pkt.buttons.cBtn() && pkt.buttons.timeHeld(BTN_C) == 1) {
            game.paused = !game.paused;
        }
    }
}

void initGame() {
    pkt.begin();
    pkt.display.invisiblecolor = 239;
    pkt.display.loadRGBPalette(auroraPal);
    pkt.display.setFont(fontTiny);
    
    game.status = STATUS_LOGO;
    
    cookie.begin("SRSCORE", cookie);
    cookie.loadCookie();
    game.hiScore = cookie.hiScore;
}

void startGame() {
    game.level = 0;
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