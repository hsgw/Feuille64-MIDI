/*   Copyright 2021 Takuya Urakawa (hsgw)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "pattern.h"

pattern_t patterns[PATTERN_COUNT] = {
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
                {.row = 1, .col = 0, .vel = 3, .enable = true},
            },
        .length = 7,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
                {.row = 0, .col = -1, .vel = 3, .enable = true},
            },
        .length = 5,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
                {.row = 0, .col = 1, .vel = 3, .enable = true},
            },
        .length = 8,
    },
};