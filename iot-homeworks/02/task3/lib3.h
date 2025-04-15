#ifndef LIB3_H
#define LIB3_H

#include <Arduino.h>

// Константы
const int pinButton[6] = {8, 9, 10, 11, 12, 13};
const int pinLed[3] = {3, 5, 6};
const int step = 50;

extern int lastStateButton[6];
extern int brightsLed[3];

// описания функций
void init_lib3();
void processing();
void inc_brightness(int n);
void dec_brightness(int n);
int debounce(int n);


#endif // LIB3_H
