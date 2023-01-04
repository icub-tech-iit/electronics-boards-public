
WORD charheight(unsigned char  TestChar)
{
  unsigned char  towrite[3] ;
  towrite[0]= F_charheight >> 8 ;
  towrite[1]= F_charheight ;
  towrite[2]= TestChar;
  sendB(towrite,3) ;
  //da rifare per ricevere risposta:
  return ACK_4DSYSTEMS() ;
}

WORD charwidth(unsigned char  TestChar)
{
  unsigned char  towrite[3] ;
  towrite[0]= F_charwidth >> 8 ;
  towrite[1]= F_charwidth ;
  towrite[2]= TestChar;
  sendB(towrite,3) ;
  //da rifare per ricevere risposta:
  return ACK_4DSYSTEMS() ;
}

void gfx_BGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_BGcolour >> 8 ;
  towrite[1]= F_gfx_BGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_ChangeColour(WORD  OldColor, WORD  NewColor)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_ChangeColour >> 8 ;
  towrite[1]= F_gfx_ChangeColour ;
  towrite[2]= OldColor >> 8 ;
  towrite[3]= OldColor ;
  towrite[4]= NewColor >> 8 ;
  towrite[5]= NewColor ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Circle(WORD  X, WORD  Y, WORD  Radius, WORD  Color)
{
  unsigned char  towrite[10] ;
  towrite[0]= F_gfx_Circle >> 8 ;
  towrite[1]= F_gfx_Circle ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Radius >> 8 ;
  towrite[7]= Radius ;
  towrite[8]= Color >> 8 ;
  towrite[9]= Color ;
  sendB(towrite,3) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_CircleFilled(WORD  X, WORD  Y, WORD  Radius, WORD  Color)
{
  unsigned char  towrite[10] ;
  towrite[0]= F_gfx_CircleFilled >> 8 ;
  towrite[1]= F_gfx_CircleFilled ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Radius >> 8 ;
  towrite[7]= Radius ;
  towrite[8]= Color >> 8 ;
  towrite[9]= Color ;
  sendB(towrite,10) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Clipping(WORD  OnOff)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_Clipping >> 8 ;
  towrite[1]= F_gfx_Clipping ;
  towrite[2]= OnOff >> 8 ;
  towrite[3]= OnOff ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_ClipWindow(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2)
{
  unsigned char  towrite[10] ;
  towrite[0]= F_gfx_ClipWindow >> 8 ;
  towrite[1]= F_gfx_ClipWindow ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  sendB(towrite,10) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Cls()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_gfx_Cls >> 8 ;
  towrite[1]= F_gfx_Cls ;
  sendB(towrite,2) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void gfx_Contrast(WORD  Contrast)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_Contrast >> 8 ;
  towrite[1]= F_gfx_Contrast ;
  towrite[2]= Contrast >> 8 ;
  towrite[3]= Contrast ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_FrameDelay(WORD  Msec)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_FrameDelay >> 8 ;
  towrite[1]= F_gfx_FrameDelay ;
  towrite[2]= Msec >> 8 ;
  towrite[3]= Msec ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD gfx_GetPixel(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_GetPixel >> 8 ;
  towrite[1]= F_gfx_GetPixel ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  sendB(towrite,2) ;
	//da rifare per la ricezione 
  return GetAckResp() ;
}*/

void gfx_Line(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  towrite[0]= F_gfx_Line >> 8 ;
  towrite[1]= F_gfx_Line ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  towrite[10]= Color >> 8 ;
  towrite[11]= Color ;
  sendB(towrite,12) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_LinePattern(WORD  Pattern)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_LinePattern >> 8 ;
  towrite[1]= F_gfx_LinePattern ;
  towrite[2]= Pattern >> 8 ;
  towrite[3]= Pattern ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_LineTo(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_LineTo >> 8 ;
  towrite[1]= F_gfx_LineTo ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_MoveTo(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_MoveTo >> 8 ;
  towrite[1]= F_gfx_MoveTo ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD gfx_Orbit(WORD  Angle, WORD  Distance, WORD *  Xdest, WORD *  Ydest)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_Orbit >> 8 ;
  towrite[1]= F_gfx_Orbit ;
  towrite[2]= Angle >> 8 ;
  towrite[3]= Angle ;
  towrite[4]= Distance >> 8 ;
  towrite[5]= Distance ;
  sendB(towrite,6) ;
  GetAck2Words(Xdest,Ydest) ;
  return 0 ;
}*/

void gfx_OutlineColour(WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_OutlineColour >> 8 ;
  towrite[1]= F_gfx_OutlineColour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

/*void gfx_Polygon(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_Polygon >> 8 ;
  towrite[1]= F_gfx_Polygon ;
  towrite[2]= n >> 8 ;
  towrite[3]= n ;
  sendB(towrite,4) ;
  WriteWords(Xvalues, n) ;
  WriteWords(Yvalues, n) ;
  towrite[0]= Color >> 8 ;
  towrite[1]= Color ;
  sendB(towrite,2) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Polyline(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_Polyline >> 8 ;
  towrite[1]= F_gfx_Polyline ;
  towrite[2]= n >> 8 ;
  towrite[3]= n ;
  sendB(towrite,2) ;
  WriteWords(Xvalues, n) ;
  WriteWords(Yvalues, n) ;
  towrite[0]= Color >> 8 ;
  towrite[1]= Color ;
  sendB(towrite,2) ;
  //return ACK_4DSYSTEMS() ;
}*/

void gfx_PutPixel(WORD  X, WORD  Y, WORD  Color)
{
  unsigned char  towrite[8] ;
  towrite[0]= F_gfx_PutPixel >> 8 ;
  towrite[1]= F_gfx_PutPixel ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Color >> 8 ;
  towrite[7]= Color ;
  sendB(towrite,8) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Rectangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  towrite[0]= F_gfx_Rectangle >> 8 ;
  towrite[1]= F_gfx_Rectangle ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  towrite[10]= Color >> 8 ;
  towrite[11]= Color ;
  sendB(towrite,12) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_RectangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  towrite[0]= F_gfx_RectangleFilled >> 8 ;
  towrite[1]= F_gfx_RectangleFilled ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  towrite[10]= Color >> 8 ;
  towrite[11]= Color ;
  sendB(towrite,12) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_ScreenMode(WORD  ScreenMode)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_ScreenMode >> 8 ;
  towrite[1]= F_gfx_ScreenMode ;
  towrite[2]= ScreenMode >> 8 ;
  towrite[3]= ScreenMode ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Set(WORD  Func, WORD  Value)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_gfx_Set >> 8 ;
  towrite[1]= F_gfx_Set ;
  towrite[2]= Func >> 8 ;
  towrite[3]= Func ;
  towrite[4]= Value >> 8 ;
  towrite[5]= Value ;
  sendB(towrite,6) ;
  while(BusyUART1());
  //return ACK_4DSYSTEMS() ;
}

void gfx_SetClipRegion()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_gfx_SetClipRegion >> 8 ;
  towrite[1]= F_gfx_SetClipRegion ;
  sendB(towrite,2) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Transparency(WORD  OnOff)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Transparency >> 8 ;
  towrite[1]= F_gfx_Transparency ;
  towrite[2]= OnOff >> 8 ;
  towrite[3]= OnOff ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_TransparentColour(WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_gfx_TransparentColour >> 8 ;
  towrite[1]= F_gfx_TransparentColour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void gfx_Triangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color)
{
  unsigned char  towrite[16] ;
  towrite[0]= F_gfx_Triangle >> 8 ;
  towrite[1]= F_gfx_Triangle ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  towrite[10]= X3 >> 8 ;
  towrite[11]= X3 ;
  towrite[12]= Y3 >> 8 ;
  towrite[13]= Y3 ;
  towrite[14]= Color >> 8 ;
  towrite[15]= Color ;
  sendB(towrite,16) ;
  //return ACK_4DSYSTEMS() ;
}

WORD media_Flush()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_media_Flush >> 8 ;
  towrite[1]= F_media_Flush ;
  sendB(towrite,2) ;
  return ACK_4DSYSTEMS() ;
}

void media_Image(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_media_Image >> 8 ;
  towrite[1]= F_media_Image ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

WORD media_Init()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_media_Init >> 8 ;
  towrite[1]= F_media_Init ;
  sendB(towrite,2) ;
  return ACK_4DSYSTEMS() ;
}

/*WORD media_ReadByte()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_media_ReadByte >> 8 ;
  towrite[1]= F_media_ReadByte ;
  sendB(towrite,2) ;
  return GetAckResp() ;
}

WORD media_ReadWord()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_media_ReadWord >> 8 ;
  towrite[1]= F_media_ReadWord ;
  sendB(towrite,2) ;
  return GetAckResp() ;
}*/

void media_SetAdd(WORD  HiWord, WORD  LoWord)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_media_SetAdd >> 8 ;
  towrite[1]= F_media_SetAdd ;
  towrite[2]= HiWord >> 8 ;
  towrite[3]= HiWord ;
  towrite[4]= LoWord >> 8 ;
  towrite[5]= LoWord ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void media_SetSector(WORD  HiWord, WORD  LoWord)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_media_SetSector >> 8 ;
  towrite[1]= F_media_SetSector ;
  towrite[2]= HiWord >> 8 ;
  towrite[3]= HiWord ;
  towrite[4]= LoWord >> 8 ;
  towrite[5]= LoWord ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void media_Video(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_media_Video >> 8 ;
  towrite[1]= F_media_Video ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void media_VideoFrame(WORD  X, WORD  Y, WORD  Framenumber)
{
  unsigned char  towrite[8] ;
  towrite[0]= F_media_VideoFrame >> 8 ;
  towrite[1]= F_media_VideoFrame ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Framenumber >> 8 ;
  towrite[7]= Framenumber ;
  sendB(towrite,8) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD media_WriteByte(WORD  Byte)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_media_WriteByte >> 8 ;
  towrite[1]= F_media_WriteByte ;
  towrite[2]= Byte >> 8 ;
  towrite[3]= Byte ;
  sendB(towrite,4) ;
  return GetAckResp() ;
}

WORD media_WriteWord(WORD  Word)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_media_WriteWord >> 8 ;
  towrite[1]= F_media_WriteWord ;
  towrite[2]= Word >> 8 ;
  towrite[3]= Word ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
  return GetAckResp() ;
}*/

void putCH(WORD  WordChar)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_putCH >> 8 ;
  towrite[1]= F_putCH ;
  towrite[2]= WordChar >> 8 ;
  towrite[3]= WordChar ;
  sendB(towrite,4) ;
  while(BusyUART1());
  //return ACK_4DSYSTEMS() ;
}

void putstr(unsigned char *  InString)
{
  int n = strlen(InString), i;
  unsigned char  towrite[n+3] ;
  towrite[0]= F_putstr >> 8 ;
  towrite[1]= F_putstr ;
  for(i=2;i<n+2;i++)
  {
  	towrite[i]=InString[i-2];
  }
  towrite[n+2]=0x00;
  sendB(towrite,n+3);
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}


void txt_Attributes(WORD  Attribs)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Attributes >> 8 ;
  towrite[1]= F_txt_Attributes ;
  towrite[2]= Attribs >> 8 ;
  towrite[3]= Attribs ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_BGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_BGcolour >> 8 ;
  towrite[1]= F_txt_BGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Bold(WORD  Bold)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Bold >> 8 ;
  towrite[1]= F_txt_Bold ;
  towrite[2]= Bold >> 8 ;
  towrite[3]= Bold ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_FGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_FGcolour >> 8 ;
  towrite[1]= F_txt_FGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_FontID(WORD  FontNumber)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_FontID >> 8 ;
  towrite[1]= F_txt_FontID ;
  towrite[2]= FontNumber >> 8 ;
  towrite[3]= FontNumber ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void txt_Height(WORD  Multiplier)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Height >> 8 ;
  towrite[1]= F_txt_Height ;
  towrite[2]= Multiplier >> 8 ;
  towrite[3]= Multiplier ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Inverse(WORD  Inverse)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Inverse >> 8 ;
  towrite[1]= F_txt_Inverse ;
  towrite[2]= Inverse >> 8 ;
  towrite[3]= Inverse ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Italic(WORD  Italic)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Italic >> 8 ;
  towrite[1]= F_txt_Italic ;
  towrite[2]= Italic >> 8 ;
  towrite[3]= Italic ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_MoveCursor(WORD  Line, WORD  Column)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_txt_MoveCursor >> 8 ;
  towrite[1]= F_txt_MoveCursor ;
  towrite[2]= Line >> 8 ;
  towrite[3]= Line ;
  towrite[4]= Column >> 8 ;
  towrite[5]= Column ;
  sendB(towrite,6) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Opacity(WORD  TransparentOpaque)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Opacity >> 8 ;
  towrite[1]= F_txt_Opacity ;
  towrite[2]= TransparentOpaque >> 8 ;
  towrite[3]= TransparentOpaque ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Set(WORD  Func, WORD  Value)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_txt_Set >> 8 ;
  towrite[1]= F_txt_Set ;
  towrite[2]= Func >> 8 ;
  towrite[3]= Func ;
  towrite[4]= Value >> 8 ;
  towrite[5]= Value ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

void txt_Underline(WORD  Underline)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Underline >> 8 ;
  towrite[1]= F_txt_Underline ;
  towrite[2]= Underline >> 8 ;
  towrite[3]= Underline ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Width(WORD  Multiplier)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Width >> 8 ;
  towrite[1]= F_txt_Width ;
  towrite[2]= Multiplier >> 8 ;
  towrite[3]= Multiplier ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void txt_Xgap(WORD  Pixels)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Xgap >> 8 ;
  towrite[1]= F_txt_Xgap ;
  towrite[2]= Pixels >> 8 ;
  towrite[3]= Pixels ;
  sendB(towrite,4) ;
 // return ACK_4DSYSTEMS() ;
}

void txt_Ygap(WORD  Pixels)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_txt_Ygap >> 8 ;
  towrite[1]= F_txt_Ygap ;
  towrite[2]= Pixels >> 8 ;
  towrite[3]= Pixels ;
  sendB(towrite,4) ;
 // return ACK_4DSYSTEMS() ;
}

void BeeP(WORD  Note, WORD  Duration)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_BeeP >> 8 ;
  towrite[1]= F_BeeP ;
  towrite[2]= Note >> 8 ;
  towrite[3]= Note ;
  towrite[4]= Duration >> 8 ;
  towrite[5]= Duration ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD sys_GetModel(unsigned char *  ModelStr)
{
  unsigned char  towrite[2] ;
  towrite[0]= F_sys_GetModel >> 8 ;
  towrite[1]= F_sys_GetModel ;
  sendB(towrite,2) ;
	//da vedere
  return GetAckResStr(ModelStr) ;
}

WORD sys_GetVersion()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_sys_GetVersion >> 8 ;
  towrite[1]= F_sys_GetVersion ;
  sendB(towrite,2) ;
	//da riveficare
  return GetAckResp() ;
}

WORD sys_GetPmmC()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_sys_GetPmmC >> 8 ;
  towrite[1]= F_sys_GetPmmC ;
  sendB(towrite,2) ;
  return ACK_4DSYSTEMS() ;
  return GetAckResp() ;
}

