/***********************************************************************/
/*  FILE        :Uart.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <iostm8l151g4.h> // CPU型号
#include "Pin_define.h"   // 管脚定义
#include "initial.h"	  // 初始�?  预定�?
#include "ram.h"		  // RAM定义
#include "eeprom.h"		  // eeprom
#include "uart.h"
#include "ADF7030_1.h"
#include "lcd.h"		// lcd


#define TXD1_enable (USART1_CR2 = 0x08) // 允许发�??
#define RXD1_enable (USART1_CR2 = 0x24) // 允许接收及其中断

//#define Using_UART

UINT8 UartStatus = 0;
UINT8 UartLen = 0;
UINT8 Uart_Fremo_NO = 0;
UINT8 Uart_Type = 0;
UINT8 UartCount = 0;
//UINT8 UART_DATA_buffer[9] = {0};
UINT8 UART_DATA_buffer[110] = {0};
__Databits_t Databits_t;
__U1Statues U1Statues;
UINT8 ACKBack[50] = {0x00};
UINT8 ACKBack_LEN=0;
unsigned int U1AckTimer = 0;

//********************************************
void UART1_INIT(u8 mode)
{
    if(mode != 0)
    {
        flag_uart_state = 1;
        unsigned int baud_div = 0;
        SYSCFG_RMPCR1_USART1TR_REMAP = 0;
        USART1_CR1_bit.M = 0;   //1
        USART1_CR1_bit.PCEN = 0;  //1
        USART1_CR1_bit.PS = 0;  //1
        USART1_CR2_bit.TIEN = 0;
        USART1_CR2_bit.TCIEN = 0;
        USART1_CR2_bit.RIEN = 1;
        USART1_CR2_bit.ILIEN = 0;
        USART1_CR2_bit.TEN = 1;
        USART1_CR2_bit.REN = 1;

        //	USART1_CR3 = 0; // 1个停止位
        //	USART1_CR4 = 0;
        //	USART1_CR5 = 0x00;  //0x08;						// 半双工模�?
        /*设置波特�?*/
        baud_div = 16000000 / 9600; /*求出分频因子*/   //9600
        USART1_BRR2 = baud_div & 0x0f;
        USART1_BRR2 |= ((baud_div & 0xf000) >> 8);
        USART1_BRR1 = ((baud_div & 0x0ff0) >> 4); /*先给BRR2赋�?? �?后再设置BRR1*/
    }
        //	USART1_BRR2 = 0x03; // 设置波特�?9600
        //	USART1_BRR1 = 0x68; // 3.6864M/9600 = 0x180
        //16.00M/9600 = 0x683
        //USART1_CR2 = 0x08;	// 允许发�??
        //USART1_CR2 = 0x24;
        //Send_char(0xa5);
    else
    {
        flag_uart_state = 0;
        UART1_end();
        KEY_SW2_open_DDR= Input;
        KEY_SW2_open_CR1= Pull_up;
        KEY_SW2_open_CR2 =InterruptDisable;

        KEY_SW3_stop_DDR= Input;
        KEY_SW3_stop_CR1= Pull_up;
        KEY_SW3_stop_CR2=InterruptDisable;
    }
}
void UART1_end(void)
{ //
	SYSCFG_RMPCR1_USART1TR_REMAP = 0;

	USART1_CR1 = 0; // 1个起始位,8个数据位
	USART1_CR3 = 0; // 1个停止位
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;  // 半双工模�?
	USART1_BRR2 = 0x00; // 设置波特�?9600
	USART1_BRR1 = 0x00; // 3.6864M/9600 = 0x180
						//16.00M/9600 = 0x683
	USART1_CR2 = 0x00;  //禁止串口
}
//--------------------------------------------
void UART1_RX_RXNE(void)
{ // RXD中断服务程序
	unsigned char dat;
	dat = USART1_DR; // 接收数据
					 //Send_char(dat);
	ReceiveFrame(dat);
	// if (dat == '(')
	// 	SIO_cnt = 0;
	// SIO_buff[SIO_cnt] = dat;
	// SIO_cnt = (SIO_cnt + 1) & 0x1F;
	// if (dat == ')')
	// {
	// 	for (dat = 0; dat < SIO_cnt; dat++)
	// 	{
	// 		SIO_DATA[dat] = SIO_buff[dat];
	// 	}
	// 	BIT_SIO = 1; // 标志
	// 				 //SIO_TOT = 20;
	// }
}

