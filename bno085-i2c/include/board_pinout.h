#ifndef __BOARD_PINOUT
// #include <Arduino.h>
#define __BOARD_PINOUT

#define _PS0_WAKE D3
// #define _PS1
#define _INT D1
#define _RST D2

#define _SPI_CS D8
#define _SPI_MOSI D7
#define _SPI_MISO D6
#define _SPI_SCK D5

#define EVERY_MS(x)                    \
    static uint32_t tmr;               \
    bool flag = millis() - tmr >= (x); \
    if (flag)                          \
        tmr = millis();                \
    if (flag)

#endif