/* Based on polygome */

#pragma once

#include <stdint.h>

#define SCALE_LENGTH (8)
#define SCALE_KIND_NUM (13)
#define SCALE_DIATONIC_MODE (6)

#define SCALE_LIMIT (12)

typedef enum {
    SCALE_off = 0,
    SCALE_chromatic,
    SCALE_M2,
    SCALE_m3,
    SCALE_M3,
    SCALE_P4,
    SCALE_tritone,
    SCALE_P5,
    SCALE_m6,
    SCALE_M6,
    SCALE_m7,
    SCALE_M7,
    SCALE_circleof5ths,
} scale_kind;

typedef enum {
    MODE_off = 0,
    MODE_chromatic,
    MODE_diatonic,
} scale_mode;

// const int8_t scale_seed_table[SCALE_LENGTH][SCALE_KIND_NUM] = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 7},
//     {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 2},
//     {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 9},
//     {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 4},
//     {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55},
//     {0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 6},
//     {0, 7, 14, 21, 28, 35, 42, 49, 56, 63, 70, 77, 13},
// };

// clang-format off
const int8_t SCALE_SEED_TABLE[SCALE_KIND_NUM][SCALE_LENGTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 1, 2, 3, 4, 5, 6, 7}, 
    {0, 2, 4, 6, 8, 10, 12, 14}, 
    {0, 3, 6, 9, 12, 15, 18, 21}, 
    {0, 4, 8, 12, 16, 20, 24, 28}, 
    {0, 5, 10, 15, 20, 25, 30, 35}, 
    {0, 6, 12, 18, 24, 30, 36, 42}, 
    {0, 7, 14, 21, 28, 35, 42, 49}, 
    {0, 8, 16, 24, 32, 40, 48, 56}, 
    {0, 9, 18, 27, 36, 45, 54, 63}, 
    {0, 10, 20, 30, 40, 50, 60, 70}, 
    {0, 11, 22, 33, 44, 55, 66, 77}, 
    {0, 7, 2, 9, 4, 60, 6, 13},
};
// clang-format on

const int8_t SCALE_CHRMOD_TABLE[SCALE_LIMIT] = {
    0, -1, 0, 1, 0, 0, -1, 0, -1, 0, 1, 0,
};

/* From satori in polygome
 *
 *    0  1  2  3  4  5  6  7  8  9  10  11
 * 0, 0     0     0  0     0     0       0;
 * 1, 0     0    -1  0     0     0      -1;
 * 2, 0    -1    -1  0     0    -1      -1;
 * 3, 0     0     0  1     0     0       0;
 * 4, 0     0     0  0     0     0      -1;
 * 5, 0     0    -1  0     0    -1      -1;
 * 6, 0    -1    -1  0    -1    -1      -1;
 */

// clang-format off
const int8_t SCALE_DIATONIC_TABLE[SCALE_DIATONIC_MODE][SCALE_LIMIT] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, -1},
    { 0, 0,-1, 0,-1, 0, 0, 0, 0,-1, 0, -1},
    { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
    { 0, 0, 0, 0,-1, 0, 0, 0, 0,-1, 0, -1},
    { 0, 0,-1, 0,-1, 0, 0,-1, 0,-1, 0, -1},
};
// clang-format on
