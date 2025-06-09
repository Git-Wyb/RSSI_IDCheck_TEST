#ifndef __PIN_DEFINE_H__
#define __PIN_DEFINE_H__
/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include "Timer.h"
#define LCD_def
//#define SeleConnect2
//以下是IO定义
/********************LED寄存器*****************************************/
#ifdef SeleConnect2
extern u8 LED_Cache;
#define LED_ON 1
#define LED_OFF 0

#define Receiver_LED_TX PB_ODR_ODR2       //PC_ODR_ODR1       // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_direc PB_DDR_DDR2 // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_CR1 PB_CR1_C12    // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_CR2 PB_CR2_C22    //输出频率

#define Receiver_LED_RX PB_ODR_ODR3       //PC_ODR_ODR0       // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_direc PB_DDR_DDR3 // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_CR1 PB_CR1_C13    // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_CR2 PB_CR2_C23    //输出频率

#define Receiver_LED_OUT PB_ODR_ODR1       //PC_ODR_ODR4       // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_direc PB_DDR_DDR1 // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_CR1 PB_CR1_C11    // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_CR2 PB_CR2_C21    //输出频率

/******************以下是ADF7030-1寄存器************************************/
/* ADF7030-1 register interface */
//#define ADF7030_REST ADF7030_REST_Cache  //PD_ODR_ODR0
//#define ADF7030_REST_DDR ADF7030_REST_Cache  //PD_DDR_DDR0
//#define ADF7030_REST_CR1 ADF7030_REST_Cache  //PD_CR1_C10
//#define ADF7030_REST_CR2 ADF7030_REST_Cache  //PD_CR2_C20

#define ADF7030_REST PD_ODR_ODR0
#define ADF7030_REST_DDR PD_DDR_DDR0
#define ADF7030_REST_CR1 PD_CR1_C10
#define ADF7030_REST_CR2 PD_CR2_C20

#define ADF7030_GPIO2 PC_IDR_IDR5
#define ADF7030_GPIO2_DDR PC_DDR_DDR5
#define ADF7030_GPIO2_CR1 PC_CR1_C15
#define ADF7030_GPIO2_CR2 PC_CR2_C25

#define ADF7030_GPIO3 PD_IDR_IDR4
#define ADF7030_GPIO3_DDR PD_DDR_DDR4
#define ADF7030_GPIO3_CR1 PD_CR1_C14
#define ADF7030_GPIO3_CR2 PD_CR2_C24
//
#define ADF7030_GPIO4 PC_IDR_IDR4
#define ADF7030_GPIO4_DDR PC_DDR_DDR4
#define ADF7030_GPIO4_CR1 PC_CR1_C14
#define ADF7030_GPIO4_CR2 PC_CR2_C24

#define ADF7030_GPIO5 PC_IDR_IDR6
#define ADF7030_GPIO5_DDR PC_DDR_DDR6
#define ADF7030_GPIO5_CR1 PC_CR1_C16
#define ADF7030_GPIO5_CR2 PC_CR2_C26

#define ADF7030CLK ADF7030_GPIO4
#define ADF7030DATA ADF7030_GPIO5
/********************天线切换 CG2214M6控制引脚寄存器*****************************************/
#define CG2214M6_VC1 PC_ODR_ODR1     //VC1
#define CG2214M6_VC1_DDR PC_DDR_DDR1 //方向
#define CG2214M6_VC1_CR1 PC_CR1_C11  //模式MODE
#define CG2214M6_VC1_CR2 PC_CR2_C21  //输出频率或者中断控制

#define CG2214M6_VC2 PC_ODR_ODR0     //VC2
#define CG2214M6_VC2_DDR PC_DDR_DDR0 //方向
#define CG2214M6_VC2_CR1 PC_CR1_C10  //模式MODE
#define CG2214M6_VC2_CR2 PC_CR2_C20  //输出频率或者中断控制

#define CG2214M6_RF1_USE  \
    {                     \
        CG2214M6_VC1 = 0; \
        CG2214M6_VC2 = 1; \
    }
#define CG2214M6_RF2_USE  \
    {                     \
        CG2214M6_VC1 = 1; \
        CG2214M6_VC2 = 0; \
    }
