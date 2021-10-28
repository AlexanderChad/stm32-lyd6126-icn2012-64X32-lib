#include "ledmatrix.h"

#include <main.h>

#define LED_MATRIX_WIDTH        64
#define LED_MATRIX_HEIGHT       32


static uint8_t swbuff = 0;
static uint16_t TOnLP = 300;
static uint8_t RAW_DISPLAY_0[2304] = {0,47,102,0,152,0,0,68,0,192,3,0,0,0,0,0,128,111,19,0,248,0,0,40,0,224,7,0,0,0,0,0,128,223,59,0,56,0,0,16,0,16,6,0,0,0,0,0,128,159,59,0,88,0,0,0,0,128,7,0,0,0,0,0,128,183,105,0,152,0,0,0,0,128,15,0,0,0,0,0,192,55,237,0,0,0,0,0,0,0,105,0,0,0,0,0,192,49,174,3,0,0,0,0,0,0,114,1,0,0,0,0,192,4,4,0,16,32,113,17,0,0,190,1,248,0,0,0,0,48,48,0,0,0,0,0,192,6,4,0,56,112,17,10,0,16,48,0,0,0,0,0,0,6,0,0,124,80,113,4,0,24,16,0,132,25,1,239,0,0,0,0,56,112,17,10,0,12,16,0,6,0,36,144,0,0,0,0,16,80,119,17,0,2,16,0,6,0,140,152,0,192,1,0,0,0,0,0,0,3,144,7,0,0,12,251,0,224,3,0,0,0,0,0,0,31,224,15,1,0,12,255,0,112,4,0,0,0,0,0,0,0,0,0,1,0,240,239,0,48,8,0,0,0,0,0,128,79,194,1,152,0,0,68,0,224,1,0,0,0,0,0,128,159,57,0,248,0,0,40,0,48,7,0,0,0,0,0,192,207,27,2,56,0,0,16,0,0,7,0,0,0,0,0,0,223,121,6,88,0,0,0,0,64,14,0,0,0,0,0,192,159,253,0,152,0,0,0,0,64,30,0,0,0,0,0,192,187,188,1,0,0,0,0,0,128,87,0,0,0,0,0,192,112,196,3,0,0,0,0,0,0,189,0,0,0,0,0,192,16,14,3,16,32,113,17,0,6,198,3,248,0,0,0,0,0,24,0,0,0,0,0,0,198,0,0,56,112,17,10,0,16,48,0,0,0,0,0,128,194,0,0,124,80,113,4,0,8,48,0,123,134,254,80,0,18,0,0,56,112,17,10,0,4,48,0,249,231,218,235,0,0,0,0,16,80,119,17,0,4,32,0,121,130,114,119,0,224,3,0,0,0,0,0,0,1,32,3,15,128,146,116,0,240,7,0,0,0,0,0,128,31,240,15,254,1,178,241,0,32,14,0,0,0,0,0,0,30,0,14,254,129,160,38,0,32,28,0,0,0,0,0,0,87,221,3,152,0,0,68,0,160,5,0,0,0,0,0,192,255,90,3,248,0,0,40,0,240,3,0,0,0,0,0,192,207,19,5,56,0,0,16,0,8,15,0,0,0,0,0,128,223,31,0,88,0,0,0,0,216,14,0,0,0,0,0,0,39,123,4,152,0,0,0,0,96,125,0,0,0,0,0,192,247,35,0,0,0,0,0,0,128,209,0,0,0,0,0,224,122,30,1,0,0,0,0,0,0,156,2,0,0,0,0,0,106,206,1,16,32,113,17,0,7,124,3,248,0,0,0,0,16,16,0,0,0,0,0,0,192,2,0,56,112,17,10,0,56,0,0,0,0,0,0,64,38,0,0,124,80,113,4,0,12,56,0,83,28,186,20,0,4,0,0,56,112,17,10,0,6,32,0,57,64,221,29,0,144,1,0,16,80,119,17,0,6,0,0,99,133,84,33,0,160,1,0,0,0,0,0,128,12,96,8,55,6,4,45,0,224,2,0,0,0,0,0,128,47,128,31,126,134,212,111,0,96,14,0,0,0,0,0,0,9,224,17,126,135,7,132,0,48,28,0,0,0,0,0,0,15,2,0,0,12,0,16,0,128,1,0,0,0,0,0,128,15,17,0,0,12,0,40,0,32,3,0,0,0,0,0,128,223,59,0,0,108,0,0,0,0,6,0,0,0,0,0,128,223,59,0,0,76,0,0,0,0,6,0,0,0,0,0,128,183,105,0,0,124,0,0,0,0,12,0,0,0,0,0,192,55,45,0,0,0,0,0,0,0,65,0,0,0,0,0,192,49,174,3,0,0,0,0,0,0,114,0,0,0,0,0,192,0,6,0,16,32,113,17,0,0,52,0,0,124,0,0,0,48,48,0,0,0,0,0,192,134,4,0,56,112,17,10,0,16,48,0,0,0,0,0,0,2,0,0,124,80,113,4,0,24,16,0,224,31,187,65,0,0,0,0,56,112,17,10,0,12,16,0,128,71,252,129,0,0,0,0,16,80,119,17,0,2,16,0,0,132,220,16,0,192,1,0,0,0,0,0,0,3,144,7,0,4,12,121,0,224,3,0,0,0,0,0,0,31,224,15,0,1,156,121,0,112,4,0,0,0,0,0,0,0,0,0,128,129,240,63,0,48,8,0,0,0,0,0,128,15,20,0,0,12,0,16,0,64,2,0,0,0,0,0,192,255,26,1,0,12,0,40,0,192,4,0,0,0,0,0,192,207,25,2,0,108,0,0,0,16,1,0,0,0,0,0,0,159,123,6,0,76,0,0,0,192,1,0,0,0,0,0,192,159,61,0,0,124,0,0,0,192,19,0,0,0,0,0,192,187,244,1,0,0,0,0,0,128,27,0,0,0,0,0,192,114,68,1,0,0,0,0,0,0,25,0,0,0,0,0,192,22,12,1,16,32,113,17,0,6,10,0,0,124,0,0,0,0,24,0,0,0,0,0,0,66,0,0,56,112,17,10,0,16,48,0,0,0,0,0,128,196,0,0,124,80,113,4,0,8,48,0,159,153,68,174,0,16,0,0,56,112,17,10,0,6,48,0,127,184,2,88,0,0,0,0,16,80,119,17,0,4,32,0,63,122,34,169,0,224,3,0,0,0,0,0,128,1,32,3,123,250,214,182,0,240,7,0,0,0,0,0,128,31,240,31,251,254,102,231,0,32,14,0,0,0,0,0,0,30,0,14,121,126,247,196,0,32,28,0,0,0,0,0,128,55,4,0,0,12,0,16,0,224,0,0,0,0,0,0,128,31,58,2,0,12,0,40,0,208,6,0,0,0,0,0,192,31,154,7,0,108,0,0,0,16,0,0,0,0,0,0,128,191,29,2,0,76,0,0,0,128,8,0,0,0,0,0,0,39,123,6,0,124,0,0,0,128,3,0,0,0,0,0,192,119,235,2,0,0,0,0,0,128,77,0,0,0,0,0,224,120,222,1,0,0,0,0,0,0,28,1,0,0,0,0,32,101,204,3,16,32,113,17,0,7,16,1,0,124,0,0,0,16,16,0,0,0,0,0,128,124,2,0,56,112,17,10,0,56,0,0,0,0,0,0,0,105,0,0,124,80,113,4,0,28,56,0,68,224,69,151,0,10,0,0,56,112,17,10,0,4,32,0,70,185,15,178,0,144,1,0,16,80,119,17,0,7,0,0,198,187,175,207,0,160,1,0,0,0,0,0,0,12,96,8,52,184,187,202,0,240,2,0,0,0,0,0,128,47,128,7,133,126,43,182,0,224,14,0,0,0,0,0,0,25,224,17,134,125,168,162,0,48,28,0,0,0,0,0,128,15,18,0,0,0,38,68,0,128,0,0,0,0,0,0,128,31,24,1,0,0,62,40,0,32,2,0,0,0,0,0,192,31,56,2,0,0,38,68,0,0,4,0,0,0,0,0,128,255,127,6,0,0,38,0,0,0,0,0,0,0,0,0,128,191,121,0,0,0,62,0,0,0,4,0,0,0,0,0,192,255,61,0,0,0,0,0,0,0,1,0,0,0,0,0,192,115,110,0,0,0,0,0,0,0,18,0,0,0,0,0,192,0,78,0,0,32,113,17,0,6,48,0,0,0,30,0,0,48,48,0,0,0,0,0,192,192,4,0,0,112,17,10,0,16,48,0,0,0,0,0,128,192,0,0,0,80,113,4,0,24,16,0,128,27,1,1,0,0,0,0,0,112,17,10,0,12,48,0,0,28,12,0,0,0,0,0,0,80,119,17,0,6,16,0,0,252,12,0,0,224,1,0,0,0,0,0,0,3,176,7,0,124,4,0,0,240,3,0,0,0,0,0,128,31,240,15,0,124,12,0,0,112,6,0,0,0,0,0,0,0,0,0,0,124,240,17,0,48,28,0,0,0,0,0,0,31,4,0,0,0,38,68,0,64,3,0,0,0,0,0,192,15,145,2,0,0,62,40,0,192,5,0,0,0,0,0,128,255,223,5,0,0,38,68,0,16,3,0,0,0,0,0,128,159,155,0,0,0,38,0,0,192,6,0,0,0,0,0,192,215,47,7,0,0,62,0,0,128,11,0,0,0,0,0,192,55,103,3,0,0,0,0,0,128,91,0,0,0,0,0,224,60,54,3,0,0,0,0,0,0,57,0,0,0,0,0,224,119,132,1,0,32,113,17,0,1,14,0,0,0,30,0,0,16,24,0,0,0,0,0,128,255,135,0,0,112,17,10,0,56,48,0,0,0,0,0,64,57,1,0,0,80,113,4,0,12,56,0,96,134,254,4,0,112,1,0,0,112,17,10,0,6,16,0,0,227,242,1,0,144,1,0,0,80,119,17,0,2,32,1,2,62,242,1,0,192,3,0,0,0,0,0,128,7,64,11,0,158,202,0,0,224,7,0,0,0,0,0,0,63,224,31,128,191,146,0,0,160,12,0,0,0,0,0,0,63,224,31,128,255,160,16,0,32,8,0,0,0,0,0,0,7,137,1,0,0,38,68,0,96,1,0,0,0,0,0,192,153,184,2,0,0,62,40,0,16,5,0,0,0,0,0,192,104,154,2,0,0,38,68,0,0,2,0,0,0,0,0,64,80,48,6,0,0,38,0,0,0,15,0,0,0,0,0,64,34,127,6,0,0,62,0,0,192,25,0,0,0,0,0,224,40,106,7,0,0,0,0,0,128,157,0,0,0,0,0,64,153,101,1,0,0,0,0,0,0,60,0,0,0,0,0,64,43,165,3,0,32,113,17,0,8,20,0,0,0,30,0,0,32,48,0,0,0,0,0,64,47,8,1,0,112,17,10,0,16,0,0,0,0,0,0,128,237,6,0,0,80,113,4,0,24,48,0,70,28,146,3,0,152,2,0,0,112,17,10,0,12,0,0,151,94,240,129,0,48,1,0,0,80,119,17,0,3,48,2,5,67,145,131,0,176,3,0,0,0,0,0,0,1,144,9,19,224,28,24,0,224,6,0,0,0,0,0,128,63,224,31,9,66,180,57,0,112,13,0,0,0,0,0,128,28,16,14,25,129,87,40,0,48,8,0,0,0,0,0};
static uint8_t RAW_DISPLAY_1[2304] = {0,1,0,0,152,0,0,68,0,0,0,0,0,0,0,0,12,2,0,0,248,0,0,40,0,62,0,0,0,0,0,0,4,0,0,0,56,0,0,16,0,62,0,0,0,0,0,0,4,247,241,31,88,0,0,0,0,62,0,0,0,0,0,0,2,224,1,0,152,0,0,0,0,60,0,0,0,0,0,0,60,16,128,1,0,0,0,0,0,56,0,0,0,0,0,0,252,31,198,0,0,0,0,0,56,16,1,0,0,0,0,0,240,12,6,0,16,32,113,17,56,1,3,0,248,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,56,112,17,10,48,0,0,0,0,0,0,0,0,195,0,0,124,80,113,4,112,0,0,0,0,255,255,255,128,135,0,0,56,112,17,10,24,0,0,0,128,255,255,255,128,7,1,0,16,80,119,17,24,0,0,0,0,255,255,255,128,3,0,0,0,0,0,0,0,0,0,0,0,255,255,255,0,2,0,0,0,0,0,0,28,0,0,0,0,255,255,255,128,1,0,0,0,0,0,0,60,0,0,0,0,255,255,255,192,1,0,0,0,0,0,0,152,35,0,0,152,0,0,68,0,0,0,0,0,0,0,0,22,4,0,0,248,0,0,40,0,28,0,0,0,0,0,0,10,246,243,71,56,0,0,16,0,31,0,0,0,0,0,0,138,0,10,78,88,0,0,0,0,23,0,0,0,0,0,0,157,55,130,28,152,0,0,0,0,26,0,0,0,0,0,0,120,44,192,0,0,0,0,0,48,16,0,0,0,0,0,0,248,14,2,0,0,0,0,0,244,164,2,0,0,0,0,0,248,15,2,0,16,32,113,17,252,141,1,0,248,0,0,0,224,0,6,0,0,0,0,0,0,172,0,0,56,112,17,10,96,0,0,0,0,0,0,0,128,3,0,0,124,80,113,4,176,0,1,0,255,0,0,0,0,3,1,0,56,112,17,10,48,0,2,0,127,0,0,0,64,131,0,0,16,80,119,17,8,0,6,0,255,0,0,0,192,199,1,0,0,0,0,0,12,0,6,0,255,0,0,0,128,129,3,0,0,0,0,0,40,0,24,0,255,0,0,0,0,0,0,0,0,0,0,0,82,0,56,0,255,0,0,0,192,0,6,0,0,0,0,0,244,64,3,0,152,0,0,68,0,0,0,0,0,0,0,0,138,7,0,0,248,0,0,40,0,2,0,0,0,0,0,0,12,176,217,10,56,0,0,16,0,63,0,0,0,0,0,0,193,236,123,12,88,0,0,0,0,14,0,0,0,0,0,0,4,65,18,15,152,0,0,0,0,30,0,0,0,0,0,0,30,90,246,1,0,0,0,0,0,62,0,0,0,0,0,0,124,14,134,1,0,0,0,0,24,141,1,0,0,0,0,0,96,199,129,0,16,32,113,17,252,36,7,0,248,0,0,0,0,65,2,0,0,0,0,0,0,4,0,0,56,112,17,10,224,128,1,0,0,0,0,0,0,160,0,0,124,80,113,4,48,0,2,0,255,240,127,0,192,67,1,0,56,112,17,10,40,0,6,0,127,240,127,0,128,67,0,0,16,80,119,17,0,0,4,0,255,240,127,0,128,1,3,0,0,0,0,0,0,0,0,0,255,240,127,0,192,1,1,0,0,0,0,0,118,0,60,0,255,240,127,0,192,128,1,0,0,0,0,0,56,0,68,0,255,240,127,0,128,65,2,0,0,0,0,0,144,35,0,0,0,12,0,16,0,0,0,0,0,0,0,0,30,6,0,0,0,12,0,40,0,60,0,0,0,0,0,0,12,0,1,0,0,108,0,0,0,62,0,0,0,0,0,0,12,230,241,15,0,76,0,0,0,22,0,0,0,0,0,0,3,224,1,0,0,124,0,0,0,24,0,0,0,0,0,0,24,0,128,0,0,0,0,0,0,16,0,0,0,0,0,0,248,14,6,0,0,0,0,0,56,0,1,0,0,0,0,0,240,132,6,0,16,32,113,17,56,1,3,0,0,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,56,112,17,10,48,0,0,0,0,0,0,0,0,3,0,0,124,80,113,4,112,0,0,0,255,255,255,255,128,3,0,0,56,112,17,10,24,0,0,0,255,255,255,255,128,3,0,0,16,80,119,17,8,0,0,0,255,255,255,255,128,3,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0,28,0,0,0,255,255,255,255,128,1,0,0,0,0,0,0,56,0,0,0,255,255,255,255,192,1,0,0,0,0,0,0,40,65,2,0,0,12,0,16,0,0,0,0,0,0,0,0,236,6,2,0,0,12,0,40,0,26,0,0,0,0,0,0,22,246,242,71,0,108,0,0,0,31,0,0,0,0,0,0,131,17,10,94,0,76,0,0,0,40,0,0,0,0,0,0,132,55,2,28,0,124,0,0,0,36,0,0,0,0,0,0,60,60,0,1,0,0,0,0,48,56,0,0,0,0,0,0,124,141,194,0,0,0,0,0,148,145,2,0,0,0,0,0,32,9,1,0,16,32,113,17,252,97,1,0,0,124,0,0,224,0,6,0,0,0,0,0,0,192,0,0,56,112,17,10,96,0,0,0,0,0,0,0,128,192,0,0,124,80,113,4,48,0,1,0,1,0,0,192,0,135,1,0,56,112,17,10,48,0,2,0,1,0,0,192,0,197,1,0,16,80,119,17,24,0,6,0,0,0,0,192,192,193,1,0,0,0,0,0,8,0,6,0,0,0,0,128,128,131,3,0,0,0,0,0,32,0,24,0,0,0,0,192,0,0,0,0,0,0,0,0,86,0,48,0,0,0,0,192,192,0,2,0,0,0,0,0,76,112,1,0,0,12,0,16,0,0,0,0,0,0,0,0,54,179,3,0,0,12,0,40,0,18,0,0,0,0,0,0,42,157,200,10,0,108,0,0,0,0,0,0,0,0,0,0,198,57,90,28,0,76,0,0,0,5,0,0,0,0,0,0,26,65,146,14,0,124,0,0,0,18,0,0,0,0,0,0,34,80,86,1,0,0,0,0,128,41,0,0,0,0,0,0,252,21,5,0,0,0,0,0,224,229,0,0,0,0,0,0,72,14,3,0,16,32,113,17,156,175,4,0,0,124,0,0,0,65,0,0,0,0,0,0,0,124,0,0,56,112,17,10,224,128,1,0,0,0,0,0,0,227,0,0,124,80,113,4,176,0,2,0,254,255,255,63,64,197,0,0,56,112,17,10,8,0,6,0,254,255,255,63,64,6,1,0,16,80,119,17,16,0,0,0,255,255,255,63,128,5,2,0,0,0,0,0,4,0,0,0,255,255,255,127,192,3,0,0,0,0,0,0,110,0,60,0,255,255,255,63,192,128,1,0,0,0,0,0,12,0,76,0,255,255,255,63,128,65,6,0,0,0,0,0,16,35,0,0,0,0,38,68,0,0,0,0,0,0,0,0,30,6,0,0,0,0,62,40,0,16,0,0,0,0,0,0,12,0,1,0,0,0,38,68,0,16,0,0,0,0,0,0,12,228,208,14,0,0,38,0,0,0,0,0,0,0,0,0,3,96,1,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,4,6,0,0,0,0,0,56,1,1,0,0,0,0,0,32,0,6,0,0,32,113,17,56,33,3,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,17,10,48,0,0,0,0,0,0,0,0,0,0,0,0,80,113,4,48,0,0,0,255,255,255,255,0,0,0,0,0,112,17,10,24,0,0,0,255,255,255,255,0,0,0,0,0,80,119,17,8,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0,28,0,0,0,255,255,255,255,128,1,0,0,0,0,0,0,56,0,0,0,255,255,255,255,192,1,0,0,0,0,0,0,168,65,2,0,0,0,38,68,0,0,0,0,0,0,0,0,236,6,3,0,0,0,62,40,0,40,0,0,0,0,0,0,30,182,242,71,0,0,38,68,0,46,0,0,0,0,0,0,131,19,43,93,0,0,38,0,0,0,0,0,0,0,0,0,132,151,2,28,0,0,62,0,0,0,0,0,0,0,0,0,24,8,0,0,0,0,0,0,176,16,0,0,0,0,0,0,40,8,2,0,0,0,0,0,144,128,0,0,0,0,0,0,80,0,2,0,0,32,113,17,220,67,0,0,0,0,30,0,224,0,2,0,0,0,0,0,0,0,0,0,0,112,17,10,96,0,0,0,0,0,0,0,0,0,0,0,0,80,113,4,112,0,1,0,255,255,255,255,0,1,0,0,0,112,17,10,32,0,2,0,255,255,255,255,0,1,0,0,0,80,119,17,16,0,6,0,255,255,255,255,128,1,0,0,0,0,0,0,0,0,6,0,255,255,255,255,0,0,0,0,0,0,0,0,32,0,24,0,255,255,255,255,0,0,0,0,0,0,0,0,84,0,32,0,255,255,255,255,128,0,2,0,0,0,0,0,204,114,1,0,0,0,38,68,0,0,0,0,0,0,0,0,54,179,2,0,0,0,62,40,0,30,0,0,0,0,0,0,50,205,136,8,0,0,38,68,0,25,0,0,0,0,0,0,30,59,33,19,0,0,38,0,0,6,0,0,0,0,0,0,26,160,16,0,0,0,62,0,0,24,0,0,0,0,0,0,8,52,22,1,0,0,0,0,0,1,0,0,0,0,0,0,140,11,0,0,0,0,0,0,196,208,2,0,0,0,0,0,192,4,0,0,0,32,113,17,180,193,5,0,0,0,30,0,0,64,4,0,0,0,0,0,0,0,0,0,0,112,17,10,96,0,1,0,0,0,0,0,128,3,0,0,0,80,113,4,192,0,2,0,241,1,0,0,0,2,0,0,0,112,17,10,16,0,4,0,158,0,0,0,0,2,0,0,0,80,119,17,24,0,0,0,220,0,0,0,0,1,0,0,0,0,0,0,12,0,0,0,24,0,0,0,0,0,0,0,0,0,0,0,106,0,36,0,208,1,0,0,192,0,0,0,0,0,0,0,6,0,92,0,206,0,0,0,192,64,6,0,0,0,0,0};

