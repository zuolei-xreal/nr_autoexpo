#include "auto_expo_control.h"

#include <pthread.h>
#include <yaml-cpp/yaml.h>
#include <cmath>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
// #define TEST_FILTER

std::vector<std::vector<int>> table = {
    {256, 1},     /* Gain = 1.000000 Exposure Index = 0 */
    {264, 1},     /* Gain = 1.031250 Exposure Index = 1 */
    {272, 1},     /* Gain = 1.062500 Exposure Index = 2 */
    {281, 1},     /* Gain = 1.097656 Exposure Index = 3 */
    {290, 1},     /* Gain = 1.132812 Exposure Index = 4 */
    {299, 1},     /* Gain = 1.167969 Exposure Index = 5 */
    {308, 1},     /* Gain = 1.203125 Exposure Index = 6 */
    {318, 1},     /* Gain = 1.242188 Exposure Index = 7 */
    {328, 1},     /* Gain = 1.281250 Exposure Index = 8 */
    {338, 1},     /* Gain = 1.320312 Exposure Index = 9 */
    {349, 1},     /* Gain = 1.363281 Exposure Index = 10 */
    {360, 1},     /* Gain = 1.406250 Exposure Index = 11 */
    {371, 1},     /* Gain = 1.449219 Exposure Index = 12 */
    {383, 1},     /* Gain = 1.496094 Exposure Index = 13 */
    {395, 1},     /* Gain = 1.542969 Exposure Index = 14 */
    {407, 1},     /* Gain = 1.589844 Exposure Index = 15 */
    {420, 1},     /* Gain = 1.640625 Exposure Index = 16 */
    {433, 1},     /* Gain = 1.691406 Exposure Index = 17 */
    {446, 1},     /* Gain = 1.742188 Exposure Index = 18 */
    {460, 1},     /* Gain = 1.796875 Exposure Index = 19 */
    {474, 1},     /* Gain = 1.851562 Exposure Index = 20 */
    {489, 1},     /* Gain = 1.910156 Exposure Index = 21 */
    {504, 1},     /* Gain = 1.968750 Exposure Index = 22 */
    {260, 2},     /* Gain = 1.015625 Exposure Index = 23 */
    {268, 2},     /* Gain = 1.046875 Exposure Index = 24 */
    {277, 2},     /* Gain = 1.082031 Exposure Index = 25 */
    {286, 2},     /* Gain = 1.117188 Exposure Index = 26 */
    {295, 2},     /* Gain = 1.152344 Exposure Index = 27 */
    {304, 2},     /* Gain = 1.187500 Exposure Index = 28 */
    {314, 2},     /* Gain = 1.226562 Exposure Index = 29 */
    {324, 2},     /* Gain = 1.265625 Exposure Index = 30 */
    {334, 2},     /* Gain = 1.304688 Exposure Index = 31 */
    {345, 2},     /* Gain = 1.347656 Exposure Index = 32 */
    {356, 2},     /* Gain = 1.390625 Exposure Index = 33 */
    {367, 2},     /* Gain = 1.433594 Exposure Index = 34 */
    {379, 2},     /* Gain = 1.480469 Exposure Index = 35 */
    {261, 3},     /* Gain = 1.019531 Exposure Index = 36 */
    {269, 3},     /* Gain = 1.050781 Exposure Index = 37 */
    {278, 3},     /* Gain = 1.085938 Exposure Index = 38 */
    {287, 3},     /* Gain = 1.121094 Exposure Index = 39 */
    {296, 3},     /* Gain = 1.156250 Exposure Index = 40 */
    {305, 3},     /* Gain = 1.191406 Exposure Index = 41 */
    {315, 3},     /* Gain = 1.230469 Exposure Index = 42 */
    {325, 3},     /* Gain = 1.269531 Exposure Index = 43 */
    {335, 3},     /* Gain = 1.308594 Exposure Index = 44 */
    {259, 4},     /* Gain = 1.011719 Exposure Index = 45 */
    {267, 4},     /* Gain = 1.042969 Exposure Index = 46 */
    {276, 4},     /* Gain = 1.078125 Exposure Index = 47 */
    {285, 4},     /* Gain = 1.113281 Exposure Index = 48 */
    {294, 4},     /* Gain = 1.148438 Exposure Index = 49 */
    {303, 4},     /* Gain = 1.183594 Exposure Index = 50 */
    {313, 4},     /* Gain = 1.222656 Exposure Index = 51 */
    {258, 5},     /* Gain = 1.007812 Exposure Index = 52 */
    {266, 5},     /* Gain = 1.039062 Exposure Index = 53 */
    {274, 5},     /* Gain = 1.070312 Exposure Index = 54 */
    {283, 5},     /* Gain = 1.105469 Exposure Index = 55 */
    {292, 5},     /* Gain = 1.140625 Exposure Index = 56 */
    {301, 5},     /* Gain = 1.175781 Exposure Index = 57 */
    {259, 6},     /* Gain = 1.011719 Exposure Index = 58 */
    {267, 6},     /* Gain = 1.042969 Exposure Index = 59 */
    {276, 6},     /* Gain = 1.078125 Exposure Index = 60 */
    {285, 6},     /* Gain = 1.113281 Exposure Index = 61 */
    {294, 6},     /* Gain = 1.148438 Exposure Index = 62 */
    {260, 7},     /* Gain = 1.015625 Exposure Index = 63 */
    {268, 7},     /* Gain = 1.046875 Exposure Index = 64 */
    {277, 7},     /* Gain = 1.082031 Exposure Index = 65 */
    {286, 7},     /* Gain = 1.117188 Exposure Index = 66 */
    {258, 8},     /* Gain = 1.007812 Exposure Index = 67 */
    {266, 8},     /* Gain = 1.039062 Exposure Index = 68 */
    {274, 8},     /* Gain = 1.070312 Exposure Index = 69 */
    {283, 8},     /* Gain = 1.105469 Exposure Index = 70 */
    {260, 9},     /* Gain = 1.015625 Exposure Index = 71 */
    {268, 9},     /* Gain = 1.046875 Exposure Index = 72 */
    {277, 9},     /* Gain = 1.082031 Exposure Index = 73 */
    {257, 10},    /* Gain = 1.003906 Exposure Index = 74 */
    {265, 10},    /* Gain = 1.035156 Exposure Index = 75 */
    {273, 10},    /* Gain = 1.066406 Exposure Index = 76 */
    {256, 11},    /* Gain = 1.000000 Exposure Index = 77 */
    {264, 11},    /* Gain = 1.031250 Exposure Index = 78 */
    {272, 11},    /* Gain = 1.062500 Exposure Index = 79 */
    {257, 12},    /* Gain = 1.003906 Exposure Index = 80 */
    {265, 12},    /* Gain = 1.035156 Exposure Index = 81 */
    {273, 12},    /* Gain = 1.066406 Exposure Index = 82 */
    {260, 13},    /* Gain = 1.015625 Exposure Index = 83 */
    {268, 13},    /* Gain = 1.046875 Exposure Index = 84 */
    {257, 14},    /* Gain = 1.003906 Exposure Index = 85 */
    {265, 14},    /* Gain = 1.035156 Exposure Index = 86 */
    {273, 14},    /* Gain = 1.066406 Exposure Index = 87 */
    {263, 15},    /* Gain = 1.027344 Exposure Index = 88 */
    {271, 15},    /* Gain = 1.058594 Exposure Index = 89 */
    {262, 16},    /* Gain = 1.023438 Exposure Index = 90 */
    {270, 16},    /* Gain = 1.054688 Exposure Index = 91 */
    {262, 17},    /* Gain = 1.023438 Exposure Index = 92 */
    {270, 17},    /* Gain = 1.054688 Exposure Index = 93 */
    {263, 18},    /* Gain = 1.027344 Exposure Index = 94 */
    {257, 19},    /* Gain = 1.003906 Exposure Index = 95 */
    {265, 19},    /* Gain = 1.035156 Exposure Index = 96 */
    {260, 20},    /* Gain = 1.015625 Exposure Index = 97 */
    {268, 20},    /* Gain = 1.046875 Exposure Index = 98 */
    {263, 21},    /* Gain = 1.027344 Exposure Index = 99 */
    {259, 22},    /* Gain = 1.011719 Exposure Index = 100 */
    {267, 22},    /* Gain = 1.042969 Exposure Index = 101 */
    {264, 23},    /* Gain = 1.031250 Exposure Index = 102 */
    {261, 24},    /* Gain = 1.019531 Exposure Index = 103 */
    {259, 25},    /* Gain = 1.011719 Exposure Index = 104 */
    {257, 26},    /* Gain = 1.003906 Exposure Index = 105 */
    {265, 26},    /* Gain = 1.035156 Exposure Index = 106 */
    {263, 27},    /* Gain = 1.027344 Exposure Index = 107 */
    {262, 28},    /* Gain = 1.023438 Exposure Index = 108 */
    {261, 29},    /* Gain = 1.019531 Exposure Index = 109 */
    {260, 30},    /* Gain = 1.015625 Exposure Index = 110 */
    {260, 31},    /* Gain = 1.015625 Exposure Index = 111 */
    {260, 32},    /* Gain = 1.015625 Exposure Index = 112 */
    {260, 33},    /* Gain = 1.015625 Exposure Index = 113 */
    {260, 34},    /* Gain = 1.015625 Exposure Index = 114 */
    {261, 35},    /* Gain = 1.019531 Exposure Index = 115 */
    {262, 36},    /* Gain = 1.023438 Exposure Index = 116 */
    {256, 38},    /* Gain = 1.000000 Exposure Index = 117 */
    {257, 39},    /* Gain = 1.003906 Exposure Index = 118 */
    {259, 40},    /* Gain = 1.011719 Exposure Index = 119 */
    {261, 41},    /* Gain = 1.019531 Exposure Index = 120 */
    {257, 43},    /* Gain = 1.003906 Exposure Index = 121 */
    {259, 44},    /* Gain = 1.011719 Exposure Index = 122 */
    {261, 45},    /* Gain = 1.019531 Exposure Index = 123 */
    {258, 47},    /* Gain = 1.007812 Exposure Index = 124 */
    {261, 48},    /* Gain = 1.019531 Exposure Index = 125 */
    {259, 50},    /* Gain = 1.011719 Exposure Index = 126 */
    {257, 52},    /* Gain = 1.003906 Exposure Index = 127 */
    {260, 53},    /* Gain = 1.015625 Exposure Index = 128 */
    {259, 55},    /* Gain = 1.011719 Exposure Index = 129 */
    {258, 57},    /* Gain = 1.007812 Exposure Index = 130 */
    {257, 59},    /* Gain = 1.003906 Exposure Index = 131 */
    {257, 61},    /* Gain = 1.003906 Exposure Index = 132 */
    {257, 63},    /* Gain = 1.003906 Exposure Index = 133 */
    {257, 65},    /* Gain = 1.003906 Exposure Index = 134 */
    {257, 67},    /* Gain = 1.003906 Exposure Index = 135 */
    {258, 69},    /* Gain = 1.007812 Exposure Index = 136 */
    {259, 71},    /* Gain = 1.011719 Exposure Index = 137 */
    {256, 74},    /* Gain = 1.000000 Exposure Index = 138 */
    {257, 76},    /* Gain = 1.003906 Exposure Index = 139 */
    {258, 78},    /* Gain = 1.007812 Exposure Index = 140 */
    {256, 81},    /* Gain = 1.000000 Exposure Index = 141 */
    {258, 83},    /* Gain = 1.007812 Exposure Index = 142 */
    {257, 86},    /* Gain = 1.003906 Exposure Index = 143 */
    {256, 89},    /* Gain = 1.000000 Exposure Index = 144 */
    {258, 91},    /* Gain = 1.007812 Exposure Index = 145 */
    {258, 94},    /* Gain = 1.007812 Exposure Index = 146 */
    {258, 97},    /* Gain = 1.007812 Exposure Index = 147 */
    {258, 100},   /* Gain = 1.007812 Exposure Index = 148 */
    {258, 103},   /* Gain = 1.007812 Exposure Index = 149 */
    {256, 107},   /* Gain = 1.000000 Exposure Index = 150 */
    {257, 110},   /* Gain = 1.003906 Exposure Index = 151 */
    {258, 113},   /* Gain = 1.007812 Exposure Index = 152 */
    {257, 117},   /* Gain = 1.003906 Exposure Index = 153 */
    {256, 121},   /* Gain = 1.000000 Exposure Index = 154 */
    {258, 124},   /* Gain = 1.007812 Exposure Index = 155 */
    {256, 129},   /* Gain = 1.000000 Exposure Index = 156 */
    {256, 133},   /* Gain = 1.000000 Exposure Index = 157 */
    {256, 137},   /* Gain = 1.000000 Exposure Index = 158 */
    {257, 141},   /* Gain = 1.003906 Exposure Index = 159 */
    {256, 146},   /* Gain = 1.000000 Exposure Index = 160 */
    {257, 150},   /* Gain = 1.003906 Exposure Index = 161 */
    {257, 155},   /* Gain = 1.003906 Exposure Index = 162 */
    {257, 160},   /* Gain = 1.003906 Exposure Index = 163 */
    {257, 165},   /* Gain = 1.003906 Exposure Index = 164 */
    {257, 170},   /* Gain = 1.003906 Exposure Index = 165 */
    {256, 176},   /* Gain = 1.000000 Exposure Index = 166 */
    {257, 181},   /* Gain = 1.003906 Exposure Index = 167 */
    {257, 187},   /* Gain = 1.003906 Exposure Index = 168 */
    {257, 193},   /* Gain = 1.003906 Exposure Index = 169 */
    {257, 199},   /* Gain = 1.003906 Exposure Index = 170 */
    {257, 205},   /* Gain = 1.003906 Exposure Index = 171 */
    {256, 212},   /* Gain = 1.000000 Exposure Index = 172 */
    {257, 218},   /* Gain = 1.003906 Exposure Index = 173 */
    {257, 225},   /* Gain = 1.003906 Exposure Index = 174 */
    {257, 232},   /* Gain = 1.003906 Exposure Index = 175 */
    {257, 239},   /* Gain = 1.003906 Exposure Index = 176 */
    {257, 247},   /* Gain = 1.003906 Exposure Index = 177 */
    {257, 255},   /* Gain = 1.003906 Exposure Index = 178 */
    {256, 264},   /* Gain = 1.000000 Exposure Index = 179 */
    {256, 272},   /* Gain = 1.000000 Exposure Index = 180 */
    {256, 281},   /* Gain = 1.000000 Exposure Index = 181 */
    {256, 290},   /* Gain = 1.000000 Exposure Index = 182 */
    {256, 299},   /* Gain = 1.000000 Exposure Index = 183 */
    {256, 308},   /* Gain = 1.000000 Exposure Index = 184 */
    {256, 318},   /* Gain = 1.000000 Exposure Index = 185 */
    {256, 328},   /* Gain = 1.000000 Exposure Index = 186 */
    {256, 338},   /* Gain = 1.000000 Exposure Index = 187 */
    {256, 349},   /* Gain = 1.000000 Exposure Index = 188 */
    {256, 360},   /* Gain = 1.000000 Exposure Index = 189 */
    {256, 371},   /* Gain = 1.000000 Exposure Index = 190 */
    {256, 383},   /* Gain = 1.000000 Exposure Index = 191 */
    {256, 395},   /* Gain = 1.000000 Exposure Index = 192 */
    {256, 407},   /* Gain = 1.000000 Exposure Index = 193 */
    {256, 420},   /* Gain = 1.000000 Exposure Index = 194 */
    {256, 433},   /* Gain = 1.000000 Exposure Index = 195 */
    {256, 446},   /* Gain = 1.000000 Exposure Index = 196 */
    {256, 460},   /* Gain = 1.000000 Exposure Index = 197 */
    {256, 474},   /* Gain = 1.000000 Exposure Index = 198 */
    {256, 489},   /* Gain = 1.000000 Exposure Index = 199 */
    {256, 504},   /* Gain = 1.000000 Exposure Index = 200 */
    {256, 520},   /* Gain = 1.000000 Exposure Index = 201 */
    {256, 536},   /* Gain = 1.000000 Exposure Index = 202 */
    {256, 553},   /* Gain = 1.000000 Exposure Index = 203 */
    {256, 570},   /* Gain = 1.000000 Exposure Index = 204 */
    {256, 588},   /* Gain = 1.000000 Exposure Index = 205 */
    {256, 606},   /* Gain = 1.000000 Exposure Index = 206 */
    {256, 625},   /* Gain = 1.000000 Exposure Index = 207 */
    {256, 644},   /* Gain = 1.000000 Exposure Index = 208 */
    {256, 664},   /* Gain = 1.000000 Exposure Index = 209 */
    {256, 684},   /* Gain = 1.000000 Exposure Index = 210 */
    {256, 705},   /* Gain = 1.000000 Exposure Index = 211 */
    {256, 727},   /* Gain = 1.000000 Exposure Index = 212 */
    {256, 749},   /* Gain = 1.000000 Exposure Index = 213 */
    {256, 772},   /* Gain = 1.000000 Exposure Index = 214 */
    {256, 796},   /* Gain = 1.000000 Exposure Index = 215 */
    {256, 820},   /* Gain = 1.000000 Exposure Index = 216 */
    {256, 845},   /* Gain = 1.000000 Exposure Index = 217 */
    {256, 871},   /* Gain = 1.000000 Exposure Index = 218 */
    {256, 898},   /* Gain = 1.000000 Exposure Index = 219 */
    {256, 925},   /* Gain = 1.000000 Exposure Index = 220 */
    {256, 953},   /* Gain = 1.000000 Exposure Index = 221 */
    {256, 982},   /* Gain = 1.000000 Exposure Index = 222 */
    {256, 1012},  /* Gain = 1.000000 Exposure Index = 223 */
    {256, 1043},  /* Gain = 1.000000 Exposure Index = 224 */
    {256, 1075},  /* Gain = 1.000000 Exposure Index = 225 */
    {256, 1108},  /* Gain = 1.000000 Exposure Index = 226 */
    {264, 1108},  /* Gain = 1.031250 Exposure Index = 227 */
    {272, 1108},  /* Gain = 1.062500 Exposure Index = 228 */
    {281, 1108},  /* Gain = 1.097656 Exposure Index = 229 */
    {290, 1108},  /* Gain = 1.132812 Exposure Index = 230 */
    {299, 1108},  /* Gain = 1.167969 Exposure Index = 231 */
    {308, 1108},  /* Gain = 1.203125 Exposure Index = 232 */
    {318, 1108},  /* Gain = 1.242188 Exposure Index = 233 */
    {328, 1108},  /* Gain = 1.281250 Exposure Index = 234 */
    {338, 1108},  /* Gain = 1.320312 Exposure Index = 235 */
    {349, 1108},  /* Gain = 1.363281 Exposure Index = 236 */
    {360, 1108},  /* Gain = 1.406250 Exposure Index = 237 */
    {371, 1108},  /* Gain = 1.449219 Exposure Index = 238 */
    {383, 1108},  /* Gain = 1.496094 Exposure Index = 239 */
    {395, 1108},  /* Gain = 1.542969 Exposure Index = 240 */
    {407, 1108},  /* Gain = 1.589844 Exposure Index = 241 */
    {420, 1108},  /* Gain = 1.640625 Exposure Index = 242 */
    {433, 1108},  /* Gain = 1.691406 Exposure Index = 243 */
    {446, 1108},  /* Gain = 1.742188 Exposure Index = 244 */
    {460, 1108},  /* Gain = 1.796875 Exposure Index = 245 */
    {474, 1108},  /* Gain = 1.851562 Exposure Index = 246 */
    {489, 1108},  /* Gain = 1.910156 Exposure Index = 247 */
    {504, 1108},  /* Gain = 1.968750 Exposure Index = 248 */
    {520, 1108},  /* Gain = 2.031250 Exposure Index = 249 */
    {536, 1108},  /* Gain = 2.093750 Exposure Index = 250 */
    {553, 1108},  /* Gain = 2.160156 Exposure Index = 251 */
    {570, 1108},  /* Gain = 2.226562 Exposure Index = 252 */
    {588, 1108},  /* Gain = 2.296875 Exposure Index = 253 */
    {606, 1108},  /* Gain = 2.367188 Exposure Index = 254 */
    {625, 1108},  /* Gain = 2.441406 Exposure Index = 255 */
    {644, 1108},  /* Gain = 2.515625 Exposure Index = 256 */
    {664, 1108},  /* Gain = 2.593750 Exposure Index = 257 */
    {684, 1108},  /* Gain = 2.671875 Exposure Index = 258 */
    {705, 1108},  /* Gain = 2.753906 Exposure Index = 259 */
    {727, 1108},  /* Gain = 2.839844 Exposure Index = 260 */
    {749, 1108},  /* Gain = 2.925781 Exposure Index = 261 */
    {772, 1108},  /* Gain = 3.015625 Exposure Index = 262 */
    {796, 1108},  /* Gain = 3.109375 Exposure Index = 263 */
    {820, 1108},  /* Gain = 3.203125 Exposure Index = 264 */
    {845, 1108},  /* Gain = 3.300781 Exposure Index = 265 */
    {871, 1108},  /* Gain = 3.402344 Exposure Index = 266 */
    {898, 1108},  /* Gain = 3.507812 Exposure Index = 267 */
    {925, 1108},  /* Gain = 3.613281 Exposure Index = 268 */
    {953, 1108},  /* Gain = 3.722656 Exposure Index = 269 */
    {982, 1108},  /* Gain = 3.835938 Exposure Index = 270 */
    {1012, 1108}, /* Gain = 3.953125 Exposure Index = 271 */
    {1043, 1108}, /* Gain = 4.074219 Exposure Index = 272 */
    {1075, 1108}, /* Gain = 4.199219 Exposure Index = 273 */
    {1108, 1108}, /* Gain = 4.328125 Exposure Index = 274 */
    {1142, 1108}, /* Gain = 4.460938 Exposure Index = 275 */
    {1177, 1108}, /* Gain = 4.597656 Exposure Index = 276 */
    {1213, 1108}, /* Gain = 4.738281 Exposure Index = 277 */
    {1250, 1108}, /* Gain = 4.882812 Exposure Index = 278 */
    {1288, 1108}, /* Gain = 5.031250 Exposure Index = 279 */
    {1327, 1108}, /* Gain = 5.183594 Exposure Index = 280 */
    {1367, 1108}, /* Gain = 5.339844 Exposure Index = 281 */
    {1409, 1108}, /* Gain = 5.503906 Exposure Index = 282 */
    {1452, 1108}, /* Gain = 5.671875 Exposure Index = 283 */
    {1496, 1108}, /* Gain = 5.843750 Exposure Index = 284 */
    {1541, 1108}, /* Gain = 6.019531 Exposure Index = 285 */
    {1588, 1108}, /* Gain = 6.203125 Exposure Index = 286 */
    {1636, 1108}, /* Gain = 6.390625 Exposure Index = 287 */
    {1686, 1108}, /* Gain = 6.585938 Exposure Index = 288 */
    {1737, 1108}, /* Gain = 6.785156 Exposure Index = 289 */
    {1790, 1108}, /* Gain = 6.992188 Exposure Index = 290 */
    {1844, 1108}, /* Gain = 7.203125 Exposure Index = 291 */
    {1900, 1108}, /* Gain = 7.421875 Exposure Index = 292 */
    {1957, 1108}, /* Gain = 7.644531 Exposure Index = 293 */
    {2016, 1108}, /* Gain = 7.875000 Exposure Index = 294 */
};

