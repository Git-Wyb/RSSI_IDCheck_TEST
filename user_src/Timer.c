/***********************************************************************/
/*  FILE        :Timer.c                                               */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <iostm8l151g4.h> // CPU型号
#include "Pin_define.h"   // 管脚定义
#include "initial.h"      // 初始化  预定义
#include "ram.h"          // RAM定义
#include "uart.h"
u16 ErrStateTimeer = 1;
u16 StateReadTimer = 500;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Timer 4 start   1ms
void TIM4_Init(void)
{
    TIM4_PSCR = 0x06; // Timer 4 prescaler  计数器时钟频率  f CK_CNT  =f CK_PSC  / 2的N次方
                      //TIM4_PSCR = 0x08;	// Timer 4 prescaler  计数器时钟频率  f CK_CNT  = f CK_PSC/ 2(PSC[3:0])
    TIM4_ARR = 0xF9;  // Timer 4 period
    TIM4_CR1 |= 0x01; // Timer 4 Enable
    TIM4_IER |= 0x01; // Timer 4 OVR interrupt
}
u8 cl = 0;
u8 step = 0;
void display_reg(u8 ch);
void TIM4_UPD_OVF(void)
{ //725==1秒
    if (TIMER1s)
        --TIMER1s;
	if(TIME_TX_RSSI_Scan)
		--TIME_TX_RSSI_Scan;
    if (TIMER300ms)
        --TIMER300ms;
    if (TIMER18ms)
        --TIMER18ms;
    if (TIME_RSSI_Scan)
        --TIME_RSSI_Scan;
    if (TIMER250ms_STOP)
        --TIMER250ms_STOP;
    if (TIME_10ms)
        --TIME_10ms;
    else
    { // 10mS FLAG
        TIME_10ms = 10;
        FG_10ms = 1;
    }
    if (U1AckTimer)
        U1AckTimer--;
    if (Flag_RSSI_Read_Timer)
        Flag_RSSI_Read_Timer--;
    if (X_ERRTimer)
        X_ERRTimer--;

    if (Time_Receive_gap)
      --Time_Receive_gap;
    if (Time_APP_RXstart)
      --Time_APP_RXstart;
    if(Time_APP_blank_TX)
       --Time_APP_blank_TX;
    if(Time_acc)
       --Time_acc;

    if(PROFILE_CH_FREQ_32bit_200002EC == PROFILE_429HighSpeed_Register)
    {
        if(time_led) time_led--;
        if(flag_reg_state == ENTER_ADD_STATE || flag_reg_state == ENTER_ERASE_STATE)
        {
            step = 1;
            time_led = 500;
            flag_reg_state = 0;
        }
        else if(flag_reg_state == REGISTER_STATE)
        {
            step = 2;
            time_led = 500;
            flag_reg_state = 0;
        }
        else if(flag_reg_state == EXIT_STATE)
        {
            step = 0;
            flag_reg_state = 0;
            display_reg(2);
        }
        switch(step)
        {
            case 0:
                Receiver_LED_OUT = 0;
                break;

            case 1:
                if(time_led == 0)
                {
                    time_led = 500;
                    Receiver_LED_OUT = !Receiver_LED_OUT;
                    //cl = !cl;
                    display_reg(1);
                }
                break;

            case 2:
                time_led = 3000;
                Receiver_LED_OUT = 1;
                step = 3;
                break;

            case 3:
                if(time_led == 0)
                {
                    step = 1;
                }
                break;
        }
    }
    TIM4_SR1_bit.UIF = 0; // 清除中断标记
}
