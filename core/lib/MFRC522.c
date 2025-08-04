//#include "MFRC522.h"
//#include "spidrv.h"
//#include "em_gpio.h"
//#include "sl_udelay.h"
//#include <string.h>
//#include <stdbool.h>
//
//// TODO: Đảm bảo tên handle này khớp với tên instance trong Simplicity Studio
//extern SPIDRV_Handle_t sl_spidrv_inst_handle;
//
//// TODO: Chỉnh lại các chân GPIO cho phù hợp với kết nối của bạn
//#define MFRC522_CS_PORT      gpioPortC // Ví dụ: Port C
//#define MFRC522_CS_PIN       10      // Ví dụ: Pin 10
//#define MFRC522_RST_PORT     gpioPortB // Ví dụ: Port B
//#define MFRC522_RST_PIN      7       // Ví dụ: Pin 7
//
//// Biến toàn cục
//Uid uid;
//
//// Các thanh ghi MFRC522
//#define CommandReg           0x01
//#define CommIRqReg           0x04
//#define FIFODataReg          0x09
//#define FIFOLevelReg         0x0A
//#define ControlReg           0x0C
//#define BitFramingReg        0x0D
//#define CollReg              0x0E
//
//#define PCD_IDLE             0x00
//#define PCD_TRANSCEIVE       0x0C
//#define PCD_RESETPHASE       0x0F
//
//#define PICC_CMD_REQA        0x26
//#define PICC_CMD_SEL_CL1     0x93
//#define PICC_CMD_HLTA        0x50
//
//// Hàm ghi vào thanh ghi
//static void MFRC522_WriteReg(uint8_t addr, uint8_t val) {
//    uint8_t tx_buf[2] = { (addr & 0x7F), val };
//    GPIO_PinOutClear(MFRC522_CS_PORT, MFRC522_CS_PIN);
//    SPIDRV_MTransmitB(sl_spidrv_inst_handle, tx_buf, 2);
//    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);
//}
//
//// Hàm đọc từ thanh ghi
//static uint8_t MFRC522_ReadReg(uint8_t addr) {
//    uint8_t tx_buf[2] = { (addr | 0x80), 0x00 };
//    uint8_t rx_buf[2];
//    GPIO_PinOutClear(MFRC522_CS_PORT, MFRC522_CS_PIN);
//    SPIDRV_MTransferB(sl_spidrv_inst_handle, tx_buf, rx_buf, 2);
//    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);
//    return rx_buf[1];
//}
//
//static void MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
//    MFRC522_WriteReg(reg, MFRC522_ReadReg(reg) | mask);
//}
//
//static void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask) {
//    MFRC522_WriteReg(reg, MFRC522_ReadReg(reg) & (~mask));
//}
//
//// Hàm giao tiếp với thẻ
//static bool MFRC522_ToCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen) {
//    MFRC522_WriteReg(CommandReg, PCD_IDLE);
//    MFRC522_WriteReg(CommIRqReg, 0x7F);
//    MFRC522_WriteReg(FIFOLevelReg, 0x80); // Xóa bộ đệm FIFO
//
//    for (uint8_t i = 0; i < sendLen; i++) {
//        MFRC522_WriteReg(FIFODataReg, sendData[i]);
//    }
//
//    MFRC522_WriteReg(CommandReg, command);
//    if (command == PCD_TRANSCEIVE) {
//        MFRC522_SetBitMask(BitFramingReg, 0x80); // Bắt đầu gửi
//    }
//
//    // Chờ cho đến khi hoàn tất
//    uint16_t timeout = 2000;
//    while (timeout--) {
//        uint8_t irq = MFRC522_ReadReg(CommIRqReg);
//        if (irq & 0x30) { // RxIRq hoặc IdleIRq
//            break;
//        }
//        if (irq & 0x01) { // Timeout
//            return false;
//        }
//    }
//    MFRC522_ClearBitMask(BitFramingReg, 0x80);
//
//    // Đọc dữ liệu trả về
//    uint8_t fifo_len = MFRC522_ReadReg(FIFOLevelReg);
//    if (backLen != NULL) {
//        *backLen = fifo_len;
//    }
//    if (backData != NULL) {
//        for (uint8_t i = 0; i < fifo_len; i++) {
//            backData[i] = MFRC522_ReadReg(FIFODataReg);
//        }
//    }
//    return true;
//}
//
//void MFRC522_Init(void) {
//    GPIO_PinModeSet(MFRC522_CS_PORT, MFRC522_CS_PIN, gpioModePushPull, 1);
//    GPIO_PinModeSet(MFRC522_RST_PORT, MFRC522_RST_PIN, gpioModePushPull, 1);
//    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);
//
//    // Reset cứng
//    GPIO_PinOutClear(MFRC522_RST_PORT, MFRC522_RST_PIN);
//    sl_udelay_wait(2000);
//    GPIO_PinOutSet(MFRC522_RST_PORT, MFRC522_RST_PIN);
//    sl_udelay_wait(2000);
//
//    // Reset mềm
//    MFRC522_WriteReg(CommandReg, PCD_RESETPHASE);
//    MFRC522_WriteReg(0x2A, 0x8D);
//    MFRC522_WriteReg(0x2B, 0x3E);
//    MFRC522_WriteReg(0x2D, 30);
//    MFRC522_WriteReg(0x2C, 0);
//    MFRC522_WriteReg(0x15, 0x40);
//    MFRC522_WriteReg(0x11, 0x3D);
//    MFRC522_SetBitMask(0x14, 0x03); // Bật Anten
//}
//
//bool MFRC522_PICC_IsNewCardPresent(void) {
//    uint8_t buffer[2];
//    // Khởi tạo độ dài bằng 0 để đảm bảo
//    uint8_t len = 0;
//    uint8_t cmd = PICC_CMD_REQA;
//
//    // Thiết lập để nhận các bit phản hồi ngắn
//    MFRC522_WriteReg(BitFramingReg, 0x07);
//
//    // Gọi hàm giao tiếp cấp thấp
//    bool status = MFRC522_ToCard(PCD_TRANSCEIVE, &cmd, 1, buffer, &len);
//
//    // Một thẻ thực sự sẽ trả lời.
//    // Vì vậy, một thẻ mới được coi là có mặt khi giao dịch thành công (status == true)
//    // VÀ có dữ liệu trả về (len > 0).
//    if (status && len > 0) {
//        return true;
//    }
//
//    return false;
//}
//
//bool MFRC522_PICC_ReadCardSerial(void) {
//    uint8_t cmd_buf[2] = {PICC_CMD_SEL_CL1, 0x20};
//    uint8_t uid_buf[5];
//    uint8_t len;
//
//    MFRC522_WriteReg(BitFramingReg, 0x00);
//
//    if (!MFRC522_ToCard(PCD_TRANSCEIVE, cmd_buf, 2, uid_buf, &len)) {
//        return false;
//    }
//    if (len == 5) { // UID 4 byte + 1 byte BCC
//        memcpy(uid.uidByte, uid_buf, 4);
//        uid.size = 4;
//        return true;
//    }
//    return false;
//}
//
//void MFRC522_PICC_HaltA(void){
//    uint8_t cmd[] = {PICC_CMD_HLTA, 0};
//    MFRC522_ToCard(PCD_TRANSCEIVE, cmd, sizeof(cmd), NULL, NULL);
//}
//
//


