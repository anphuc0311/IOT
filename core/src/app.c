//#include "em_device.h"
//#include "em_chip.h"
//#include "em_cmu.h"
//#include "em_gpio.h"
//#include "em_usart.h" // Bao gồm em_usart.h cho giao tiếp SPI trực tiếp
//#include <stdio.h>
//#include <string.h>
//
//#include "pn532.h" // Bao gồm thư viện PN532 của bạn
//// #include "spidrv.h" // Không còn cần SPIDRV nữa
//// #include "sl_spidrv_instances.h" // Không còn cần SPIDRV nữa
//#include "sl_iostream.h"
//#include "sl_sleeptimer.h" // Để sử dụng sl_sleeptimer_delay_millisecond
//#include "sl_zigbee_debug_print.h" // Để sử dụng sl_zigbee_app_debug_println
//
//// Định nghĩa ngoại vi USART và các chân GPIO cho giao tiếp SPI PN532
//// Cần điều chỉnh theo phần cứng EFR32xG26 của bạn
//#define PN532_USART_INSTANCE   USART1 // Chọn USART instance bạn muốn dùng cho SPI
//#define PN532_USART_CLK        cmuClock_USART1 // Clock cho USART instance đã chọn
//
//#define PN532_SPI_PORT         gpioPortC // Ví dụ, thay đổi nếu cần
//#define PN532_SPI_MOSI_PIN     13        // Chân MOSI, thay đổi nếu cần
//#define PN532_SPI_MISO_PIN     12         // Chân MISO, thay đổi nếu cần
//#define PN532_SPI_SCLK_PIN     11         // Chân SCLK, thay đổi nếu cần
//#define PN532_SPI_CS_PIN       10         // Chip Select cho PN532, thay đổi nếu cần
//#define PN532_RST_PORT         gpioPortB // Ví dụ, thay đổi nếu cần
//#define PN532_RST_PIN          7         // Chân Reset cho PN532, thay đổi nếu cần
//
//// Khai báo biến PN532 toàn cục
//PN532 pn532_module;
//
//// --- Các hàm giao tiếp phần cứng (Triển khai cụ thể cho EFR32xG26 với EMLIB USART) ---
//
///**
// * @brief Hàm reset cho module PN532.
// * Thực hiện reset phần cứng cho PN532 bằng cách điều khiển chân RST.
// * @retval PN532_STATUS_OK nếu thành công, PN532_STATUS_ERROR nếu có lỗi.
// */
//int hardware_reset(void) {
//    // Kéo chân RST của PN532 xuống LOW
//    GPIO_PinOutClear(PN532_RST_PORT, PN532_RST_PIN);
//    sl_sleeptimer_delay_millisecond(2); // Delay ngắn (ví dụ 2ms)
//
//    // Kéo chân RST lên HIGH
//    GPIO_PinOutSet(PN532_RST_PORT, PN532_RST_PIN);
//    sl_sleeptimer_delay_millisecond(10); // Delay để PN532 khởi động
//
//    return PN532_STATUS_OK;
//}
//
///**
// * @brief Hàm đọc dữ liệu từ PN532 qua giao tiếp SPI (sử dụng EMLIB USART).
// * Gửi một byte dummy và đọc dữ liệu phản hồi.
// * @param data Con trỏ tới buffer để lưu dữ liệu đọc được.
// * @param count Số byte cần đọc.
// * @retval PN532_STATUS_OK nếu thành công, PN532_STATUS_ERROR nếu có lỗi.
// */
//int hardware_read_data(uint8_t* data, uint16_t count) {
//    // Kéo CS xuống LOW để bắt đầu giao tiếp
//    GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//    sl_sleeptimer_delay_millisecond(1); // Delay nhỏ để đảm bảo CS ổn định
//
//    uint8_t tx_dummy = PN532_SPI_DATAREAD; // Lệnh đọc dữ liệu cho PN532
//
//    for (uint16_t i = 0; i < count; i++) {
//        // Gửi byte dummy và nhận byte dữ liệu
//        USART_Tx(PN532_USART_INSTANCE, tx_dummy);
//        data[i] = USART_Rx(PN532_USART_INSTANCE);
//    }
//
//    // Kéo CS lên HIGH để kết thúc giao tiếp
//    GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//
//    return PN532_STATUS_OK;
//}
//
///**
// * @brief Hàm ghi dữ liệu tới PN532 qua giao tiếp SPI (sử dụng EMLIB USART).
// * Ghi 'count' byte dữ liệu từ 'data'.
// * @param data Con trỏ tới buffer chứa dữ liệu cần ghi.
// * @param count Số byte cần ghi.
// * @retval PN532_STATUS_OK nếu thành công, PN532_STATUS_ERROR nếu có lỗi.
// */
//int hardware_write_data(uint8_t *data, uint16_t count) {
//    // Kéo CS xuống LOW để bắt đầu giao tiếp
//    GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//    sl_sleeptimer_delay_millisecond(1); // Delay nhỏ để đảm bảo CS ổn định
//
//    for (uint16_t i = 0; i < count; i++) {
//        // Gửi byte dữ liệu
//        USART_Tx(PN532_USART_INSTANCE, data[i]);
//        // Đọc byte dummy để xóa bộ đệm nhận (nếu cần, tùy thuộc vào chế độ SPI)
//        USART_Rx(PN532_USART_INSTANCE);
//    }
//
//    // Kéo CS lên HIGH để kết thúc giao tiếp
//    GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//
//    return PN532_STATUS_OK;
//}
//
///**
// * @brief Hàm chờ PN532 sẵn sàng (sử dụng EMLIB USART).
// * Kiểm tra trạng thái sẵn sàng của PN532 bằng cách đọc thanh ghi trạng thái SPI.
// * @param timeout Thời gian chờ tối đa (ms).
// * @retval true nếu sẵn sàng, false nếu hết thời gian chờ.
// */
//bool hardware_wait_ready(uint32_t timeout) {
//    uint32_t start_time = sl_sleeptimer_get_tick_count(); // Lấy thời gian bắt đầu
//    uint32_t current_time;
//    uint8_t status_reg_val;
//    uint8_t dummy_tx = PN532_SPI_STATREAD; // Lệnh đọc thanh ghi trạng thái
//
//    do {
//        // Kéo CS xuống LOW
//        GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//        sl_sleeptimer_delay_millisecond(1); // Delay nhỏ
//
//        // Gửi lệnh đọc trạng thái và nhận phản hồi
//        USART_Tx(PN532_USART_INSTANCE, dummy_tx);
//        status_reg_val = USART_Rx(PN532_USART_INSTANCE);
//
//        // Kéo CS lên HIGH
//        GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);
//
//        if ((status_reg_val & PN532_SPI_READY) == PN532_SPI_READY) {
//            return true; // PN532 đã sẵn sàng
//        }
//
//        current_time = sl_sleeptimer_get_tick_count();
//    } while (sl_sleeptimer_tick_to_ms(current_time - start_time) < timeout);
//
//    return false; // Hết thời gian chờ
//}
//
///**
// * @brief Hàm đánh thức PN532 (sử dụng EMLIB USART).
// * Gửi một byte 0x55 (PN532_WAKEUP) qua giao tiếp để đánh thức PN532.
// * @retval PN532_STATUS_OK nếu thành công, PN532_STATUS_ERROR nếu có lỗi.
// */
//int hardware_wakeup(void) {
//    uint8_t wakeup_byte = PN532_WAKEUP;
//    return hardware_write_data(&wakeup_byte, 1);
//}
//
///**
// * @brief Hàm ghi log đơn giản.
// * Sử dụng sl_iostream_printf để in thông báo ra console.
// * @param log_msg Chuỗi thông báo cần ghi.
// */
//void hardware_log(const char* log_msg) {
//    sl_iostream_printf(sl_iostream_get_default(), "%s\n", log_msg);
//}
//
//// --- Hàm khởi tạo PN532 và cấu hình giao tiếp ---
//void pn532_init(void) {
//    // Khởi tạo GPIO cho các chân SPI và điều khiển PN532
//    CMU_ClockEnable(cmuClock_GPIO, true);
//    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_MOSI_PIN, gpioModePushPull, 0); // MOSI
//    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_MISO_PIN, gpioModeInput, 0);    // MISO
//    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_SCLK_PIN, gpioModePushPull, 0); // SCLK
//    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_CS_PIN, gpioModePushPull, 1);   // CS ban đầu HIGH
//    GPIO_PinModeSet(PN532_RST_PORT, PN532_RST_PIN, gpioModePushPull, 1);     // RST ban đầu HIGH
//    // GPIO_PinModeSet(PN532_SPI_PORT, PN532_IRQ_PIN, gpioModeInputPullUp, 1); // IRQ (nếu sử dụng)
//
//    // Khởi tạo ngoại vi USART cho chế độ SPI Master
//    CMU_ClockEnable(PN532_USART_CLK, true);
//
//    USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
//    init.msbf = true;       // PN532 là MSB first
//    init.baudrate = 1000000; // Tốc độ baud cho SPI (ví dụ 1MHz), điều chỉnh nếu cần
//    init.master = true;     // Chế độ Master
//    init.clockMode = usartClockMode0; // Chế độ SPI (CPOL=0, CPHA=0) - kiểm tra datasheet PN532
//                                      // Có thể là usartClockMode1, usartClockMode2, usartClockMode3
//                                      // tùy thuộc vào yêu cầu của PN532
//
//    USART_InitSync(PN532_USART_INSTANCE, &init);
//
//    // Định tuyến chân cho USART (cần điều chỉnh ROUTELOC và ROUTEPEN theo chip cụ thể)
//    // Ví dụ cho EFR32xG26, cần kiểm tra tài liệu của chip để biết các vị trí chân chính xác
//    #if defined(USART_ROUTELOC0_TXLOC_LOC0) // Kiểm tra xem có định nghĩa ROUTELOC0 không
//    PN532_USART_INSTANCE->ROUTELOC0 = (USART_ROUTELOC0_TXLOC_LOC0 << _USART_ROUTELOC0_TXLOC_SHIFT) |  // MOSI
//                                      (USART_ROUTELOC0_RXLOC_LOC0 << _USART_ROUTELOC0_RXLOC_SHIFT) |  // MISO
//                                      (USART_ROUTELOC0_CLKLOC_LOC0 << _USART_ROUTELOC0_CLKLOC_SHIFT); // SCLK
//    PN532_USART_INSTANCE->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
//    #else
//    // Đối với các chip EFR32 khác có thể sử dụng ROUTEPEN và ROUTELOC
//    // Bạn cần tra cứu trong datasheet của EFR32xG26 để cấu hình đúng
//    // Ví dụ: GPIO_PinToLocation(PN532_SPI_MOSI_PIN)
//    // Hoặc sử dụng Device Configuration Tool trong Simplicity Studio để tạo ra mã này
//    #warning "Vui lòng cấu hình định tuyến chân USART thủ công hoặc thông qua công cụ cấu hình!"
//    #endif
//
//
//    // Gán các hàm giao tiếp phần cứng vào cấu trúc PN532
//    pn532_module.reset = hardware_reset;
//    pn532_module.read_data = hardware_read_data;
//    pn532_module.write_data = hardware_write_data;
//    pn532_module.wait_ready = hardware_wait_ready;
//    pn532_module.wakeup = hardware_wakeup;
//    pn532_module.log = hardware_log;
//
//    // Thực hiện reset phần cứng cho PN532
//    pn532_module.reset();
//
//    // Kiểm tra phiên bản firmware của PN532
//    uint8_t version[4];
//    if (PN532_GetFirmwareVersion(&pn532_module, version) == PN532_STATUS_OK) {
//        sl_iostream_printf(sl_iostream_get_default(), "Tìm thấy PN532. Phiên bản Firmware: %d.%d\n", version[1], version[2]);
//    } else {
//        sl_iostream_printf(sl_iostream_get_default(), "Không tìm thấy PN532 hoặc lỗi giao tiếp.\n");
//        while (1); // Dừng chương trình nếu không tìm thấy PN532
//    }
//
//    // Cấu hình SAM (Secure Access Module)
//    if (PN532_SamConfiguration(&pn532_module) == PN532_STATUS_OK) {
//        sl_iostream_printf(sl_iostream_get_default(), "Cấu hình SAM thành công.\n");
//    } else {
//        sl_iostream_printf(sl_iostream_get_default(), "Cấu hình SAM thất bại.\n");
//    }
//}
//
//// --- Hàm chính của ứng dụng ---
//// Hàm này được gọi một lần khi khởi động (thay thế app_init của bạn)
//void app_init(void)
//{
//    // Không còn cần SPIDRV_Init nữa
//    // SPIDRV_Init(sl_spidrv_usart_rfid_handle, &sl_spidrv_usart_init_rfid);
//
//    // Khởi tạo module PN532 và cấu hình giao tiếp (sẽ khởi tạo USART)
//    pn532_init();
//
//    sl_iostream_printf(sl_iostream_get_default(), "Sẵn sàng đọc thẻ RFID...\n");
//}
//
///** @brief Main Init
// *
// * Hàm này được gọi sau khi các driver hệ thống đã được khởi tạo.
// * Đây là nơi an toàn để bắt đầu sử dụng các ngoại vi.
// * (Giữ nguyên callback này nếu bạn cần nó cho các mục đích Zigbee khác)
// */
//void sl_zigbee_af_main_init_cb(void)
//{
//  // Không cần gọi lại ở đây trừ khi có lý do cụ thể
//}
//
//
//// Hàm này được gọi lặp đi lặp lại trong vòng lặp chính (thay thế app_process_action của bạn)
//void app_process_action(void)
//{
//    uint8_t uid_buffer[10]; // Buffer để lưu UID (tối đa 10 byte cho PN532)
//    int8_t uid_len;         // Độ dài của UID
//
//    // 1. Kiểm tra xem có thẻ mới trong vùng đọc không
//    // PN532_ReadPassiveTarget sẽ cố gắng tìm và đọc UID của thẻ
//    uid_len = PN532_ReadPassiveTarget(&pn532_module, uid_buffer, PN532_MIFARE_ISO14443A, 1000); // 1000ms timeout
//
//    if (uid_len > 0) {
//        // In UID ra console.
//        sl_iostream_printf(sl_iostream_get_default(), "Card Detected! UID: ");
//        for (uint8_t i = 0; i < uid_len; i++) {
//            sl_iostream_printf(sl_iostream_get_default(), "%02X ", uid_buffer[i]);
//        }
//        sl_iostream_printf(sl_iostream_get_default(), "\n");
//
//        // Tạm dừng để tránh đọc đi đọc lại liên tục quá nhanh
//        sl_sleeptimer_delay_millisecond(2000); // Đợi 2 giây
//    }
//    // else if (uid_len == PN532_STATUS_ERROR) {
//    //     // Không tìm thấy thẻ hoặc lỗi - có thể in thông báo debug nếu cần
//    //     // sl_iostream_printf(sl_iostream_get_default(), "Không tìm thấy thẻ hoặc lỗi đọc.\n");
//    // }
//}
//
//// ... các hàm callback khác của Zigbee ...
//void sl_zigbee_af_network_steering_complete_cb(sl_status_t status,
//                                               uint8_t totalBeacons,
//                                               uint8_t joinAttempts,
//                                               uint8_t finalState)
//{
//  sl_zigbee_app_debug_println("%s network %s: 0x%02X", "Join", "complete", status);
//}
//
//void sl_zigbee_af_radio_needs_calibrating_cb(void)
//{
//  sl_mac_calibrate_current_channel();
//}


