int REF_EXPO = table[0][0] * table[0][1]; // 256*2

struct Options
{
    int cam_width;
    int cam_height;
    int total_pixel_count;
    int target_exposure;
    int data_bits;
    bool is_load_from_file;

    Options()
        : cam_width(640),
          cam_height(480),
          total_pixel_count(cam_width * cam_height),
          target_exposure(60),
          data_bits(8),
          is_load_from_file(false)
    {
    }
};

bool load_luma_target_ok_ = false;
Options gOptions;

bool LoadOptionsFromFile(const std::string &config_file, Options &options)
{
    YAML::Node config_node = YAML::LoadFile(config_file);

    options.target_exposure = config_node["target_exposure"].as<int>();
    options.data_bits = config_node["data_bits"].as<int>();

    options.is_load_from_file = true;

    return true;
}

void CalMeanIwith0OverExpo(unsigned char *InputData, int *info)
{
    int mean = 0;
    int gray = 0;
    if (gOptions.data_bits == 16)
    {
        uint16_t *data_16 = reinterpret_cast<uint16_t *>(InputData);
        for (int i = 0; i < gOptions.total_pixel_count; i++)
        {
            gray = (int)data_16[i];
            mean += gray;
        }
        info[0] = (mean >> 2);
    }
    else
    {
        for (int i = 0; i < gOptions.total_pixel_count; i++)
        {
            gray = (int)InputData[i];
            mean += gray;
        }
        info[0] = mean;
    }
    info[1] = gOptions.total_pixel_count;
}

