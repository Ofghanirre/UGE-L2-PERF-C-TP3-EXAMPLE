//
// Created by Antonin Jean on 18/02/2025.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Time.h"

#define CP_BLUE_ON_BLACK 1

void graphic_color_init();

void graphic_init();

void graphic_clear();

void graphic_display(const Chrono *chrono);

void graphic_refresh(const Chrono *chrono);

bool gui_refresh(Chrono *chrono);

#endif //GRAPHICS_H