#define CG2214M6_USE_T CG2214M6_RF1_USE
#define CG2214M6_USE_R CG2214M6_RF2_USE
/******************以下是KEY寄存器*******输入*****************************/
//#define KEY_SW2 PA_IDR_IDR4
//#define KEY_SW2_DDR PA_DDR_DDR4
//#define KEY_SW2_CR1 PA_CR1_C14
//#define KEY_SW2_CR2 PA_CR2_C24
//
//#define KEY_SW3 PA_IDR_IDR5
//#define KEY_SW3_DDR PA_DDR_DDR5
//#define KEY_SW3_CR1 PA_CR1_C15
//#define KEY_SW3_CR2 PA_CR2_C25
//
//#define KEY_SW4 PA_IDR_IDR2
//#define KEY_SW4_DDR PA_DDR_DDR2
//#define KEY_SW4_CR1 PA_CR1_C12
//#define KEY_SW4_CR2 PA_CR2_C22

// #define Receiver_Login PC_IDR_IDR6       // Input   受信机登录键   低电平有效
// #define Receiver_Login_direc PC_DDR_DDR6 // Input   受信机登录键   低电平有效
// #define Receiver_Login_CR1 PC_CR1_C16    // Input   受信机登录键   低电平有效

#define Receiver_Login PA_IDR_IDR2       // Input   受信机登录键   低电平有效
#define Receiver_Login_direc PA_DDR_DDR2 // Input   受信机登录键   低电平有效
#define Receiver_Login_CR1 PA_CR1_C12    // Input   受信机登录键   低电平有效
#define Receiver_Login_CR2 PA_CR2_C22    // Input   受信机登录键   低电平有效

#define KEY_Empty 0
#define KEY_SW2_Down 1
#define KEY_SW3_Down 2
#define KEY_SW4_Down 3

/**受信机使用的IO HA 异常信号 寄存器 */
// #define HA_L_signal PA_IDR_IDR4       // Input   HA 下限信号   低电平有效
// #define HA_L_signal_direc PA_DDR_DDR4 // Input   HA 下限信号   低电平有效
// #define HA_L_signal_CR1 PA_CR1_C14    // Input   HA 下限信号   低电平有效
// #define HA_L_signal_CR2 PA_CR2_C24

// #define HA_ERR_signal PA_IDR_IDR5       // Input   HA 异常信号  低电平有效
// #define HA_ERR_signal_direc PA_DDR_DDR5 // Input   HA 异常信号  低电平有效
// #define HA_ERR_signal_CR1 PA_CR1_C15    // Input   HA 异常信号  低电平有效
// #define HA_ERR_signal_CR2 PA_CR2_C25

// #define HA_Sensor_signal PA_IDR_IDR3       // Input   HA 传感器信号  低电平有效
// #define HA_Sensor_signal_direc PA_DDR_DDR3 // Input   HA 传感器信号  低电平有效
// #define HA_Sensor_signal_CR1 PA_CR1_C13    // Input   HA 传感器信号  低电平有效
// #define HA_Sensor_signal_CR2 PA_CR2_C23

/**WORK/TEST切换引脚寄存器*****/
#define WORK_TEST PB_IDR_IDR0     // Input 受信机测试脚  高电平有效
#define WORK_TEST_DDR PB_DDR_DDR0 // Input 受信机测试脚  高电平有效
#define WORK_TEST_CR1 PB_CR1_C10  // Input 受信机测试脚  高电平有效
#define WORK_TEST_CR2 PB_CR2_C20  // Input 受信机测试脚  高电平有效

#define Receiver_test PB_IDR_IDR0       // Input 受信机测试脚  高电平有效
#define Receiver_test_direc PB_DDR_DDR0 // Input 受信机测试脚  高电平有效
#define Receiver_test_CR1 PB_CR1_C10    // Input 受信机测试脚  高电平有效

#define TP3 PA_IDR_IDR4
#define TP3_DDR PA_DDR_DDR4
#define TP3_CR1 PA_CR1_C14
#define TP3_CR2 PA_CR2_C24

#define TP4 PA_IDR_IDR5
#define TP4_DDR PA_DDR_DDR5
#define TP4_CR1 PA_CR1_C15
#define TP4_CR2 PA_CR2_C25

/******************以下是data寄存器************************************/
#define Receiver_vent Receiver_vent_Cache       // Input   受信机换气联动ON/OFF
#define Receiver_vent_direc Receiver_vent_Cache // Input   受信机换气联动ON/OFF
#define Receiver_vent_CR1 Receiver_vent_Cache   // Input   受信机换气联动ON/OFF