void blitComtoDisplay(WORD  X, WORD  Y, WORD  Width, WORD  Height, t4DByteArray  Pixels)
{
  unsigned char  towrite[10] ;
  towrite[0]= F_blitComtoDisplay >> 8 ;
  towrite[1]= F_blitComtoDisplay ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Width >> 8 ;
  towrite[7]= Width ;
  towrite[8]= Height >> 8 ;
  towrite[9]= Height ;
  sendB(towrite,10) ;

  WriteBytes(Pixels, Width*Height*2) ;

  //return ACK_4DSYSTEMS() ;
}

void setbaudWait(WORD  Newrate)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_setbaudWait >> 8 ;
  towrite[1]= F_setbaudWait ;
  towrite[2]= Newrate >> 8 ;
  towrite[3]= Newrate ;
  sendB(towrite,4) ;

  SetThisBaudrate(Newrate) ; // change this systems baud rate to match new display rate, ACK is 100ms away

  //return ACK_4DSYSTEMS() ;
}

WORD peekW(WORD  Address)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_peekW >> 8 ;
  towrite[1]= F_peekW ;
  towrite[2]= Address >> 8 ;
  towrite[3]= Address ;
  sendB(towrite,4) ;

  //return GetAckResp() ;
}*/

void pokeW(WORD  Address, WORD  WordValue)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_pokeW >> 8 ;
  towrite[1]= F_pokeW ;
  towrite[2]= Address >> 8 ;
  towrite[3]= Address ;
  towrite[4]= WordValue >> 8 ;
  towrite[5]= WordValue ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD peekB(WORD  Address)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_peekB >> 8 ;
  towrite[1]= F_peekB ;
  towrite[2]= Address >> 8 ;
  towrite[3]= Address ;
  sendB(towrite,2) ;

  return GetAckResp() ;
}*/

