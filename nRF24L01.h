#ifndef __NRF24L01_H
#define __NRF24L01_H


// соединение с discovery
//
// CE --> pa3
// CSn --> pa4
// miso --> pa6
// mosi --> pa7
// sck --> pa5
// irq --> pa2

// макросы управления CS
// устанавливает ножку CS в 1 состояние
#define nRF24L01_CS_SET     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
// сбрасывает ножку CS в 0 состояние
#define nRF24L01_CS_RESET   GPIO_SetBits(GPIOA, GPIO_Pin_4)

// макросы управления сигналом ChipEnable
#define nRF24L01_CE_SET     GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define nRF24L01_CE_RESET   GPIO_ResetBits(GPIOA, GPIO_Pin_3)

// инициализация
void nRF24L01_init();
void nRF24L01_spi_init();

/**
* Посылка команды
* @return ответ на запрос
**/
u8 nRF24L01_cmd_send(u8 cmd);

/**
* Отправка данных по spi
* @return полученные данные
**/
u8 nRF24L01_spi_send(u8 data);

/**
* Читаем регистр
**/
u8 nRF24L01_read_reg(u8 reg, u8 *resp, u8 len);

/**
* Пишем регистр
**/
u8 nRF24L01_write_reg(u8 reg, u8 data);

/**
* Настраиваем на передачу
**/
u8 nRF24L01_configure_tx();

/**
* Настраиваем на прием
**/
u8 nRF24L01_configure_rx();

/**
* Отправляем байт данных
**/
u8 nRF24L01_send_byte(u8 data);

// регистры nRF24L01
enum nRF24L01_REG {
    nRF24L01_CONFIG_REG = 0,
    nRF24L01_EN_AA_REG,
    nRF24L01_EN_RXADDR_REG,
    nRF24L01_SETUP_AW_REG,
    nRF24L01_SETUP_RETR_REG,
    nRF24L01_RF_CH_REG,
    nRF24L01_RF_SETUP_REG,
    nRF24L01_STATUS_REG,
    nRF24L01_OBSERVE_TX_REG,
    nRF24L01_RPD_REG,
    nRF24L01_RX_ADDR_P0_REG,
    nRF24L01_RX_ADDR_P1_REG,
    nRF24L01_RX_ADDR_P2_REG,
    nRF24L01_RX_ADDR_P3_REG,
    nRF24L01_RX_ADDR_P4_REG,
    nRF24L01_RX_ADDR_P5_REG,
    nRF24L01_TX_ADDR_REG,
    nRF24L01_RX_PW_P0_REG,
    nRF24L01_RX_PW_P1_REG,
    nRF24L01_RX_PW_P2_REG,
    nRF24L01_RX_PW_P3_REG,
    nRF24L01_RX_PW_P4_REG,
    nRF24L01_RX_PW_P5_REG,
    nRF24L01_FIFO_STATUS_REG,
    
    
    nRF24L01_ACK_PLD_REG, // n/a addr
    nRF24L01_TX_PLD_REG,  // n/a addr
    nRF24L01_RX_PLD_REG,  // n/a addr
    
    nRF24L01_DYNPD_REG = 0x1c, //1c
    nRF24L01_FEATURE_REG = 0x1d,
    
    nRF24L01_REG_MAX // максимальный номер регистра
};

// команды nRF24L01
enum nRF24L01_COMMAND {
    nRF24L01_R_REGISTER = 0,
    nRF24L01_W_REGISTER = 0x20,
    nRF24L01_R_RX_PAYLOAD = 0x61,
    nRF24L01_W_TX_PAYLOAD = 0xA0,
    nRF24L01_FLUSH_TX = 0xE1,
    nRF24L01_FLUSH_RX = 0xE2,
    nRF24L01_REUSE_TX_PL = 0xE3,
    nRF24L01_R_RX_PL_WID = 0x60,
    nRF24L01_nRF24L01_W_ACK_PAYLOAD = 0xA8,
    nRF24L01_W_TX_PAYLOAD_NOACK = 0xB0,
    nRF24L01_NOP = 0xFF
    
};
#endif // __NRF24L01_H