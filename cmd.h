#ifndef CMD_H
#define CMD_H

#include "serie.h"

#define cmd_flags_sendfull serie_flags.sendfull
typedef struct{
  unsigned char rcvstr:1; // flag: marks receive complete string
  unsigned char rcvempty:1; // flag: marks receive buffer empty
}CmdFlag;

#define CmdInitialize(baude_rate) SerieInitialize(baude_rate)
void CmdProcess(void);

#define CmdPutChar(c) SeriePutByte(c)
void PutHex(unsigned char byte0);
void PutDec(unsigned char byte);
char GetChar(void);

#define CmdPutString(string) SeriePutString(string); // Print string
void GetString(void); // Get String

#ifdef CMD_C
#undef CMD_C
#else

extern const char instring[ILEN]; // storage for old buffer

extern const CmdFlag cmd_flags;

#endif

#endif
