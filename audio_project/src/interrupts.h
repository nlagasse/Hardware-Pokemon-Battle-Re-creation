#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "xparameters.h"
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "main.h"
#include "sleep.h"

// Parameter definitions
#define INTC_DEVICE_ID 		XPAR_PS7_SCUGIC_0_DEVICE_ID
#define BTNS_DEVICE_ID		XPAR_AXI_GPIO_1_DEVICE_ID
#define INTC_GPIO_INTERRUPT_ID XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR

#define BTN_INT 			XGPIO_IR_CH1_MASK

extern XGpio BTNInst;
extern XScuGic INTCInst;
extern int btn_value;

//----------------------------------------------------
// PROTOTYPE FUNCTIONS
//----------------------------------------------------
void BTN_Intr_Handler(void *baseaddr_p);
int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr);

extern int playing;
extern int stop;

#endif
