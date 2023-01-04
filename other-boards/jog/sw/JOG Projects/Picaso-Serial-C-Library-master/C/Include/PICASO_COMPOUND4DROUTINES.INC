WORD charheight(unsigned char  TestChar)
{
  unsigned char  towrite[3] ;
  DWORD  written ;
  towrite[0]= F_charheight >> 8 ;
  towrite[1]= F_charheight ;
  towrite[2]= TestChar;
  WriteFile(ComHandle4D, &towrite[0], 3, &written, NULL) ;
  return GetAckResp() ;
}

WORD charwidth(unsigned char  TestChar)
{
  unsigned char  towrite[3] ;
  DWORD  written ;
  towrite[0]= F_charwidth >> 8 ;
  towrite[1]= F_charwidth ;
  towrite[2]= TestChar;
  WriteFile(ComHandle4D, &towrite[0], 3, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Close(WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_Close >> 8 ;
  towrite[1]= F_file_Close ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Count(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Count >> 8 ;
  towrite[1]= F_file_Count ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_Dir(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Dir >> 8 ;
  towrite[1]= F_file_Dir ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_Erase(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Erase >> 8 ;
  towrite[1]= F_file_Erase ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_Error()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Error >> 8 ;
  towrite[1]= F_file_Error ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Exec(unsigned char *  Filename, WORD  ArgCount, t4DWordArray  Args)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Exec >> 8 ;
  towrite[1]= F_file_Exec ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  towrite[0]= ArgCount >> 8 ;
  towrite[1]= ArgCount ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteWords(Args, ArgCount) ;
  return GetAckResp() ;
}

WORD file_Exists(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Exists >> 8 ;
  towrite[1]= F_file_Exists ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_FindFirst(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_FindFirst >> 8 ;
  towrite[1]= F_file_FindFirst ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_FindNext()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_FindNext >> 8 ;
  towrite[1]= F_file_FindNext ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

unsigned char file_GetC(WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_GetC >> 8 ;
  towrite[1]= F_file_GetC ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_GetS(unsigned char *  StringIn, WORD  Size, WORD  Handle)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_file_GetS >> 8 ;
  towrite[1]= F_file_GetS ;
  towrite[2]= Size >> 8 ;
  towrite[3]= Size ;
  towrite[4]= Handle >> 8 ;
  towrite[5]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResStr(StringIn) ;
}

WORD file_GetW(WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_GetW >> 8 ;
  towrite[1]= F_file_GetW ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Image(WORD  X, WORD  Y, WORD  Handle)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_file_Image >> 8 ;
  towrite[1]= F_file_Image ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Handle >> 8 ;
  towrite[7]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Index(WORD  Handle, WORD  HiSize, WORD  LoSize, WORD  Recordnum)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
  towrite[0]= F_file_Index >> 8 ;
  towrite[1]= F_file_Index ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= HiSize >> 8 ;
  towrite[5]= HiSize ;
  towrite[6]= LoSize >> 8 ;
  towrite[7]= LoSize ;
  towrite[8]= Recordnum >> 8 ;
  towrite[9]= Recordnum ;
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_LoadFunction(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_LoadFunction >> 8 ;
  towrite[1]= F_file_LoadFunction ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_LoadImageControl(unsigned char *  Datname, unsigned char *  GCIName, WORD  Mode)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_LoadImageControl >> 8 ;
  towrite[1]= F_file_LoadImageControl ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Datname) ;
  WriteChars(GCIName) ;
  towrite[0]= Mode >> 8 ;
  towrite[1]= Mode ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Mount()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Mount >> 8 ;
  towrite[1]= F_file_Mount ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Open(unsigned char *  Filename, unsigned char  Mode)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Open >> 8 ;
  towrite[1]= F_file_Open ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  towrite[0]= Mode;
  WriteFile(ComHandle4D, &towrite[0], 1, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_PlayWAV(unsigned char *  Filename)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_PlayWAV >> 8 ;
  towrite[1]= F_file_PlayWAV ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResp() ;
}

WORD file_PutC(unsigned char  Character, WORD  Handle)
{
  unsigned char  towrite[5] ;
  DWORD  written ;
  towrite[0]= F_file_PutC >> 8 ;
  towrite[1]= F_file_PutC ;
  towrite[2]= Character;
  towrite[3]= Handle >> 8 ;
  towrite[4]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 5, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_PutS(unsigned char *  StringOut, WORD  Handle)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_PutS >> 8 ;
  towrite[1]= F_file_PutS ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(StringOut) ;
  towrite[0]= Handle >> 8 ;
  towrite[1]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_PutW(WORD  Word, WORD  Handle)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_file_PutW >> 8 ;
  towrite[1]= F_file_PutW ;
  towrite[2]= Word >> 8 ;
  towrite[3]= Word ;
  towrite[4]= Handle >> 8 ;
  towrite[5]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Read(t4DByteArray  Data, WORD  Size, WORD  Handle)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_file_Read >> 8 ;
  towrite[1]= F_file_Read ;
  towrite[2]= Size >> 8 ;
  towrite[3]= Size ;
  towrite[4]= Handle >> 8 ;
  towrite[5]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResData(Data,Size) ;
}

WORD file_Rewind(WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_Rewind >> 8 ;
  towrite[1]= F_file_Rewind ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Run(unsigned char *  Filename, WORD  ArgCount, t4DWordArray  Args)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Run >> 8 ;
  towrite[1]= F_file_Run ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  towrite[0]= ArgCount >> 8 ;
  towrite[1]= ArgCount ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteWords(Args, ArgCount) ;
  return GetAckResp() ;
}

WORD file_ScreenCapture(WORD  X, WORD  Y, WORD  Width, WORD  Height, WORD  Handle)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
  towrite[0]= F_file_ScreenCapture >> 8 ;
  towrite[1]= F_file_ScreenCapture ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Width >> 8 ;
  towrite[7]= Width ;
  towrite[8]= Height >> 8 ;
  towrite[9]= Height ;
  towrite[10]= Handle >> 8 ;
  towrite[11]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Seek(WORD  Handle, WORD  HiWord, WORD  LoWord)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_file_Seek >> 8 ;
  towrite[1]= F_file_Seek ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= HiWord >> 8 ;
  towrite[5]= HiWord ;
  towrite[6]= LoWord >> 8 ;
  towrite[7]= LoWord ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_Size(WORD  Handle, WORD *  HiWord, WORD *  LoWord)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_Size >> 8 ;
  towrite[1]= F_file_Size ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckRes2Words(HiWord,LoWord) ;
}

WORD file_Tell(WORD  Handle, WORD *  HiWord, WORD *  LoWord)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_Tell >> 8 ;
  towrite[1]= F_file_Tell ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckRes2Words(HiWord,LoWord) ;
}

void file_Unmount()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_Unmount >> 8 ;
  towrite[1]= F_file_Unmount ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

WORD file_Write(WORD  Size, t4DByteArray  Source, WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_file_Write >> 8 ;
  towrite[1]= F_file_Write ;
  towrite[2]= Size >> 8 ;
  towrite[3]= Size ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  WriteBytes(Source, Size) ;
  towrite[0]= Handle >> 8 ;
  towrite[1]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_BevelShadow(WORD  Value)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_BevelShadow >> 8 ;
  towrite[1]= F_gfx_BevelShadow ;
  towrite[2]= Value >> 8 ;
  towrite[3]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_BevelWidth(WORD  Value)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_BevelWidth >> 8 ;
  towrite[1]= F_gfx_BevelWidth ;
  towrite[2]= Value >> 8 ;
  towrite[3]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_BGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_BGcolour >> 8 ;
  towrite[1]= F_gfx_BGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Button(WORD  Up, WORD  x, WORD  y, WORD  buttonColour, WORD  txtColour, WORD  font, WORD  txtWidth, WORD  txtHeight, unsigned char *   text)
{
  unsigned char  towrite[18] ;
  DWORD  written ;
  towrite[0]= F_gfx_Button >> 8 ;
  towrite[1]= F_gfx_Button ;
  towrite[2]= Up >> 8 ;
  towrite[3]= Up ;
  towrite[4]= x >> 8 ;
  towrite[5]= x ;
  towrite[6]= y >> 8 ;
  towrite[7]= y ;
  towrite[8]= buttonColour >> 8 ;
  towrite[9]= buttonColour ;
  towrite[10]= txtColour >> 8 ;
  towrite[11]= txtColour ;
  towrite[12]= font >> 8 ;
  towrite[13]= font ;
  towrite[14]= txtWidth >> 8 ;
  towrite[15]= txtWidth ;
  towrite[16]= txtHeight >> 8 ;
  towrite[17]= txtHeight ;
  WriteFile(ComHandle4D, &towrite[0], 18, &written, NULL) ;
  WriteChars( text) ;
  GetAck() ;
}

void gfx_ChangeColour(WORD  OldColor, WORD  NewColor)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_ChangeColour >> 8 ;
  towrite[1]= F_gfx_ChangeColour ;
  towrite[2]= OldColor >> 8 ;
  towrite[3]= OldColor ;
  towrite[4]= NewColor >> 8 ;
  towrite[5]= NewColor ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void gfx_Circle(WORD  X, WORD  Y, WORD  Radius, WORD  Color)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  GetAck() ;
}

void gfx_CircleFilled(WORD  X, WORD  Y, WORD  Radius, WORD  Color)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  GetAck() ;
}

void gfx_Clipping(WORD  OnOff)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Clipping >> 8 ;
  towrite[1]= F_gfx_Clipping ;
  towrite[2]= OnOff >> 8 ;
  towrite[3]= OnOff ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  GetAck() ;
}

void gfx_ClipWindow(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  GetAck() ;
}

void gfx_Cls()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_gfx_Cls >> 8 ;
  towrite[1]= F_gfx_Cls ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

WORD gfx_Contrast(WORD  Contrast)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Contrast >> 8 ;
  towrite[1]= F_gfx_Contrast ;
  towrite[2]= Contrast >> 8 ;
  towrite[3]= Contrast ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Ellipse(WORD  X, WORD  Y, WORD  Xrad, WORD  Yrad, WORD  Color)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
  towrite[0]= F_gfx_Ellipse >> 8 ;
  towrite[1]= F_gfx_Ellipse ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Xrad >> 8 ;
  towrite[7]= Xrad ;
  towrite[8]= Yrad >> 8 ;
  towrite[9]= Yrad ;
  towrite[10]= Color >> 8 ;
  towrite[11]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  GetAck() ;
}

void gfx_EllipseFilled(WORD  X, WORD  Y, WORD  Xrad, WORD  Yrad, WORD  Color)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
  towrite[0]= F_gfx_EllipseFilled >> 8 ;
  towrite[1]= F_gfx_EllipseFilled ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Xrad >> 8 ;
  towrite[7]= Xrad ;
  towrite[8]= Yrad >> 8 ;
  towrite[9]= Yrad ;
  towrite[10]= Color >> 8 ;
  towrite[11]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  GetAck() ;
}

WORD gfx_FrameDelay(WORD  Msec)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_FrameDelay >> 8 ;
  towrite[1]= F_gfx_FrameDelay ;
  towrite[2]= Msec >> 8 ;
  towrite[3]= Msec ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_Get(WORD  Mode)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Get >> 8 ;
  towrite[1]= F_gfx_Get ;
  towrite[2]= Mode >> 8 ;
  towrite[3]= Mode ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_GetPixel(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_GetPixel >> 8 ;
  towrite[1]= F_gfx_GetPixel ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Line(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  GetAck() ;
}

WORD gfx_LinePattern(WORD  Pattern)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_LinePattern >> 8 ;
  towrite[1]= F_gfx_LinePattern ;
  towrite[2]= Pattern >> 8 ;
  towrite[3]= Pattern ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_LineTo(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_LineTo >> 8 ;
  towrite[1]= F_gfx_LineTo ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void gfx_MoveTo(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_MoveTo >> 8 ;
  towrite[1]= F_gfx_MoveTo ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

WORD gfx_Orbit(WORD  Angle, WORD  Distance, WORD *  Xdest, WORD *  Ydest)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_Orbit >> 8 ;
  towrite[1]= F_gfx_Orbit ;
  towrite[2]= Angle >> 8 ;
  towrite[3]= Angle ;
  towrite[4]= Distance >> 8 ;
  towrite[5]= Distance ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck2Words(Xdest,Ydest) ;
  return 0 ;
}

WORD gfx_OutlineColour(WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_OutlineColour >> 8 ;
  towrite[1]= F_gfx_OutlineColour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Panel(WORD  Raised, WORD  X, WORD  Y, WORD  Width, WORD  Height, WORD  Color)
{
  unsigned char  towrite[14] ;
  DWORD  written ;
  towrite[0]= F_gfx_Panel >> 8 ;
  towrite[1]= F_gfx_Panel ;
  towrite[2]= Raised >> 8 ;
  towrite[3]= Raised ;
  towrite[4]= X >> 8 ;
  towrite[5]= X ;
  towrite[6]= Y >> 8 ;
  towrite[7]= Y ;
  towrite[8]= Width >> 8 ;
  towrite[9]= Width ;
  towrite[10]= Height >> 8 ;
  towrite[11]= Height ;
  towrite[12]= Color >> 8 ;
  towrite[13]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 14, &written, NULL) ;
  GetAck() ;
}

void gfx_Polygon(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Polygon >> 8 ;
  towrite[1]= F_gfx_Polygon ;
  towrite[2]= n >> 8 ;
  towrite[3]= n ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  WriteWords(Xvalues, n) ;
  WriteWords(Yvalues, n) ;
  towrite[0]= Color >> 8 ;
  towrite[1]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

void gfx_PolygonFilled(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_PolygonFilled >> 8 ;
  towrite[1]= F_gfx_PolygonFilled ;
  towrite[2]= n >> 8 ;
  towrite[3]= n ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  WriteWords(Xvalues, n) ;
  WriteWords(Yvalues, n) ;
  towrite[0]= Color >> 8 ;
  towrite[1]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

void gfx_Polyline(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Polyline >> 8 ;
  towrite[1]= F_gfx_Polyline ;
  towrite[2]= n >> 8 ;
  towrite[3]= n ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  WriteWords(Xvalues, n) ;
  WriteWords(Yvalues, n) ;
  towrite[0]= Color >> 8 ;
  towrite[1]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

void gfx_PutPixel(WORD  X, WORD  Y, WORD  Color)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_gfx_PutPixel >> 8 ;
  towrite[1]= F_gfx_PutPixel ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Color >> 8 ;
  towrite[7]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  GetAck() ;
}

void gfx_Rectangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  GetAck() ;
}

void gfx_RectangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color)
{
  unsigned char  towrite[12] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 12, &written, NULL) ;
  GetAck() ;
}

void gfx_ScreenCopyPaste(WORD  Xs, WORD  Ys, WORD  Xd, WORD  Yd, WORD  Width, WORD  Height)
{
  unsigned char  towrite[14] ;
  DWORD  written ;
  towrite[0]= F_gfx_ScreenCopyPaste >> 8 ;
  towrite[1]= F_gfx_ScreenCopyPaste ;
  towrite[2]= Xs >> 8 ;
  towrite[3]= Xs ;
  towrite[4]= Ys >> 8 ;
  towrite[5]= Ys ;
  towrite[6]= Xd >> 8 ;
  towrite[7]= Xd ;
  towrite[8]= Yd >> 8 ;
  towrite[9]= Yd ;
  towrite[10]= Width >> 8 ;
  towrite[11]= Width ;
  towrite[12]= Height >> 8 ;
  towrite[13]= Height ;
  WriteFile(ComHandle4D, &towrite[0], 14, &written, NULL) ;
  GetAck() ;
}

WORD gfx_ScreenMode(WORD  ScreenMode)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_ScreenMode >> 8 ;
  towrite[1]= F_gfx_ScreenMode ;
  towrite[2]= ScreenMode >> 8 ;
  towrite[3]= ScreenMode ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Set(WORD  Func, WORD  Value)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_gfx_Set >> 8 ;
  towrite[1]= F_gfx_Set ;
  towrite[2]= Func >> 8 ;
  towrite[3]= Func ;
  towrite[4]= Value >> 8 ;
  towrite[5]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void gfx_SetClipRegion()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_gfx_SetClipRegion >> 8 ;
  towrite[1]= F_gfx_SetClipRegion ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

WORD gfx_Slider(WORD  Mode, WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color, WORD  Scale, WORD  Value)
{
  unsigned char  towrite[18] ;
  DWORD  written ;
  towrite[0]= F_gfx_Slider >> 8 ;
  towrite[1]= F_gfx_Slider ;
  towrite[2]= Mode >> 8 ;
  towrite[3]= Mode ;
  towrite[4]= X1 >> 8 ;
  towrite[5]= X1 ;
  towrite[6]= Y1 >> 8 ;
  towrite[7]= Y1 ;
  towrite[8]= X2 >> 8 ;
  towrite[9]= X2 ;
  towrite[10]= Y2 >> 8 ;
  towrite[11]= Y2 ;
  towrite[12]= Color >> 8 ;
  towrite[13]= Color ;
  towrite[14]= Scale >> 8 ;
  towrite[15]= Scale ;
  towrite[16]= Value >> 8 ;
  towrite[17]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 18, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_Transparency(WORD  OnOff)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_Transparency >> 8 ;
  towrite[1]= F_gfx_Transparency ;
  towrite[2]= OnOff >> 8 ;
  towrite[3]= OnOff ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD gfx_TransparentColour(WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_gfx_TransparentColour >> 8 ;
  towrite[1]= F_gfx_TransparentColour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void gfx_Triangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color)
{
  unsigned char  towrite[16] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 16, &written, NULL) ;
  GetAck() ;
}

void gfx_TriangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color)
{
  unsigned char  towrite[16] ;
  DWORD  written ;
  towrite[0]= F_gfx_TriangleFilled >> 8 ;
  towrite[1]= F_gfx_TriangleFilled ;
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
  WriteFile(ComHandle4D, &towrite[0], 16, &written, NULL) ;
  GetAck() ;
}

WORD img_ClearAttributes(WORD  Handle, WORD  Index, WORD  Value)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_img_ClearAttributes >> 8 ;
  towrite[1]= F_img_ClearAttributes ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  towrite[6]= Value >> 8 ;
  towrite[7]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Darken(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Darken >> 8 ;
  towrite[1]= F_img_Darken ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Disable(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Disable >> 8 ;
  towrite[1]= F_img_Disable ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Enable(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Enable >> 8 ;
  towrite[1]= F_img_Enable ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_GetWord(WORD  Handle, WORD  Index, WORD  Offset )
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_img_GetWord >> 8 ;
  towrite[1]= F_img_GetWord ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  towrite[6]= Offset  >> 8 ;
  towrite[7]= Offset  ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Lighten(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Lighten >> 8 ;
  towrite[1]= F_img_Lighten ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_SetAttributes(WORD  Handle, WORD  Index, WORD  Value)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_img_SetAttributes >> 8 ;
  towrite[1]= F_img_SetAttributes ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  towrite[6]= Value >> 8 ;
  towrite[7]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_SetPosition(WORD  Handle, WORD  Index, WORD  Xpos, WORD  Ypos)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
  towrite[0]= F_img_SetPosition >> 8 ;
  towrite[1]= F_img_SetPosition ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  towrite[6]= Xpos >> 8 ;
  towrite[7]= Xpos ;
  towrite[8]= Ypos >> 8 ;
  towrite[9]= Ypos ;
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_SetWord(WORD  Handle, WORD  Index, WORD  Offset , WORD  Word)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
  towrite[0]= F_img_SetWord >> 8 ;
  towrite[1]= F_img_SetWord ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  towrite[6]= Offset  >> 8 ;
  towrite[7]= Offset  ;
  towrite[8]= Word >> 8 ;
  towrite[9]= Word ;
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Show(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Show >> 8 ;
  towrite[1]= F_img_Show ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD img_Touched(WORD  Handle, WORD  Index)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_img_Touched >> 8 ;
  towrite[1]= F_img_Touched ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= Index >> 8 ;
  towrite[5]= Index ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  return GetAckResp() ;
}

WORD media_Flush()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_Flush >> 8 ;
  towrite[1]= F_media_Flush ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

void media_Image(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_media_Image >> 8 ;
  towrite[1]= F_media_Image ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

WORD media_Init()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_Init >> 8 ;
  towrite[1]= F_media_Init ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD media_RdSector(t4DSector  SectorIn)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_RdSector >> 8 ;
  towrite[1]= F_media_RdSector ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResSector(SectorIn) ;
}

WORD media_ReadByte()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_ReadByte >> 8 ;
  towrite[1]= F_media_ReadByte ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD media_ReadWord()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_ReadWord >> 8 ;
  towrite[1]= F_media_ReadWord ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

void media_SetAdd(WORD  HiWord, WORD  LoWord)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_media_SetAdd >> 8 ;
  towrite[1]= F_media_SetAdd ;
  towrite[2]= HiWord >> 8 ;
  towrite[3]= HiWord ;
  towrite[4]= LoWord >> 8 ;
  towrite[5]= LoWord ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void media_SetSector(WORD  HiWord, WORD  LoWord)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_media_SetSector >> 8 ;
  towrite[1]= F_media_SetSector ;
  towrite[2]= HiWord >> 8 ;
  towrite[3]= HiWord ;
  towrite[4]= LoWord >> 8 ;
  towrite[5]= LoWord ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void media_Video(WORD  X, WORD  Y)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_media_Video >> 8 ;
  towrite[1]= F_media_Video ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

void media_VideoFrame(WORD  X, WORD  Y, WORD  Framenumber)
{
  unsigned char  towrite[8] ;
  DWORD  written ;
  towrite[0]= F_media_VideoFrame >> 8 ;
  towrite[1]= F_media_VideoFrame ;
  towrite[2]= X >> 8 ;
  towrite[3]= X ;
  towrite[4]= Y >> 8 ;
  towrite[5]= Y ;
  towrite[6]= Framenumber >> 8 ;
  towrite[7]= Framenumber ;
  WriteFile(ComHandle4D, &towrite[0], 8, &written, NULL) ;
  GetAck() ;
}

WORD media_WriteByte(WORD  Byte)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_media_WriteByte >> 8 ;
  towrite[1]= F_media_WriteByte ;
  towrite[2]= Byte >> 8 ;
  towrite[3]= Byte ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD media_WriteWord(WORD  Word)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_media_WriteWord >> 8 ;
  towrite[1]= F_media_WriteWord ;
  towrite[2]= Word >> 8 ;
  towrite[3]= Word ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD media_WrSector(t4DSector  SectorOut)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_media_WrSector >> 8 ;
  towrite[1]= F_media_WrSector ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteBytes(SectorOut, 512) ;
  return GetAckResp() ;
}

WORD mem_Free(WORD  Handle)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_mem_Free >> 8 ;
  towrite[1]= F_mem_Free ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD mem_Heap()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_mem_Heap >> 8 ;
  towrite[1]= F_mem_Heap ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

void putCH(WORD  WordChar)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_putCH >> 8 ;
  towrite[1]= F_putCH ;
  towrite[2]= WordChar >> 8 ;
  towrite[3]= WordChar ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  GetAck() ;
}

WORD putstr(unsigned char *  InString)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_putstr >> 8 ;
  towrite[1]= F_putstr ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(InString) ;
  return GetAckResp() ;
}

void snd_BufSize(WORD  Bufsize)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_snd_BufSize >> 8 ;
  towrite[1]= F_snd_BufSize ;
  towrite[2]= Bufsize >> 8 ;
  towrite[3]= Bufsize ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  GetAck() ;
}

void snd_Continue()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_snd_Continue >> 8 ;
  towrite[1]= F_snd_Continue ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

void snd_Pause()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_snd_Pause >> 8 ;
  towrite[1]= F_snd_Pause ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

WORD snd_Pitch(WORD  Pitch)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_snd_Pitch >> 8 ;
  towrite[1]= F_snd_Pitch ;
  towrite[2]= Pitch >> 8 ;
  towrite[3]= Pitch ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD snd_Playing()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_snd_Playing >> 8 ;
  towrite[1]= F_snd_Playing ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

void snd_Stop()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_snd_Stop >> 8 ;
  towrite[1]= F_snd_Stop ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  GetAck() ;
}

void snd_Volume(WORD  Volume)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_snd_Volume >> 8 ;
  towrite[1]= F_snd_Volume ;
  towrite[2]= Volume >> 8 ;
  towrite[3]= Volume ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  GetAck() ;
}

