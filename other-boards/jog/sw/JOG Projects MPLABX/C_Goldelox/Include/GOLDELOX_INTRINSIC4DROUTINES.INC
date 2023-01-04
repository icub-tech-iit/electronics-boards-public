
void WriteChars(unsigned char * charsout)
{
 	unsigned char wk ;
	DWORD written ;
	do
	{
		wk = *charsout++ ;
		WriteFile(ComHandle4D, &wk, 1, &written, NULL) ;
	} while (wk) ;

}

void WriteBytes(unsigned char * Source, int Size)
{
 	unsigned char wk ;
	int i ;
	DWORD written ;
	for (i = 0; i < Size; i++)
	{
		wk = *Source++ ;
	//	wk = (wk >> 8) + (wk << 8) ;
		WriteFile(ComHandle4D, &wk, 1, &written, NULL) ;
	}
}

void WriteWords(WORD * Source, int Size)
{
 	WORD wk ;
	int i ;
	DWORD written ;
	for (i = 0; i < Size; i++)
	{
		wk = *Source++ ;
		wk = (wk >> 8) + (wk << 8) ;
		WriteFile(ComHandle4D, &wk, 2, &written, NULL) ;
	}
}

void getbytes(/*t4DByteArray*/ unsigned char * data, int size)
{
	DWORD read ;
	DWORD sttime ;
//	unsigned char xdata[512] ;
 	int readc, toread ;
	readc  = 0 ;
	toread = size ;
	sttime = GetTickCount();
	while ((readc != size) && (GetTickCount() - sttime < TimeLimit4D))
	{
 		//  application.processmessages ;
		ReadFile(ComHandle4D,&data[readc], toread,&read, NULL) ;
   //     ReadFile(ComHandle4D,&xdata[readc],toread,&read, NULL) ;
		readc  += read ;
		toread -= read ;
	}
	if (   (readc != size)
	    && (Callback4D != NULL) )
	{
		Error4D = Err4D_Timeout ;
		Callback4D(Error4D, Error4D_Inv) ;
		//printf("Timeout waiting for Data") ;
		//exit(2) ;
 	}
//	for (readc = 0; readc < size; readc ++)
//		*data++ = xdata[readc] ;
}

void GetAck(void)
{
	DWORD read ;
	unsigned char readx ;
	DWORD sttime ;
	Error4D = Err4D_OK ;
	sttime  = GetTickCount();
	read    = 0 ;
	while ((read != 1) && (GetTickCount() - sttime < TimeLimit4D))
	{
	  	// application.processmessages ;
	   	ReadFile(ComHandle4D,&readx,1,&read, NULL) ;
	}
	if (read == 0)
  {
		Error4D = Err4D_Timeout ;
	if (Callback4D != NULL)
 		Callback4D(Error4D, Error4D_Inv) ;
  }
	else if (readx != 6)
	{
	   	Error4D     = Err4D_NAK ;
	   	Error4D_Inv = readx ;
		if (Callback4D != NULL)
	 		Callback4D(Error4D, Error4D_Inv) ;
	}

}


WORD GetWord(void)
{
	DWORD read ;
 	unsigned char readx[2] ;
 	int readc, toread ;
 	DWORD sttime ;

 	if (Error4D != Err4D_OK)
 		return 0 ;
 	sttime   = GetTickCount();
	readc    = 0 ;
	toread   = 2 ;
	while ((readc != 2) && (GetTickCount() - sttime < TimeLimit4D))
	{
   //application.processmessages ;
   		ReadFile(ComHandle4D, &readx[readc], toread, &read, NULL) ;
		readc  += read ;
		toread -= read ;
	}

	if (readc != 2)
	{
		Error4D  = Err4D_Timeout ;
		if (Callback4D != NULL)
	 		Callback4D(Error4D, Error4D_Inv) ;
		return 0 ;
	}
	else
		return readx[0] << 8 | readx[1] ;
}