#define PIN_BEEP PA_ODR_ODR0       // Output   蜂鸣器
#define PIN_BEEP_direc PA_DDR_DDR0 // Output   蜂鸣器
#define PIN_BEEP_CR1 PA_CR1_C10    // Output   蜂鸣器

#define Receiver_OUT_OPEN PD_ODR_ODR3       // Output   受信机继电器OPEN  高电平有效
#define Receiver_OUT_OPEN_direc PD_DDR_DDR3 // Output   受信机继电器OPEN  高电平有效
#define Receiver_OUT_OPEN_CR1 PD_CR1_C13    // Output   受信机继电器OPEN  高电平有效

#define Receiver_OUT_CLOSE PD_ODR_ODR2       // Output   受信机继电器close  高电平有效
#define Receiver_OUT_CLOSE_direc PD_DDR_DDR2 // Output   受信机继电器close  高电平有效
#define Receiver_OUT_CLOSE_CR1 PD_CR1_C12    // Output   受信机继电器close  高电平有效

#define Receiver_OUT_STOP PD_ODR_ODR1       // Output   受信机继电器stop  高电平有效
#define Receiver_OUT_STOP_direc PD_DDR_DDR1 // Output   受信机继电器stop  高电平有效
#define Receiver_OUT_STOP_CR1 PD_CR1_C11    // Output   受信机继电器stop  高电平有效

#define Receiver_OUT_VENT ADF7030_REST_Cache//PD_ODR_ODR0       // Output   受信机继电器VENT  高电平有效
#define Receiver_OUT_VENT_direc ADF7030_REST_Cache//PD_DDR_DDR0 // Output 受信机继电器VENT  高电平有效
#define Receiver_OUT_VENT_CR1 ADF7030_REST_Cache//PD_CR1_C10    // Output 受信机继电器VENT  高电平有效

#define Inverters_OUT PA_IDR_IDR2       // 输入   继电器输出信号反向   低电平有效
#define Inverters_OUT_direc PA_DDR_DDR2 // 输入   继电器输出信号反向   低电平有效
#define Inverters_OUT_CR1 PA_CR1_C12    // 输入   继电器输出信号反向   低电平有效

/*********************************************************************************/
#endif



#ifdef LCD_def
extern u8 LED_Cache;
#define LED_ON 1
#define LED_OFF 0

#define Receiver_LED_TX PB_ODR_ODR2       //PC_ODR_ODR1       // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_direc PB_DDR_DDR2 // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_CR1 PB_CR1_C12    // Output   受信机送信指示  高电平有效
#define Receiver_LED_TX_CR2 PB_CR2_C22    //输出频率

#define Receiver_LED_RX PB_ODR_ODR3       //PC_ODR_ODR0       // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_direc PB_DDR_DDR3 // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_CR1 PB_CR1_C13    // Output   受信机受信指示  高电平有效
#define Receiver_LED_RX_CR2 PB_CR2_C23    //输出频率

#define Receiver_LED_OUT PB_ODR_ODR1       //PC_ODR_ODR4       // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_direc PB_DDR_DDR1 // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_CR1 PB_CR1_C11    // Output   受信机继电器动作输出  高电平有效
#define Receiver_LED_OUT_CR2 PB_CR2_C21    //输出频率

/******************以下是ADF7030-1寄存器************************************/
/* ADF7030-1 register interface */
//#define ADF7030_REST ADF7030_REST_Cache  //PD_ODR_ODR0
//#define ADF7030_REST_DDR ADF7030_REST_Cache  //PD_DDR_DDR0
//#define ADF7030_REST_CR1 ADF7030_REST_Cache  //PD_CR1_C10
//#define ADF7030_REST_CR2 ADF7030_REST_Cache  //PD_CR2_C20

#define ADF7030_REST PD_ODR_ODR0
#define ADF7030_REST_DDR PD_DDR_DDR0
#define ADF7030_REST_CR1 PD_CR1_C10
#define ADF7030_REST_CR2 PD_CR2_C20

#define ADF7030_GPIO2 PC_IDR_IDR5
#define ADF7030_GPIO2_DDR PC_DDR_DDR5
#define ADF7030_GPIO2_CR1 PC_CR1_C15
#define ADF7030_GPIO2_CR2 PC_CR2_C25