#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h" // Include em_usart.h for direct SPI communication
#include <stdio.h>
#include <string.h>

#include "pn532.h" // Include your PN532 library header
#include "sl_iostream.h"
#include "sl_sleeptimer.h" // For sl_sleeptimer_delay_millisecond
#include "sl_zigbee_debug_print.h" // For sl_zigbee_app_debug_println

// Define the USART peripheral and GPIO pins for PN532 SPI communication
// These definitions are based on the provided EFR32xG26 pinout image.
#define PN532_USART_INSTANCE   USART1 // Changed from USART0 to USART1
#define PN532_USART_CLK        cmuClock_USART1 // Clock for the chosen USART instance (cmuClock_USART1 for USART1)

// SPI Pins (from Expansion Header Breakout Pads)
#define PN532_SPI_PORT         gpioPortC // All SPI pins are on Port C
#define PN532_SPI_MOSI_PIN     13        // EXP4 - SPI_COPI - PC13
#define PN532_SPI_MISO_PIN     12        // EXP6 - SPI_CIPO - PC12
#define PN532_SPI_SCLK_PIN     11        // EXP8 - SPI_SCLK - PC11
#define PN532_SPI_CS_PIN       10        // EXP10 - SPI_CS - PC10

// PN532 Control Pins (example assignments, change if needed)
#define PN532_RST_PORT         gpioPortD // EXP11 - PD08
#define PN532_RST_PIN          8         // EXP11 - PD08
#define PN532_IRQ_PORT         gpioPortB // EXP3 - PB07 (if you plan to use IRQ)
#define PN532_IRQ_PIN          7         // EXP3 - PB07