static uint8_t *RAW_DISPLAY;
static uint8_t *RAW_DISPLAY_B;

void digitalWrite(GPIO_TypeDef * Port, uint16_t NumP, uint8_t  stat) {
if(stat){
	HAL_GPIO_WritePin(Port, NumP, GPIO_PIN_SET);
}else{
	HAL_GPIO_WritePin(Port, NumP, GPIO_PIN_RESET);
}
}

void led_matrix_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, D_Pin|C_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, B_Pin|A_Pin|LAT_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, OE_Pin|CLK_Pin|B2_Pin|G2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, R2_Pin|B1_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, G1_Pin|R1_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : D_Pin C_Pin */
	  GPIO_InitStruct.Pin = D_Pin|C_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pins : B_Pin A_Pin LAT_Pin */
	  GPIO_InitStruct.Pin = B_Pin|A_Pin|LAT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : OE_Pin CLK_Pin B2_Pin G2_Pin */
	  GPIO_InitStruct.Pin = OE_Pin|CLK_Pin|B2_Pin|G2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /*Configure GPIO pins : R2_Pin B1_Pin */
	  GPIO_InitStruct.Pin = R2_Pin|B1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : G1_Pin R1_Pin */
	  GPIO_InitStruct.Pin = G1_Pin|R1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  RAW_DISPLAY = RAW_DISPLAY_0;
}