//--------------------------------------------
void Send_char(unsigned char ch)
{				 // 发�?�字�?
	TXD1_enable; // 允许发�??
	while (!USART1_SR_TXE)
		;
	USART1_DR = ch; // 发�??
	while (!USART1_SR_TC)
		;		 // 等待完成发�??
	RXD1_enable; // 允许接收及其中断
}
//--------------------------------------------
void Send_String(unsigned char *string)
{ // 发�?�字符串
	unsigned char i = 0;
	TXD1_enable; // 允许发�??
	while (string[i])
	{
		while (!USART1_SR_TXE)
			;				   // �?查发送OK
		USART1_DR = string[i]; // 发�??
		i++;
	}
	while (!USART1_SR_TC)
		;		 // 等待完成发�??
	RXD1_enable; // 允许接收及其中断
				 //	BIT_SIO = 0;							// 标志
}
void Send_Data(unsigned char *P_data, unsigned int length)
{ // 发�?�字符串
	unsigned int i = 0;
	TXD1_enable; // 允许发�??
	for (i = 0; i < length; i++)
	{
		while (!USART1_SR_TXE)
			;					   // �?查发送OK
		USART1_DR = *(P_data + i); // 发�??
	}
	while (!USART1_SR_TC)
		;		 // 等待完成发�??
	RXD1_enable; // 允许接收及其中断
}

/***********************************************************************/
unsigned char asc_hex(unsigned char asc) // HEX
{
	unsigned char i;
	if (asc < 0x3A)
		i = asc & 0x0F;
	else
		i = asc - 0x37;
	return i;
}

unsigned char hex_asc(unsigned char hex)
{
	unsigned char i;
	hex = hex & 0x0F;
	if (hex < 0x0A)
		i = hex | 0x30;
	else
		i = hex + 0x37;
	return i;
}

