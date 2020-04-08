#include "types.h"
#include "screen.h"
#include "game.h"
#include "entities.h"
#include <Tilemap.hpp>
#include "maps.h"
#include "img/sidebarBg.h"

// Variables
extern 
entity_t        player;
extern 
entity_t        platform;
extern
game_t          game;
extern
Pokitto::Core   pkt;

int             offsetY = 0;
int             stageHeight = 0;
Tilemap         stageTiles;

void calculateOffset() {
    if (player.y < OFFSET_START) {
        offsetY = 0;
    } else {
        offsetY = player.y - OFFSET_START;
    }
}

void drawSidebar() {
    pkt.display.drawBitmap(176, 0, sidebarBg);
    //pkt.display.setColor(15);
    //pkt.display.print(180, 0, Pokitto::Core::fps_counter);
}

void drawPlayer() {
    player.sprite.draw(player.x, offsetY == 0 ? SCREEN_HEIGHT - player.y - player.height : PLAYER_TOP_DISTANCE, false, false, 0);
}

void drawPlatform() {
    if (offsetY < platform.y) {
        platform.sprite.draw(platform.x, SCREEN_HEIGHT - platform.y - platform.height - offsetY, false, false, 0);
    }
}

void drawEntities() {
    
}

void drawStage() {
    stageTiles.draw(0, -stageHeight + SCREEN_HEIGHT + offsetY);
}

void initTilemap() {
    // TODO: Do this by level
    
    // Load tiles and calculate height
    stageTiles.set(stage[0], stage[1], stage + 2);
    for(int i = 0; i < sizeof(tiles) / (POK_TILE_W * POK_TILE_H); i++) {
        stageTiles.setTile(i, POK_TILE_W, POK_TILE_H, tiles + i * POK_TILE_W * POK_TILE_H);
    }
    stageHeight = POK_TILE_H * stage[1];
}