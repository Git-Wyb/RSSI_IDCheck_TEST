/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    13-May-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <iostm8l151g4.h> // CPU??
#include "Pin_define.h"   // ????
#include "initial.h"      // ???  ???
#include "ram.h"          // RAM??
#include "ADF7030_1.h"    // ???ADF7021
#include "Timer.h"        // ???
#include "ID_Decode.h"    // ID_Decode??
#include "eeprom.h"       // eeprom
#include "uart.h"         // uart
#include "lcd.h"		// lcd

/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
unsigned char Soft_Version[7]="Ver0.33";

void main(void)
{
    _DI();             // ?????
    OTA_bootloader_enable(); //??IAP???OTA
    RAM_clean();       // ??RAM
    WDT_init();        //???
    VHF_GPIO_INIT();   //IO???
    SysClock_Init();   //???????
    InitialFlashReg(); //flash EEPROM
    eeprom_sys_load(); //ID??
    TIM4_Init();       // ???
    beep_init();       // ???
    ClearWDT();        // Service the WDT

    if(KEY_SW2_open == 0)
        PROFILE_CH_FREQ_32bit_200002EC = 426075000;
    else
        PROFILE_CH_FREQ_32bit_200002EC = PROFILE_429HighSpeed_Register;
    PROFILE_RADIO_AFC_CFG1_32bit_2000031C = 0x0005005A;
    PROFILE_RADIO_DATA_RATE_32bit_200002FC = 0x6400000C;
    PROFILE_GENERIC_PKT_FRAME_CFG1_32bit_20000500 = 0x0000100C;
    ADF7030Init();     //?????

    UART1_INIT();      // UART1 for PC Software
    _EI();             // ????
    ClearWDT();        // Service the WDT
    lcd_init();

	  FLAG_ID_Login_FromUART=0;
    FLAG_APP_RX = 1;
    FLAG_APP_TX_fromUART=0;
    FLAG_APP_TX=0;
    FG_Receiver_LED_RX = 0;
    TIME_EMC = 10;
    Power_ON_sendVer();

	FLAG_Freq_Select_429or426MHz=Freq_Select_429or426MHz;
    flag_mode = 0;
    if(KEY_SW2_open == 0)
    {
        flag_mode = 1;
        if(FLAG_Freq_Select_429or426MHz==0)Channels=1;//FLAG_ID_Login_FromUART=1;
        else Channels=12;//FLAG_ID_Login_FromUART=0;
    }
    else
    {
        RF_test_mode();
        Channels = 15;
        display_set_rssi((set_check_rssi * 100),120);
    }
    while (1)
    {
        if(flag_mode == 1)if(FLAG_Freq_Select_429or426MHz!=Freq_Select_429or426MHz)while(1);

        ClearWDT(); // Service the WDT
        if (time_Login_exit_256 == 0)
            ID_Decode_OUT();
        ID_learn();
        //APP_TX_PACKET();
        if(FLAG_APP_RX==1)
        {
    		  Freq_Scanning();
			  	SCAN_RECEIVE_PACKET(); //??????
        }
        TranmissionACK();
        wireless_Receive_SendUart();

		lcd_desplay();

        if (FG_Receiver_LED_RX == 1)
            Receiver_LED_RX = 1;
        else if (FG_Receiver_LED_RX == 0)
            Receiver_LED_RX = 0;

    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