unsigned char asc_hex_2(unsigned char asc1, unsigned char asc0)
{
	unsigned char i;
	i = (asc_hex(asc1) << 4) + (asc_hex(asc0) & 0x0F);
	return i;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void PC_PRG(void) // 串口命令
{
	unsigned int i, j;
	unsigned char d3, d2, d1, d0;

	if (BIT_SIO)
	{
		BIT_SIO = 0;
		//SIO_TOT = 20;
		switch (SIO_DATA[1])
		{
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 写操�?               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'W':
			//==================================== ADF7012
			if (SIO_DATA[2] == 'I') // (WIxd0d1d2d3)
			{
				i = asc_hex_2(0x30, SIO_buff[3]);
				d0 = asc_hex_2(SIO_buff[4], SIO_buff[5]);
				d1 = asc_hex_2(SIO_buff[6], SIO_buff[7]);
				d2 = asc_hex_2(SIO_buff[8], SIO_buff[9]);
				d3 = asc_hex_2(SIO_buff[10], SIO_buff[11]);

				//write Rx
				ROM_adf7030_value[i].byte[0] = d0;
				ROM_adf7030_value[i].byte[1] = d1;
				ROM_adf7030_value[i].byte[2] = d2;
				ROM_adf7030_value[i].byte[3] = d3;
				//ttset dd_write_7021_reg(&ROM_adf7030_value[i].byte[0]);
				Delayus(122); //delay 40us

				//-------------------------------- 保存
				if (i == 1)
				{
					j = 0x380 + i * 4;
					UnlockFlash(UNLOCK_EEPROM_TYPE);
					WriteByteToFLASH(addr_eeprom_sys + j, d0);
					WriteByteToFLASH(addr_eeprom_sys + j + 1, d1);
					WriteByteToFLASH(addr_eeprom_sys + j + 2, d2);
					WriteByteToFLASH(addr_eeprom_sys + j + 3, d3);
					LockFlash(UNLOCK_EEPROM_TYPE);

					ClearWDT(); // Service the WDT
				}
				//-------------------------------返回  (WHx)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);
				d1 = 'I';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				Send_char(SIO_buff[3]);
			}

			//==================================== ADF7012 TX/RX调试
			if (SIO_DATA[2] == 'J') // (WJx)
			{
				Tx_Rx_mode = asc_hex_2(0x30, SIO_buff[3]);
				//-------------------------------返回  (WHx)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);
				d1 = 'J';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				Send_char(SIO_buff[3]);
			}
			break;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 读操�?               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'R':
			//==================================== ADF7012   //(RIx)
			if (SIO_DATA[2] == 'I') // (RI)d0d1d2d3
			{
				i = asc_hex_2(0x30, SIO_buff[3]);
				d1 = '(';
				d2 = 'R';
				Send_char(d1);
				Send_char(d2);
				d1 = 'I';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				for (j = 0; j < 4; j++)
				{
					d1 = hex_asc(ROM_adf7030_value[i].byte[j] / 16);
					d2 = hex_asc(ROM_adf7030_value[i].byte[j] % 16);
					Send_char(d1);
					Send_char(d2);
				}
			}
			break;
		default:
			break;
		}
	}
}
void ReceiveFrame(UINT8 Cache)
{
	switch (UartStatus)
	{
	case FrameHeadSataus:
	{
		UART_DATA_buffer[0] = UART_DATA_buffer[1];
		UART_DATA_buffer[1] = UART_DATA_buffer[2];
                UART_DATA_buffer[2] = UART_DATA_buffer[3];
		UART_DATA_buffer[3] = Cache;
		/*if ((UART_DATA_buffer[0] == FrameHead) &&
			(UART_DATA_buffer[1] != FrameHead)
                          &&(UART_DATA_buffer[2] != FrameHead)
                            &&(UART_DATA_buffer[3] != FrameHead)) */
    if (UART_DATA_buffer[0] == FrameHead)
		{
			U1Statues = ReceivingStatues;
			UartStatus++;
                        UartCount=0;
                        Uart_Fremo_NO = UART_DATA_buffer[1];
                        Uart_Type = UART_DATA_buffer[2];
			UartLen = UART_DATA_buffer[3];
                        if(UartLen==0)UartStatus++;
		}
	}
	break;
	case DataStatus:
	{
		UART_DATA_buffer[UartCount + 4] = Cache;
		UartCount++;
		if (UartCount >= UartLen)
			UartStatus++;
	}
	break;
	default:
		UartStatus = 0;
		U1Statues = IdelStatues;
		break;
	}
	if (UartStatus == FrameEndStatus) //接收完一帧处理数�?
	{
		UartStatus = 0;
		UartCount = 0;
		//        Receiver_LED_OUT_INV = !Receiver_LED_OUT_INV;
		U1Statues = ReceiveDoneStatues;
		U1AckTimer = U1AckDelayTime;
	}
}

void OprationFrame(void)
{
  u16 check_sum=0,n;
  u8 i=0;
  uni_rom_id xn;

  switch (Uart_Type)
	  {
	  case 0x01:
	  case 0x02:
		   for(i=0;i<UART_DATA_buffer[3]-2;i++)  check_sum+=UART_DATA_buffer[i+4];
           n=UART_DATA_buffer[i+4]+UART_DATA_buffer[i+5]*256;
           if(check_sum==n)
           {
                xn.IDB[0]=0;
                xn.IDB[1]=UART_DATA_buffer[6];
                xn.IDB[2]=UART_DATA_buffer[5];
                xn.IDB[3]=UART_DATA_buffer[4];
                TX_ID_data=xn.IDL;
                if(Uart_Type== 0x01)
                {
                  TX_Control_code_TYPE01=UART_DATA_buffer[7];
                }
                else if(Uart_Type== 0x02)
                {
                  Uart_Struct_DATA_Packet_Contro.Fno_Type.byte=UART_DATA_buffer[7];
                  for(i=0;i<UART_DATA_buffer[3]-6;i++)Uart_Struct_DATA_Packet_Contro.data[i/2].uc[i%2]=UART_DATA_buffer[i+8];
				  for(i=UART_DATA_buffer[3]-6;i<8;i++)Uart_Struct_DATA_Packet_Contro.data[i/2].uc[i%2]=0x00;
                }
                FLAG_APP_TX_fromUART=1;

		        ACKBack[0] = FrameHead;
                ACKBack[1] = Uart_Fremo_NO;
                ACKBack[2] = 0x80;
                ACKBack[3] = 5;
                ACKBack[4] = UART_DATA_buffer[4];
                ACKBack[5] = UART_DATA_buffer[5];
                ACKBack[6] = UART_DATA_buffer[6];
                ACKBack[7] = 0x00;
                ACKBack[8] = 0x00;
                ACKBack_LEN=9;
           }
		   else
		   	U1Statues = IdelStatues;   //不返回ACK
		  break;
	  case 0x10:
	  	  if(UART_DATA_buffer[4]<=32)
		  	ID_DATA_PCS=UART_DATA_buffer[4];
		  else ID_DATA_PCS=0;
		  for (i = 0; i < UART_DATA_buffer[4]; i++)
			  {
			    xn.IDB[0]=0;
                xn.IDB[1]=UART_DATA_buffer[i*3+7];
                xn.IDB[2]=UART_DATA_buffer[i*3+6];
                xn.IDB[3]=UART_DATA_buffer[i*3+5];
				ID_Receiver_DATA[i]=xn.IDL;
			  }
		  //U1Statues = IdelStatues;   //不返回ACK
		  ACKBack[0] = FrameHead;
		  ACKBack[1] = Uart_Fremo_NO;
		  ACKBack[2] = 0x90;
		  ACKBack[3] = 2;
		  ACKBack[4] = 0x00;
		  ACKBack[5] = 0x00;
		  ACKBack_LEN=6;
		  break;
	  case 0x11:
	  	  if(UART_DATA_buffer[3]==1)
	  	  	{
	  	      if(UART_DATA_buffer[4]==0)
                 FLAG_ID_Login_FromUART=0;
			  else if(UART_DATA_buffer[4]==1)
			  	FLAG_ID_Login_FromUART=1;
	  	  	}
		  U1Statues = IdelStatues;   //不返回ACK
		  break;
	  case 0x60:
		  		ACKBack[0] = FrameHead;
                ACKBack[1] = Uart_Fremo_NO;
                ACKBack[2] = 0xE0;
                ACKBack[3] = 0x00;
                ACKBack_LEN=4;
		  break;
	  case 0x61:
		  Power_ON_sendVer();
		  break;
	  }
   UART_DATA_buffer[0] = 0x00;
	 UART_DATA_buffer[1] = 0x00;
   UART_DATA_buffer[2] = 0x00;
	 UART_DATA_buffer[3] = 0x00;
}

void Power_ON_sendVer(void)
{
   u8 i;
     		ACKBack[0] = FrameHead;
                ACKBack[1] = Uart_Fremo_NO;
                ACKBack[2] = 0xE1;
                ACKBack[3] = 7;
                for(i=0;i<7;i++)
                   ACKBack[i+4]=Soft_Version[i];
                ACKBack_LEN=11;
                U1Statues=ACKingStatues;
}

void TranmissionACK(void)
{
        if(U1Statues == ReceiveDoneStatues)
        {
           U1Statues=ACKingStatues;
           OprationFrame();
        }

	if ((U1Statues == ACKingStatues) && (U1AckTimer == 0)&&(FLAG_APP_TX_fromUART==0)&&(FLAG_APP_TX==0))
	{
                U1Statues = ACKDoneStatues;
		Send_Data(ACKBack, ACKBack_LEN);
		U1Statues = IdelStatues;
	}
}

void wireless_Receive_SendUart(void)
{
    u8 i,data[18],length;
    uni_rom_id xn;
    u16 check_sum=0;
    static u32 Last_DATA_Packet_ID=0;
    static u8 Last_DATA_Packet_Control=0;


    if((U1Statues!= ACKingStatues)&&(flag_ID_Receiver_sendUART==1))
    {
      flag_ID_Receiver_sendUART=0;

	  if(Radio_Date_Type==1)
	  {
	      if((DATA_Packet_ID!=Last_DATA_Packet_ID)||(DATA_Packet_Control!=Last_DATA_Packet_Control)||
	          ((DATA_Packet_ID==Last_DATA_Packet_ID)&&(DATA_Packet_Control==Last_DATA_Packet_Control)&&(Time_Receive_gap==0))
	          )
	      {
            lcd_DATA_Packet_ID=DATA_Packet_ID;
			lcd_DATA_Packet_Control=DATA_Packet_Control;
            flag_lcd_id_updata=1;

		    data[0] = FrameHead;
	        data[1] = 0;//Uart_Fremo_NO;  //受信时Fremo�?0
	        data[2] = 0x81;
	        data[3] = 6;
	        xn.IDL=DATA_Packet_ID;
	        data[4]=xn.IDB[3];
	        check_sum+=data[4];
	        data[5]=xn.IDB[2];
	        check_sum+=data[5];
	        data[6]=xn.IDB[1];
	        check_sum+=data[6];
	        data[7]=DATA_Packet_Control;
	        check_sum+=data[7];
	        data[8]=check_sum%256;
	        data[9]=check_sum/256;
	        Send_Data(data, 10);

	        Last_DATA_Packet_ID=DATA_Packet_ID;
	        Last_DATA_Packet_Control=DATA_Packet_Control;
	        Time_Receive_gap=720;
	      }
	  }
	  else if(Radio_Date_Type==2)
	  {
	      if((DATA_Packet_ID!=Last_DATA_Packet_ID)||(Struct_DATA_Packet_Contro.Fno_Type.byte!=Last_Struct_DATA_Packet_Contro.Fno_Type.byte)||
		  	 (Struct_DATA_Packet_Contro.data[0].ui!=Last_Struct_DATA_Packet_Contro.data[0].ui)||
		  	 (Struct_DATA_Packet_Contro.data[1].ui!=Last_Struct_DATA_Packet_Contro.data[1].ui)||
		  	 (Struct_DATA_Packet_Contro.data[2].ui!=Last_Struct_DATA_Packet_Contro.data[2].ui)||
		  	 (Struct_DATA_Packet_Contro.data[3].ui!=Last_Struct_DATA_Packet_Contro.data[3].ui)||
	          ((DATA_Packet_ID==Last_DATA_Packet_ID)&&(Struct_DATA_Packet_Contro.Fno_Type.byte==Last_Struct_DATA_Packet_Contro.Fno_Type.byte)&&
	          (Struct_DATA_Packet_Contro.data[0].ui==Last_Struct_DATA_Packet_Contro.data[0].ui)&&
              (Struct_DATA_Packet_Contro.data[1].ui==Last_Struct_DATA_Packet_Contro.data[1].ui)&&
              (Struct_DATA_Packet_Contro.data[2].ui==Last_Struct_DATA_Packet_Contro.data[2].ui)&&
              (Struct_DATA_Packet_Contro.data[3].ui==Last_Struct_DATA_Packet_Contro.data[3].ui)&&
		       (Time_Receive_gap==0))
		       )
	      {

            lcd_DATA_Packet_ID=DATA_Packet_ID;
            flag_lcd_id_updata=1;

		    data[0] = FrameHead;
	        data[1] = 0;//Uart_Fremo_NO;  //受信时Fremo�?0
	        data[2] = 0x81;

			if(Struct_DATA_Packet_Contro.Fno_Type.UN.type==1)
				length=3;
			else length=8;
			lcd_length_Struct_DATA_Packet_Contro=length;
	        data[3] = length+6;

	        xn.IDL=DATA_Packet_ID;
	        data[4]=xn.IDB[3];
	        check_sum+=data[4];
	        data[5]=xn.IDB[2];
	        check_sum+=data[5];
	        data[6]=xn.IDB[1];
	        check_sum+=data[6];

			data[7]=Struct_DATA_Packet_Contro.Fno_Type.byte;
	            check_sum+=data[7];
			lcd_Struct_DATA_Packet_Contro[0]=data[7];

			for (i = 0; i < length; i++)
			{
				data[8+i]=Struct_DATA_Packet_Contro.data[i/2].uc[i%2];
				check_sum+=data[8+i];
				lcd_Struct_DATA_Packet_Contro[1+i]=data[8+i];
			}
	        data[8+i]=check_sum%256;
	        data[9+i]=check_sum/256;

			//if(Struct_DATA_Packet_Contro.Fno_Type.UN.type==1)
	          Send_Data(data, length+10);

	        Last_DATA_Packet_ID=DATA_Packet_ID;
	        Last_Struct_DATA_Packet_Contro=Struct_DATA_Packet_Contro;
	        Time_Receive_gap=300;
	      }
	  }

    }
}