// Global PN532 module instance
PN532 pn532_module;

// --- Hardware communication functions (Implemented for EFR32xG26 with EMLIB USART) ---

/**
 * @brief Hardware reset function for the PN532 module.
 * Performs a hardware reset by controlling the RST pin.
 * @retval PN532_STATUS_OK on success, PN532_STATUS_ERROR on failure.
 */
int hardware_reset(void) {
    // Drive the PN532 RST pin LOW
    GPIO_PinOutClear(PN532_RST_PORT, PN532_RST_PIN);
    sl_sleeptimer_delay_millisecond(2); // Short delay (e.g., 2ms)

    // Drive the PN532 RST pin HIGH
    GPIO_PinOutSet(PN532_RST_PORT, PN532_RST_PIN);
    sl_sleeptimer_delay_millisecond(10); // Delay for PN532 startup

    return PN532_STATUS_OK;
}

/**
 * @brief Reads data from PN532 via SPI (using EMLIB USART).
 * Sends a dummy byte and reads the response data.
 * @param data Pointer to the buffer to store the read data.
 * @param count Number of bytes to read.
 * @retval PN532_STATUS_OK on success, PN532_STATUS_ERROR on failure.
 */
int hardware_read_data(uint8_t* data, uint16_t count) {
    // Drive CS LOW to start communication
    GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
    sl_sleeptimer_delay_millisecond(1); // Small delay to ensure CS is stable

    // Send the PN532_SPI_DATAREAD command ONCE
    USART_Tx(PN532_USART_INSTANCE, PN532_SPI_DATAREAD);
    // Read dummy byte to clear receive buffer for the command byte's response
    USART_Rx(PN532_USART_INSTANCE); // Discard this byte

    // Now, read the actual 'count' bytes of the frame
    for (uint16_t i = 0; i < count; i++) {
        // Send a dummy byte (0x00) to clock out data from PN532
        USART_Tx(PN532_USART_INSTANCE, 0x00); // Send dummy byte for clocking
        data[i] = USART_Rx(PN532_USART_INSTANCE); // Receive actual data byte
    }

    // Drive CS HIGH to end communication
    GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);

    return PN532_STATUS_OK;
}

