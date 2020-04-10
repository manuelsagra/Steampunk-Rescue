#include "types.h"
#include "screen.h"
#include "game.h"
#include "entities.h"
#include <Tilemap.hpp>
#include "maps.h"

#include "img/sidebarBg.h"
#include "img/number0.h"
#include "img/number1.h"
#include "img/number2.h"
#include "img/number3.h"
#include "img/number4.h"
#include "img/number5.h"
#include "img/number6.h"
#include "img/number7.h"
#include "img/number8.h"
#include "img/number9.h"

// Variables
extern 
entity_t        player;
extern
int             playerJump;
extern 
entity_t        platform;
extern
game_t          game;
extern
Pokitto::Core   pkt;

int             offsetY = 0;
int             stageHeight = 0;
Tilemap         stageTiles;
Sprite          deleteSprite;

const uint8_t* numbers[] = {
    number0,
    number1,
    number2,
    number3,
    number4,
    number5,
    number6,
    number7,
    number8,
    number9
};

void drawScreen() {
    calculateOffset();
    drawStage();
    drawEntities();
    drawPlayer();
    drawPlatform();
    drawSidebar();
}

void calculateOffset() {
    if (player.y < OFFSET_START) {
        offsetY = 0;
    } else {
        offsetY = player.y - OFFSET_START;
    }
}

void drawSidebar() {
    pkt.display.drawSprite(176, 0, sidebarBg, false, false, 0);
    
    drawNumber(SCORE_X, SCORE_Y, player.y, 5);
    
    drawNumber(LIVES_X, LIVES_Y, Pokitto::Core::fps_counter, 2);
}

void drawPlayer() {
    player.sprite.draw(player.x, SCREEN_HEIGHT - player.y - player.height + offsetY, false, false, 0);
}

void drawPlatform() {
    platform.sprite.draw(platform.x, SCREEN_HEIGHT - platform.y - platform.height + offsetY, false, false, 0);
}

void drawEntities() {
}

void drawStage() {
    stageTiles.draw(0, -stageHeight + SCREEN_HEIGHT + offsetY);
}

void initTilemap() {
    // TODO: Do this by level
    
    // Load tiles and calculate height
    stageTiles.set(stage1[0], stage1[1], stage1 + 2);
    for(int i = 0; i < sizeof(tiles) / (POK_TILE_W * POK_TILE_H); i++) {
        stageTiles.setTile(i, POK_TILE_W, POK_TILE_H, tiles + i * POK_TILE_W * POK_TILE_H);
    }
    stageHeight = POK_TILE_H * stage1[1];
    playerJump = stageHeight - player.height - PLAYER_TOP_DISTANCE - PLATFORM_Y - PLATFORM_HEIGHT;
}

void drawNumber(int x, int y, int number, int precision) {
    for (int i = precision; i > 0; i--) {
        int p = pow(10, i - 1);
        int n = number / p;
        
        pkt.display.drawBitmap(x, y, numbers[n]);
        
        x += 8;
        number -= p * n;
    }
}