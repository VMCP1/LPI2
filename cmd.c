#define CMD_C

#include "cmd.h"

static unsigned char istart; // receiving buffer start index
static unsigned char iend; // receiving buffer end index
static char inbuf[ILEN];

char instring[ILEN]; // storage for old buffer

CmdFlag cmd_flags;

void CmdProcess(void){
  char c;

  if(serie_flags.rcvempty)
    return;
  c = SerieGetByte();

  if(c > 0x1f && c < 0x7f && istart + ILEN != iend){
    inbuf[iend++ & (ILEN-1)] = c; // put character into buffer
    SeriePutByte((unsigned char)c); // eco
    cmd_flags.rcvempty = 0;
  }
  else if(c == '\r' && istart + ILEN != iend){
    inbuf[iend++ & (ILEN-1)] = '\0'; // put character into buffer
    SeriePutByte('\r');
    SeriePutByte('\n');
    cmd_flags.rcvempty = 0;
    cmd_flags.rcvstr = 1;
  }
  else if(c == 0x08){
    SeriePutByte(0x08);
    SeriePutByte(' ');
    SeriePutByte(0x08);
  }
}

void CmdPutHex(unsigned char byte0){
  unsigned char byte1;
  
  byte1 = byte0;
  byte1 >>= 4;
  if(byte1 < 10)
    SeriePutByte('0' + byte1);
  else
    SeriePutByte(0x37 + byte1);

  byte0 &= 0x0f;
  if(byte0 < 10)
    SeriePutByte('0' + byte0);
  else
    SeriePutByte(0x37 + byte0);
}

void CmdPutDec(unsigned char byte){
  unsigned char dig0, dig1, dig2;
  
  dig0 = '0' + (byte%10);
  byte /= 10;
  dig1 = '0' + (byte%10);
  byte /= 10;
  dig2 = '0' + (byte%10);
  
  SeriePutByte(dig2);
  SeriePutByte(dig1);
  SeriePutByte(dig0);
}

/*--------------------------------------------------------------------------------
* Replacement routine for the standard library _getkey routine.
* The getchar and gets functions uses _getkey to read a character.
*------------------------------------------------------------------------------*/
char CmdGetChar(void){
  char c;
  
  while(cmd_flags.rcvempty)
    CmdProcess();
  c = inbuf[istart++ & (ILEN-1)];
  cmd_flags.rcvempty = (istart == iend);
  
  return c;
}

void CmdGetString(void){
  char c;
  unsigned char i = 0;

  while(!cmd_flags.rcvstr);
  cmd_flags.rcvstr = 0;
  do{
    c = GetChar();
    instring[i] = c;
    i++;
  }
  while(c != '\0');
}