#define ADF7030_GPIO3 PD_IDR_IDR4
#define ADF7030_GPIO3_DDR PD_DDR_DDR4
#define ADF7030_GPIO3_CR1 PD_CR1_C14
#define ADF7030_GPIO3_CR2 PD_CR2_C24
//
#define ADF7030_GPIO4 PC_IDR_IDR4
#define ADF7030_GPIO4_DDR PC_DDR_DDR4
#define ADF7030_GPIO4_CR1 PC_CR1_C14
#define ADF7030_GPIO4_CR2 PC_CR2_C24

#define ADF7030_GPIO5 PC_IDR_IDR6
#define ADF7030_GPIO5_DDR PC_DDR_DDR6
#define ADF7030_GPIO5_CR1 PC_CR1_C16
#define ADF7030_GPIO5_CR2 PC_CR2_C26

#define ADF7030CLK ADF7030_GPIO4
#define ADF7030DATA ADF7030_GPIO5
/********************天线切换 CG2214M6控制引脚寄存器*****************************************/
#define CG2214M6_VC1 PC_ODR_ODR1     //VC1
#define CG2214M6_VC1_DDR PC_DDR_DDR1 //方向
#define CG2214M6_VC1_CR1 PC_CR1_C11  //模式MODE
#define CG2214M6_VC1_CR2 PC_CR2_C21  //输出频率或者中断控制

#define CG2214M6_VC2 PC_ODR_ODR0     //VC2
#define CG2214M6_VC2_DDR PC_DDR_DDR0 //方向
#define CG2214M6_VC2_CR1 PC_CR1_C10  //模式MODE
#define CG2214M6_VC2_CR2 PC_CR2_C20  //输出频率或者中断控制

#define CG2214M6_RF1_USE  \
    {                     \
        CG2214M6_VC1 = 0; \
        CG2214M6_VC2 = 1; \
    }
#define CG2214M6_RF2_USE  \
    {                     \
        CG2214M6_VC1 = 1; \
        CG2214M6_VC2 = 0; \
    }
#define CG2214M6_USE_T CG2214M6_RF1_USE
#define CG2214M6_USE_R CG2214M6_RF2_USE

#define KEY_SW2_open PC_IDR_IDR2
#define KEY_SW2_open_DDR PC_DDR_DDR2
#define KEY_SW2_open_CR1 PC_CR1_C12
#define KEY_SW2_open_CR2 PC_CR2_C22

#define KEY_SW3_stop PC_IDR_IDR3
#define KEY_SW3_stop_DDR PC_DDR_DDR3
#define KEY_SW3_stop_CR1 PC_CR1_C13
#define KEY_SW3_stop_CR2 PC_CR2_C23

#define KEY_SW4_close PA_IDR_IDR2
#define Receiver_Login 1//PA_IDR_IDR2       // Input   受信机登录键   低电平有效
#define Receiver_Login_direc PA_DDR_DDR2 // Input   受信机登录键   低电平有效
#define Receiver_Login_CR1 PA_CR1_C12    // Input   受信机登录键   低电平有效
#define Receiver_Login_CR2 PA_CR2_C22    // Input   受信机登录键   低电平有效

#define KEY_Empty 0
#define KEY_SW2_Down 1
#define KEY_SW3_Down 2
#define KEY_SW4_Down 3

/**WORK/TEST切换引脚寄存器*****/
#define WORK_TEST PB_IDR_IDR0     // Input 受信机测试脚  高电平有效
#define WORK_TEST_DDR PB_DDR_DDR0 // Input 受信机测试脚  高电平有效
#define WORK_TEST_CR1 PB_CR1_C10  // Input 受信机测试脚  高电平有效
#define WORK_TEST_CR2 PB_CR2_C20  // Input 受信机测试脚  高电平有效

#define Receiver_test PB_IDR_IDR0       // Input 受信机测试脚  高电平有效
#define Freq_Select_429or426MHz  PB_IDR_IDR0
#define Receiver_test_direc PB_DDR_DDR0 // Input 受信机测试脚  高电平有效
#define Receiver_test_CR1 PB_CR1_C10    // Input 受信机测试脚  高电平有效

#define TP3 Undefined_IO//PA_IDR_IDR4
#define TP3_DDR Undefined_IO//PA_DDR_DDR4
#define TP3_CR1 Undefined_IO//PA_CR1_C14
#define TP3_CR2 Undefined_IO//PA_CR2_C24

#define TP4 Undefined_IO//PA_IDR_IDR5
#define TP4_DDR Undefined_IO//PA_DDR_DDR5
#define TP4_CR1 Undefined_IO//PA_CR1_C15
#define TP4_CR2 Undefined_IO//PA_CR2_C25

