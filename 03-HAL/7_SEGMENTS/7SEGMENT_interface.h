
	#ifndef _7SEGMENT_INTERFACE_H_
	#define _7SEGMENT_INTERFACE_H_
	
	
		//comman anode intialization//
	#define off                  0b1111111
	#define zero                 0b1000000
	#define one                  0b1111001
	#define two                  0b0100100
	#define three                0b0110000
	#define four                 0b0011001
	#define five                 0b0010010
	#define six                  0b0000010
	#define seven                0b1111000
	#define eight                0b0000000
	#define nine                 0b0010000
	//TYPES OF 7SEGMENTS//
	#define ANODE                   1
	#define CATHODE                 0
	#define SEG_TYPE              CATHODE
	
	
	
	
	
	//       loc_u8data= numbers from 0 to 9        ,           //
	void SEGMENT_VidCommanAnodeCathode(u8 loc_u8port_name,u8 loc_u8data);
	#endif
