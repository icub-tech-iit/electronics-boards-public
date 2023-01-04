#include "Picaso_Types4D.h"			// defines data types used by the 4D Routines

#define   Err4D_OK      0
#define   Err4D_Timeout 1
#define   Err4D_NAK		2 // other than ACK received

unsigned char *Error4DText[] = {"OK\0", "Timeout\0", "NAK\0", "Length\0", "Invalid\0"} ;

// 4D Global variables
extern HANDLE ComHandle4D ;  		// comp port handle, used by Intrinsic routines
extern int Error4D ;  				// Error indicator,  used and set by Intrinsic routines
extern unsigned char Error4D_Inv ;	// Error byte returned from com port, onl set if error = Err_Invalid
extern int TimeLimit4D ;			// time limit in ms for total serial command duration, 2000 (2 seconds) should be adequate for most commands
		                            // assuming a reasonable baud rate AND low latency AND 0 for the Serial Delay Parameter
		                            // temporary increase might be required for very long (bitmap write, large image file opens)
		                            // or indeterminate (eg file_exec, file_run, file_callFunction)  commands
extern int(*Callback4D) (int, unsigned char) ;	// Error callback. Set to NULL if no callback is required. i.e. all errors will be handled in your code
												// Set to callback routine in your program to enable you to diagnose and display errors. You can
												// simply return from the error routine if you so desire, but really, the correct thing to do is produce
												// an error message of some kind and terminate your application.

