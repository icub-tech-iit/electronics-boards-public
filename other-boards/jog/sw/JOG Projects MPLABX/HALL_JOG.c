/*********************************************************************************
author:JENVRIN Julien
company: Italian Institute of Technology
Date: 12/11/2013
program name: HALL_JOG.c
content: All functions use to configure and test HALL SENSORS
*************************************************************************************/


void setup_HALL_JOG(void)
{
	



}

int rotor_position(int poleAB, int poleBC, int poleCA)
{
	int rotor_pos=0;
	//where is the rotor
	if(poleAB == 1 && poleBC == 0 && poleCA == 0)
	{
		rotor_pos=1;
	}
	if(poleAB == 1 && poleBC == 1 && poleCA == 0)
	{
		rotor_pos=2;
	}
	if(poleAB == 0 && poleBC == 1 && poleCA == 0)
	{
		rotor_pos=3;
	}
	if(poleAB == 0 && poleBC == 1 && poleCA == 1)
	{
		rotor_pos=4;
	}
	if(poleAB == 0 && poleBC == 0 && poleCA == 1)
	{
		rotor_pos=5;
	}
	if(poleAB == 1 && poleBC == 0 && poleCA == 1)
	{
		rotor_pos=6;
	}
	return rotor_pos;

}

