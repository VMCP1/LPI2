#ifndef SERIE_H
#define SERIE_H

#define OLEN 64 // size of serial transmission buffer
#define ILEN 64 // size of serial receiving buffer

typedef struct{
  unsigned char sendfull:1; // flag: marks transmit buffer full
  unsigned char sendactive:1; // flag: marks transmitter active
  unsigned char rcvempty:1; // flag: marks receive buffer empty
}SerieFlag;

void SerieInitialize(unsigned int baude_rate);

char SerieGetByte(void);
void SeriePutByte(char c);
void SeriePutString(const char* string); // Print string

#ifdef SERIE_C
#undef SERIE_C
#else

extern volatile const SerieFlag serie_flags;

#endif

#endif