extern unsigned char file_GetC(WORD  Handle) ;
extern int OpenComm(char *comport, int newrate) ;
extern void blitComtoDisplay(WORD  X, WORD  Y, WORD  Width, WORD  Height, t4DByteArray  Pixels);
extern void file_Unmount(void);
extern void gfx_Button(WORD  Up, WORD  x, WORD  y, WORD  buttonColour, WORD  txtColour, WORD  font, WORD  txtWidth, WORD  txtHeight, unsigned char *   text);
extern void gfx_ChangeColour(WORD  OldColor, WORD  NewColor);
extern void gfx_Circle(WORD  X, WORD  Y, WORD  Radius, WORD  Color);
extern void gfx_CircleFilled(WORD  X, WORD  Y, WORD  Radius, WORD  Color);
extern void gfx_Clipping(WORD  OnOff);
extern void gfx_ClipWindow(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2);
extern void gfx_Cls(void);
extern void gfx_Ellipse(WORD  X, WORD  Y, WORD  Xrad, WORD  Yrad, WORD  Color);
extern void gfx_EllipseFilled(WORD  X, WORD  Y, WORD  Xrad, WORD  Yrad, WORD  Color);
extern void gfx_Line(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color);
extern void gfx_LineTo(WORD  X, WORD  Y);
extern void gfx_MoveTo(WORD  X, WORD  Y);
extern void gfx_Panel(WORD  Raised, WORD  X, WORD  Y, WORD  Width, WORD  Height, WORD  Color);
extern void gfx_Polygon(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color);
extern void gfx_PolygonFilled(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color);
extern void gfx_Polyline(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color);
extern void gfx_PutPixel(WORD  X, WORD  Y, WORD  Color);
extern void gfx_Rectangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color);
extern void gfx_RectangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color);
extern void gfx_ScreenCopyPaste(WORD  Xs, WORD  Ys, WORD  Xd, WORD  Yd, WORD  Width, WORD  Height);
extern void gfx_Set(WORD  Func, WORD  Value);
extern void gfx_SetClipRegion(void);
extern void gfx_Triangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color);
extern void gfx_TriangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color);
extern void media_Image(WORD  X, WORD  Y);
extern void media_SetAdd(WORD  HiWord, WORD  LoWord);
extern void media_SetSector(WORD  HiWord, WORD  LoWord);
extern void media_Video(WORD  X, WORD  Y);
extern void media_VideoFrame(WORD  X, WORD  Y, WORD  Framenumber);
extern void setbaudWait(WORD  Newrate);
extern void snd_BufSize(WORD  Bufsize);
extern void snd_Continue(void);
extern void snd_Pause(void);
extern void snd_Stop(void);
extern void snd_Volume(WORD  Volume);
extern void touch_DetectRegion(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2);
extern void touch_Set(WORD  Mode);
extern void txt_MoveCursor(WORD  Line, WORD  Column);
extern void txt_Set(WORD  Func, WORD  Value);
extern WORD charheight(unsigned char  TestChar);
extern WORD charwidth(unsigned char  TestChar);
extern WORD file_CallFunction(WORD  Handle, WORD  ArgCount, t4DWordArray  Args);
extern WORD file_Close(WORD  Handle);
extern WORD file_Count(unsigned char *  Filename);
extern WORD file_Dir(unsigned char *  Filename);
extern WORD file_Erase(unsigned char *  Filename);
extern WORD file_Error(void);
extern WORD file_Exec(unsigned char *  Filename, WORD  ArgCount, t4DWordArray  Args);
extern WORD file_Exists(unsigned char *  Filename);
extern WORD file_FindFirst(unsigned char *  Filename);
extern WORD file_FindFirstRet(unsigned char *  Filename, unsigned char *  StringIn);
extern WORD file_FindNext(void);
extern WORD file_FindNextRet(unsigned char *  StringIn);
extern WORD file_GetS(unsigned char *  StringIn, WORD  Size, WORD  Handle);
extern WORD file_GetW(WORD  Handle);
extern WORD file_Image(WORD  X, WORD  Y, WORD  Handle);
extern WORD file_Index(WORD  Handle, WORD  HiSize, WORD  LoSize, WORD  Recordnum);
extern WORD file_LoadFunction(unsigned char *  Filename);
extern WORD file_LoadImageControl(unsigned char *  Datname, unsigned char *  GCIName, WORD  Mode);
extern WORD file_Mount(void);
extern WORD file_Open(unsigned char *  Filename, unsigned char  Mode);
extern WORD file_PlayWAV(unsigned char *  Filename);
extern WORD file_PutC(unsigned char  Character, WORD  Handle);
extern WORD file_PutS(unsigned char *  StringOut, WORD  Handle);
extern WORD file_PutW(WORD  Word, WORD  Handle);
extern WORD file_Read(t4DByteArray  Data, WORD  Size, WORD  Handle);
extern WORD file_Rewind(WORD  Handle);
extern WORD file_Run(unsigned char *  Filename, WORD  ArgCount, t4DWordArray  Args);
extern WORD file_ScreenCapture(WORD  X, WORD  Y, WORD  Width, WORD  Height, WORD  Handle);
extern WORD file_Seek(WORD  Handle, WORD  HiWord, WORD  LoWord);
extern WORD file_Size(WORD  Handle, WORD *  HiWord, WORD *  LoWord);
extern WORD file_Tell(WORD  Handle, WORD *  HiWord, WORD *  LoWord);
extern WORD file_Write(WORD  Size, t4DByteArray  Source, WORD  Handle);
extern WORD gfx_BevelShadow(WORD  Value);
extern WORD gfx_BevelWidth(WORD  Value);
extern WORD gfx_BGcolour(WORD  Color);
extern WORD gfx_Contrast(WORD  Contrast);
extern WORD gfx_FrameDelay(WORD  Msec);
extern WORD gfx_Get(WORD  Mode);
extern WORD gfx_GetPixel(WORD  X, WORD  Y);
extern WORD gfx_LinePattern(WORD  Pattern);
extern WORD gfx_Orbit(WORD  Angle, WORD  Distance, WORD *  Xdest, WORD *  Ydest);
extern WORD gfx_OutlineColour(WORD  Color);
extern WORD gfx_ScreenMode(WORD  ScreenMode);
extern WORD gfx_Slider(WORD  Mode, WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color, WORD  Scale, WORD  Value);
extern WORD gfx_Transparency(WORD  OnOff);
extern WORD gfx_TransparentColour(WORD  Color);
extern WORD img_ClearAttributes(WORD  Handle, WORD  Index, WORD  Value);
extern WORD img_Darken(WORD  Handle, WORD  Index);
extern WORD img_Disable(WORD  Handle, WORD  Index);
extern WORD img_Enable(WORD  Handle, WORD  Index);
extern WORD img_GetWord(WORD  Handle, WORD  Index, WORD  Offset );
extern WORD img_Lighten(WORD  Handle, WORD  Index);
extern WORD img_SetAttributes(WORD  Handle, WORD  Index, WORD  Value);
extern WORD img_SetPosition(WORD  Handle, WORD  Index, WORD  Xpos, WORD  Ypos);
extern WORD img_SetWord(WORD  Handle, WORD  Index, WORD  Offset , WORD  Word);
extern WORD img_Show(WORD  Handle, WORD  Index);
extern WORD img_Touched(WORD  Handle, WORD  Index);
extern WORD media_Flush(void);
extern WORD media_Init(void);
extern WORD media_RdSector(t4DSector  SectorIn);
extern WORD media_ReadByte(void);
extern WORD media_ReadWord(void);
extern WORD media_WriteByte(WORD  Byte);
extern WORD media_WriteWord(WORD  Word);
extern WORD media_WrSector(t4DSector  SectorOut);
extern WORD mem_Free(WORD  Handle);
extern WORD mem_Heap(void);
extern WORD putstr(unsigned char *  InString);
extern WORD readString(WORD  Handle, unsigned char *  StringIn);
extern WORD snd_Pitch(WORD  Pitch);
extern WORD snd_Playing(void);
extern WORD sys_GetModel(unsigned char *  ModelStr);
extern WORD sys_GetPmmC(void);
extern WORD sys_GetVersion(void);
extern WORD sys_Sleep(WORD  Units);
extern WORD touch_Get(WORD  Mode);
extern WORD txt_Attributes(WORD  Attribs);
extern WORD txt_BGcolour(WORD  Color);
extern WORD txt_Bold(WORD  Bold);
extern WORD txt_FGcolour(WORD  Color);
extern WORD txt_FontID(WORD  FontNumber);
extern WORD txt_Height(WORD  Multiplier);
extern WORD txt_Inverse(WORD  Inverse);
extern WORD txt_Italic(WORD  Italic);
extern WORD txt_Opacity(WORD  TransparentOpaque);
extern WORD txt_Underline(WORD  Underline);
extern WORD txt_Width(WORD  Multiplier);
extern WORD txt_Wrap(WORD  Position);
extern WORD txt_Xgap(WORD  Pixels);
extern WORD txt_Ygap(WORD  Pixels);
extern WORD writeString(WORD  Handle, unsigned char *  StringOut);
