#include <stm32f4xx.h>
#include <stm32f4_discovery.h>

#include "nRF24L01.h"

#include <stdio.h>
#include <string.h>

// ������� 
static __IO uint32_t TimingDelay;
 
// ���������
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

nRF24L01_STATUS_REGISTER status_reg;

/* My address */
uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE7
};
/* Receiver address */
uint8_t TxAddress[] = {
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E
};

void main(void){
  
    // 0.001 � = 1/1000 � = 1��
    if (SysTick_Config(SystemCoreClock / 1000)){ 
        /* ���� �������� �� ���� - ������ */
        while (1);
    }
    
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);
    
    nRF24L01_init();

    nRF24L01_set_rf(nRF24L01_DataRate_2M, nRF24L01_OutputPower_M18dBm);
    
    // ������������� ������ ��������� � �����������
    nRF24L01_set_my_addr(MyAddress);
    nRF24L01_set_tx_addr(TxAddress);
    
    u8 str[32] = "Hello blablacode.ru by nRF24\n";
    u8 dataIn[32];
    u16 req = 0;
    
    u16 badTransactions = 0;
    u16 successfulTransactions = 0;  
    
    while (1)  {
        status_reg = nRF24L01_readStatus();
        STM_EVAL_LEDToggle(LED3);
        nRF24L01_writeTx(str);
        do {
            status_reg = nRF24L01_readStatus();
        } while (status_reg.bit.MAX_RT == 0 && status_reg.bit.TX_DS == 0);
        
        nRF24L01_ClearStatus();
        
        nRF24L01_configure_rx();
        do {
            status_reg = nRF24L01_readStatus();
            req++;
            if (req > 1000)
            {
                req = 0;
                break;
            }
        } while (status_reg.bit.RX_DR == 0);
        
        if (status_reg.bit.RX_DR)
        {
            // ������ �����
            memset(dataIn,0,32);
            // ������
            nRF24L01_readRx(dataIn,32);
            
            // ����������
            int ret = memcmp(dataIn,str,32);
            if (ret == 0)
                successfulTransactions++;
            else
                badTransactions++;
        }        

        status_reg = nRF24L01_readStatus();
    }
}

/* ������� �������� */
void Delay(__IO uint32_t nTime){ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
 
/* ��������� �������� �������� ��������, ���� �� �� ����� ���� */
void TimingDelay_Decrement(void){
  if (TimingDelay != 0x00){ 
    TimingDelay--;
  }
}
