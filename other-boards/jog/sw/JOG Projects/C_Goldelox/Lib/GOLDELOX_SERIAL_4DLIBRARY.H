#include "Goldelox_Types4D.h"			// defines data types used by the 4D Routines

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

extern int OpenComm(char *comport, int newrate) ;
extern void blitComtoDisplay(WORD  X, WORD  Y, WORD  Width, WORD  Height, t4DByteArray  Pixels) ;
extern void gfx_BGcolour(WORD  Color) ;
extern void gfx_ChangeColour(WORD  OldColor, WORD  NewColor) ;
extern void gfx_Circle(WORD  X, WORD  Y, WORD  Radius, WORD  Color) ;
extern void gfx_CircleFilled(WORD  X, WORD  Y, WORD  Radius, WORD  Color) ;
extern void gfx_Clipping(WORD  OnOff) ;
extern void gfx_ClipWindow(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2) ;
extern void gfx_Cls() ;
extern void gfx_Contrast(WORD  Contrast) ;
extern void gfx_FrameDelay(WORD  Msec) ;
extern void gfx_Line(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color) ;
extern void gfx_LinePattern(WORD  Pattern) ;
extern void gfx_LineTo(WORD  X, WORD  Y) ;
extern void gfx_MoveTo(WORD  X, WORD  Y) ;
extern void gfx_OutlineColour(WORD  Color) ;
extern void gfx_Polygon(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color) ;
extern void gfx_Polyline(WORD  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, WORD  Color) ;
extern void gfx_PutPixel(WORD  X, WORD  Y, WORD  Color) ;
extern void gfx_Rectangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color) ;
extern void gfx_RectangleFilled(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  Color) ;
extern void gfx_ScreenMode(WORD  ScreenMode) ;
extern void gfx_Set(WORD  Func, WORD  Value) ;
extern void gfx_Transparency(WORD  OnOff) ;
extern void gfx_TransparentColour(WORD  Color) ;
extern void gfx_Triangle(WORD  X1, WORD  Y1, WORD  X2, WORD  Y2, WORD  X3, WORD  Y3, WORD  Color) ;
extern void media_Image(WORD  X, WORD  Y) ;
extern void media_SetAdd(WORD  HiWord, WORD  LoWord) ;
extern void media_SetSector(WORD  HiWord, WORD  LoWord) ;
extern void media_Video(WORD  X, WORD  Y) ;
extern void media_VideoFrame(WORD  X, WORD  Y, WORD  Framenumber) ;
extern void pokeB(WORD  Address, WORD  ByteValue) ;
extern void pokeW(WORD  Address, WORD  WordValue) ;
extern void putCH(WORD  WordChar) ;
extern void setbaudWait(WORD  Newrate) ;
extern void SSMode(WORD  Parm) ;
extern void SSSpeed(WORD  Speed) ;
extern void SSTimeout(WORD  Seconds) ;
extern void txt_Attributes(WORD  Attribs) ;
extern void txt_BGcolour(WORD  Color) ;
extern void txt_Bold(WORD  Bold) ;
extern void txt_FGcolour(WORD  Color) ;
extern void txt_FontID(WORD  FontNumber) ;
extern void txt_Height(WORD  Multiplier) ;
extern void txt_Inverse(WORD  Inverse) ;
extern void txt_Italic(WORD  Italic) ;
extern void txt_MoveCursor(WORD  Line, WORD  Column) ;
extern void txt_Opacity(WORD  TransparentOpaque) ;
extern void txt_Set(WORD  Func, WORD  Value) ;
extern void txt_Underline(WORD  Underline) ;
extern void txt_Width(WORD  Multiplier) ;
extern void txt_Xgap(WORD  Pixels) ;
extern void txt_Ygap(WORD  Pixels) ;
extern void BeeP(WORD  Note, WORD  Duration) ;
extern WORD charheight(unsigned char  TestChar) ;
extern WORD charwidth(unsigned char  TestChar) ;
extern WORD gfx_GetPixel(WORD  X, WORD  Y) ;
extern WORD gfx_Orbit(WORD  Angle, WORD  Distance, WORD *  Xdest, WORD *  Ydest) ;
extern void gfx_SetClipRegion() ;
extern WORD joystick() ;
extern WORD media_Flush() ;
extern WORD media_Init() ;
extern WORD media_ReadByte() ;
extern WORD media_ReadWord() ;
extern WORD media_WriteByte(WORD  Byte) ;
extern WORD media_WriteWord(WORD  Word) ;
extern WORD peekB(WORD  Address) ;
extern WORD peekW(WORD  Address) ;
extern void putstr(unsigned char *  InString) ;
extern WORD sys_GetModel(unsigned char *  ModelStr) ;
extern WORD sys_GetPmmC() ;
extern WORD sys_GetVersion() ;