#include "MFRC522.h"
#include "spidrv.h"
#include "em_gpio.h"
#include "sl_udelay.h"
#include <string.h>

Uid uid;
// TODO: Đảm bảo tên handle này khớp với tên instance trong Simplicity Studio
extern SPIDRV_Handle_t sl_spidrv_usart_rfid_handle;

// Hàm ghi vào thanh ghi
 void MFRC522_WriteReg(uint8_t addr, uint8_t val) {
    uint8_t tx_buf[2] = { (addr & 0x7F), val };
    GPIO_PinOutClear(MFRC522_CS_PORT, MFRC522_CS_PIN);
    SPIDRV_MTransmitB(sl_spidrv_usart_rfid_handle, tx_buf, 2);
    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);
}

// Hàm đọc từ thanh ghi
 uint8_t MFRC522_ReadReg(uint8_t addr) {
    uint8_t tx_buf[5] = { (addr | 0x80), 0x00 };
    uint8_t rx_buf[5] = {0};
    GPIO_PinOutClear(MFRC522_CS_PORT, MFRC522_CS_PIN);
    SPIDRV_MTransferB(sl_spidrv_usart_rfid_handle, tx_buf, rx_buf, 5);
    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);
    return rx_buf[1];
}

static void MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
    MFRC522_WriteReg(reg, MFRC522_ReadReg(reg) | mask);
}

static void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask) {
    MFRC522_WriteReg(reg, MFRC522_ReadReg(reg) & (~mask));
}