void NR_INTERFACE_EXPORT NR_INTERFACE_API NRExposurePredict(unsigned char *InputData0, uint16_t *i_time, uint16_t *i_gain, uint16_t i_width,
                                                            uint16_t i_height, uint16_t i_step)
{
    if (NULL == i_time || NULL == i_gain)
    {
        std::cout << "LOGE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ i_time or i_gain NULL " << std::endl;
        return;
    }

    if (i_step != i_width)
        std::cout << "warning !" << std::endl;

    if (!load_luma_target_ok_)
    {
        const char *filename = "/usrdata/config/uvc/nr_auto_exposure.yaml";
        std::ifstream file(filename);
        if (file)
        {
            if (LoadOptionsFromFile(filename, gOptions))
            {
                gOptions.cam_width = i_width;
                gOptions.cam_height = i_height;
                gOptions.total_pixel_count = gOptions.cam_width * gOptions.cam_height;
                load_luma_target_ok_ = true;
            }
        }
    }

    int info[4][2];

    // char threadname[256];
    // snprintf(threadname, 256, "ExposurePredict");
    // pthread_setname_np(pthread_self(), threadname);

    // cpu_set_t cpuset;
    // CPU_SET(0, &cpuset);
    // CPU_SET(1, &cpuset);
    // CPU_SET(2, &cpuset);
    // CPU_SET(3, &cpuset);

    // std::thread thread0(CalMeanIwith0OverExpo, InputData0, info[0]);
    // sched_setaffinity(thread0.native_handle(), sizeof(cpu_set_t), &cpuset);
    CalMeanIwith0OverExpo(InputData0, info[0]);

    // std::thread thread1(CalMeanIwith0OverExpo, InputData1, info[1]);
    // sched_setaffinity(thread1.native_handle(), sizeof(cpu_set_t), &cpuset);

    // std::thread thread2(CalMeanIwith0OverExpo, InputData2, info[2]);
    // sched_setaffinity(thread2.native_handle(), sizeof(cpu_set_t), &cpuset);

    // std::thread thread3(CalMeanIwith0OverExpo, InputData3, info[3]);
    // sched_setaffinity(thread3.native_handle(), sizeof(cpu_set_t), &cpuset);

    //  thread0.join();
    //  thread1.join();
    //  thread2.join();
    //  thread3.join();

    double mean[3];
    mean[0] = (double)info[0][0] / info[0][1];
    // mean[1] = (double)info[1][0] / info[1][1];
    // mean[2] = (double)(info[2][0] + info[3][0]) / (info[2][1] + info[3][1]);

    double log104_inv = 1.0 / log(1.03125);
    int table_size = (int)table.size();
    for (int cnt = 0; cnt < 1; cnt++)
    {
        int cur_time = (int)*(i_time + cnt);
        int cur_gain = (int)*(i_gain + cnt);
        int lastExpo = cur_time * cur_gain;

#ifdef TEST_FILTER
        int lastExpo1 = (int)*(i_time + cnt + 1) * (int)*(i_gain + cnt + 1);
        int lastExpo2 = (int)*(i_time + cnt + 2) * (int)*(i_gain + cnt + 2);
        lastExpo = int((lastExpo + lastExpo1 + lastExpo2) / 3.0);

#endif
        int lastIndex = (int)(log((double)lastExpo / REF_EXPO) * log104_inv + 0.5);
        if (lastIndex - 2 >= 0)
            lastIndex = lastIndex - 2;
        int i_last = table[lastIndex][0] * table[lastIndex][1];
        if (i_last > lastExpo && lastIndex >= 1)
            lastIndex--;
        else if (i_last < lastExpo && lastIndex + 1 <= 294)
            lastIndex++;

        if (std::abs(gOptions.target_exposure - mean[cnt]) < 9)
        {
#ifdef TEST_FILTER
            i_gain[cnt + 2] = i_gain[cnt + 1];
            i_time[cnt + 2] = i_time[cnt + 1];
            i_gain[cnt + 1] = i_gain[cnt];
            i_time[cnt + 1] = i_time[cnt];
#endif

            return;
        }
        int gap = (int)((log(gOptions.target_exposure / mean[cnt]) * log104_inv + 0.5) * 0.4);
        if (gap > 10)
        {
            gap = 10;
        }
        else if (gap < -10)
        {
            gap = -10;
        }

        int curIndex = std::min(std::max(lastIndex + gap, 0), table_size - 1);

#ifdef TEST_FILTER
        i_gain[cnt + 2] = i_gain[cnt + 1];
        i_time[cnt + 2] = i_time[cnt + 1];
        i_gain[cnt + 1] = i_gain[cnt];
        i_time[cnt + 1] = i_time[cnt];
#endif

        i_gain[cnt] = (uint16_t)table[curIndex][0];
        i_time[cnt] = (uint16_t)table[curIndex][1];
    }
}