/******************以下是data寄存器************************************/
#define Receiver_vent Receiver_vent_Cache       // Input   受信机换气联动ON/OFF
#define Receiver_vent_direc Receiver_vent_Cache // Input   受信机换气联动ON/OFF
#define Receiver_vent_CR1 Receiver_vent_Cache   // Input   受信机换气联动ON/OFF

#define PIN_BEEP PA_ODR_ODR0       // Output   蜂鸣器
#define PIN_BEEP_direc PA_DDR_DDR0 // Output   蜂鸣器
#define PIN_BEEP_CR1 PA_CR1_C10    // Output   蜂鸣器

#define Receiver_OUT_OPEN Undefined_IO//PD_ODR_ODR3       // Output   受信机继电器OPEN  高电平有效
#define Receiver_OUT_OPEN_direc Undefined_IO//PD_DDR_DDR3 // Output   受信机继电器OPEN  高电平有效
#define Receiver_OUT_OPEN_CR1 Undefined_IO//PD_CR1_C13    // Output   受信机继电器OPEN  高电平有效

#define Receiver_OUT_CLOSE Undefined_IO//PD_ODR_ODR2       // Output   受信机继电器close  高电平有效
#define Receiver_OUT_CLOSE_direc Undefined_IO//PD_DDR_DDR2 // Output   受信机继电器close  高电平有效
#define Receiver_OUT_CLOSE_CR1 Undefined_IO//PD_CR1_C12    // Output   受信机继电器close  高电平有效

#define Receiver_OUT_STOP Undefined_IO//PD_ODR_ODR1       // Output   受信机继电器stop  高电平有效
#define Receiver_OUT_STOP_direc Undefined_IO//PD_DDR_DDR1 // Output   受信机继电器stop  高电平有效
#define Receiver_OUT_STOP_CR1 Undefined_IO//PD_CR1_C11    // Output   受信机继电器stop  高电平有效

#define Receiver_OUT_VENT ADF7030_REST_Cache//PD_ODR_ODR0       // Output   受信机继电器VENT  高电平有效
#define Receiver_OUT_VENT_direc ADF7030_REST_Cache//PD_DDR_DDR0 // Output 受信机继电器VENT  高电平有效
#define Receiver_OUT_VENT_CR1 ADF7030_REST_Cache//PD_CR1_C10    // Output 受信机继电器VENT  高电平有效

#define Inverters_OUT 1//PA_IDR_IDR2       // 输入   继电器输出信号反向   低电平有效
#define Inverters_OUT_direc PA_DDR_DDR2 // 输入   继电器输出信号反向   低电平有效
#define Inverters_OUT_CR1 PA_CR1_C12    // 输入   继电器输出信号反向   低电平有效

/*********************************************************************************/

#define	PIN_LCD_SCLK	    PD_ODR_ODR1			// 输出；LCD串行时钟(√)
#define	PIN_LCD_RST	        PD_ODR_ODR2			// 输出；LCD复位脚  低电平有效(√)
#define	PIN_LCD_SDATA		PA_ODR_ODR4			// 输出；LCD串行数据(√)
#define	PIN_LCD_A0_RS		PA_ODR_ODR5			// 输出；LCD命令数据选择端  0--命令   1--数据(√)
#define	PIN_LCD_SEL		    PD_ODR_ODR3			// 输出；芯片片选   低电平有效(√)
#define	PIN_LCD_LED		    PA_ODR_ODR3

#define PIN_LCD_LED_direc      PA_DDR_DDR3    // Output
#define PIN_LCD_SDATA_direc    PA_DDR_DDR4    // Output
#define PIN_LCD_SEL_direc      PD_DDR_DDR3  // Output
#define PIN_LCD_RST_direc      PD_DDR_DDR2  // Output
#define PIN_LCD_SCLK_direc     PD_DDR_DDR1  // Output
#define PIN_LCD_A0_RS_direc    PA_DDR_DDR5   // Output

#define PIN_LCD_LED_CR1       PA_CR1_C13    // Output
#define PIN_LCD_SDATA_CR1     PA_CR1_C14    // Output
#define PIN_LCD_SEL_CR1       PD_CR1_C13  // Output
#define PIN_LCD_RST_CR1       PD_CR1_C12  // Output
#define PIN_LCD_SCLK_CR1      PD_CR1_C11  // Output
#define PIN_LCD_A0_RS_CR1     PA_CR1_C15   // Output



#endif




#endif
