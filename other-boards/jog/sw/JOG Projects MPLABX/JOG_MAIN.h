/*~|-_-|~**~¦|-_-|~**~|-_-|~**~|-_-|~**~|-_-|~**~|-_-|~**~|-_-|~*
 * File:   JOG_MAIN.h
 * Author: jjenvrin
 *
 * Created on 15 giugno 2017, 12.22
 */

#ifndef JOG_MAIN_H
#define	JOG_MAIN_H


#define MAIN_MENU 0
#define MOTOR_MENU 1
#define SENSOR_MENU 2
#define SPI_MENU 3
#define QEI_MENU 4
#define HALL_MENU 5
#define ADC_MENU 6
#define ROIE_L_MENU 7
#define DC_M_MENU 8
#define BLESS_MENU 9
#define CAN_4_BLESS_MENU 10
#define BLESS_WO_HALL_RPM_MENU 11
#define DCM_TENS_PROX_MENU 12
#define DCM_MOVE_IT_MENU 13
#define QEI_ENC_MAN_MENU 14
#define BLESS_WO_HALL_TENSION_MENU 15
#define FIRMWARE_MENU 55

#define SPI 1
#define QEI 2
#define HALL_T 3
#define ADC 4
#define CAN_4_BLESS 5
#define CAN_4_BLESS_WO_HALL 6
#define DCM_TENS_PROX 7
#define QEI_ENC_MAN 8
#define BLESS_WO_HALL_RPM 9
#define BLESS_WO_HALL_TENSION 10

#define MOTOR_AND_ENCODER_TEST 55
#define OUT -1

//variable for the screen image
#define    iiCub1H           0x0000
#define    iiCub1L           0x0000
#define    Inputs          0

//GLOBALE VARIABLES FOR HALL SENSOR
int HALL[6]={4,2,3,0,5,1};
int sens = 0;
int where_is_rotor;
int where_was_rotor;
int poleAB;
int poleBC;
int poleCA;

//GLOBALE VARIABLE FOR MENU SELECTION
int select = 0;
int change_menu = 0;
int mode = 0;
int menu = -1;
int test = -1;
int fois = 0;
int change = 1; //because when CN interrupt is launched the level is high on pin RA4
char DATA2SCREEN[7]={0};
float ratio = 0.0;
int x;

//OTHER VARIABLES
int ADC_DEFAULT=512;
float VOLT =0.0;
int HALF_RANGE;
float volt_desired = 0.0;


//for CAN line
#define  dataarray 0x1820
/*commands send on CAN Line to move BLESS MOTORS*/
unsigned char get_firmware[8] =  		{0x5B,0x09,0x09,0x00,0x00,0x00,0x00,0x00};
unsigned char V3[8] =  					{0x77,0x00,0x00,0xE0,0x00,0x00,0x08,0x00};
unsigned char V1[8] = 			 		{0x77,0x02,0x00,0xE0,0x00,0x00,0x08,0x00};
unsigned char open_loop[8] =     		{0x09,0x50,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char PID_value[8] = 			{0x65,0x08,0x00,0x02,0x00,0x00,0x00,0x0A};
unsigned char TEST_value[8] = 			{0x09,0xB3,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char idle[8] =          		{0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char force_idle[8] =          	{0x09,0x09,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char set_PWM[8] = 		 		{0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char current_limit[8] = 		{0x48,0x00,0x14,0x00,0x00,0x00,0x00,0x00};
unsigned char mode_speed[8] =    		{0x09,0x0A,0x10,0x00,0x00,0x00,0x00,0x00};
unsigned char _6_round_per_min[8] =		{0x17,0x90,0xF7,0xD0,0x07,0x00,0x00,0x00};
unsigned char _3_round_per_min[8] =  	{0x17,0xC8,0xFB,0xD0,0x07,0x00,0x00,0x00};
unsigned char _1_round_per_min[8] =  	{0x17,0x98,0xFE,0xD0,0x07,0x00,0x00,0x00};
unsigned char round_per_min[8] =  		{0x17,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char O_round_per_min[8] =  	{0x17,0x68,0x01,0xD0,0x07,0x00,0x00,0x00};
unsigned char T_round_per_min[8] =  	{0x17,0x38,0x04,0xD0,0x07,0x00,0x00,0x00};
unsigned char S_round_per_min[8] =  	{0x17,0x70,0x08,0xD0,0x07,0x00,0x00,0x00};

unsigned int encoder_count_cur[3];
unsigned int encoder_count_abs[3];
short encoder_counter;
//MAIN MENU SELECTION
unsigned char* MENU_MAIN[16]={"  ","UPDATE FIRMWARE","TEST MOTORS","TEST SENSORS","            ","             ","             ","use left joystick ","for select & click","               ", " "," "," ", " JOG FW 2.0",  "2FOC FW 6.6.6"," "};
int MENU_MAIN_LGTH = 16;
//MENU LEVEL -1
unsigned char* MENU_SENSORS[14]={" ", "SPI (AEA)","QUADRATURE ENCODER","HALL SENSOR","ANALOG SENSOR","            EXIT","                  ","                  ","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
int MENU_SENSORS_LGTH = 14;
unsigned char* MENU_MOTOR[13]={" ","BRUSHLESS MOTOR","DC MOTOR","            EXIT","","","                  ","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
int MENU_MOTOR_LGTH = 13;
unsigned char* MENU_UPDATE[2]={"LOAD FIRM.","            EXIT"};
int MENU_UPDATE_LGTH = 2;
//MENU LEVEL -2
unsigned char* MENU_SPI[6] = {"AEA ENCODER","            EXIT","","","use left joystick ","for select & click",};
int MENU_SPI_LGTH = 6;
unsigned char* MENU_QEI[3] = {" 1-LCORE/ROIE", " 2- DC MOTOR ENC.","            EXIT"};
int MENU_QEI_LGTH = 3;
unsigned char* MENU_BLESS[13] = {" ", "1- TEST HALL SENS","2- MOVE IT", "3- MOVE IT wo HALL", "            EXIT","","","use left joystick ","for select & click","                  ","                  ","                  ","                  "};
int MENU_BLESS_LGTH = 13;
unsigned char* MENU_DCM[12] = {" ", "MOVE IT","READ ENCODER","TENSE PROXIMAL JNT.","            EXIT","","","use left joystick ","for select & click","                  ","                  ","                  "};
int MENU_DCM_LGTH = 12;
unsigned char* MENU_BLESS_WO_HALL_RPM[13] = {" ", "Please use the", "left joystick", "to select the", "rotation desired", " ", " ", " ", " ", " ", " ", " ", "RIGHT CLICK 2 EXIT"};
int MENU_BLESS_WO_HALL_RPM_LGTH = 13;
unsigned char* MENU_ADC[5]={"NOT YET","NOT YET","NOT YET","NOT YET","NOT YET"};
int MENU_ADC_LGTH = 5;
unsigned char* MENU_BLESS_WO_HALL_TENSION[13] = {" ", "Please use the", "left joystick", "to select the", "rotation desired", " ", " ", " ", " ", " ", " ", " ", "RIGHT CLICK 2 EXIT"};
int MENU_BLESS_WO_HALL_TENSION_LGTH = 13;
unsigned char* MENU[16];		//it will be the replacement MENU NAME for any kind of MENU_...
int MENU_LGTH;
    
    
#endif	/* JOG_MAIN_H */