// --- HÀM ĐÃ ĐƯỢC SỬA LỖI ---
// Thêm tham số 'maxBackLen' để truyền kích thước tối đa của bộ đệm nhận
static bool MFRC522_ToCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen, uint8_t maxBackLen) {
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t n, errorReg;

    if (command == PCD_AUTHENT) {
        irqEn = 0x12;
        waitIRq = 0x10;
    } else if (command == PCD_TRANSCEIVE) {
        irqEn = 0x77;
        waitIRq = 0x30;
    }

    MFRC522_WriteReg(CommIEnReg, irqEn | 0x80); // Cho phép ngắt
    MFRC522_ClearBitMask(CommIrqReg, 0x80);     // Clear ngắt
    MFRC522_SetBitMask(FIFOLevelReg, 0x80);     // Xóa FIFO

    MFRC522_WriteReg(CommandReg, PCD_IDLE);     // Đặt về trạng thái rỗi

    // Ghi dữ liệu vào FIFO
    for (uint8_t i = 0; i < sendLen; i++) {
        MFRC522_WriteReg(FIFODataReg, sendData[i]);
    }

    // Bắt đầu gửi
    MFRC522_WriteReg(CommandReg, command);
    if (command == PCD_TRANSCEIVE) {
        MFRC522_SetBitMask(BitFramingReg, 0x80); // Gửi dữ liệu
    }

    // Chờ hoàn tất (timeout ~ 25ms)
    uint16_t i = 2000;
    do {
        n = MFRC522_ReadReg(CommIrqReg);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & waitIRq)); // Timeout hoặc ngắt

    MFRC522_ClearBitMask(BitFramingReg, 0x80); // Tắt bit gửi

    // Kiểm tra lỗi
    errorReg = MFRC522_ReadReg(ErrorReg);
    if (errorReg & 0x1B) {  // BufferOvfl, ParityErr, ProtocolErr
        return false;
    }

    // Đọc dữ liệu trả về
    volatile uint8_t len = MFRC522_ReadReg(FIFOLevelReg);
    if (backLen != NULL) {
        *backLen = len;
    }

    printf("FIFO Level = %d\r\n", len);

    if (backData != NULL && len > 0) {
        for (uint8_t i = 0; i < len; i++) {
            uint8_t b = MFRC522_ReadReg(FIFODataReg);
            printf("Back[%d] = 0x%02X\r\n", i, b);
            backData[i] = b;
        }
    }

    if (backData != NULL && len > 0) {
        if (len > maxBackLen) {
            len = maxBackLen;
        }
        for (uint8_t i = 0; i < len; i++) {
            backData[i] = MFRC522_ReadReg(FIFODataReg);
        }
    }

    return true;
}

void MFRC522_Init(void) {
    GPIO_PinModeSet(MFRC522_CS_PORT, MFRC522_CS_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(MFRC522_RST_PORT, MFRC522_RST_PIN, gpioModePushPull, 1);
    GPIO_PinOutSet(MFRC522_CS_PORT, MFRC522_CS_PIN);

    // Reset cứng
    GPIO_PinOutClear(MFRC522_RST_PORT, MFRC522_RST_PIN);
    sl_udelay_wait(2000);
    GPIO_PinOutSet(MFRC522_RST_PORT, MFRC522_RST_PIN);
    sl_udelay_wait(2000);

    // Reset mềm
    MFRC522_WriteReg(CommandReg, PCD_RESETPHASE);
    MFRC522_WriteReg(0x2A, 0x8D);
    MFRC522_WriteReg(0x2B, 0x3E);
    MFRC522_WriteReg(0x2D, 30);
    MFRC522_WriteReg(0x2C, 0);
    MFRC522_WriteReg(0x15, 0x40);
    MFRC522_WriteReg(0x11, 0x3D);
    MFRC522_SetBitMask(0x14, 0x03); // Bật Anten

}

// Hàm này đã được sửa lỗi logic và cập nhật để gọi hàm ToCard mới
bool MFRC522_PICC_IsNewCardPresent(void) {
    uint8_t buffer[2];
    uint8_t len = 0;
    uint8_t cmd = PICC_CMD_REQA;
    MFRC522_WriteReg(BitFramingReg, 0x07);

    // Truyền vào kích thước của buffer (sizeof(buffer))
    bool status = MFRC522_ToCard(PCD_TRANSCEIVE, &cmd, 1, buffer, &len, sizeof(buffer));

    if (status && len > 0) {
        return true;
    }
    return false;
}

// Cập nhật để gọi hàm ToCard mới
bool MFRC522_PICC_ReadCardSerial(void) {
    uint8_t cmd_buf[2] = {PICC_CMD_SEL_CL1, 0x20};
    uint8_t uid_buf[5];
    uint8_t len;

    MFRC522_WriteReg(BitFramingReg, 0x00);

    // Truyền vào kích thước của uid_buf (sizeof(uid_buf))
    if (!MFRC522_ToCard(PCD_TRANSCEIVE, cmd_buf, 2, uid_buf, &len, sizeof(uid_buf))) {
        return false;
    }
    if (len == 5) { // UID 4 byte + 1 byte BCC
        memcpy(uid.uidByte, uid_buf, 4);
        uid.size = 4;
        return true;
    }
    return false;
}

// Cập nhật để gọi hàm ToCard mới
void MFRC522_PICC_HaltA(void){
    uint8_t cmd[] = {PICC_CMD_HLTA, 0};
    // Không cần nhận dữ liệu trả về
    MFRC522_ToCard(PCD_TRANSCEIVE, cmd, sizeof(cmd), NULL, NULL, 0);
}
