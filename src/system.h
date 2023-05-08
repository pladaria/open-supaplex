/*
* This file is part of the OpenSupaplex distribution (https://github.com/sergiou87/open-supaplex).
* Copyright (c) 2020 Sergio Padrino
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef system_h
#define system_h

#include <stdint.h>

void initializeSystem(void);
void destroySystem(void);

uint8_t isOld3DSSystem(void);

void exitWithError(const char *format, ...);

void handleSystemEvents(void);
uint32_t getTicks(void);
void waitTime(uint32_t time);

#endif /* system_h */
