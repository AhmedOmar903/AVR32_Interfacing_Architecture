#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"TIMER1_interface.h"
#include"OSILLOSCOPE_private.h"


/*Config TImer1 on InputCapture Mode With  Prescaller 8*/






void OSCILLISCOPE_VoidInitialization(void)
{
	
	DIO_VidSetPinDirection(PORTD,6,INPUT);//InputCaptureUnit PIN
	TIMERONE_VoidSetCAllBackInputCaptureUnit(OSCILLISCOPE_VoidInputCaptureUnitInterruptServiceRoutine);
	TIMERONE_VoidSetCallBackOverFlow(OSCILLISCOPE_VoidOverFlowInterruptServiceRoutine);
	TIMERONE_VidInitializtaion();
	
}


void OSCILLISCOPE_VoidGetTheReadingsOfTheSignalSyncrounase(u32 *PointerToFrequancy,u32 *PointerToDutyCycle)
{
	
	//ValidationFlag=0;
	while(		ValidationFlag 		!=			3			);

	*PointerToFrequancy=(	(	256	 )/  (	0.000001	*	(  SNAP3-SNAP1  )		)			);
	
	*PointerToDutyCycle=(		(	(SNAP2-SNAP1)*(100)	)	/	(  SNAP3-SNAP1  )	);

	ValidationFlag=0;
}


static void OSCILLISCOPE_VoidInputCaptureUnitInterruptServiceRoutine(u16 TimerValue)
{
	if(		ValidationFlag		==		0				)
	{
		SNAP1=TimerValue;
		TIMERONEICU_VidSenceControl(FALLING);
		ValidationFlag=1;
		OVERFLOW=0;

	}
	else if(		ValidationFlag		==		1				)
	{
		SNAP2=TimerValue+(OVERFLOW*65536);
		TIMERONEICU_VidSenceControl(RISING);
		ValidationFlag=2;
		OVERFLOW=0;
	}
	else if(		ValidationFlag		==		2				)
	{
		SNAP3=TimerValue+(OVERFLOW*65536);
		OVERFLOW=0;
		ValidationFlag=3;
	}

}



static void OSCILLISCOPE_VoidOverFlowInterruptServiceRoutine(void)
{
	OVERFLOW++;
}