WORD sys_Sleep(WORD  Units)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_sys_Sleep >> 8 ;
  towrite[1]= F_sys_Sleep ;
  towrite[2]= Units >> 8 ;
  towrite[3]= Units ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void touch_DetectRegion(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
  towrite[0]= F_touch_DetectRegion >> 8 ;
  towrite[1]= F_touch_DetectRegion ;
  towrite[2]= X1 >> 8 ;
  towrite[3]= X1 ;
  towrite[4]= Y1 >> 8 ;
  towrite[5]= Y1 ;
  towrite[6]= X2 >> 8 ;
  towrite[7]= X2 ;
  towrite[8]= Y2 >> 8 ;
  towrite[9]= Y2 ;
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  GetAck() ;
}

WORD touch_Get(WORD  Mode)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_touch_Get >> 8 ;
  towrite[1]= F_touch_Get ;
  towrite[2]= Mode >> 8 ;
  towrite[3]= Mode ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void touch_Set(WORD  Mode)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_touch_Set >> 8 ;
  towrite[1]= F_touch_Set ;
  towrite[2]= Mode >> 8 ;
  towrite[3]= Mode ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  GetAck() ;
}

WORD txt_Attributes(WORD  Attribs)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Attributes >> 8 ;
  towrite[1]= F_txt_Attributes ;
  towrite[2]= Attribs >> 8 ;
  towrite[3]= Attribs ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_BGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_BGcolour >> 8 ;
  towrite[1]= F_txt_BGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Bold(WORD  Bold)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Bold >> 8 ;
  towrite[1]= F_txt_Bold ;
  towrite[2]= Bold >> 8 ;
  towrite[3]= Bold ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_FGcolour(WORD  Color)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_FGcolour >> 8 ;
  towrite[1]= F_txt_FGcolour ;
  towrite[2]= Color >> 8 ;
  towrite[3]= Color ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_FontID(WORD  FontNumber)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_FontID >> 8 ;
  towrite[1]= F_txt_FontID ;
  towrite[2]= FontNumber >> 8 ;
  towrite[3]= FontNumber ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Height(WORD  Multiplier)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Height >> 8 ;
  towrite[1]= F_txt_Height ;
  towrite[2]= Multiplier >> 8 ;
  towrite[3]= Multiplier ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Inverse(WORD  Inverse)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Inverse >> 8 ;
  towrite[1]= F_txt_Inverse ;
  towrite[2]= Inverse >> 8 ;
  towrite[3]= Inverse ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Italic(WORD  Italic)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Italic >> 8 ;
  towrite[1]= F_txt_Italic ;
  towrite[2]= Italic >> 8 ;
  towrite[3]= Italic ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void txt_MoveCursor(WORD  Line, WORD  Column)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_txt_MoveCursor >> 8 ;
  towrite[1]= F_txt_MoveCursor ;
  towrite[2]= Line >> 8 ;
  towrite[3]= Line ;
  towrite[4]= Column >> 8 ;
  towrite[5]= Column ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

