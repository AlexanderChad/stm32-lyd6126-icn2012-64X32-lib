#ifndef _ledmatrix_H_
#define _ledmatrix_H_

#include <stdint.h>

#define LED_MATRIX_WIDTH        64
#define LED_MATRIX_HEIGHT       32

void led_matrix_init(void);
void led_matrix_loop(void);

void led_matrix_setPixel(uint8_t x, uint8_t y, uint16_t color);
void led_matrix_setBright(uint16_t bright);
void led_matrix_clear(void);
void led_matrix_switchBuff(void);

#endif
