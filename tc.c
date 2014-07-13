
#include "../ATSAM3X8E/include/startup_sam3xa.h"
#include "tc.h"
#include "pio.h"
#include "uart.h"

typedef struct{
	unsigned char execute;
	unsigned int time;
}ProcessExecute;

static Process *processes;
static ProcessExecute processes_execute[NUM_PROCESSES];

// Interrupt
void TC0_Handler(){
	unsigned int index;
	
	// this is the scheduler
	for(index = 0; index < NUM_PROCESSES; index++)
		if(--processes_execute[index].time == 0){
			processes_execute[index].execute = 1;
			processes_execute[index].time = processes[index].time;
		}
}

// TC Configuration
void SchedulerInitialize(Process *local_processes){
	unsigned int index;
	
	processes = local_processes;
	for(index = 0; index < NUM_PROCESSES; index++){
		processes_execute[index].execute = 0;
		processes_execute[index].time = processes[index].time;
	}
	
	_TC0->TC_CHANNEL[0].TC_CMR.CPCTRG = 1;
	_TC0->TC_CHANNEL[0].TC_IER.CPCS = 1;
	_TC0->TC_CHANNEL[0].TC_RC = 210; // 5us
	_TC0->TC_CHANNEL[0].TC_CCR.CLKEN = 1;
	_TC0->TC_CHANNEL[0].TC_CCR.SWTRG = 1;
}

void SchedulerProcess(void){
	unsigned int index = NUM_PROCESSES;

	// this is the scheduler
	while(index){
		index--;
		if(processes_execute[index].execute){
			processes_execute[index].execute = 0;
			processes[index].Function();
		}
	}
}
