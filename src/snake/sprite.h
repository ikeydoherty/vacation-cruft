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

#include <SDL.h>
#include <stddef.h>

/**
 * A RenderTarget is passed to a Sprite for rendering & updating
 */
typedef struct FrameInfo {
        SDL_Renderer *render;
        SDL_Rect rect;
        uint32_t ticks;
        uint32_t prev_ticks;
} FrameInfo;

/**
 * A Sprite provides us with a very simple system to generically render and
 * update sprites on a surface.
 */
typedef struct Sprite {
        /**
         * Perform the update cycle for this sprite in relation to global
         * events.
         */
        void (*update)(struct Sprite *, FrameInfo *);

        /**
         * Draw to the given renderer
         */
        void (*draw)(struct Sprite *, FrameInfo *);

} Sprite;

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