WORD txt_Opacity(WORD  TransparentOpaque)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Opacity >> 8 ;
  towrite[1]= F_txt_Opacity ;
  towrite[2]= TransparentOpaque >> 8 ;
  towrite[3]= TransparentOpaque ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

void txt_Set(WORD  Func, WORD  Value)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_txt_Set >> 8 ;
  towrite[1]= F_txt_Set ;
  towrite[2]= Func >> 8 ;
  towrite[3]= Func ;
  towrite[4]= Value >> 8 ;
  towrite[5]= Value ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  GetAck() ;
}

WORD txt_Underline(WORD  Underline)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Underline >> 8 ;
  towrite[1]= F_txt_Underline ;
  towrite[2]= Underline >> 8 ;
  towrite[3]= Underline ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Width(WORD  Multiplier)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Width >> 8 ;
  towrite[1]= F_txt_Width ;
  towrite[2]= Multiplier >> 8 ;
  towrite[3]= Multiplier ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Wrap(WORD  Position)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Wrap >> 8 ;
  towrite[1]= F_txt_Wrap ;
  towrite[2]= Position >> 8 ;
  towrite[3]= Position ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Xgap(WORD  Pixels)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Xgap >> 8 ;
  towrite[1]= F_txt_Xgap ;
  towrite[2]= Pixels >> 8 ;
  towrite[3]= Pixels ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD txt_Ygap(WORD  Pixels)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_txt_Ygap >> 8 ;
  towrite[1]= F_txt_Ygap ;
  towrite[2]= Pixels >> 8 ;
  towrite[3]= Pixels ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResp() ;
}

