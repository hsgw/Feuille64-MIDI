#pragma once

#include "pattern.h"

pattern_t patterns[PATTERN_COUNT] = {
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 0, .col = 1, .vel = 100},
                {.row = 0, .col = 2, .vel = 100},
                {.row = 0, .col = 3, .vel = 100},
                {.row = 0, .col = 4, .vel = 100},
                {.row = 0, .col = 5, .vel = 100},
                {.row = 0, .col = 6, .vel = 100},
                {.row = 0, .col = 7, .vel = 100},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 1, .col = 0, .vel = 100},
                {.row = 2, .col = 0, .vel = 100},
                {.row = 3, .col = 0, .vel = 100},
                {.row = 4, .col = 0, .vel = 100},
                {.row = 5, .col = 0, .vel = 100},
                {.row = 6, .col = 0, .vel = 100},
                {.row = 7, .col = 0, .vel = 100},
            },
        .length = 7,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 0, .col = -1, .vel = 100},
                {.row = 1, .col = 0, .vel = 100},
                {.row = 0, .col = 1, .vel = 100},
                {.row = -1, .col = 0, .vel = 100},
                {.row = 0, .col = 5, .vel = 100},
                {.row = 0, .col = 6, .vel = 100},
                {.row = 0, .col = 7, .vel = 100},
            },
        .length = 5,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 0, .col = 1, .vel = 100},
                {.row = 0, .col = 2, .vel = 100},
                {.row = 0, .col = 3, .vel = 100},
                {.row = 0, .col = 4, .vel = 100},
                {.row = 0, .col = 5, .vel = 100},
                {.row = 0, .col = 6, .vel = 100},
                {.row = 0, .col = 7, .vel = 100},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 0, .col = 1, .vel = 100},
                {.row = 0, .col = 2, .vel = 100},
                {.row = 0, .col = 3, .vel = 100},
                {.row = 0, .col = 4, .vel = 100},
                {.row = 0, .col = 5, .vel = 100},
                {.row = 0, .col = 6, .vel = 100},
                {.row = 0, .col = 7, .vel = 100},
            },
        .length = 8,
    },
    {
        .steps =
            {
                {.row = 0, .col = 0, .vel = 100},
                {.row = 0, .col = 1, .vel = 100},
                {.row = 0, .col = 2, .vel = 100},
                {.row = 0, .col = 3, .vel = 100},
                {.row = 0, .col = 4, .vel = 100},
                {.row = 0, .col = 5, .vel = 100},
                {.row = 0, .col = 6, .vel = 100},
                {.row = 0, .col = 7, .vel = 100},
            },
        .length = 8,
    },
};