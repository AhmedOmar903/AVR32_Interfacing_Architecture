#ifndef _TIMER1_CONFIG_H_
#define _TIMER1_CONFIG_H_

/*
TIMERONE_PRESCALLER:	
					PRE_8
					PRE_64
					PRE_256
					PRE_1024
*/

#define TIMERONE_PRESCALLER       PRE_8


/*
	TIMERONE_MODE:
					
					OVER_FLOW
					INPUT_CAPTURE_UNIT
					FAST_PWM
										
												
	TIMERONE_TCCRA_CONFIG:	
						OVER_FLOW_A_CONFIG
						INPUT_CAPTURE_UNIT_A_CONFIG
						FAST_PWM_A_CONFIG
						
						
	TIMERONE_TCCRB_CONFIG:
						
						OVER_FLOW_B_CONFIG
						INPUT_CAPTURE_UNIT_B_CONFIG
						FAST_PWM_B_CONFIG
						

*/





#define TIMERONE_MODE       		INPUT_CAPTURE_UNIT
#define TIMERONE_TCCRA_CONFIG       INPUT_CAPTURE_UNIT_A_CONFIG
#define TIMERONE_TCCRB_CONFIG       INPUT_CAPTURE_UNIT_B_CONFIG



// ICU PIN D6


//*****************************						If The Mode Is FAST_PWM								*****************************//


/*
		CHANNEL:									HINT:
				CHANNEL_A			               		pinD5
				CHANNEL_B								pinD4
	                                                   
*/
#define CHANNEL   		CHANNEL_A
	
//	Please Write The Frequancy in Hertz		//
	
#define FREQUANCY			50
	
/*
			PWM_PRESCALLER:
							8
							64
							256
							1024
*/
	
#define PWM_PRESCALLER			256
	

#endif
