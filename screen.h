#pragma once

#define SCREEN_HEIGHT           176
#define PLAYER_TOP_DISTANCE     24
#define OFFSET_START            (SCREEN_HEIGHT - PLAYER_TOP_DISTANCE - player.height)

void    calculateOffset();

void    drawSidebar();
void    drawPlayer();
void    drawPlatform();
void    drawEntities();
void    drawStage();

void    initTilemap();