void getString(unsigned char * outStr, int strLen)
{
	DWORD read ;
 	unsigned char readx[2] ;
 	int readc, toread ;
 	DWORD sttime ;

 	if (Error4D != Err4D_OK)
	{
		outStr[0] = 0 ;
 		return ;
	}
 	sttime   = GetTickCount();
	readc    = 0 ;
	toread   = strLen ;
	while ((readc != strLen) && (GetTickCount() - sttime < TimeLimit4D))
	{
   //application.processmessages ;
   		ReadFile(ComHandle4D, &outStr[readc], toread, &read, NULL) ;
		readc  += read ;
		toread -= read ;
	}

	if (readc != strLen)
	{
		Error4D  = Err4D_Timeout ;
		if (Callback4D != NULL)
	 		Callback4D(Error4D, Error4D_Inv) ;
	}
	outStr[readc] = 0 ;
}

WORD GetAckResp(void)
{
	GetAck() ;
	return GetWord() ;
}

WORD GetAckRes2Words(WORD * word1, WORD * word2)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	*word1 = GetWord() ;
	*word2 = GetWord() ;
	return Result ;
}

void GetAck2Words(WORD * word1, WORD * word2)
{
	GetAck() ;
	*word1 = GetWord() ;
	*word2 = GetWord() ;
}

WORD GetAckResSector(t4DSector Sector)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getbytes(Sector, 512) ;
	return Result ;
}

WORD GetAckResStr(unsigned char * OutStr)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getString(OutStr, Result) ;
	return Result ;
}

WORD GetAckResData(t4DByteArray OutData, WORD size)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getbytes(OutData, size) ;
	return Result ;
}

void SetBaudrate(int Newrate)
{
	DCB com1dcb ;
	GetCommState(ComHandle4D,&com1dcb) ;
	com1dcb.ByteSize = 8 ;
	com1dcb.StopBits = ONESTOPBIT ;
	com1dcb.Parity   = NOPARITY ;
	com1dcb.XonChar  = 0 ;
	com1dcb.XoffChar = 0 ;
	com1dcb.fBinary  = 1 ; //TRUE ;
	switch(Newrate)
	{
        case BAUD_110    : com1dcb.BaudRate = 110 ;
		 	break ;
		case BAUD_300    : com1dcb.BaudRate = 300 ;
		 	break ;
        case BAUD_600    : com1dcb.BaudRate = 600 ;
		 	break ;
        case BAUD_1200   : com1dcb.BaudRate = 1200 ;
		 	break ;
        case BAUD_2400   : com1dcb.BaudRate = 2400 ;
		 	break ;
        case BAUD_4800   : com1dcb.BaudRate = 4800 ;
		 	break ;
        case BAUD_9600   : com1dcb.BaudRate = 9600 ;
		 	break ;
        case BAUD_14400  : com1dcb.BaudRate = 14400 ;
		 	break ;
        case BAUD_19200  : com1dcb.BaudRate = 19200 ;
		 	break ;
        case BAUD_31250  : com1dcb.BaudRate = 31250 ;
		 	break ;
        case BAUD_38400  : com1dcb.BaudRate = 38400 ;
		 	break ;
        case BAUD_56000  : com1dcb.BaudRate = 56000 ;
		 	break ;
        case BAUD_57600  : com1dcb.BaudRate = 57600 ;
		 	break ;
        case BAUD_115200 : com1dcb.BaudRate = 115200 ;
		 	break ;
        case BAUD_128000 : com1dcb.BaudRate = 133928 ; // actual rate is not 128000 ;
		 	break ;
        case BAUD_256000 : com1dcb.BaudRate = 281250 ; // actual rate is not  256000 ;
		 	break ;
        case BAUD_300000 : com1dcb.BaudRate = 312500 ; // actual rate is not  300000 ;
		 	break ;
        case BAUD_375000 : com1dcb.BaudRate = 401785 ; // actual rate is not  375000 ;
		 	break ;
        case BAUD_500000 : com1dcb.BaudRate = 562500 ; // actual rate is not  500000 ;
		 	break ;
        case BAUD_600000 : com1dcb.BaudRate = 703125 ; // actual rate is not  600000 ;
		 	break ;
	}
	SetCommState(ComHandle4D,&com1dcb) ;
}


void SetThisBaudrate(int Newrate)
{
	FlushFileBuffers(ComHandle4D) ;  // ensure the change bause rate gets out
  	sleep(10) ;               // seems to be needed to enable Windows to change speed
  	SetBaudrate(Newrate) ;
  	sleep(50) ; // Display sleeps for 100
  	PurgeComm(ComHandle4D,PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR) ; // thow away any potential rubbish
}

