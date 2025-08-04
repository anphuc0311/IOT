#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[CMU]
// [CMU]$

// $[LFXO]
// [LFXO]$

// $[KEYSCAN]
// [KEYSCAN]$

// $[PRS.ASYNCH0]
// [PRS.ASYNCH0]$

// $[PRS.ASYNCH1]
// [PRS.ASYNCH1]$

// $[PRS.ASYNCH2]
// [PRS.ASYNCH2]$

// $[PRS.ASYNCH3]
// [PRS.ASYNCH3]$

// $[PRS.ASYNCH4]
// [PRS.ASYNCH4]$

// $[PRS.ASYNCH5]
// [PRS.ASYNCH5]$

// $[PRS.ASYNCH6]
// [PRS.ASYNCH6]$

// $[PRS.ASYNCH7]
// [PRS.ASYNCH7]$

// $[PRS.ASYNCH8]
// [PRS.ASYNCH8]$

// $[PRS.ASYNCH9]
// [PRS.ASYNCH9]$

// $[PRS.ASYNCH10]
// [PRS.ASYNCH10]$

// $[PRS.ASYNCH11]
// [PRS.ASYNCH11]$

// $[PRS.ASYNCH12]
// [PRS.ASYNCH12]$

// $[PRS.ASYNCH13]
// [PRS.ASYNCH13]$

// $[PRS.ASYNCH14]
// [PRS.ASYNCH14]$

// $[PRS.ASYNCH15]
// [PRS.ASYNCH15]$

// $[PRS.SYNCH0]
// [PRS.SYNCH0]$

// $[PRS.SYNCH1]
// [PRS.SYNCH1]$

// $[PRS.SYNCH2]
// [PRS.SYNCH2]$

// $[PRS.SYNCH3]
// [PRS.SYNCH3]$

// $[GPIO]
// GPIO SWV on PA03
#ifndef GPIO_SWV_PORT                           
#define GPIO_SWV_PORT                            SL_GPIO_PORT_A
#endif
#ifndef GPIO_SWV_PIN                            
#define GPIO_SWV_PIN                             3
#endif

// [GPIO]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[TIMER2]
// [TIMER2]$

// $[TIMER3]
// [TIMER3]$

// $[TIMER4]
// [TIMER4]$

// $[TIMER5]
// [TIMER5]$

// $[TIMER6]
// [TIMER6]$

// $[TIMER7]
// [TIMER7]$

// $[TIMER8]
// [TIMER8]$

// $[TIMER9]
// [TIMER9]$

// $[EUSART1]
// [EUSART1]$

// $[EUSART2]
// [EUSART2]$

// $[EUSART3]
// [EUSART3]$

// $[USART0]
// USART0 CTS on PA09
#ifndef USART0_CTS_PORT                         
#define USART0_CTS_PORT                          SL_GPIO_PORT_A
#endif
#ifndef USART0_CTS_PIN                          
#define USART0_CTS_PIN                           9
#endif

// USART0 RTS on PA08
#ifndef USART0_RTS_PORT                         
#define USART0_RTS_PORT                          SL_GPIO_PORT_A
#endif
#ifndef USART0_RTS_PIN                          
#define USART0_RTS_PIN                           8
#endif

// USART0 RX on PA06
#ifndef USART0_RX_PORT                          
#define USART0_RX_PORT                           SL_GPIO_PORT_A
#endif
#ifndef USART0_RX_PIN                           
#define USART0_RX_PIN                            6
#endif

// USART0 TX on PA05
#ifndef USART0_TX_PORT                          
#define USART0_TX_PORT                           SL_GPIO_PORT_A
#endif
#ifndef USART0_TX_PIN                           
#define USART0_TX_PIN                            5
#endif

// [USART0]$

// $[USART1]
// USART1 CLK on PC11
#ifndef USART1_CLK_PORT                         
#define USART1_CLK_PORT                          SL_GPIO_PORT_C
#endif
#ifndef USART1_CLK_PIN                          
#define USART1_CLK_PIN                           11
#endif

// USART1 CS on PC10
#ifndef USART1_CS_PORT                          
#define USART1_CS_PORT                           SL_GPIO_PORT_C
#endif
#ifndef USART1_CS_PIN                           
#define USART1_CS_PIN                            10
#endif

// USART1 RX on PC13
#ifndef USART1_RX_PORT                          
#define USART1_RX_PORT                           SL_GPIO_PORT_C
#endif
#ifndef USART1_RX_PIN                           
#define USART1_RX_PIN                            13
#endif

// USART1 TX on PC12
#ifndef USART1_TX_PORT                          
#define USART1_TX_PORT                           SL_GPIO_PORT_C
#endif
#ifndef USART1_TX_PIN                           
#define USART1_TX_PIN                            12
#endif

// [USART1]$

// $[USART2]
// [USART2]$

// $[I2C1]
// [I2C1]$

// $[I2C2]
// [I2C2]$

// $[I2C3]
// [I2C3]$

// $[LCD]
// [LCD]$

// $[LETIMER0]
// [LETIMER0]$

// $[IADC0]
// [IADC0]$

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[VDAC0]
// [VDAC0]$

// $[VDAC1]
// [VDAC1]$

// $[PCNT0]
// [PCNT0]$

// $[HFXO0]
// [HFXO0]$

// $[I2C0]
// [I2C0]$

// $[EUSART0]
// [EUSART0]$

// $[PTI]
// PTI DFRAME on PC07
#ifndef PTI_DFRAME_PORT                         
#define PTI_DFRAME_PORT                          SL_GPIO_PORT_C
#endif
#ifndef PTI_DFRAME_PIN                          
#define PTI_DFRAME_PIN                           7
#endif

// PTI DOUT on PC06
#ifndef PTI_DOUT_PORT                           
#define PTI_DOUT_PORT                            SL_GPIO_PORT_C
#endif
#ifndef PTI_DOUT_PIN                            
#define PTI_DOUT_PIN                             6
#endif

// [PTI]$

// $[MODEM]
// [MODEM]$

// $[CUSTOM_PIN_NAME]
#ifndef _PORT                                   
#define _PORT                                    SL_GPIO_PORT_A
#endif
#ifndef _PIN                                    
#define _PIN                                     0
#endif

#ifndef RFID_RST_PORT                           
#define RFID_RST_PORT                            SL_GPIO_PORT_B
#endif
#ifndef RFID_RST_PIN                            
#define RFID_RST_PIN                             7
#endif

#ifndef MOSI_PORT                               
#define MOSI_PORT                                SL_GPIO_PORT_C
#endif
#ifndef MOSI_PIN                                
#define MOSI_PIN                                 12
#endif

#ifndef MISO_PORT                               
#define MISO_PORT                                SL_GPIO_PORT_C
#endif
#ifndef MISO_PIN                                
#define MISO_PIN                                 13
#endif

// [CUSTOM_PIN_NAME]$

#endif // PIN_CONFIG_H

