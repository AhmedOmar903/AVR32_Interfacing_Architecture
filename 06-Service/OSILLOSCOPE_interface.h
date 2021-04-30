#ifndef _OSILLOSCOPE_INTERFACE_H_
#define _OSILLOSCOPE_INTERFACE_H_

/*Config TImer1 on InputCapture Mode With  Prescaller 8*/

void OSCILLISCOPE_VoidInitialization(void);
void OSCILLISCOPE_VoidGetTheReadingsOfTheSignalSyncrounase(u32 *PointerToFrequancy,u32 *PointerToDutyCycle);

#endif
