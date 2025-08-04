#ifndef APP_H
#define APP_H

#include "em_gpio.h"
#include <stdint.h>
#include <stdbool.h>

// Khai báo các chân kết nối RC522
#define MFRC522_RST_PORT   gpioPortB
#define MFRC522_RST_PIN    7

#define MFRC522_CS_PORT    gpioPortC
#define MFRC522_CS_PIN     10

// Prototype các hàm chính
void app_init(void);
void app_process_action(void);

#endif // APP_H
