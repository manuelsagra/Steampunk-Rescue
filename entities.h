#pragma once

#define PLAYER_WIDTH                13
#define PLAYER_HEIGHT               16

#define PLATFORM_Y                  8
#define PLATFORM_WIDTH              46
#define PLATFORM_HEIGHT             5

void            initEntities();
void            updateEntities();
bool            checkEntityCollision(entity_t* e1, entity_t* e2);