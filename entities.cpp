#include "types.h"
#include "entities.h"

extern
game_t      game;

entity_t    platform;
entity_t    player;
float       playerDelta = 0;
float       playerStep = 0;
int         oldPlayerY = 0;
int         playerJump = 100;

float deltas[] = {
    3.2,
    2.1,
    1.4,
    0.8,
    0,
    -0.8,
    -1.4,
    -2.1,
    -3.2
};

void initEntities() {
    player.status = ENTITY_STATUS_NORMAL;
    player.width = PLAYER_WIDTH;
    player.height = PLAYER_HEIGHT;
    player.x = 80;
    player.y = PLATFORM_HEIGHT + PLATFORM_Y;
    playerStep = 0;
    playerDelta = 0;
    oldPlayerY = player.y;
    player.sprite.play(playerSprite, PlayerSprite::jumping);
    
    platform.width = PLATFORM_WIDTH;
    platform.height = PLATFORM_HEIGHT;
    platform.x = 60;
    platform.y = PLATFORM_Y;
    platform.sprite.play(platformSprite, PlatformSprite::normal);
}

void updateEntities() {
    // Move player
    if (player.status != ENTITY_STATUS_CRASHED) {
        oldPlayerY = player.y;
        
        // Screen bounds
        if (player.x >= (176 - player.width) || player.x <= 0) {
            playerDelta = -playerDelta;
        }
        
        // TODO: Vertical falls
        player.x += playerDelta;
        if (player.x < 0) {
            player.x = 0;
        }
        if (player.y > (PLATFORM_Y + PLATFORM_HEIGHT) || playerStep == 0) {
            playerStep += 0.01 * PI;
            player.y = (int) ((float) playerJump * sin(playerStep));
            player.y += PLATFORM_Y + PLATFORM_HEIGHT;
        }
    }

    // Limit platform movement
    if (platform.x < 0) {
        platform.x = 0;
    } else if ((platform.x + platform.width) > 176) {
        platform.x = 176 - platform.width;
    }
    
    // Check if player rebounds
    if (player.status != ENTITY_STATUS_CRASHED) {
        // If player is falling and is on (or just below) the platform
        if (player.y <= (PLATFORM_Y + PLATFORM_HEIGHT) && player.y < oldPlayerY) {
            if ((player.x + player.width) > platform.x && player.x < (platform.x + platform.width)) {
                float playerCenter = player.x + (player.width / 2);
                int deltaIndex = ((playerCenter - (float) platform.x) / (float) platform.width) * 9;
                if (deltaIndex < 0) {
                    deltaIndex = 0;
                } else if (deltaIndex > 8) {
                    deltaIndex = 8;
                }
                playerDelta = deltas[deltaIndex];
                playerStep = 0;
            } else {
                player.status = ENTITY_STATUS_CRASHED;
            }
        }
    }
}

bool checkEntityCollision(entity_t* e1, entity_t* e2) {
    return (
        e1->x < e2->x + e2->width &&
        e1->x + e1->width > e2->x &&
        e1->y < e2->y + e2->height &&
        e1->y + e1->height > e2->y);
}