WORD file_CallFunction(WORD  Handle, WORD  ArgCount, t4DWordArray  Args)
{
  unsigned char  towrite[6] ;
  DWORD  written ;
  towrite[0]= F_file_CallFunction >> 8 ;
  towrite[1]= F_file_CallFunction ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  towrite[4]= ArgCount >> 8 ;
  towrite[5]= ArgCount ;
  WriteFile(ComHandle4D, &towrite[0], 6, &written, NULL) ;
  WriteWords(Args, ArgCount) ;
  return GetAckResp() ;
}

WORD sys_GetModel(unsigned char *  ModelStr)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_sys_GetModel >> 8 ;
  towrite[1]= F_sys_GetModel ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResStr(ModelStr) ;
}

WORD sys_GetVersion()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_sys_GetVersion >> 8 ;
  towrite[1]= F_sys_GetVersion ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD sys_GetPmmC()
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_sys_GetPmmC >> 8 ;
  towrite[1]= F_sys_GetPmmC ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResp() ;
}

WORD writeString(WORD  Handle, unsigned char *  StringOut)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_writeString >> 8 ;
  towrite[1]= F_writeString ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  WriteChars(StringOut) ;
  return GetAckResp() ;
}

WORD readString(WORD  Handle, unsigned char *  StringIn)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_readString >> 8 ;
  towrite[1]= F_readString ;
  towrite[2]= Handle >> 8 ;
  towrite[3]= Handle ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  return GetAckResStr(StringIn) ;
}