//HAL_Delay(us);

void led_matrix_setBright(uint16_t Panel_Brightness) {
  TOnLP = Panel_Brightness;
}

static void delay_us (uint16_t us) //create delay function
{
int i=0;
for (i=0; i<=us; i++)
{
	asm("NOP"); //Perform no operation //assembly code
}
}

void led_matrix_loop(void) {
  uint8_t i_m;
  uint8_t bit_mask;
  for (uint8_t RGB333_i = 0; RGB333_i < 3; RGB333_i++) {
  for (uint8_t y_b = 0; y_b < 8; y_b++) {
    digitalWrite(GPIOD, OE_Pin, 1);
    digitalWrite(GPIOB, LAT_Pin, 0);
    for (uint8_t x_b = 0; x_b < 128; x_b++) {
      bit_mask = 1 << (x_b % 8);
      i_m = (y_b * 16) + (x_b / 8);
      digitalWrite(GPIOD, CLK_Pin, 0);
      digitalWrite(GPIOA, R1_Pin, *(RAW_DISPLAY + (RGB333_i * 256) + i_m) & bit_mask);
      digitalWrite(GPIOA, G1_Pin, *(RAW_DISPLAY + ((3+RGB333_i) * 256) + i_m) & bit_mask);
      digitalWrite(GPIOC, B1_Pin, *(RAW_DISPLAY + ((6+RGB333_i)  * 256) + i_m) & bit_mask);
      i_m += 128;
      digitalWrite(GPIOC, R2_Pin, *(RAW_DISPLAY + (RGB333_i * 256) + i_m) & bit_mask);
      digitalWrite(GPIOD, G2_Pin, *(RAW_DISPLAY + ((3+RGB333_i) * 256) + i_m) & bit_mask);
      digitalWrite(GPIOD, B2_Pin, *(RAW_DISPLAY + ((6+RGB333_i) * 256) + i_m) & bit_mask);
      digitalWrite(GPIOD, CLK_Pin, 1);
      if (x_b == 125) {
        digitalWrite(GPIOB, LAT_Pin, 1);
      }
    }
    digitalWrite(GPIOB, A_Pin, y_b & 0b1);
    digitalWrite(GPIOB, B_Pin, y_b & 0b10);
    digitalWrite(GPIOE, C_Pin, y_b & 0b100);
    digitalWrite(GPIOD, OE_Pin, 0);
    delay_us(TOnLP);
  }
  }
}

