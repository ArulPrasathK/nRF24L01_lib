#include <stm32f4xx.h>
#include "nRF24L01.h"

void nRF24L01_init()
{
    nRF24L01_spi_init();
}

void nRF24L01_spi_init()
{
    // gpio init
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;    // ��������� ������������ ����� D 
    
    // ������������ spi2
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    
    GPIOA->MODER &= ~GPIO_MODER_MODER0;  // ������ ��� ��� ������ - ����
    GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;    /// �� ����� - �����
    
    
    // spi
    // master 8bit
    // crc
    // �������� 256
    // ���������� CS
    SPI2->CR1 = SPI_CR1_CRCEN | SPI_CR1_SPE | SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SSM;
    
    // CRC: x^8 + x^2 + x + 1
    SPI2->CRCPR = 0x07;
}

u8 spi_send(u8 data)
{
    SPI2->DR = data;
    // ���� �������� ������
    while(SPI2->SR & SPI_SR_TXE);
    
    // ��� ���� ������ ������
    while(SPI2->SR ^ SPI_SR_RXNE);
    
    return SPI2->DR;
}