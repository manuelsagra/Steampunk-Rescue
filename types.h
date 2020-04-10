#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "sprites.h"

// Game Status
#define STATUS_LOGO 0
#define STATUS_TITLE 1
#define STATUS_STARTING 2
#define STATUS_PLAYING 3
#define STATUS_GAMEOVER 4

// Entity Types
#define ENTITY_TYPE_PLAYER 1
#define ENTITY_TYPE_PLATFORM 2

// Entity Status
#define ENTITY_STATUS_NORMAL 1
#define ENTITY_STATUS_CRASHED 2

typedef struct {
    int         level;
    int         lives;
    bool        finished;
    bool        gameOver;
    bool        demo;
    bool        paused;
    int         status;
    int         timeLeft;
    int         timeLeftFrame;
    int         score;
    bool        scoreChanged;
    int         hiScore;
} game_t;

typedef struct {
    int     type;
    float   x;
    float   y;
    int     width;
    int     height;
    int     status;
    Sprite  sprite;
} entity_t;

class SRCookie : public Pokitto::Cookie {
public:
    int hiScore = 0;
};