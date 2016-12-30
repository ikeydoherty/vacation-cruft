/*
 * This file is part of vacation-cruft
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "sprite.h"
#include "tilesheet.h"

/**
 * Valid direction (one only) for a player */
typedef enum { DIR_UP = 0, DIR_DOWN, DIR_LEFT, DIR_RIGHT } PlayerDirection;

/**
 * A PlayerSegment represents each segment in the body of a snake
 */
typedef struct PlayerSegment {
        int x;
        int y;
        PlayerDirection dir;
} PlayerSegment;

/**
 * A Player is the actual human controlled snake on screen
 */
typedef struct Player {
        TileSheet *sheet;
        PlayerDirection dir;

        /* How many blocks per second to travel */
        int speed;

        PlayerSegment *segments;
        int n_segments;
} Player;

/**
 * Construct a new player using the given tilesheet
 */
Player *player_new(TileSheet *sheet);

/**
 * Set the new direction for the player
 */
void player_set_direction(Player *player, PlayerDirection direction);

/**
 * Update the player within the world
 */
void player_update(Player *player, FrameInfo *frame);

/**
 * Render the player within the world
 */
void player_draw(Player *player, FrameInfo *frame);

/**
 * Grow the player by one (for testing)
 */
void player_grow(Player *player);

/**
 * Cleanup a previously created player
 */
void player_free(Player *player);

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
