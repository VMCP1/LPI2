
#ifndef TC_H
#define TC_H

#define _TC0 ((volatile Tc*)0x40080000)
#define _TC1 ((volatile Tc*)0x40084000)
#define _TC2 ((volatile Tc*)0x40088000)

#define NUM_PROCESSES 2

typedef struct{
  unsigned int CLKEN:1;  // Counter Clock Enable Command
  unsigned int CLKDIS:1; // Counter Clock Disable Command
  unsigned int SWTRG:1;  // Software Trigger Command
}TcCcr;

// TCCLKS: Clock Selection
#define TIMER_CLOCK1 0
#define TIMER_CLOCK2 1
#define TIMER_CLOCK3 2
#define TIMER_CLOCK4 3
#define TIMER_CLOCK5 4
#define XC0 5
#define XC1 6
#define XC2 7
// BURST: Burst Signal Selection
//#define NONE 0
//#define XC0 1
//#define XC1 2
//#define XC2 3
// ETRGEDG: External Trigger Edge Selection
// LDRA: RA Loading Selection
// LDRB: RB Loading Selection
#define NONE 0
#define RISING 1
#define FALLING 2
#define EDGE 3
typedef struct{
  unsigned int TCCLKS:3;    // Clock Selection
  unsigned int CLKI:1;      // Clock Invert
  unsigned int BURST:2;     // Burst Signal Selection
  unsigned int LDBSTOP:1;   // Counter Clock Stopped with RB Loading
  unsigned int LDBDIS:1;    // Counter Clock Disable with RB Loading
  unsigned int ETRGEDG:2;   // External Trigger Edge Selection
  unsigned int ABETRG:1;    // TIOA or TIOB External Trigger Selection
  unsigned int Reserved1:3;
  unsigned int CPCTRG:1;    // RC Compare Trigger Enable
  unsigned int WAVE:1;      // Wave
  unsigned int LDRA:1;      // RA Loading Selection
  unsigned int LDRB:1;      // RB Loading Selection
}TcCmr;

typedef struct{
  unsigned int COVFS:1;     // Counter Overflow Status
  unsigned int LOVRS:1;     // Load Overrun Status
  unsigned int CPAS:1;      // RA Compare Status
  unsigned int CPBS:1;      // RB Compare Status
  unsigned int CPCS:1;      // RC Compare Status
  unsigned int LDRAS:1;     // RA Loading Status
  unsigned int LDRBS:1;     // RB Loading Status
  unsigned int ETRGS:1;     // External Trigger Status
  unsigned int Reserved1:8;
  unsigned int CLKSTA:1;    // Clock Enabling Status
  unsigned int MTIOA:1;     // TIOA Mirror
  unsigned int MTIOB:1;     // TIOB Mirror
}TcSr;

typedef struct{
  unsigned int COVFS:1; // Counter Overflow
  unsigned int LOVRS:1; // Load Overrun
  unsigned int CPAS:1;  // RA Compare
  unsigned int CPBS:1;  // RB Compare
  unsigned int CPCS:1;  // RC Compare
  unsigned int LDRAS:1; // RA Loading
  unsigned int LDRBS:1; // RB Loading
  unsigned int ETRGS:1; // External Trigger
}TcInt;

/* STcChannel hardware registers */
typedef struct{
  TcCcr        TC_CCR;       /* (TcChannel Offset: 0x0) Channel Control Register */
  TcCmr        TC_CMR;       /* (TcChannel Offset: 0x4) Channel Mode Register */
  unsigned int TC_SMMR;      /* (TcChannel Offset: 0x8) Stepper Motor Mode Register */
  unsigned int Reserved1[1];
  unsigned int TC_CV;        /* (TcChannel Offset: 0x10) Counter Value */
  unsigned int TC_RA;        /* (TcChannel Offset: 0x14) Register A */
  unsigned int TC_RB;        /* (TcChannel Offset: 0x18) Register B */
  unsigned int TC_RC;        /* (TcChannel Offset: 0x1C) Register C */
  TcSr         TC_SR;        /* (TcChannel Offset: 0x20) Status Register */
  TcInt        TC_IER;       /* (TcChannel Offset: 0x24) Interrupt Enable Register */
  TcInt        TC_IDR;       /* (TcChannel Offset: 0x28) Interrupt Disable Register */
  TcInt        TC_IMR;       /* (TcChannel Offset: 0x2C) Interrupt Mask Register */
  unsigned int Reserved2[4];
}TcChannel;

/* Tc hardware registers */
typedef struct{
  TcChannel    TC_CHANNEL[3]; /* (Tc Offset: 0x0) channel = 0 .. 2 */
  unsigned int TC_BCR;        /* (Tc Offset: 0xC0) Block Control Register */
  unsigned int TC_BMR;        /* (Tc Offset: 0xC4) Block Mode Register */
  unsigned int TC_QIER;       /* (Tc Offset: 0xC8) QDEC Interrupt Enable Register */
  unsigned int TC_QIDR;       /* (Tc Offset: 0xCC) QDEC Interrupt Disable Register */
  unsigned int TC_QIMR;       /* (Tc Offset: 0xD0) QDEC Interrupt Mask Register */
  unsigned int TC_QISR;       /* (Tc Offset: 0xD4) QDEC Interrupt Status Register */
  unsigned int TC_FMR;        /* (Tc Offset: 0xD8) Fault Mode Register */
  unsigned int Reserved1[2];
  unsigned int TC_WPMR;       /* (Tc Offset: 0xE4) Write Protect Mode Register */
}Tc;

typedef struct {
  void (*Function)(void);
  unsigned int time;
} Process;

void SchedulerInitialize(Process *local_processes);
void SchedulerProcess(void);

#endif
