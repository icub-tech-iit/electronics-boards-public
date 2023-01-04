















	oscConfig();
	SetupPorts();
	
#ifdef OSC_TEST
	{
		while(1)
		{
			wait_ms(500);	
			PORTBbits.RB7=!PORTBbits.RB7;
		}
	}
#endif

#ifdef  UART_TEST
	{
		//int i=0;
		//unsigned char buf[10]={0};
		//char ReceivedChar;
		//unsigned char byte = 'C';
//		unsigned char Txdata[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','O','P','Q','R','U','\0'};
		char Txdata[] = {0xFF,0xCC,0x00,0x00,0x00,0x00,0x00,0x23,0x1B,0x10,'\0'};
//		unsigned char AutoBaudRate[] = {0x00,0x0B,0x00,0x19,'\0'};
//		buf[i] = /*(char) ReceivedChar   U1RXREG*/(unsigned char) ReadUART1();
		//int j = strlen(Txdata);
//		U1TXREG=byte
//		send_byte_serial(byte);
//		putsUART1((unsigned int*)Txdata);
//		while(BusyUART1());
		int nbr=0;
		while(1)
		{
			nbr++;
			sendB(Txdata,10);
			while(BusyUART1());
			wait_ms(20);
			if(ACK_4DSYSTEMS()==1)
			{
				break;
			}	
		}
	}	
#endif
		
#ifdef SCREEN
	{
		init_screen();
	}
#endif	

#ifdef UART
	{		
    	CloseUART1();
	}
#endif