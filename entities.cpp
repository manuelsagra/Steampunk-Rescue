#include "types.h"
#include "entities.h"

extern
int         stageHeight;

entity_t    player;
float       playerDelta = 1.5;
float       playerStep = 0;
entity_t    platform;

void initEntities() {
    player.status = ENTITY_STATUS_NORMAL;
    player.width = 13;
    player.height = 16;
    player.x = 60;
    player.y = 16;
    player.sprite.play(playerSprite, PlayerSprite::jumping);
    
    platform.width = 46;
    platform.height = 10;
    platform.x = 40;
    platform.y = 8;
    platform.sprite.play(platformSprite, PlatformSprite::normal);
}

void updateEntities() {
    // Player
    if (player.x >= 176 - player.width) {
        playerDelta = -1.5;
    } else if (player.x == 0) {
        playerDelta = 1.5;
    }
    
    player.x += playerDelta;
    
    player.y = (int) (stageHeight - DISTANCE_FROM_STAGE_TOP) * abs(sin(playerStep));
    playerStep += 0.01 * PI;
    if (playerStep >= PI) {
        playerStep = 0;
    }
    
    // Platform
    if (platform.x < 0) {
        platform.x = 0;
    } else if ((platform.x + platform.width) > 176) {
        platform.x = 176 - platform.width;
    }
}