/**
 * @brief Writes data to PN532 via SPI (using EMLIB USART).
 * Writes 'count' bytes of data from 'data' buffer.
 * @param data Pointer to the buffer containing data to write.
 * @param count Number of bytes to write.
 * @retval PN532_STATUS_OK on success, PN532_STATUS_ERROR on failure.
 */
int hardware_write_data(uint8_t *data, uint16_t count) {
    // Drive CS LOW to start communication
    GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
    sl_sleeptimer_delay_millisecond(1); // Small delay to ensure CS is stable

    // Send the PN532_SPI_DATAWRITE command ONCE
    USART_Tx(PN532_USART_INSTANCE, PN532_SPI_DATAWRITE);
    USART_Rx(PN532_USART_INSTANCE); // Discard response to command byte

    // Now, send the actual 'count' bytes of data
    for (uint16_t i = 0; i < count; i++) {
        USART_Tx(PN532_USART_INSTANCE, data[i]);
        USART_Rx(PN532_USART_INSTANCE); // Receive dummy byte
    }

    // Drive CS HIGH to end communication
    GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);

    return PN532_STATUS_OK;
}

/**
 * @brief Waits for PN532 to be ready (using EMLIB USART).
 * Checks the PN532's ready status by reading the SPI status register.
 * @param timeout Maximum timeout in milliseconds.
 * @retval true if ready, false if timeout.
 */
