#pragma once

#define SCREEN_HEIGHT           176
#define PLAYER_TOP_DISTANCE     32
#define OFFSET_START            (SCREEN_HEIGHT - PLAYER_TOP_DISTANCE - player.height)

#define SCORE_X                 178
#define SCORE_Y                 26

#define TIME_X                  178
#define TIME_Y                  61

#define LIVES_X                 190
#define LIVES_Y                 96

#define PEOPLE_X                200
#define PEOPLE1_Y               131
#define PEOPLE2_Y               144
#define PEOPLE3_Y               157

void    calculateOffset();

void    drawScreen();
void    drawSidebar();
void    drawPlayer();
void    drawPlatform();
void    drawEntities();
void    drawStage();

void    initTilemap();
void    drawNumber(int x, int y, int number, int precision);