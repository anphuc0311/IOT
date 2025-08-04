#ifndef MFRC522_H
#define MFRC522_H

#include <stdint.h>
#include <stdbool.h>

// Register addresses
#define CommIEnReg       0x02
#define ErrorReg         0x06

// TODO: Chỉnh lại các chân GPIO cho phù hợp với kết nối của bạn
#define MFRC522_CS_PORT      gpioPortC // Ví dụ: Port C
#define MFRC522_CS_PIN       10      // Ví dụ: Pin 10
#define MFRC522_RST_PORT     gpioPortB // Ví dụ: Port B
#define MFRC522_RST_PIN      7       // Ví dụ: Pin 7

// Các thanh ghi MFRC522
#define CommandReg           0x01
#define CommIrqReg           0x04
#define FIFODataReg          0x09
#define FIFOLevelReg         0x0A
#define ControlReg           0x0C
#define BitFramingReg        0x0D
#define CollReg              0x0E

#define PCD_IDLE             0x00
#define PCD_TRANSCEIVE       0x0C
#define PCD_AUTHENT          0x0E
#define PCD_RESETPHASE       0x0F

#define PICC_CMD_REQA        0x26
#define PICC_CMD_SEL_CL1     0x93
#define PICC_CMD_HLTA        0x50

// Định nghĩa kiểu dữ liệu cho UID
typedef struct {
    uint8_t size;         // Số byte trong UID (thường là 4, 7 hoặc 10)
    uint8_t uidByte[10];
} Uid;


// Các hàm chức năng chính
void MFRC522_Init(void);
bool MFRC522_PICC_IsNewCardPresent(void);
bool MFRC522_PICC_ReadCardSerial(void);
void MFRC522_PICC_HaltA(void);
void MFRC522_WriteReg(uint8_t addr, uint8_t val);


#endif // MFRC522_H