bool hardware_wait_ready(uint32_t timeout) {
    uint32_t start_time = sl_sleeptimer_get_tick_count(); // Get start time
    uint32_t current_time;
    uint8_t status_reg_val;

    do {
        // Drive CS LOW
        GPIO_PinOutClear(PN532_SPI_PORT, PN532_SPI_CS_PIN);
        sl_sleeptimer_delay_millisecond(1); // Small delay

        // Transmit status read command ONCE per check
        USART_Tx(PN532_USART_INSTANCE, PN532_SPI_STATREAD);
        USART_Rx(PN532_USART_INSTANCE); // Discard response to command byte

        // Receive the actual status byte
        USART_Tx(PN532_USART_INSTANCE, 0x00); // Send dummy byte to clock out status
        status_reg_val = USART_Rx(PN532_USART_INSTANCE);

        // Drive CS HIGH
        GPIO_PinOutSet(PN532_SPI_PORT, PN532_SPI_CS_PIN);

        if ((status_reg_val & PN532_SPI_READY) == PN532_SPI_READY) {
            return true; // PN532 is ready
        }

        current_time = sl_sleeptimer_get_tick_count();
    } while (sl_sleeptimer_tick_to_ms(current_time - start_time) < timeout);

    return false; // Timeout
}

/**
 * @brief Wakes up the PN532 module (using EMLIB USART).
 * Sends a 0x55 byte (PN532_WAKEUP) via SPI to wake up the PN532.
 * @retval PN532_STATUS_OK on success, PN532_STATUS_ERROR on failure.
 */
