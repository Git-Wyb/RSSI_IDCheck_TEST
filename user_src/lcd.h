/***********************************************************************/
/*  FILE        :lcd.h                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/


void lcd_GPIO_init(void);
void  lcd_init(void);
void send_command(UINT8 data);
void send_data(UINT8 data);
void delay(UINT16 i);
void display_map_xy(unsigned char x,unsigned char y,unsigned char l,unsigned char h,const unsigned char *p);
void lcd_clear(unsigned char data1) ;
void lcd_desplay(void);
void LCD_display_argos_rssi(unsigned int m, unsigned char y);

extern const unsigned char char_Large_L11_H24[];
extern const unsigned char char_ID[];
extern const unsigned char char_ID_CHECKER[]; 
extern const unsigned char char_company[];

extern const unsigned char char_Small[];
extern const unsigned char char_Medium[];
extern const unsigned char char_Contro[];
extern const unsigned char char_RSSI[];
extern const unsigned char char_rssi[];




extern UINT32 lcd_DATA_Packet_ID;
extern u8 lcd_DATA_Packet_Control;
extern u8 lcd_length_Struct_DATA_Packet_Contro;
extern u8 lcd_Struct_DATA_Packet_Contro[9];
extern UINT8  flag_lcd_id_updata;
extern UINT16 time_LCD_Display;
extern u8 FLAG_KEY_SW4_close;
extern u8 FLAG_KEY_SW3_stop;
extern u8 FLAG_KEY_SW2_open;