void led_matrix_setPixel(uint8_t Xp, uint8_t Yp, uint16_t Color3) {
  uint8_t adr[] = {8, 24, 40, 56, 72, 88, 104, 120, 0, 16, 32, 48, 64, 80, 96, 112};
  uint8_t Red_p0 = 0;
  uint8_t Green_p0 = 0;
  uint8_t Blue_p0 = 0;
  uint8_t Red_p1 = 0;
  uint8_t Green_p1 = 0;
  uint8_t Blue_p1 = 0;
  uint8_t Red_p2 = 0;
  uint8_t Green_p2 = 0;
  uint8_t Blue_p2 = 0;
  if (Yp < 16) {
    Yp = adr[Yp] + (Xp / 8);
  } else {
    Yp = adr[Yp - 16] + (Xp / 8) + 128;
  }
  Xp %= 8;
  if (Color3 & 0b100000000) {
	  Red_p0 = 1 << Xp;
  }
  if (Color3 & 0b010000000) {
  	  Red_p1 = 1 << Xp;
    }
  if (Color3 & 0b001000000) {
	  Red_p2 = 1 << Xp;
    }
  if (Color3 & 0b000100000) {
	  Green_p0 = 1 << Xp;
    }
  if (Color3 & 0b000010000) {
	  Green_p1 = 1 << Xp;
    }
  if (Color3 & 0b000001000) {
	  Green_p2 = 1 << Xp;
    }
  if (Color3 & 0b000000100) {
	  Blue_p0 = 1 << Xp;
    }
  if (Color3 & 0b000000010) {
	  Blue_p1 = 1 << Xp;
    }
  if (Color3 & 0b000000001) {
	  Blue_p2 = 1 << Xp;
    }
  if (!(*(RAW_DISPLAY_B + (0 * 256) + Yp) & Red_p0)) {
    if (Red_p0) {
      *(RAW_DISPLAY_B + (0 * 256) + Yp) |= Red_p0;
    }
    else {
      *(RAW_DISPLAY_B + (0 * 256) + Yp) &= ~(1 << Xp);
    }
  }
  if (!(*(RAW_DISPLAY_B + (1 * 256) + Yp) & Red_p1)) {
    if (Red_p1) {
      *(RAW_DISPLAY_B + (1 * 256) + Yp) |= Red_p1;
    }
    else {
      *(RAW_DISPLAY_B + (1 * 256) + Yp) &= ~(1 << Xp);
    }
  }
  if (!(*(RAW_DISPLAY_B + (2 * 256) + Yp) & Red_p2)) {
    if (Red_p2) {
      *(RAW_DISPLAY_B + (2 * 256) + Yp) |= Red_p2;
    }
    else {
      *(RAW_DISPLAY_B + (2 * 256) + Yp) &= ~(1 << Xp);
    }
  }
  if (!(*(RAW_DISPLAY_B + (3 * 256) + Yp) & Green_p0)) {
      if (Green_p0) {
        *(RAW_DISPLAY_B + (3 * 256) + Yp) |= Green_p0;
      }
      else {
        *(RAW_DISPLAY_B + (3 * 256) + Yp) &= ~(1 << Xp);
      }
  }
  if (!(*(RAW_DISPLAY_B + (4 * 256) + Yp) & Green_p1)) {
      if (Green_p1) {
        *(RAW_DISPLAY_B + (4 * 256) + Yp) |= Green_p1;
      }
      else {
        *(RAW_DISPLAY_B + (4 * 256) + Yp) &= ~(1 << Xp);
      }
  }
  if (!(*(RAW_DISPLAY_B + (5 * 256) + Yp) & Green_p2)) {
      if (Green_p2) {
        *(RAW_DISPLAY_B + (5 * 256) + Yp) |= Green_p2;
      }
      else {
        *(RAW_DISPLAY_B + (5 * 256) + Yp) &= ~(1 << Xp);
      }
  }
  if (!(*(RAW_DISPLAY_B + (6 * 256) + Yp) & Blue_p0)) {
      if (Blue_p0) {
        *(RAW_DISPLAY_B + (6 * 256) + Yp) |= Blue_p0;
      }
      else {
        *(RAW_DISPLAY_B + (6 * 256) + Yp) &= ~(1 << Xp);
      }
  }
  if (!(*(RAW_DISPLAY_B + (7 * 256) + Yp) & Blue_p1)) {
      if (Blue_p1) {
        *(RAW_DISPLAY_B + (7 * 256) + Yp) |= Blue_p1;
      }
      else {
        *(RAW_DISPLAY_B + (7 * 256) + Yp) &= ~(1 << Xp);
      }
  }
  if (!(*(RAW_DISPLAY_B + (8 * 256) + Yp) & Blue_p2)) {
      if (Blue_p2) {
        *(RAW_DISPLAY_B + (8 * 256) + Yp) |= Blue_p2;
      }
      else {
        *(RAW_DISPLAY_B + (8 * 256) + Yp) &= ~(1 << Xp);
      }
  }
}

void led_matrix_clear(void) {
  uint16_t i_p;
  for (i_p = 0; i_p < 2304; i_p++) {
    *(RAW_DISPLAY_B + i_p) = 0;
  }
}

void led_matrix_switchBuff(void) {
  swbuff = !swbuff;
  if (swbuff) {
    RAW_DISPLAY = RAW_DISPLAY_1;
    RAW_DISPLAY_B = RAW_DISPLAY_0;
  }
  else {
    RAW_DISPLAY = RAW_DISPLAY_0;
    RAW_DISPLAY_B = RAW_DISPLAY_1;
  }
}