int hardware_wakeup(void) {
    uint8_t wakeup_byte = PN532_WAKEUP;
    return hardware_write_data(&wakeup_byte, 1);
}

/**
 * @brief Simple logging function.
 * Uses sl_iostream_printf to print messages to the console.
 * @param log_msg String message to log.
 */
void hardware_log(const char* log_msg) {
    sl_iostream_printf(sl_iostream_get_default(), "%s\n", log_msg);
}

// --- PN532 Initialization and Communication Configuration ---
void pn532_init(void) {
    // Initialize GPIO for SPI and PN532 control pins
    CMU_ClockEnable(cmuClock_GPIO, true);

    // SPI Pins
    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_MOSI_PIN, gpioModePushPull, 0); // MOSI
    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_MISO_PIN, gpioModeInput, 0);    // MISO
    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_SCLK_PIN, gpioModePushPull, 0); // SCLK
    GPIO_PinModeSet(PN532_SPI_PORT, PN532_SPI_CS_PIN, gpioModePushPull, 1);   // CS initially HIGH

    // PN532 Control Pins
    GPIO_PinModeSet(PN532_RST_PORT, PN532_RST_PIN, gpioModePushPull, 1);     // RST initially HIGH
    // GPIO_PinModeSet(PN532_IRQ_PORT, PN532_IRQ_PIN, gpioModeInputPullUp, 1); // IRQ (if used)

    // Initialize USART peripheral for SPI Master mode
    CMU_ClockEnable(PN532_USART_CLK, true); // Use cmuClock_USART1 for USART1

    USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
    init.msbf = true;       // PN532 is MSB first
    init.baudrate = 1000000; // SPI baud rate (e.g., 1MHz), adjust if needed
    init.master = true;     // Master mode
    init.clockMode = usartClockMode0; // SPI mode (CPOL=0, CPHA=0) - check PN532 datasheet
                                      // Could be usartClockMode1, usartClockMode2, usartClockMode3
                                      // depending on PN532 requirements
                                      // Common modes for PN532 are Mode 0 (CPOL=0, CPHA=0) and Mode 1 (CPOL=0, CPHA=1)
                                      // Try usartClockMode1 if Mode 0 doesn't work consistently.

    USART_InitSync(PN532_USART_INSTANCE, &init);

    // --- START: Pin Routing Configuration (Paste generated code here) ---
    // IMPORTANT: You MUST generate the correct pin routing code using Simplicity Studio's
    // Device Configuration Tool (Pin Tool) for your specific EFR32xG26 part and USART1.
    // Select USART1, then assign MOSI (PC13), MISO (PC12), SCLK (PC11).
    // The tool will provide the exact ROUTELOC0 and ROUTEPEN values.
    // Replace this comment block with the generated code.
    // Example of what the generated code might look like (VERIFY LOCATIONS!):
    // PN532_USART_INSTANCE->ROUTELOC0 = (USART_ROUTELOC0_TXLOC_LOCX << _USART_ROUTELOC0_TXLOC_SHIFT) |
    //                                   (USART_ROUTELOC0_RXLOC_LOCY << _USART_ROUTELOC0_RXLOC_SHIFT) |
    //                                   (USART_ROUTELOC0_CLKLOC_LOCZ << _USART_ROUTELOC0_CLKLOC_SHIFT);
    // PN532_USART_INSTANCE->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN;
    // --- END: Pin Routing Configuration ---


    // Assign hardware communication functions to the PN532 structure
    pn532_module.reset = hardware_reset;
    pn532_module.read_data = hardware_read_data;
    pn532_module.write_data = hardware_write_data;
    pn532_module.wait_ready = hardware_wait_ready;
    pn532_module.wakeup = hardware_wakeup;
    pn532_module.log = hardware_log;

    // Perform hardware reset for PN532
    pn532_module.reset();

    // Check PN532 firmware version
    uint8_t version[4];
    if (PN532_GetFirmwareVersion(&pn532_module, version) == PN532_STATUS_OK) {
        sl_iostream_printf(sl_iostream_get_default(), "Found PN532. Firmware Version: %d.%d\n", version[1], version[2]);
    } else {
        sl_iostream_printf(sl_iostream_get_default(), "Failed to find PN532 or communication error.\n");
        while (1); // Halt program if PN532 is not found
    }

    // Configure SAM (Secure Access Module)
    if (PN532_SamConfiguration(&pn532_module) == PN532_STATUS_OK) {
        sl_iostream_printf(sl_iostream_get_default(), "SAM configuration successful.\n");
    } else {
        sl_iostream_printf(sl_iostream_get_default(), "SAM configuration failed.\n");
    }
}

