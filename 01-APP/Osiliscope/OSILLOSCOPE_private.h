#ifndef _OSILLOSCOPE_PRIVATE_H_
#define _OSILLOSCOPE_PRIVATE_H_



volatile u16 SNAP1=0;
volatile u32 SNAP2=0;
volatile u32 SNAP3=0;
volatile u16 OVERFLOW=0;
volatile u8 ValidationFlag=0;


static void OSCILLISCOPE_VoidInputCaptureUnitInterruptServiceRoutine(u16 TimerValue);
static void OSCILLISCOPE_VoidOverFlowInterruptServiceRoutine(void);


#endif
