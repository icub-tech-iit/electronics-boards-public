/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 21/06/2013
program name: conf.h
content: prototypes for the functions of conf.c
*************************************************************************************/

typedef unsigned int WORD;

void wait_us(int number);
void wait_ms(int number);
void wait_s(int number);
void Setup_Pins_4_Push_Buttons(void);
void SetupPorts_SPI1(void);
void Setup_Pins_4_CAN_module(void);
void SetupPorts_UART1(void);
void SetupPorts_ADC1(void);
void SetupDMA0(void);
void SetupPorts(void);
void ON_OFF_SCREEN(void);
void init_screen(void);
void init_basic_syntax(void);
void init_char_size(int size);
void init_color(WORD color);
void basic_screen_tool(int char_size,WORD font_color);
void WRITE_STHG(void);
void MENU0(void);
void splash_screen_selection(char** member,int length);
void return_2_root_menu(void);