// --- Main Application Functions ---
// This function is called once at startup (replaces your app_init)
void app_init(void)
{
    sl_spidrv_init_instances();
    // Initialize PN532 module and communication (will initialize USART)
    pn532_init();
    sl_iostream_printf(sl_iostream_get_default(), "Ready to read RFID cards...\n");
}

/** @brief Main Init
 *
 * This function is called after system drivers (including SPIDRV) have been initialized.
 * This is a safe place to start using peripherals.
 * (Keep this callback if you need it for other Zigbee purposes)
 */
void sl_zigbee_af_main_init_cb(void)
{
  // No need to call again here unless for specific reasons
}


// This function is called repeatedly in the main loop (replaces your app_process_action)
void app_process_action(void)
{
    uint8_t uid_buffer[10]; // Buffer to store UID (max 10 bytes for PN532)
    int8_t uid_len;         // Length of the UID

    // 1. Check if a new card is present
    // PN532_ReadPassiveTarget will attempt to find and read the card's UID
    uid_len = PN532_ReadPassiveTarget(&pn532_module, uid_buffer, PN532_MIFARE_ISO14443A, 1000); // 1000ms timeout

    if (uid_len > 0) {
        // Print UID to console.
        sl_iostream_printf(sl_iostream_get_default(), "Card Detected! UID: ");
        for (uint8_t i = 0; i < uid_len; i++) {
            sl_iostream_printf(sl_iostream_get_default(), "%02X ", uid_buffer[i]);
        }
        sl_iostream_printf(sl_iostream_get_default(), "\n");

        // Pause to avoid continuous rapid reading
        sl_sleeptimer_delay_millisecond(2000); // Wait for 2 seconds
    }
    // else if (uid_len == PN532_STATUS_ERROR) {
    //     // No card found or read error - can print debug message if needed
    //     // sl_iostream_printf(sl_iostream_get_default(), "No card found or read error.\n");
    // }
}

// ... other Zigbee callbacks ...
void sl_zigbee_af_network_steering_complete_cb(sl_status_t status,
                                               uint8_t totalBeacons,
                                               uint8_t joinAttempts,
                                               uint8_t finalState)
{
  sl_zigbee_app_debug_println("%s network %s: 0x%02X", "Join", "complete", status);
}

void sl_zigbee_af_radio_needs_calibrating_cb(void)
{
  sl_mac_calibrate_current_channel();
}