void pokeB(WORD  Address, WORD  ByteValue)
{
  unsigned char  towrite[6] ;
  towrite[0]= F_pokeB >> 8 ;
  towrite[1]= F_pokeB ;
  towrite[2]= Address >> 8 ;
  towrite[3]= Address ;
  towrite[4]= ByteValue >> 8 ;
  towrite[5]= ByteValue ;
  sendB(towrite,6) ;
  //return ACK_4DSYSTEMS() ;
}

/*WORD joystick()
{
  unsigned char  towrite[2] ;
  towrite[0]= F_joystick >> 8 ;
  towrite[1]= F_joystick ;
  sendB(towrite,2) ;

  return GetAckResp() ;
}*/

void SSTimeout(void)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_SSTimeout >> 8 ;
  towrite[1]= F_SSTimeout ;
  towrite[2]= 0x00 ;
  towrite[3]= 0x00 ;
  sendB(towrite,4) ;
  while(BusyUART1());
  while(ACK_4DSYSTEMS()!=1);
}

void SSSpeed(WORD  Speed)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_SSSpeed >> 8 ;
  towrite[1]= F_SSSpeed ;
  towrite[2]= Speed >> 8 ;
  towrite[3]= Speed ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}

void SSMode(WORD  Parm)
{
  unsigned char  towrite[4] ;
  towrite[0]= F_SSMode >> 8 ;
  towrite[1]= F_SSMode ;
  towrite[2]= Parm >> 8 ;
  towrite[3]= Parm ;
  sendB(towrite,4) ;
  //return ACK_4DSYSTEMS() ;
}
