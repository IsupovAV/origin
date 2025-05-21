#ifndef LIB3_H
#define LIB3_H

#include <Arduino.h>

// Константы
const int DEBOUNCE_TIME = 5;
const int BRIGHT_TIME = 15;
const int pinButton[6] = {12, 13, 10, 11, 8, 9};
const int pinLed[3] = {6, 5, 3};  // красный, зеленый, синий
const int step = 51; // шаг изменения яркости

extern int lastStateButton[6];
extern int brightsLed[3];

// описания функций
void init_lib3();
void processing();
void inc_brightness(int n);
void dec_brightness(int n);
int debounce(int n);


#endif // LIB3_H