void blitComtoDisplay(WORD  X, WORD  Y, WORD  Width, WORD  Height, t4DByteArray  Pixels)
{
  unsigned char  towrite[10] ;
  DWORD  written ;
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
  WriteFile(ComHandle4D, &towrite[0], 10, &written, NULL) ;
  WriteBytes(Pixels, Width*Height*2) ;
  GetAck() ;
}

WORD file_FindFirstRet(unsigned char *  Filename, unsigned char *  StringIn)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_FindFirstRet >> 8 ;
  towrite[1]= F_file_FindFirstRet ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  WriteChars(Filename) ;
  return GetAckResStr(StringIn) ;
}

WORD file_FindNextRet(unsigned char *  StringIn)
{
  unsigned char  towrite[2] ;
  DWORD  written ;
  towrite[0]= F_file_FindNextRet >> 8 ;
  towrite[1]= F_file_FindNextRet ;
  WriteFile(ComHandle4D, &towrite[0], 2, &written, NULL) ;
  return GetAckResStr(StringIn) ;
}

void setbaudWait(WORD  Newrate)
{
  unsigned char  towrite[4] ;
  DWORD  written ;
  towrite[0]= F_setbaudWait >> 8 ;
  towrite[1]= F_setbaudWait ;
  towrite[2]= Newrate >> 8 ;
  towrite[3]= Newrate ;
  WriteFile(ComHandle4D, &towrite[0], 4, &written, NULL) ;
  SetThisBaudrate(Newrate) ; // change this systems baud rate to match new display rate, ACK is 100ms away
  GetAck() ;
}

